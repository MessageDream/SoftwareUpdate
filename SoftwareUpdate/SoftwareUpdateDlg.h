
// SoftwareUpdateDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "zfilesocket.h"
#include "afxwin.h"

// CSoftwareUpdateDlg 对话框
class CSoftwareUpdateDlg : public CDialogEx
{
// 构造
public:
	CSoftwareUpdateDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CSoftwareUpdateDlg();
// 对话框数据
	enum { IDD = IDD_SOFTWAREUPDATE_DIALOG };

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
private:
	CProgressCtrl m_progressUpdate;
	HANDLE m_hEvtExitUpdate;
	ZFileSocket m_filesock;
	ULONGLONG m_llTimeCount;
	CButton m_btnRetry;
	bool m_bIsUpdateSuccess;
	int m_nRetryTimes;
protected:
	afx_msg LRESULT OnMsgrecvpro(WPARAM wParam, LPARAM lParam);
public:
	static UINT UpdateThreadFunc(LPVOID lpParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonRetry();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
