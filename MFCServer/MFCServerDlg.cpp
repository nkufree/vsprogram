
// MFCServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCServer.h"
#include "MFCServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hMutex;
struct ClientArgs {
	SOCKET sockClient;
	CMFCServerDlg* dlg;
};

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


// CMFCServerDlg 对话框



CMFCServerDlg::CMFCServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERVER_DIALOG, pParent)
	, serverIP(_T("127.0.0.1"))
	, serverPort(9000)
	, msg(_T(""))
	, isRunning(false)
	, clientNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SERVERIP, serverIP);
	DDX_Text(pDX, IDC_SERVERPORT, serverPort);
	DDX_Text(pDX, IDC_MSG, msg);
	DDX_Text(pDX, IDC_CLIENTNUM, clientNum);
	DDX_Control(pDX, IDC_SHOWCLIENTS, showClients);
}

BEGIN_MESSAGE_MAP(CMFCServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_APPLY, &CMFCServerDlg::OnBnClickedApply)
	ON_MESSAGE(WM_UPDATE_MSG, &CMFCServerDlg::OnUpdateMsg)
	ON_MESSAGE(WM_REMOVE_CLIENT, &CMFCServerDlg::OnRemoveClient)
	ON_BN_CLICKED(IDC_CLEARALL, &CMFCServerDlg::OnBnClickedClearall)
END_MESSAGE_MAP()


// CMFCServerDlg 消息处理程序

BOOL CMFCServerDlg::OnInitDialog()
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
	/*
	WSADATA WSAData;
	char hostName[256];
	if (!WSAStartup(MAKEWORD(2, 2), &WSAData))
	{
		if (!gethostname(hostName, sizeof(hostName)))
		{
			hostent* host = gethostbyname(hostName);
			if (host != NULL)
			{
				char* ip = inet_ntoa(*(struct in_addr*)*host->h_addr_list);
				CString str(ip);
				SetDlgItemText(IDC_SERVERIP, str);

			}
		}
	}*/
	CString str[] = { _T("IP地址"),_T("端口") };
	showClients.InsertColumn(0, str[0], LVCFMT_LEFT, 150);
	showClients.InsertColumn(1, str[1],LVCFMT_LEFT,100);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCServerDlg::OnPaint()
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
HCURSOR CMFCServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCServerDlg::sendMsg(CMFCServerDlg* dlg, char* msg, int len)
{
	WaitForSingleObject(hMutex, INFINITE);
	list<SOCKET>::iterator it = (dlg->sockClients).begin();
	while (it != sockClients.end())
	{
		send(*it, msg, len, 0);
		it++;
	}
	ReleaseMutex(hMutex);
}

void CMFCServerDlg::handleClient(void* arg)
{
	SOCKET sockClient = ((ClientArgs*)arg)->sockClient;
	CMFCServerDlg* dlg = ((ClientArgs*)arg)->dlg;
	int len = 0;
	char recvBuf[MAXSIZE] = {};
	sockaddr_in sa;
	int len_addr = sizeof(sa);
	WaitForSingleObject(hMutex, INFINITE);
	int index = dlg->sockClients.size();
	CString ip;
	CString port;
	if (!getpeername(sockClient, (struct sockaddr*)&sa, &len_addr))
	{
		ip = inet_ntoa(sa.sin_addr);
		port.Format(_T("%d"), ntohs(sa.sin_port));
		int temp = dlg->showClients.InsertItem(index, ip);
		dlg->showClients.SetItemText(temp,1, port);
	}
	ReleaseMutex(hMutex);
	while (true)
	{
		len = recv(sockClient, recvBuf, MAXSIZE, 0);
		int state = 0;
		if (len > 0 && len < MAXSIZE - 1)
		{
			recvBuf[len] = 0;
			if (!strcmp(recvBuf, "bye"))
			{
				break;
			}
			char temp[MAXSIZE+19] = {};
			strcpy_s(temp, "（接收消息）");
			strcat_s(temp, recvBuf);
			dlg->PostMessageW(WM_UPDATE_MSG, 1, (LPARAM)temp);
			dlg->sendMsg(dlg, recvBuf, len);
		}
		else break;
		Sleep(1000);
	}
	
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < dlg->sockClients.size(); i++)
	{
		CString s1 = dlg->showClients.GetItemText(i, 0);
		CString s2 = dlg->showClients.GetItemText(i, 1);
		if (s1 == ip && s2 == port)
		{
			dlg->showClients.DeleteItem(i);
			break;
		}
	}
	//dlg->showClients.DeleteItem()
	dlg->sockClients.remove(sockClient);
	dlg->PostMessageW(WM_REMOVE_CLIENT, 1,(LPARAM)&sockClient);
	//Sleep(100);
	ReleaseMutex(hMutex);
	//closesocket(sockClient);
}

void CMFCServerDlg::OnBnClickedApply()
{
	// TODO: 在此添加控件通知处理程序代码
	if (isRunning)
	{
		char endMsg[] = "bye";
		sendMsg(this, endMsg, 4);
		isRunning = false;
		closesocket(sockServer);
		CloseHandle(hMutex);
		CloseHandle(hAccept);
		sockClients.clear();
		showClients.DeleteAllItems();
		PostMessageW(WM_REMOVE_CLIENT, 1, 0);
		SetDlgItemText(IDC_APPLY, _T("启动服务"));
		PostMessageW(WM_UPDATE_MSG, 1, (LPARAM) & ("服务器关闭\r\n"));
		return;
	}
	WSADATA data;
	int ret = WSAStartup(MAKEWORD(2, 2), &data);
	if (ret)
	{
		msg+= "初始化网络错误\r\n";
		this->UpdateData(false);
		WSACleanup();
		return;
	}
	sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (sockServer == INVALID_SOCKET)
	{
		msg += "创建套接字失败\r\n";
		this->UpdateData(false);
		WSACleanup();
		return;
	}
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.S_un.S_addr = inet_addr((char*)serverIP.GetBuffer());
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	ret = bind(sockServer, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		msg += "绑定端口号错误\r\n";
		this->UpdateData(false);
		return;
	}
	ret = listen(sockServer, 5);
	if (ret == SOCKET_ERROR)
	{
		msg += "监听套接字失败\r\n";
		this->UpdateData(false);
		return;
	}
	hMutex = CreateMutex(NULL, FALSE, NULL);
	hAccept = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleAccept, (LPVOID)this, 0, (LPDWORD)&threadID);
	SetDlgItemText(IDC_APPLY, _T("断开服务"));
	isRunning = true;
}

void CMFCServerDlg::handleAccept(void* arg)
{
	CMFCServerDlg* dlg = (CMFCServerDlg*)arg;
	int len = sizeof(sockaddr);
	sockaddr_in addrClient;
	dlg->PostMessageW(WM_UPDATE_MSG, 1, (LPARAM) & ("服务器启动，等待客户端连接……\r\n"));
	while (true)
	{
		
		SOCKET sockClient = accept(dlg->sockServer, (sockaddr*)&addrClient, &len);
		if (!dlg->isRunning)
		{
			return;
		}
		if (sockClient == INVALID_SOCKET)
		{
			Sleep(100);
			continue;
		}
		WaitForSingleObject(hMutex, INFINITE);
		// sockClients[clientNum] = sockClient;
		(dlg->sockClients).push_back(sockClient);
		SOCKET temp = INVALID_SOCKET;
		dlg->PostMessageW(WM_REMOVE_CLIENT, 1, (LPARAM)&(temp));
		// clientNum++;
		ReleaseMutex(hMutex);
		ClientArgs args = { sockClient,dlg };
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)handleClient, (LPVOID)&args, 0, 0);
		Sleep(100);
	}
}


afx_msg LRESULT CMFCServerDlg::OnUpdateMsg(WPARAM wParam, LPARAM lParam)
{
	char* s = (char*)lParam;
	this->msg += s;
	this->UpdateData(false);
	return 0;
}


afx_msg LRESULT CMFCServerDlg::OnRemoveClient(WPARAM wParam, LPARAM lParam)
{
	//SOCKET sock = *((SOCKET *)lParam);
	//if(sock != INVALID_SOCKET)
	CString str;
	str.Format(_T("此时连接主机数量为：%d\r\n"),(int)sockClients.size());
	clientNum = sockClients.size();
	//this->msg += str;
	this->UpdateData(false);
	return 0;
}


void CMFCServerDlg::OnBnClickedClearall()
{
	// TODO: 在此添加控件通知处理程序代码
	msg = "";
	this->UpdateData(false);
}
