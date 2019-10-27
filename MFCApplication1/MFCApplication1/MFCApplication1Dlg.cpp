
// MFCApplication1Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_TAB1, m_table1);
  DDX_Control(pDX, IDC_TAB2, m_table2);
  DDX_Control(pDX, IDC_TAB3, m_table3);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序
#include "CUIThread.h"



BOOL CMFCApplication1Dlg::OnInitDialog()
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
  m_table1.ShowWindow(FALSE);
  m_table2.ShowWindow(FALSE);
  m_table3.ShowWindow(FALSE);
  /************************************************************************/
  /* 
  
  CTestDlg testdlg;
testdlg.Create(IDD_DIALOG_TEST);
CRect rc;
GetWindowRect(&rc);
rc.top += 23;
rc.bottom -= 8;
rc.left += 7;
rc.right -= 7;
testdlg.MoveWindow(&rc);
testdlg.ShowWindow(SW_SHOW);
  
  
  */
  /************************************************************************/
//   int i = 0;
//   CRect rc;
//   GetWindowRect(&rc);
//   rc.left += 30;
//   rc.right += 30;
//   rc.top += 23*(i+1);
//   rc.bottom -= 8*(i+1);
//   _cd.Create(IDD_DIALOG1, this);
//   _cd.MoveWindow(&rc);
//   _cd.ShowWindow(SW_SHOW);
//   _vcd.push_back(&_cd);
//   CChildDlg *d = new CChildDlg;
//   i = 1;
//   rc.top += 23 * (i + 1);
//   rc.bottom -= 8 * (i + 1);
//   d->Create(IDD_DIALOG1, this);
//   _cd.MoveWindow(&rc);
//   d->ShowWindow(SW_SHOW);
//   _vcd.push_back(d);

 // gddd = this;
  CRect rc;
  GetWindowRect(&rc);
  int top = rc.top;
  int bottom = rc.bottom;
  rc.left += 30;
  rc.right += 30;
  int boom = 60;
  int ttt = 30;
  for (int i = 0; i < 4; i++) {
    //CChildDlg *d = new CChildDlg;
    rc.top = boom * (i) + ttt;
    rc.bottom = boom * (i + 1) + ttt;
    //rc.bottom = bottom - 8 * (i + 1);
    //Init(d,&rc);
    //_vcd.push_back(d);
   // grc.push_back(rc);
    //CWinThread * cs = AfxBeginThread(RUNTIME_CLASS(CUIThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
   // cs->mes
    //CUIThread *ucs = (CUIThread*)cs;
    //ucs->uu.cwnd = GetSafeHwnd();
    //memcpy(&(ucs->uu.rc), &rc, sizeof(rc));

   // ucs->uuUIMyStruct{GetSafeHwnd(),rc };

    //auto sscs = cs->PostThreadMessageW(WM_TEST,0,(LPARAM)(s));
   // ::SendMessage(cs->Get,);
   // cs->ResumeThread();
    //v.push_back(cs);

//     if (i == 0) {
//       m_table1.InsertItem(0, "1");
//       CChildDlg *d = new CChildDlg;
//       Init(d, &rc, &m_table1);
//     }
//     else {
//       m_table2.InsertItem(0, "1");
//       CChildDlg *d = new CChildDlg;
//       Init(d, &rc, &m_table2);
//     }
//     else {
//     
//       m_table2.SetItemSize(CSize(0, 0));
//     }
    CTabCtrl *cb = new CTabCtrl();
   
      rc.left = 0;
      //rc.right = 170;
    
    //CRect rc;
    //GetClientRect(rc);
    cb->Create(WS_VISIBLE, rc, this, i);
    cb->SetItemSize(CSize(0, 0));
    //cb->SetItemSize(CSize(60, 20));
    //cb->InsertItem(0, "水 深 图");
    //cb->InsertItem(1, "卫星分布");

    CChildDlg *d = new CChildDlg;
    Init(d, &CRect{0,0,60,100}, cb);
    _ctb.push_back(cb);
  }
  //m_table3.SetItemSize(CSize(0, 0));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton2()
{
  // TODO: 在此添加控件通知处理程序代码
  //_vcd[0]->StartProgress();
}
