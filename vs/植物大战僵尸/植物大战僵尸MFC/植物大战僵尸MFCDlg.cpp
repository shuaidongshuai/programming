
// 植物大战僵尸MFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "植物大战僵尸MFC.h"
#include "植物大战僵尸MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C植物大战僵尸MFCDlg 对话框



C植物大战僵尸MFCDlg::C植物大战僵尸MFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C植物大战僵尸MFCDlg::IDD, pParent)
	, bigPass(_T(""))
	, smallPass(_T(""))
	, check(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C植物大战僵尸MFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bigPass);
	DDV_MaxChars(pDX, bigPass, 1);
	DDX_Text(pDX, IDC_EDIT2, smallPass);
	DDV_MaxChars(pDX, smallPass, 2);
	DDX_Text(pDX, IDC_STATIC1, check);
}

BEGIN_MESSAGE_MAP(C植物大战僵尸MFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C植物大战僵尸MFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &C植物大战僵尸MFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &C植物大战僵尸MFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C植物大战僵尸MFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &C植物大战僵尸MFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C植物大战僵尸MFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C植物大战僵尸MFCDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &C植物大战僵尸MFCDlg::OnBnClickedButton8)

	ON_BN_CLICKED(IDC_BUTTON10, &C植物大战僵尸MFCDlg::OnBnClickedButton10)

	ON_BN_CLICKED(IDC_BUTTON9, &C植物大战僵尸MFCDlg::OnBnClickedButton9)
END_MESSAGE_MAP()



// C植物大战僵尸MFCDlg 消息处理程序
BOOL IsSunUnLimite = false;
BOOL IsMoneyUnLimite = false;
BOOL IsCDUnLimite = false;
BOOL IsPause = true;
BOOL initWaigua(HANDLE *h);
void modifySun();
void modifyMoney();
void modifyCD();
void modifyPause();
void pauseYes(unsigned char *pCode, unsigned char code[]);
void pauseNo(unsigned char *pCode, unsigned char code[]);
void modifyPass(int pass);
unsigned char *pCode = (unsigned char*)0x00472B50;//暂停基址
unsigned char OldOpCode[3];

DWORD WINAPI waiguaThread(LPVOID lpThreadParameter)
{
	while (1)
	{
		if (IsSunUnLimite)
		{
			modifySun();
		}
		if (IsMoneyUnLimite)
		{
			modifyMoney();
		}
		if (IsCDUnLimite)
		{
			modifyCD();
		}
	}
}

BOOL C植物大战僵尸MFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MINIMIZE);

	// TODO:  在此添加额外的初始化代码
	/* 创建线程 不断修改阳光 */
	CreateThread(0, 0, waiguaThread, 0, 0, 0);
	check = "请检测是否捕捉到游戏";
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C植物大战僵尸MFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C植物大战僵尸MFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C植物大战僵尸MFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C植物大战僵尸MFCDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	IsSunUnLimite = TRUE;
}

void C植物大战僵尸MFCDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	IsSunUnLimite = FALSE;
}

void C植物大战僵尸MFCDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	IsMoneyUnLimite = true;
}

void C植物大战僵尸MFCDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	IsMoneyUnLimite = false;
}

void C植物大战僵尸MFCDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	IsCDUnLimite = true;
}

void C植物大战僵尸MFCDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	IsCDUnLimite = false;
}


void C植物大战僵尸MFCDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	pauseNo(pCode, OldOpCode);
	
}


void C植物大战僵尸MFCDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	unsigned char newOpCode[] = "\xC2\x04\x00";
	pauseYes(pCode, newOpCode);
}

void C植物大战僵尸MFCDlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData();

	long lBigPass = wcstol(bigPass, NULL, 10);
	long lSmallPass = wcstol(smallPass, NULL, 10);
	if (lBigPass < 1 || lBigPass > 6 || lSmallPass < 1 || lSmallPass > 10)
	{
		AfxMessageBox(TEXT("关卡不合格"));
	}
	int pass = (lBigPass - 1) * 10 + lSmallPass;
	modifyPass(pass);
}


void C植物大战僵尸MFCDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	HANDLE hProcess;
	if (initWaigua(&hProcess))
	{
		ReadProcessMemory(hProcess, pCode, OldOpCode, 3, NULL);

		check = "请放心大胆的虐僵尸";
		UpdateData(false);
	}
	else
	{
		check = "未检测到游戏";
		UpdateData(false);
	}
}
