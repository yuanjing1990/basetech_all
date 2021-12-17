#!/usr/bin/python
# -*-coding:utf-8
import tkinter
import random
import threading
import zmq
from tkinter import *

character_tbl = {}

svr_socket_str = "tcp://*:5555"
clt_socket_str = "tcp://localhost:5555"

# MVC模型示例
# 此程序是一个选择题生成工具，带命令行和GUI两种视图


class Question:
    # 此类是具体问题的数据表示：（目标选项，所有选项）
    def __init__(self, data=()):
        self.m_data = data
        pass

    def __str__(self):
        return self.m_data.str()
        pass

    def __getitem__(self, i):
        return self.m_data[i]

    def __len__(self):
        return len(self.m_data)


class QuestionFactory:
    # 此类是Question的工厂类，根据题库自动生成问题
    @staticmethod
    def createQuestion():
        sel_index = []
        while len(sel_index) < 4:
            sel = random.randint(1, 10)
            if sel not in sel_index:
                sel_index.append(sel)
        ret = (random.choice(sel_index), sel_index)
        return Question(ret)
        pass


class ConsoleView:
    # 控制台视图，问题显示和作答都在控制台中进行
    def __init__(self):
        self.m_question = Question()
        self.m_ctrl = None
        pass

    def close(self):
        pass

    def setctrl(self, ctrl):
        self.m_ctrl = ctrl
        pass

    def setQuestion(self, question):
        self.m_question = question

    # 显示Question的具体方法
    def draw(self):
        print("How to write the character %d?" % self.m_question[0])
        choice_str = ""
        for i in range(1, len(self.m_question[1]) + 1):
            choice_str += "%d.%d\t" % (i, self.m_question[1][i-1])
        print(choice_str)
        pass

    # 获取answer并判断答案
    def getAnswer(self):
        while True:
            if len(self.m_question) < 2:
                continue
            answer = input(
                "Please input your answer[1-%d] or q|quit:" % len(self.m_question[1]))
            ret = 0
            try:
                if answer in ("q", "quit"):
                    ret = -1
                elif int(answer) in range(1, len(self.m_question[1])+1):
                    ret = int(answer)
                else:
                    print("Input Error!")
            except ValueError as e:
                print("Input ValueError:%s!" % e)

            ctx = zmq.Context()
            sck = ctx.socket(zmq.REQ)
            sck.connect(clt_socket_str)
            sck.send(b"%d" % ret)
        pass

    def checkAnswer(self, ans):
        if ans == -1:
            return -1
        elif ans == self.m_question[1].index(self.m_question[0])+1:
            print("You are right!")
            return 1
        else:
            print("You are wrong!")
            return 0
        pass


class GuiView:
    def __init__(self):
        self.m_okEvent = threading.Event()
        self.m_question = Question()
        self.m_rootWnd = tkinter.Tk()
        self.m_qstLabel = tkinter.Label(self.m_rootWnd)
        self.m_qstLabel.pack()
        self.m_ansEntry = tkinter.Entry(self.m_rootWnd)
        self.m_ansEntry.pack()
        self.m_okBtn = tkinter.Button(
            self.m_rootWnd, text="OK", command=self.onOkBtnClick)
        self.m_okBtn.pack()
        self.m_msgLabel = tkinter.Label(self.m_rootWnd)
        self.m_msgLabel.pack()
        self.m_ctrl = None
        pass

    def close(self):
        self.m_rootWnd.destroy()

    def setctrl(self, ctrl):
        self.m_ctrl = ctrl
        pass

    def onOkBtnClick(self):
        self.m_okEvent.set()
        pass

    def setQuestion(self, question):
        self.m_question = question

    def draw(self):
        qst_str = "How to write the character %d?\n" % self.m_question[0]
        for e in self.m_question[1]:
            qst_str += "%d.%d\t" % (self.m_question[1].index(e)+1, e)
        # self.m_qstLabel.delete(BEG,END)
        # self.m_qstLabel.insert(END,qst_str)
        self.m_qstLabel.config(text=qst_str)
        pass

    def getAnswer(self):
        # hint_str = "Please input your answer[1-%d] or q|quit:" % len(self.m_question[1])
        # self.m_ansEntry.config(hint=hint_str)
        while True:
            self.m_okEvent.wait()
            answer = self.m_ansEntry.get()
            self.m_okEvent.clear()

            ret = 0
            try:
                if answer in ("q", "quit"):
                    ret = -1
                elif int(answer) in range(1, len(self.m_question[1])+1):
                    ret = int(answer)
                else:
                    self.m_msgLabel.config(text="Input Error!")
            except ValueError as e:
                self.m_msgLabel.config(text="Input ValueError:%s!" % e)
            ctx = zmq.Context()
            sck = ctx.socket(zmq.REQ)
            sck.connect(clt_socket_str)
            sck.send(b"%d" % ret)

    def checkAnswer(self, ans):
        if ans == -1:
            return -1
        elif ans == self.m_question[1].index(self.m_question[0])+1:
            self.m_msgLabel.config(text="You are right!")
            return 1
        else:
            self.m_msgLabel.config(text="You are wrong!")
            return 0
        pass


class TrainModel:
    def __init__(self, view):
        self.m_question = []
        self.m_view = [view, ]
        pass

    def add_view(self, view):
        self.m_view.append(view)
        pass

    def nextQuestion(self, index):
        if len(self.m_question) > index:
            return self.m_question[index]
        else:
            self.m_question.append(QuestionFactory.createQuestion())
            return self.m_question[len(self.m_question)-1]
        pass

    def checkAnswer(self, ans):
        return ans
        pass

    def getView(self):
        return self.m_view


class Controller:
    def __init__(self, model):
        self.m_model = model
        self.m_view = model.getView()
        self.m_index = 0
        pass

    def checkAnswer(self, ans):
        ret = self.m_model.checkAnswer(ans)
        for e in self.m_view:
            ret = e.checkAnswer(ans)
        return ret
        pass

    def getAnswerFromViews(self):
        for e in self.m_view:
            thd = threading.Thread(target=e.getAnswer)
            thd.start()

    def train(self):
        ret = 0
        while ret != -1:
            qst = self.m_model.nextQuestion(self.m_index)
            self.m_index += 1
            for e in self.m_view:
                e.setQuestion(qst)
                e.draw()
            # ans = self.m_view[0].getAnswer()
            ctx = zmq.Context()
            sck = ctx.socket(zmq.REP)
            sck.bind(svr_socket_str)
            ans = sck.recv()
            ret = self.checkAnswer(int(ans))
        for e in self.m_view:
            e.close()
        print("Exit!")
        pass


def main():
    view = GuiView()
    model = TrainModel(view)
    conview = ConsoleView()
    model.add_view(conview)
    ctrl = Controller(model)
    view.setctrl(ctrl)
    conview.setctrl(ctrl)
    ctrl.getAnswerFromViews()
    threading.Thread(target=ctrl.train).start()
    view.m_rootWnd.mainloop()
    pass


if __name__ == "__main__":
    main()
