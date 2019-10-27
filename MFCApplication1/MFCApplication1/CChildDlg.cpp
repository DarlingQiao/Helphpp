// CChildDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "CChildDlg.h"
#include "afxdialogex.h"


// CChildDlg 对话框

IMPLEMENT_DYNAMIC(CChildDlg, CDialogEx)

CChildDlg::CChildDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialogEx)
  ON_BN_CLICKED(IDC_BUTTON1, &CChildDlg::OnBnClickedButton1)
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CChildDlg::OnNMCustomdrawProgress1)
  ON_BN_CLICKED(IDC_BUTTON2, &CChildDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CChildDlg 消息处理程序

#include <thread>
#include <chrono>
BOOL CChildDlg::OnInitDialog()
{
  //::SetWindowPos(GetSafeHwnd(), wndTopMost, 0, 0, 300, 100, SWP_SHOWWINDOW);
  //CenterWindow();



  CDialogEx::OnInitDialog();


  // TODO:  在此添加额外的初始化
  /*
  
   CWnd *pWnd;
    HWND hWnd;
    hWnd = pWnd->GetSafeHwnd();        //CWnd->HWND
    pWnd = CWnd::FromHandle(hWnd); //HWND->CWnd
  */
  
  /*
  std::thread([&] {
    m_progress.SetRange(0, 100);
    for (int i = 0; i < 100; i++) {
      //myProCtrl2->OffsetPos(1); //此句代码等同于下两句，以固定步长1更新显示，该功能也可以这样实现：myProCtrl2->SetPos(i); 
      m_progress.SetStep(1);
      m_progress.StepIt();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });*/
  return TRUE;  // return TRUE unless you set the focus to a control
                // 异常: OCX 属性页应返回 FALSE
}


void CChildDlg::OnBnClickedButton1()
{
  // TODO: 在此添加控件通知处理程序代码
  //SetWindowPos(xxxdlg.GetSafeHwnd(), …)
  MessageBox("测试");
}

void CChildDlg::StartProgress() {
  m_progress.SetRange(0, 100);
  //std::thread([&] {
    for (int i = 0; i < 100; i++) {
      //myProCtrl2->OffsetPos(1); //此句代码等同于下两句，以固定步长1更新显示，该功能也可以这样实现：myProCtrl2->SetPos(i); 
      m_progress.SetStep(1);
      m_progress.StepIt();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  //});
}


void CChildDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
  // TODO: 在此添加控件通知处理程序代码
  
  *pResult = 0;
}

#include "CUIThread.h"
void Change(LPVOID pParam)
{//下面的消息使得按钮闪烁三次 
  ((CChildDlg*)pParam)->StartProgress();
}


void CChildDlg::OnBnClickedButton2()
{
  // TODO: 在此添加控件通知处理程序代码
  //CWinThread* m_pThrd;
  //启动
  AfxBeginThread((AFX_THREADPROC)Change, (LPVOID)this, 0, 0, 0, 0);
}
