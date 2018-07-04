#!/usr/bin/python
#-*-coding:utf-8
import tkinter
import random
import threading
from tkinter import *

character_tbl = {}

class Question:
    def __init__(self):
        self.m_data = ()
        pass
    def __init__(self,data=()):
        self.m_data = data
        pass
    def __str__(self):
        pass
    def __getitem__(self,i):
        return self.m_data[i]

class QuestionFactory:
    @staticmethod
    def createQuestion():
        sel_index = []
        while len(sel_index) < 4:
            sel = random.randint(1,10)
            if sel not in sel_index:
                sel_index.append(sel)
        ret = (random.choice(sel_index),sel_index)
        return Question(ret)
        pass

class ConsoleView:
    def __init__(self):
        self.m_question = Question()
        pass
    def setQuestion(self,question):
        self.m_question = question
    def draw(self):
        print("How to write the character %d?"%self.m_question[0])
        choice_str = ""
        for e in self.m_question[1]:
            choice_str += "%d.%d\t" % (self.m_question[1].index(e)+1,e)
        print(choice_str)
        pass
    def getAnswer(self):
        while True:
            answer = raw_input("Please input your answer[1-%d] or q|quit:"%len(self.m_question[1]))
            try:
                if answer in ("q","quit"):
                    return -1
                elif int(answer) in range(1,len(self.m_question[1])+1):
                    return int(answer)
                else:
                    print("Input Error!")
            except ValueError as e:
                print("Input ValueError:%s!"%e)
        pass
    def checkAnswer(self,ans):
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
        self.m_okBtn = tkinter.Button(self.m_rootWnd,text="OK",command=self.onOkBtnClick)
        self.m_okBtn.pack()
        self.m_msgLabel = tkinter.Label(self.m_rootWnd)
        self.m_msgLabel.pack()
        pass
    def onOkBtnClick(self):
        self.m_okEvent.set()
        pass
    def setQuestion(self,question):
        self.m_question = question
    def draw(self):
        qst_str = "How to write the character %d?\n"%self.m_question[0]
        for e in self.m_question[1]:
            qst_str += "%d.%d\t" % (self.m_question[1].index(e)+1,e)
        # self.m_qstLabel.delete(BEG,END)
        # self.m_qstLabel.insert(END,qst_str)
        self.m_qstLabel.config(text=qst_str)
        pass
    def getAnswer(self):
        hint_str = "Please input your answer[1-%d] or q|quit:"%len(self.m_question[1])
        # self.m_ansEntry.config(hint=hint_str)
        self.m_okEvent.wait()
        answer = self.m_ansEntry.get()
        self.m_okEvent.clear()

        try:
            if answer in ("q","quit"):
                return -1
            elif int(answer) in range(1,len(self.m_question[1])+1):
                return int(answer)
            else:
                self.m_qstLabel.config(text="Input Error!")
        except ValueError as e:
            self.m_qstLabel.config(text="Input ValueError:%s!"%e)
        pass
    def checkAnswer(self,ans):
        if ans == -1:
            return -1
        elif ans == self.m_question[1].index(self.m_question[0])+1:
            self.m_qstLabel.config(text="You are right!")
            return 1
        else:
            self.m_qstLabel.config(text="You are wrong!")
            return 0
        pass

class TrainModel:
    def __init__(self,view):
        self.m_question = QuestionFactory.createQuestion()
        self.m_view = view
        pass
    def generateProblem(self):
        return QuestionFactory.createQuestion()
        pass
    def getView(self):
        return self.m_view

class Controller:
    def __init__(self,model):
        self.m_model = model
        self.m_view = model.getView()
        pass
    def checkAnswer(self,ans):
        pass
    def train(self):
        ret = 0
        while ret != -1:
            self.m_view.setQuestion(self.m_model.generateProblem())
            self.m_view.draw()
            ans = self.m_view.getAnswer()
            ret = self.m_view.checkAnswer(ans)
        pass

class GuiController:
    def __init__(self,model):
        self.m_model = model
        self.m_view = model.getView()
        pass
    def checkAnswer(self,ans):
        pass
    def train(self):
        self.m_view.setQuestion(self.m_model.generateProblem())
        self.m_view.draw()
        ans = self.m_view.getAnswer()
        ret = self.m_view.checkAnswer(ans)
        self.m_view.m_rootWnd.mainloop()
        pass

def main():
    print("trace ------0")
    view = GuiView()
    print("trace ------0.5")
    model = TrainModel(view)
    print("trace ------0.6")
    ctrl = Controller(model)

    print("trace ------1")
    ctrl.train()
    pass

if __name__ == "__main__":
    main()

