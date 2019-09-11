#pragma once

#include <string>
#include <wtypes.h>
#include <map>

using namespace std;

#define  MEMORYSIZE 102400000 //ÿ���ڴ�Ĵ�С

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
  string strMapName;                // �ڴ�ӳ���������
  string strComData;        // �����ڴ��е�����
  int MemoeryNum; //�����ڴ���

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
  // ������ͼ��һ���������ڴ�ӳ���ļ�����  
  HANDLE hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0,(LPCWSTR) MeName.c_str());

  if (NULL == hMap)
  {    // ��ʧ�ܣ�����֮
    hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, MEMORYSIZE, (LPCWSTR)MeName.c_str());
    // ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬�������������
    pBuffer = ::MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
  }
  else
  {    // �򿪳ɹ���ӳ������һ����ͼ���õ�ָ�����ڴ��ָ�룬��ʾ�����������
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