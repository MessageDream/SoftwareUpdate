
// SoftwareUpdateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "zfilesocket.h"
#include "afxwin.h"

// CSoftwareUpdateDlg �Ի���
class CSoftwareUpdateDlg : public CDialogEx
{
// ����
public:
	CSoftwareUpdateDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CSoftwareUpdateDlg();
// �Ի�������
	enum { IDD = IDD_SOFTWAREUPDATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
