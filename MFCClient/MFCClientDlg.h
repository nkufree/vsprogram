
// MFCClientDlg.h: 头文件
//

#pragma once
#define MAXSIZE 1024
#define WM_UPDATE_MSG WM_USER+100


// CMFCClientDlg 对话框
class CMFCClientDlg : public CDialogEx
{
// 构造
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
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
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedConnect();
//	CEdit ipCtrl;
//	CEdit portCtrl;
	CString recvMsg;
	CString myName;
	CString sendMsg;
//	afx_msg void OnBnClickedSetname();
//	CString serverIP;
	int serverPort;
	HANDLE hThreadRecv;
	struct RecvArgs {
		SOCKET sockClient;
		CMFCClientDlg* dlg;
	} recvArgs;
	SOCKET sockClient;
	static void receiveMessage(void* arg);
	bool isConnect;
protected:
	afx_msg LRESULT OnUpdateMsg(WPARAM wParam, LPARAM lParam);
public:
	CIPAddressCtrl ipCtrl;
};
