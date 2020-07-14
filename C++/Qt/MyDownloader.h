#ifndef MYDOWNLOADER_H
#define MYDOWNLOADER_H

#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
class MyDownloader : public QObject {
    Q_OBJECT

  public:
    MyDownloader();
    ~MyDownloader();

    void setData(QUrl url, QString pathtoSave);

    void getFile();
    void startRequest(QUrl url);

    int lastError();

    bool errorValid();

    bool isRunning();

    bool isFinished();

    QString getDownloadVersionCode();

    QString getFileName();
    void cancel();

  private:
    bool bisFinished;
    bool bisRunning;
    bool bisError;
    int errorCode;
    int allBits = 0;
    bool httpRequestAborted;

    QFile *downloadFile;
    QUrl downloadUrl;
    QString savePath;
    QString versionCode = "";
    QString fileName = "";
    QNetworkReply *downloadReply;
    QNetworkAccessManager downloadmanager;

  signals:

    void error(QNetworkReply::NetworkError);

    void updateProgress(qint64, qint64);

    void downloadResult(int retCode);

  private slots:

    void downloadReadyRead();

    void downloadFinished();

    void downloadError(QNetworkReply::NetworkError);
};

#endif // MYDOWNLOADER_H