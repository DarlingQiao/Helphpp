// help.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include "ShareMemory.hpp"
#include <vector>
#include "te.h"


class MyStruct {
public:
  std::vector<char> v;
  int a;
  char data[1024];

  //void get() {}

  //u uu;
};

#include "SortingAlgorithm.h"

int main()
{
  float z = 0.0;
  auto asdsdc = SortingAlgorithm::Zero(z);

  if (z == 0) {
    printf("\n");
  }
     
  int ab = 2;
  int cd = 3;
  SortingAlgorithm::Swap(ab, cd);
  int aa[] = { 1,2,3,4,5,0,100,78,190,455,12,0 };
  int aa1[] = { 1,2,3,4,5,0,100,78,190,455,12,0 };
  int aaa[12] = { 0 };
  std::cout << sizeof(aa) << "| " << sizeof(aaa) << std::endl;
  SortingAlgorithm::BubbleSort(aa,sizeof(aa)/sizeof(int));
  SortingAlgorithm::SelectionSort(aa1,sizeof(aa1)/ sizeof(int));
  SortingAlgorithm::SelectionSort(aa1,sizeof(aa1)/ sizeof(int),true);
  SortingAlgorithm::QuickSort(aa1,0, sizeof(aa1) / sizeof(int) - 1);

  SharedMemory sh;
  sh.Init("2223");
  std::string in;
  while (std::cin >> in)
  {
    if (in == "q") {
      break;
    }
    std::cout << sh.OutPutData("2223") << std::endl;
  }



#if 0
  B b;
  auto s = b.f();
  s = b.get();
  MyStruct my;
 // my.v.


  char t[120] = { 0 };
  ShareMemoryWindows<MyStruct> w("1");
  std::cout << w.GetShareMemoryName();
  std::error_code ec;
  w.Init(ec);
  std::string c;
  while (std::cin >> c) {
    if (c == "q")
    {
      break;
    }
    auto p = w.Data();
    char * spp = (char*) p->data;
    char t[1024] = { 0 };
    memcpy(t,spp,p->a);
    std::cout << "\n" << p << " | " << p->data << " | " << std::string(t)  << std::endl;
    
    //std::cout <<  << std::endl;
  }
  return 0;
  int i = 0;
  while (std::cin >> c) {
    if (c == "q")
    {
      break;
    }
    auto p = w.Data();
    std::cout << "\n" << p << " | " << p->data << std::endl;
    auto da = new char[c.length() + 1];
    int s1s = sizeof(da);
    memset(da,0,c.length() + 1);
    std::cout << da << std::endl;
    strncpy_s(da, c.length()+1,c.c_str(),c.length());
    p->a = c.length() + 1;
    //p->data = da;
    memcpy(&p->data,da,c.length() + 1);
    //p->uu.p = da;
    p->v.push_back(0x10);
    std::cout << p << " | " << p->data << " | " << std::endl;
  }
 
#endif
  return 0;
}

