from MainFrame import *

subFrameMode = {
'add':1,
'updata':2,
'find':3
}

if __name__ == "__main__":
    app = wx.App()
    frame = MainFrame(None, "")
    frame.Show()
    app.MainLoop() 