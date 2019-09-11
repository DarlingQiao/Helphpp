#pragma once

#include <string>
#include <wtypes.h>
#include <map>

using namespace std;

#define  MEMORYSIZE 102400000 //每块内存的大小

struct MemoryAddr {
  string StrName;
  LPVOID pBuffer;
  HANDLE m_Handle;
};

class SharedMemory
{
public:
  SharedMemory(void);
  ~SharedMemory(void);
public:
  string strMapName;                // 内存映射对象名称
  string strComData;        // 共享内存中的数据
  int MemoeryNum; //开辟内存数

  map<int, MemoryAddr>MemoryInfo;

  LPVOID Init(string MeName);
  void   IntPutData(string MeName, string str);
  string OutPutData(string MeName);
  string GetAllData();
};



SharedMemory::SharedMemory(void)
{
  MemoeryNum = 0;
}

SharedMemory::~SharedMemory(void)
{
  map<int, MemoryAddr>::iterator it;

  for (it = MemoryInfo.begin(); it != MemoryInfo.end(); it++)
  {
    ::UnmapViewOfFile(it->second.pBuffer);
    ::CloseHandle(it->second.m_Handle);
  }

  MemoryInfo.clear();
}

LPVOID SharedMemory::Init(string MeName)
{
  MemoryAddr mMemoryAddr;
  LPVOID pBuffer;
  // 首先试图打开一个命名的内存映射文件对象  
  HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0,(LPCWSTR) MeName.c_str());

  if (NULL == hMap)
  {    // 打开失败，创建之
    hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEMORYSIZE, (LPCWSTR)MeName.c_str());
    // 映射对象的一个视图，得到指向共享内存的指针，设置里面的数据
    pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  }
  else
  {    // 打开成功，映射对象的一个视图，得到指向共享内存的指针，显示出里面的数据
    pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  }

  mMemoryAddr.StrName = MeName.c_str();
  mMemoryAddr.pBuffer = pBuffer;
  mMemoryAddr.m_Handle = hMap;

  MemoryInfo.insert(pair<int, MemoryAddr>(MemoeryNum, mMemoryAddr));

  MemoeryNum++;

  return pBuffer;
}

void SharedMemory::IntPutData(string MeName, string str)
{
  map<int, MemoryAddr>::iterator itr;
  for (itr = MemoryInfo.begin(); itr != MemoryInfo.end(); itr++)
  {
    if (MeName == itr->second.StrName)
    {
      strcpy((char*)itr->second.pBuffer, str.c_str());
    }
  }
}

std::string SharedMemory::OutPutData(string MeName)
{
  map<int, MemoryAddr>::iterator iter;

  for (iter = MemoryInfo.begin(); iter != MemoryInfo.end(); iter++)
  {
    if (iter->second.StrName == MeName)
    {
      return (char*)iter->second.pBuffer;
    }
  }
}

std::string SharedMemory::GetAllData()
{
  string str = "";
  map<int, MemoryAddr>::iterator ir;
  for (ir = MemoryInfo.begin(); ir != MemoryInfo.end(); ir++)
  {
    string strTemp = "";
    strTemp.append(ir->second.StrName);
    strTemp.append(":");
    strTemp.append((char*)ir->second.pBuffer);
    str.append(strTemp.c_str());
    str.append(",");
  }
  return str;
}