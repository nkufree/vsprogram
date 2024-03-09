
// MFCServerDlg.h: 头文件
//

#pragma once
#include <list>
#define MAXSIZE 1024
#define MAXCLIENT 30
#define WM_UPDATE_MSG WM_USER+100
#define WM_REMOVE_CLIENT WM_USER+200

using namespace std;
// CMFCServerDlg 对话框
class CMFCServerDlg : public CDialogEx
{
// 构造
public:
	CMFCServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString serverIP;
	int serverPort;
	afx_msg void OnBnClickedApply();
	static void handleClient(void* arg);
	static void handleAccept(void* arg);
	
	void sendMsg(CMFCServerDlg* dlg, char* msg, int len);
	list<SOCKET> sockClients;
	CString msg;
	SOCKET sockServer;
	bool isRunning;
	HANDLE hAccept;
	int threadID;
protected:
	afx_msg LRESULT OnUpdateMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoveClient(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedClearall();
	int clientNum;
	CListCtrl showClients;
};
