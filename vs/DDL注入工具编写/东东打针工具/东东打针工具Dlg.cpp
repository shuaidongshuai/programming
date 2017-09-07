
// 东东打针工具Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "东东打针工具.h"
#include "东东打针工具Dlg.h"
#include "afxdialogex.h"

#include <TlHelp32.h>
#include <AtlConv.h>

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


// C东东打针工具Dlg 对话框



C东东打针工具Dlg::C东东打针工具Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C东东打针工具Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C东东打针工具Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, mEditBrowse);
	DDX_Control(pDX, IDC_LIST1, mPropListBox);
}

BEGIN_MESSAGE_MAP(C东东打针工具Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &C东东打针工具Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &C东东打针工具Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &C东东打针工具Dlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// C东东打针工具Dlg 消息处理程序

BOOL C东东打针工具Dlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	C东东打针工具Dlg::OnBnClickedOk();
	mEditBrowse.EnableFileBrowseButton(NULL, _T("Dll Files (*.dll)|*.dll|All Files (*.*)|*.*||"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C东东打针工具Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C东东打针工具Dlg::OnPaint()
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
HCURSOR C东东打针工具Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C东东打针工具Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void C东东打针工具Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//AfxMessageBox(L"陈明东");//L""代表unicode码
	//AfxMessageBox(TEXT("text"));//TEXT表示自动适配编码

	//首先清空ListBox
	mPropListBox.ResetContent();

	//创建进程快照
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (INVALID_HANDLE_VALUE == hProcessSnapshot)//INVALID_HANDLE_VALUE == -1
	{
		AfxMessageBox(TEXT("Error while create snapshot"));//TEXT表示自动适配编码
		return;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);//设置大小

	Process32First(hProcessSnapshot, &pe);//获取第一个进程信息，放入pe结构体中
	//AfxMessageBox(pe.szExeFile);//第一个是系统的空进程，不需要
	TCHAR szProcessString[MAX_PATH];
	TCHAR *szBit;
	int i = 0;
	SYSTEM_INFO si;
	GetNativeSystemInfo(&si);
	while (Process32Next(hProcessSnapshot, &pe))
	{
		//判断进程是32位还是64位
		//从进程id获取进程句柄
		if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);//获取所有权限,获取进程句柄
			if (NULL == hProcess)
			{
				continue;//有些进程打不开，系统进程打不开，直接跳过
			}
			//有可能是64位进程
			BOOL bWow64;
			if (!IsWow64Process(hProcess, &bWow64))
			{
				AfxMessageBox(L"判断进程bit失败");
				return;
			}
			CloseHandle(hProcess);
			if (bWow64)//如果是64位下模拟的32位
			{
				//32
				szBit = TEXT("32位");
			}
			else
			{
				//64
				szBit = TEXT("64位");
			}
		}
		else if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL)
		{
			//32位
			szBit = TEXT("32位");
		}
		else
		{
			//其他
			szBit = TEXT("unKnow");
		}
		_stprintf_s(szProcessString, TEXT("【%s】->%s  PID:%d"), szBit, pe.szExeFile, pe.th32ProcessID);
		//把所有进程加入到ListBox
		int iListIndex = mPropListBox.AddString(szProcessString);
		//关联进程iD到添加进程字符串那一行   //吧行数和id关联起来，等一下要用行数找id
		mPropListBox.SetItemData(iListIndex, pe.th32ProcessID);

	}
	CloseHandle(hProcessSnapshot);
}

//·OpenProcess - 用于打开要寄生的目标进程。
//·VirtualAllocEx / VirtualFreeEx - 用于在目标进程中分配 / 释放内存空间。
//·WriteProcessMemory - 用于在目标进程中写入要加载的DLL名称。
//·CreateRemoteThread - 远程加载DLL的核心内容，用于控制目标进程调用API函数。
//·LoadLibrary - 目标进程通过调用此函数来加载病毒DLL。
BOOL RemoteLoadLibrary(HANDLE hProcess, LPCSTR lpLibFileName)
{
	if ((CString)lpLibFileName == "")
	{
		AfxMessageBox(TEXT("请检查是否添加DLL文件"));
		return FALSE;
	}
	// 向目标进程地址空间写入DLL名称
	DWORD dwSize;// , dwWritten;
	SIZE_T dwWritten;
	dwSize = lstrlenA(lpLibFileName) + 1;
	//在对方进程里面分配空间
	PCHAR pMem = (PCHAR)VirtualAllocEx(hProcess, NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (NULL == pMem)
	{
		return FALSE;
	}
	//向对方进程里面写DLL地址字符串	
	if (WriteProcessMemory(hProcess, pMem, (LPVOID)lpLibFileName, dwSize, &dwWritten))
	{
		// 要写入字节数与实际写入字节数不相等，仍属失败
		if (dwWritten != dwSize)
		{
			VirtualFreeEx(hProcess, pMem, dwSize, MEM_DECOMMIT);//释放空间
			CloseHandle(hProcess);
			// 失败处理
			return FALSE;
		}
		//通过审核
	}
	else
	{
		CloseHandle(hProcess);
		// 失败处理
		return FALSE;
	}
	/// 使目标进程调用LoadLibrary，加载DLL
	DWORD dwID;
	//LPVOID pFunc = LoadLibraryA;
	//HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, pMem, 0, &dwID);
	//if (hThread == NULL)
	//{
	//	//AfxMessageBox(TEXT("注入失败"));
	//	return FALSE;
	//}
	HMODULE  hModule = LoadLibrary(TEXT("kernel32.dll"));
	LPTHREAD_START_ROUTINE pfThread = (LPTHREAD_START_ROUTINE)GetProcAddress(hModule, "LoadLibraryA");//GetModuleHandle(_T("Kernel32"))第一个采参数也可以这样填
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, pfThread, pMem, 0, &dwID);

	//在远程创建的线程中运行加载的DLL中的函数LoadLibraryA("陈明东inject.dll");
	//HMODULE  hModule2 = pfThread - LoadLibraryA + ExitCode;
	//LPTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(, "go");//GetModuleHandle(TEXT("注射进程.dll"))
	//if (pfnStartAddr == NULL)
	//{
	//	MessageBox(NULL, L"获取函数go的地址失败", L"Error", MB_OK);
	//	return FALSE;
	//}
	//HANDLE hThread2;
	//if ((hThread2 = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, pMem, 0, &dwID)) == NULL)
	//{
	//	MessageBox(NULL, L"创建远程线程PrintMsg失败", L"Error", MB_OK);
	//	return FALSE;
	//}
	//WaitForSingleObject(hThread2, INFINITE);
	//FreeLibrary(hModule2);

	// 等待LoadLibrary加载完毕
	WaitForSingleObject(hThread, INFINITE);

	DWORD ExitCode;
	GetExitCodeThread(hThread, &ExitCode);//ExitCode取得的HMODULE是目标进程（远程）的模块基址
	CloseHandle(hThread);
	// 释放目标进程中申请的空间
	VirtualFreeEx(hProcess, pMem, dwSize, MEM_DECOMMIT);
	return ExitCode;
}
BOOL RemoteLoadLibrary2(HANDLE hProcess, LPCSTR lpLibFileName)
{
	PCHAR lpRemoteLibFileName = (PCHAR)VirtualAllocEx(hProcess, NULL, lstrlenA(lpLibFileName) + 1, MEM_COMMIT, PAGE_READWRITE);
	if (lpRemoteLibFileName == NULL)
	{
		return FALSE;
	}
	WriteProcessMemory(hProcess, lpRemoteLibFileName, (void *)lpLibFileName, lstrlenA(lpLibFileName) + 1, NULL);
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(_T("Kernel32")), "LoadLibraryA");
	HANDLE hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, lpRemoteLibFileName, 0, NULL);
	if (hRemoteThread == NULL)
	{
		return FALSE;
	}
	WaitForSingleObject(hRemoteThread, INFINITE);
	DWORD ExitCode;
	GetExitCodeThread(hRemoteThread, &ExitCode);
	CloseHandle(hRemoteThread);
	VirtualFreeEx(hProcess, lpRemoteLibFileName, 0, MEM_RELEASE);

	return ExitCode;
}

void C东东打针工具Dlg::OnBnClickedOk2()
{
	// TODO:  在此添加控件通知处理程序代码

	USES_CONVERSION;//用这个宏就可以用W2A了

	CString strDLLPathName;
	mEditBrowse.GetWindowText(strDLLPathName);

	//获取选中的进程id,并打开进程
	int iSelectIndex = mPropListBox.GetCurSel();
	DWORD pid = mPropListBox.GetItemData(iSelectIndex);
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | SYNCHRONIZE | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, pid);
	if (INVALID_HANDLE_VALUE == hProcess || NULL == hProcess)
	{
		AfxMessageBox(_T("打开进程失败!"));
		return;
	}
	//然后通过PID获取进程句柄
	if (RemoteLoadLibrary(hProcess, W2A(strDLLPathName)))//如果这里不用W2A会一直注入不成功，但是视频上没有用，也成功了
	{
		MessageBoxA(0, "成功注入", "恭喜", 0);
	}
	else
	{
		AfxMessageBox(_T("注入失败"));
	}

}

