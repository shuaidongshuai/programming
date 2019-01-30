import wx
from subFrame import *
from switchFrame import *
from main import *

class MainFrame(wx.Frame):
    dbUtil = DBUitl()

    def __init__(self, parent, title):
        #生成一个宽为400，高为400的frame框
        wx.Frame.__init__(self, parent, title = title, size=(520, 400))
        #定一个网格布局,两行一列
        self.main_layout = wx.BoxSizer(wx.VERTICAL)

        #生成一个列表
        self.list = wx.ListCtrl(self, -1, size = (520,300), style = wx.LC_REPORT | wx.LC_HRULES | wx.LC_VRULES | wx.LC_SORT_ASCENDING) # LC_SORT_ASCENDING 排序，默认按第一列排序，可以通过setItemData进行设置，但必须是整数
        #列表有散列，分别是书本ID,书名，添加日期
        self.list.InsertColumn(0, "学号")
        self.list.InsertColumn(1, "姓名")
        self.list.InsertColumn(2, "奖项")

        #设置各列的宽度
        self.list.SetColumnWidth(0, 153)                                         #设置每一列的宽度
        self.list.SetColumnWidth(1, 133)
        self.list.SetColumnWidth(2, 234)

        #添加一组按钮，实现增删改查,用一个panel来管理该组按钮的布局
        self.panel = wx.Panel(self, pos = (0, 300), size = (520, 100))

        #定义一组按钮
        add_button = wx.Button(self.panel, label = "添加", pos = (65, 15), size = (60, 30))    #, size = (75, 30)
        del_button = wx.Button(self.panel, label = "删除", pos = (135, 15), size = (60, 30))    #, size = (75, 30)
        update_button = wx.Button(self.panel, label = "修改", pos = (205, 15), size = (60, 30)) #, size = (75, 30)
        find_button = wx.Button(self.panel, label = "查找", pos = (275, 15), size = (60, 30))  #, size = (75, 30)
        switch_button = wx.Button(self.panel, label = "切换班级", pos = (345, 15), size = (70, 30))  #, size = (75, 30)

        #为按钮绑定相应事件函数，第一个参数为默认参数，指明为按钮类事件，第二个为事件函数名，第三个为按钮名
        self.Bind(wx.EVT_BUTTON, self.addStudent, add_button)
        self.Bind(wx.EVT_BUTTON, self.delStudent, del_button)
        self.Bind(wx.EVT_BUTTON, self.updateStudent, update_button)
        self.Bind(wx.EVT_BUTTON, self.findStudent, find_button)
        self.Bind(wx.EVT_BUTTON, self.switchStudent, switch_button)

        #将列表和panel添加到主面板
        self.main_layout.Add(self.list, 1)
        self.main_layout.Add(self.panel, 2)

        self.SetSizer(self.main_layout)

        self.showAllStudentByClazz('1')

        self.sortId = 1

    def showAllStudentByClazz(self, clazz):
        self.SetTitle(str(clazz) + "班级获奖管理")
        self.clazz = clazz
        self.showAllStudent()

    def showAllStudent(self):
        allStu = self.dbUtil.getAllStuByClazz(self.clazz)
        for stu in allStu:
            index = self.list.InsertItem(self.list.GetItemCount(), stu.no)
            self.list.SetItem(index, 1, stu.name)
            self.list.SetItem(index, 2, stu.winning)

    def addStudent(self, evt):
        subFrame = SubFrame(self, '添加学生信息')
        subFrame.Show(True)
        subFrame.changeFrame(subFrameMode['add'])

    def delStudent(self, evt):
        '''先选中 然后删除'''
        selectId = self.list.GetFirstSelected()
        if selectId == -1:
            warn = wx.MessageDialog(self, message = "未选中任何条目！！！", caption = "错误警告", style = wx.YES_DEFAULT | wx.ICON_ERROR)
            warn.ShowModal()                                                             #提示错误
            warn.Destroy()
        else:
            stuNo = self.list.GetItem(selectId, 0).Text                                 #得到学生学号
            stuWinning = self.list.GetItem(selectId, 2).Text
            self.list.DeleteItem(selectId)
            self.dbUtil.delete(stuNo, stuWinning)

    def clearAllStudent(self):
        self.list.DeleteAllItems()

    def updateStudent(self, evt):
        selectId = self.list.GetFirstSelected()
        if selectId == -1:
            warn = wx.MessageDialog(self, message = "未选中任何条目！！！", caption = "错误警告", style = wx.YES_DEFAULT | wx.ICON_ERROR)
            warn.ShowModal()                                                       #提示错误
            warn.Destroy()      
        else:
            subFrame = SubFrame(self, '修改学生信息')
            subFrame.Show()
            subFrame.changeFrame(subFrameMode['updata'])

    def findStudent(self, evt):
        subFrame = SubFrame(self, '采用模糊查询')
        subFrame.Show()
        subFrame.changeFrame(subFrameMode['find'])

    def switchStudent(self, evt):
        switchFrame = SwitchFrame(self, "切换班级")
        switchFrame.Show()

    # # 升序
    # def listCompareFunctionUp(self, item1, item2):
    #     return item2 - item1

    # # 降序
    # def listCompareFunctionDown(self, item1, item2):
    #     return item1 - item2

    # def sortwinning(self, evt):
    #     # 为了一次升序一次降序
    #     if self.sortId == 1:
    #         self.sortId = 0
    #         self.list.SortItems(self.listCompareFunctionUp)
    #     else:
    #         self.sortId = 1
    #         self.list.SortItems(self.listCompareFunctionDown)