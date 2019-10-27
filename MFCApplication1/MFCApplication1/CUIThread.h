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
    dlg = new CChildDlg(pParent);//����һ���Ի�����
    dlg->Create(129, pParent);
    dlg->MoveWindow(rc);
    dlg->ShowWindow(SW_SHOW);
    dlg->RunModalLoop();//�����������,�������һ��ģ̬�Ի�����ʽ��
    return FALSE;//������Ҫ����false����Ȼ�߳̾Ͳ���رյ�
  }
  virtual BOOL InitInstance() {


    InitInstance(uu.cwnd,&uu.rc);
    return FALSE;//������Ҫ����false����Ȼ�߳̾Ͳ���رյ�
  }





  virtual int ExitInstance() {
  
    return CWinThread::ExitInstance();
  }

  UIMyStruct uu;

};

