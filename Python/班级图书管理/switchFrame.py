import wx
from DBUitl import *

class SwitchFrame(wx.Frame):

    def __init__(self, parent, title):
        self.mainframe = parent
        # 生成一个300*300的框
        wx.Frame.__init__(self, None, title = title, size=(280, 110))

        self.panel = wx.Panel(self, pos=(0, 0), size=(400, 100))
        self.panel.SetBackgroundColour("#FFFFFF")  # 背景为白色

        wx.StaticText(self.panel, label="班级:", pos=(5, 8), size=(35, 25))
        clazz_text = wx.TextCtrl(self.panel, pos=(40, 5), size=(200, 25))
        self.clazz = clazz_text

        self.button = button = wx.Button(self.panel, label="切换", pos=(80, 35))

        self.Bind(wx.EVT_BUTTON, self.switchStudent, self.button)

    def switchStudent(self, env):
        self.mainframe.clearAllStudent()
        self.mainframe.showAllStudentByClazz(self.clazz.GetValue())
        self.Show(False)