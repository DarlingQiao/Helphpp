#include "stdafx.h"
#include "CUIThread.h"

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)
CUIThread::CUIThread()
{
}


CUIThread::~CUIThread()
{
  if (dlg) {
    delete dlg;
    dlg = nullptr;
  }
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
  ON_THREAD_MESSAGE(WM_TEST, OnMessage)
END_MESSAGE_MAP()


void CUIThread::OnMessage(WPARAM wParam, LPARAM lParam) {
  UIMyStruct * s = (UIMyStruct*)lParam;
  InitInstance(s->cwnd,&(s->rc));
}