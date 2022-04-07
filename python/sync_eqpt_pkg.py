import tkinter
import os
import threading
import re
from ftplib import FTP

class FtpHelper(object):
    ftp = FTP()
    def __init__(self, srv, port=21):
        self.ftp.connect(srv, port)
    
    def login(self, username, passwd):
        self.ftp.login(username, passwd)

    def uploadFile(self, srcPath, destPath):
        self.createFtpPath(destPath)
        fileHandler = open(srcPath, "rb")
        self.ftp.storbinary("STOR %s" % os.path.basename(srcPath), fileHandler, 4096)
        self.ftp.cwd("/")
        fileHandler.close()

    def createFtpPath(self, ftpPath):
        for path in ftpPath.split("/"):
            try:
                self.ftp.cwd(path)
            except Exception as e:
                self.ftp.mkd(path)
                self.ftp.cwd(path)

    def close(self):
        self.ftp.close()

def UploadEqptFile(dirPath, subDirName):
    dirPath = dirPath.rstrip("/")
    srcPath = os.path.join(dirPath, subDirName)
    files = os.listdir(srcPath)
    debugSrv = "10.117.177.18"
    formalSrv = "10.43.100.242"
    ftpHelper = FtpHelper(formalSrv)
    ftpHelper.login("51ftpvipuser", "ftpvipuser@51")
    for file in files:
        filePath = os.path.join(srcPath, file)
        if os.path.isfile(filePath):
            dstPath = r"Board-Software/" + subDirName + "/" + file[file.find("V100"):file.find(".rar")]
            print("dstPath:%s" % dstPath)
            ftpHelper.uploadFile(filePath, dstPath)
            print("srcPath:%s" % filePath)
    ftpHelper.close()

def GetDirFileList(dirpath):
    files = os.listdir(dirpath)
    for file in files:
        fi_d = os.path.join(dirpath, file)
        if os.path.isdir(fi_d):
            yield file

class GuiView:
    def __init__(self):
        self.m_copyEvent = threading.Event()
        self.m_rootWnd = tkinter.Tk()
        self.m_rootWnd.title("SyncEqptPkg Ver0.1")
        self.m_srcPathLabel = tkinter.Label(self.m_rootWnd)
        self.m_srcPathLabel.pack()
        self.m_srcPathEntry = tkinter.Entry(self.m_rootWnd, width=80)
        self.m_srcPathEntry.pack()
        self.m_srcPathEntry.focus()
        self.m_copyBtn = tkinter.Button(
            self.m_rootWnd, text="Copy", command=self.onCopyBtnClick)
        self.m_copyBtn.pack()
        self.m_msgLabel = tkinter.Label(self.m_rootWnd)
        self.m_msgLabel.pack()
        self.m_rootWnd.protocol("WM_DELETE_WINDOW", self.close)
        pass

    def close(self):
        self.m_copyEvent.set()
        self.m_rootWnd.destroy()

    def onCopyBtnClick(self):
        if self.m_msgLabel["text"] == r"拷贝中...":
            return
        self.m_msgLabel.config(text=r"拷贝中...")
        threading.Thread(target=self.copy).start()

    def draw(self):
        self.m_srcPathLabel.config(text=r"请输入装备包路径")

    def copy(self):
        dirpath = self.m_srcPathEntry.get()
        try:
            for file in GetDirFileList(dirpath):
                UploadEqptFile(dirpath, file)
            self.m_msgLabel.config(text=r"拷贝成功！")
        except Exception as err:
            self.m_msgLabel.config(text=r"拷贝失败:%s！" % err)

if __name__ == "__main__":
    view = GuiView()
    view.draw()
    view.m_rootWnd.mainloop()