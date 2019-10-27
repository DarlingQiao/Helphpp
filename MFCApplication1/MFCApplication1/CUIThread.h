#pragma once

#include <windows.h>
#include "CChildDlg.h"


#define WM_TEST  WM_USER + 10

struct UIMyStruct
{
  HWND cwnd;
  CRect rc;
};


class CUIThread : public CWinThread {
  DECLARE_DYNCREATE(CUIThread)
private:
  CChildDlg * dlg;
protected:

  afx_msg void OnMessage(WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()
public:
  CUIThread();
  virtual ~CUIThread();
  BOOL InitInstance(HWND pParentWnd, CRect* rc) {
    CWnd* pParent = CWnd::FromHandle(pParentWnd);
    dlg = new CChildDlg(pParent);//声明一个对话框类
    dlg->Create(129, pParent);
    dlg->MoveWindow(rc);
    dlg->ShowWindow(SW_SHOW);
    dlg->RunModalLoop();//调用这个方法,把他变成一个模态对话框形式的
    return FALSE;//这里需要返回false，不然线程就不会关闭的
  }
  virtual BOOL InitInstance() {


    InitInstance(uu.cwnd,&uu.rc);
    return FALSE;//这里需要返回false，不然线程就不会关闭的
  }





  virtual int ExitInstance() {
  
    return CWinThread::ExitInstance();
  }

  UIMyStruct uu;

};

