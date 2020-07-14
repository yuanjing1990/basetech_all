#include "MyDownloader.h"
#include <QtCore/QFileInfo>
#include <QtCore/QtDebug>
#include <iostream>
MyDownloader::MyDownloader() {
    downloadFile = NULL;
    downloadReply = NULL;
    bisFinished = false;
}

MyDownloader::~MyDownloader() { cancel(); }

void MyDownloader::setData(QUrl url, QString pathtoSave) {
    downloadUrl = url;
    savePath = pathtoSave;
}

void MyDownloader::getFile() {
    if (savePath.isEmpty() || downloadUrl.isEmpty()) {
        return;
    }
    if (downloadFile) {
        return;
    }
    bisFinished = false;
    downloadFile = new QFile(savePath);

    if (!downloadFile->open(QIODevice::WriteOnly)) {
        delete downloadFile;
        downloadFile = 0;
        return;
    }
    allBits = downloadFile->size();
    httpRequestAborted = false;

    startRequest(downloadUrl);
}

void MyDownloader::startRequest(QUrl url) {
    QNetworkRequest req(url);
    if (allBits) {
    }
    downloadReply = downloadmanager.get(req);

    if (downloadReply) {
        connect(downloadReply, SIGNAL(readyRead()), this,
                SLOT(downloadReadyRead()));
        connect(downloadReply, SIGNAL(finished()), this,
                SLOT(downloadFinished()));
        std::cout << "startRequest:" << url.toString().toStdString() << "!" << std::endl;
    }
}

QString MyDownloader::getDownloadVersionCode() { return versionCode; }

QString MyDownloader::getFileName() { return fileName; }

void MyDownloader::downloadReadyRead() {
    if (downloadFile)
        downloadFile->write(downloadReply->readAll());
}

void MyDownloader::cancel() {
    if (downloadFile) {
        downloadFile->close();
        delete downloadFile;
        downloadFile = NULL;
    }
    if (downloadReply) {
        downloadReply->deleteLater();
        downloadReply = NULL;
    }
}

void MyDownloader::downloadFinished() {
    downloadFile->flush();
    downloadFile->close();
    std::cout << "downloadFinished!" << std::endl;

    if (downloadReply->error()) {
        std::cout << "download error!" << std::endl;
        emit downloadResult(downloadReply->error());
    } else {
        QString fileName = QFileInfo(downloadUrl.path()).fileName();
        delete downloadFile;
        downloadFile = 0;
        bisFinished = true;
        emit downloadResult(0);
    }
    downloadReply->deleteLater();
    downloadReply = 0;
    if (downloadFile) {
        delete downloadFile;
        downloadFile = 0;
    }
}

void MyDownloader::downloadError(QNetworkReply::NetworkError errorcode) {
    emit downloadResult(-1);
}

bool MyDownloader::errorValid() { return false; }

int MyDownloader::lastError() { return 0; }

bool MyDownloader::isRunning() { return false; }

bool MyDownloader::isFinished() { return bisFinished; }