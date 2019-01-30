import wx
from DBUitl import *
from MainFrame import *
from main import *

class SubFrame(wx.Frame):
    dbUtil = DBUitl()

    def __init__(self, parent, title):
        self.mainframe = parent
        # 生成一个300*300的框
        wx.Frame.__init__(self, parent, title = title, size=(280, 210))

        self.panel = wx.Panel(self, pos=(0, 0), size=(400, 100))
        self.panel.SetBackgroundColour("#FFFFFF")  # 背景为白色

        # 四个编辑框
        wx.StaticText(self.panel, label="班级:", pos=(5, 8), size=(35, 25))
        clazz_text = wx.TextCtrl(self.panel, pos=(40, 5), size=(200, 25))
        self.clazz = clazz_text

        wx.StaticText(self.panel, label="学号:", pos=(5, 38), size=(35, 25))
        no_text = wx.TextCtrl(self.panel, pos=(40, 35), size=(200, 25))
        self.no = no_text

        wx.StaticText(self.panel, label="姓名:", pos=(5, 68), size=(35, 25))
        name_text = wx.TextCtrl(self.panel, pos=(40, 65), size=(200, 25))
        self.name = name_text

        wx.StaticText(self.panel, label="奖项:", pos=(5, 98), size=(35, 25))
        winning_text = wx.TextCtrl(self.panel, pos=(40, 95), size=(200, 25))
        self.winning = winning_text

        self.button = button = wx.Button(self.panel, label="完成", pos=(80, 128))
        

    def changeFrame(self, mode = subFrameMode['add']):
        if mode == subFrameMode['add']:
            self.Bind(wx.EVT_BUTTON, self.addStudent, self.button)
        elif mode == subFrameMode['updata']:
            self.Bind(wx.EVT_BUTTON, self.updateStudent, self.button)

            selectId = self.mainframe.list.GetFirstSelected()
            self.selectId = selectId
            no = self.mainframe.list.GetItem(selectId, 0).Text                                    #得到学生学号
            self.changeNo = no
            winning = self.mainframe.list.GetItem(selectId, 2).Text   
            self.changeWinning = winning
            clazz = self.mainframe.clazz
            name = self.mainframe.list.GetItem(selectId, 1).Text                                  #得到学生姓名
            self.clazz.SetValue(clazz)
            self.no.SetValue(no)
            self.name.SetValue(name)
            self.winning.SetValue(winning)
        elif mode == subFrameMode['find']:
            self.Bind(wx.EVT_BUTTON, self.findStudent, self.button)


    def addStudent(self, evt):
        stu = Student(self.clazz.GetValue(), self.no.GetValue(),
                         self.name.GetValue(), self.winning.GetValue())

        stuDB = self.dbUtil.getStudentByNo(stu.no)
        # print stu.clazz, stu.no, stu.name, stu.winning
        # print stuDB.clazz, stuDB.no, stuDB.name, stuDB.winning
        if stuDB:
            stu.clazz = str(stuDB.clazz)
            stu.no = stuDB.no
            stu.name = stuDB.name
        else:
            self.dbUtil.insertStudent(stu)
        self.dbUtil.insertWinning(stu)
        self.Show(False)

        if self.mainframe.clazz == stu.clazz:
            index = self.mainframe.list.InsertItem(self.mainframe.list.GetItemCount(), str(stu.no))
            self.mainframe.list.SetItem(index, 1, stu.name)
            self.mainframe.list.SetItem(index, 2, stu.winning)

    def updateStudent(self, evt):
        stu = Student(self.clazz.GetValue(), self.no.GetValue(),
                         self.name.GetValue(), self.winning.GetValue())

        self.dbUtil.updateStudent(stu, self.changeNo)
        self.dbUtil.updateWinning(stu, self.changeNo, self.changeWinning)
        self.Show(False)

        if self.mainframe.clazz == stu.clazz:
            self.mainframe.list.SetItem(self.selectId, 0, stu.no)
            self.mainframe.list.SetItem(self.selectId, 1, stu.name)
            self.mainframe.list.SetItem(self.selectId, 2, stu.winning)
        else:
            self.mainframe.list.DeleteItem(self.selectId)

    def findStudent(self, evt):
        # 根据输入的学号查询
        stu = Student(self.clazz.GetValue(), self.no.GetValue(),
                         self.name.GetValue(), self.winning.GetValue())
        self.Show(False)
        allStu = self.dbUtil.getStudentByLike(stu)

        self.mainframe.clearAllStudent()
        for stu in allStu:
            index = self.mainframe.list.InsertItem(self.mainframe.list.GetItemCount(), stu.no)
            self.mainframe.list.SetItem(index, 1, stu.name)
            self.mainframe.list.SetItem(index, 2, stu.winning)




