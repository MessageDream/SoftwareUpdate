
// SoftwareUpdateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SoftwareUpdate.h"
#include "SoftwareUpdateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

//Timer
const int nUpdateSpeedInfo=1;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSoftwareUpdateDlg �Ի���




CSoftwareUpdateDlg::CSoftwareUpdateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSoftwareUpdateDlg::IDD, pParent)
	, m_hEvtExitUpdate(NULL)
	, m_llTimeCount(0)
	, m_bIsUpdateSuccess(false)
	, m_nRetryTimes(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CSoftwareUpdateDlg::~CSoftwareUpdateDlg()
{
	WaitForSingleObject(m_hEvtExitUpdate, INFINITE);
	if(m_hEvtExitUpdate!=NULL)
	{
		CloseHandle(m_hEvtExitUpdate);
		m_hEvtExitUpdate=NULL;
	}
}

void CSoftwareUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_UPDATE, m_progressUpdate);
	DDX_Control(pDX, IDC_BUTTON_RETRY, m_btnRetry);
}

BEGIN_MESSAGE_MAP(CSoftwareUpdateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MSGRECVPRO, &CSoftwareUpdateDlg::OnMsgrecvpro)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RETRY, &CSoftwareUpdateDlg::OnBnClickedButtonRetry)
	ON_BN_CLICKED(IDCANCEL, &CSoftwareUpdateDlg::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CSoftwareUpdateDlg ��Ϣ�������

BOOL CSoftwareUpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_progressUpdate.SetRange(0,100); 
	m_progressUpdate.SetPos(0);
	SetDlgItemText(IDC_EDIT_UPDATE,_T("Loading..."));
	m_hEvtExitUpdate=CreateEvent(NULL,TRUE,TRUE,NULL);
	while(AfxBeginThread(UpdateThreadFunc,(LPVOID)this)==NULL);
	SetTimer(nUpdateSpeedInfo,1000,NULL);
	m_btnRetry.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSoftwareUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSoftwareUpdateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSoftwareUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CSoftwareUpdateDlg::OnMsgrecvpro(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case MSGUSER_UPDATERESULT:
	{
		if (!wParam)
		{
			m_bIsUpdateSuccess = true;
			BOOL nDelRst = ::DeleteFile(g_sz_strParameter[2]);
			while (!nDelRst)
			{
				int nRtn = AfxMessageBox(_T("�������ʧ��,��ȷ��Ӧ�ó����Ƿ�ر�!"), MB_RETRYCANCEL);
				if (nRtn == IDCANCEL)
					break;
				else
					nDelRst = ::DeleteFile(g_sz_strParameter[2]);
			}
			if (nDelRst)
				CFile::Rename(g_sz_strParameter[2] + _T("temp"), g_sz_strParameter[2]);
			else
				::DeleteFile(g_sz_strParameter[2] + _T("temp"));
			ShellExecute(0, _T("open"), g_sz_strParameter[2], NULL, NULL, SW_SHOWNORMAL);
			PostMessage(WM_CLOSE);
		}
		else
		{
			++m_nRetryTimes;
			if(m_nRetryTimes<=5)
				while (AfxBeginThread(UpdateThreadFunc, (LPVOID)this) == NULL);
			else
			{
				m_nRetryTimes = 0;
				KillTimer(nUpdateSpeedInfo);
				SetDlgItemText(IDC_EDIT_UPDATE, _T("����ʧ��!"));
				m_btnRetry.EnableWindow(TRUE);
			}
		}
	}
	break;
	}
	return 0;
}

UINT CSoftwareUpdateDlg::UpdateThreadFunc(LPVOID lpParam)
{
	CSoftwareUpdateDlg* pMainDlg = (CSoftwareUpdateDlg *)lpParam;
	ResetEvent(pMainDlg->m_hEvtExitUpdate);
	CString strDataIn,strHead,strPath,strLength,strFinish,strCurTimes;
	strHead.Format(_T("[%06d01]"),strDataIn.GetLength()+10);
	strDataIn=strHead+strDataIn;
	int nRtn=0;
	nRtn=pMainDlg->m_filesock.Connect(g_sz_strParameter[0],g_sz_strParameter[1]);
	if (nRtn)
	{
		SendMessageTimeout(pMainDlg->m_hWnd, WM_MSGRECVPRO, (WPARAM)nRtn, MSGUSER_UPDATERESULT, SMTO_BLOCK, 500, NULL);
		SetEvent(pMainDlg->m_hEvtExitUpdate);
		return 0;
	}
	nRtn=pMainDlg->m_filesock.StringSend(strDataIn);
	if(nRtn)
	{
		SendMessageTimeout(pMainDlg->m_hWnd, WM_MSGRECVPRO, (WPARAM)nRtn, MSGUSER_UPDATERESULT, SMTO_BLOCK, 500, NULL);
		SetEvent(pMainDlg->m_hEvtExitUpdate);
		return 0;
	}
	strPath=g_sz_strParameter[2]+_T("temp");
	pMainDlg->m_filesock.SetFilePath(strPath);
	ULONGLONG llLength=0;
	nRtn=pMainDlg->m_filesock.StringRecv(strLength);
	if(nRtn)
		goto end;
	llLength=_ttoi64(strLength);
	pMainDlg->m_filesock.SetFileLength(llLength);
	strCurTimes.Format(_T("%lld"), pMainDlg->m_filesock.GetCurTimes());
	nRtn=pMainDlg->m_filesock.StringSend(strCurTimes);
	if(nRtn)
		goto end;
	nRtn=pMainDlg->m_filesock.FileRecv();
end:
	pMainDlg->m_filesock.StringRecv(strFinish);
	SendMessageTimeout(pMainDlg->m_hWnd,WM_MSGRECVPRO,(WPARAM)nRtn, MSGUSER_UPDATERESULT,SMTO_BLOCK,500,NULL);
	SetEvent(pMainDlg->m_hEvtExitUpdate);
	return 0;
}

void CSoftwareUpdateDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case nUpdateSpeedInfo:
		{
			++m_llTimeCount;
			ULONGLONG llFileLength,llCurTimes,llTotalTimes;
			int nBuf;
			llFileLength=m_filesock.GetFileLength();
			llCurTimes=m_filesock.GetCurTimes();
			llTotalTimes=m_filesock.GetTotalTimes();
			nBuf=m_filesock.GetBuf();
			if(llFileLength&&llTotalTimes)
			{
				if(llCurTimes==llTotalTimes)
					KillTimer(nUpdateSpeedInfo);
				CString strSpeed,strLeftTime,strShowInfo;
				ULONGLONG llSpeed,llLeftTime;
				if(llCurTimes<llTotalTimes)
					llSpeed=llCurTimes*nBuf/m_llTimeCount;
				else
					llSpeed=llFileLength/m_llTimeCount;
				if(llSpeed/1048576>0)
					strSpeed.Format(_T("%.2fMB/s"),llSpeed/1048576.0);
				else if(llSpeed/1024>0)
					strSpeed.Format(_T("%.2fKB/s"),llSpeed/1024.0);
				else
					strSpeed.Format(_T("%.2fB/s"),double(llSpeed));
				if(llCurTimes<llTotalTimes&&llSpeed)
					llLeftTime=(llFileLength-llCurTimes*nBuf)/llSpeed;
				else
					llLeftTime=0;
				strLeftTime.Format(_T("%02lld:%02lld:%02lld"),llLeftTime/3600,(llLeftTime%3600)/60,(llLeftTime%3600)%60);
				strShowInfo=strSpeed+_T(" ")+strLeftTime;
				SetDlgItemText(IDC_EDIT_UPDATE,strShowInfo);
				int nProgress=int(llCurTimes*100/llTotalTimes);
				m_progressUpdate.SetPos(nProgress);
			}
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSoftwareUpdateDlg::OnBnClickedButtonRetry()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_UPDATE,_T("Loading..."));
	while(AfxBeginThread(UpdateThreadFunc,(LPVOID)this)==NULL);
	SetTimer(nUpdateSpeedInfo,1000,NULL);
	m_btnRetry.EnableWindow(FALSE);
}


void CSoftwareUpdateDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bIsUpdateSuccess)
	{
		if(IDOK ==AfxMessageBox(_T("ȷ��Ҫ��ֹ���£�"),MB_OKCANCEL))
		{
			m_filesock.StopComm();
			WaitForSingleObject(m_hEvtExitUpdate, INFINITE);
			::DeleteFile(g_sz_strParameter[2]+_T("temp"));
		}
		else
			return;
	}
	CDialogEx::OnCancel();
}


BOOL CSoftwareUpdateDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_BKGND);
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap * p_bmpOld=dcMem.SelectObject(&bmp);
	BITMAP bmpInfo;
	bmp.GetBitmap(&bmpInfo);
	CRect rc; 
	GetClientRect(&rc);
	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,SRCCOPY);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(0,0,rc.Width(),rc.Height(),&dcMem,0,0,bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);
	dcMem.SelectObject(p_bmpOld);
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
