
// MFCClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClientDlg 对话框



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
	, recvMsg(_T(""))
	, myName(_T(""))
	, sendMsg(_T(""))
	, serverPort(9000)
	, isConnect(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_SERVERIP, ipCtrl);
	//  DDX_Control(pDX, IDC_SERVERPORT, portCtrl);
	DDX_Text(pDX, IDC_RECVMSG, recvMsg);
	DDX_Text(pDX, IDC_NAME, myName);
	DDX_Text(pDX, IDC_SENDMSG, sendMsg);
	//  DDX_Text(pDX, IDC_SERVERIP, serverIP);
	DDX_Text(pDX, IDC_SERVERPORT, serverPort);
	DDV_MinMaxInt(pDX, serverPort, 1024, 65535);
	DDX_Control(pDX, IDC_SERVERIP, ipCtrl);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CMFCClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CONNECT, &CMFCClientDlg::OnBnClickedConnect)
	//ON_BN_CLICKED(IDC_SETNAME, &CMFCClientDlg::OnBnClickedSetname)
	ON_MESSAGE(WM_UPDATE_MSG, &CMFCClientDlg::OnUpdateMsg)
END_MESSAGE_MAP()


// CMFCClientDlg 消息处理程序

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	ipCtrl.SetAddress(127, 0, 0, 1);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCClientDlg::OnPaint()
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
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCClientDlg::receiveMessage(void* arg)
{
	SOCKET sockClient = ((RecvArgs*)arg)->sockClient;
	CMFCClientDlg* dlg = ((RecvArgs*)arg)->dlg;

	char recvBuf[MAXSIZE] = {};
	int len;
	int noMsg = 0;
	while (true)
	{
		len = recv(sockClient, recvBuf, MAXSIZE, 0);
		if (len == SOCKET_ERROR)
		{
			Sleep(100);
			noMsg++;
			if (noMsg == 10)
			{
				dlg->PostMessageW(WM_UPDATE_MSG, 1, (LPARAM) & ("服务器连接错误\r\n"));
				//dlg->OnBnClickedConnect();
				break;
			}
			continue;
		}
		noMsg = 0;
		//strcat_s(recvBuf, "\r\n");
		if (!strcmp(recvBuf,"bye"))
		{
			dlg->PostMessageW(WM_UPDATE_MSG, 1, (LPARAM)&("服务器断开连接\r\n"));
			dlg->OnBnClickedConnect();
			return;

		}
		dlg->PostMessageW(WM_UPDATE_MSG, 1, (LPARAM)recvBuf);

		Sleep(100);
	}

}

void CMFCClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!isConnect)
	{
		PostMessageW(WM_UPDATE_MSG, 1, (LPARAM) & ("请重新连接服务器\r\n"));
		return;
	}
	this->UpdateData(true);
	if (myName == "")
	{
		AfxMessageBox(_T("请输入昵称！"));
		return;
	}
	CString str = myName + "：" + sendMsg + "\r\n";
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	char* sendBuf = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), sendBuf, len, NULL, NULL);
	sendBuf[len] = '\0';

	int byte = send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
	delete[] sendBuf;
	sendMsg = "";
	this->UpdateData(false);
	if (byte == SOCKET_ERROR)
	{
		recvMsg += "服务器连接错误\r\n";
		this->UpdateData(false);
		return;
	}
}


void CMFCClientDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isConnect)
	{
		char sendBuf[] = "bye";
		int byte = send(sockClient, sendBuf, strlen(sendBuf) + 1, 0);
		isConnect = false;
		SetDlgItemText(IDC_CONNECT, _T("连接"));
		closesocket(sockClient);
		CloseHandle(hThreadRecv);
		WSACleanup();
		return;
	}
	this->UpdateData(true);
	WSADATA data;
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret)
	{
		recvMsg += "初始化网络错误\r\n";
		this->UpdateData(false);
		WSACleanup();
		return;
	}
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClient == INVALID_SOCKET)
	{
		recvMsg += "创建套接字失败\r\n";
		this->UpdateData(false);
		WSACleanup();
		return;
	}

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(serverPort);
	BYTE a1, a2, a3, a4;
	ipCtrl.GetAddress(a1, a2, a3, a4);
	CString a;
	a.Format(_T("%d.%d.%d.%d"), a1, a2, a3, a4);
	int len = WideCharToMultiByte(CP_ACP, 0, a, a.GetLength(), NULL, 0, NULL, NULL);
	char* chars = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, a, a.GetLength(), chars, len, NULL, NULL);
	chars[len] = '\0';
	addrServer.sin_addr.S_un.S_addr = inet_addr(chars);
	ret = connect(sockClient, (sockaddr*)&addrServer, sizeof(sockaddr));
	delete[] chars;
	if (ret == SOCKET_ERROR)
	{
		recvMsg += "服务器连接错误\r\n";
		this->UpdateData(false);
		WSACleanup();
		return;
	}
	recvArgs.sockClient = sockClient;
	recvArgs.dlg = this;
	isConnect = true;
	hThreadRecv = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)receiveMessage, (LPVOID)&recvArgs, 0, 0);
	this->UpdateData(false);
	PostMessageW(WM_UPDATE_MSG, 1, (LPARAM) & ("服务器连接成功\r\n"));
	SetDlgItemText(IDC_CONNECT, _T("断开连接"));
}


//void CMFCClientDlg::OnBnClickedSetname()
//{
	// TODO: 在此添加控件通知处理程序代码
//	this->UpdateData(true);
//}


afx_msg LRESULT CMFCClientDlg::OnUpdateMsg(WPARAM wParam, LPARAM lParam)
{
	char* s = (char*)lParam;
	this->recvMsg += s;
	this->UpdateData(false);
	return 0;
}
