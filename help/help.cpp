// help.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include "ShareMemory.hpp"
#include <vector>
#include "te.h"

#include "Socket.hpp"
class MyStruct {
public:
  std::vector<char> v;
  int a;
  char data[1024];

  //void get() {}

  //u uu;
};

#include "SortingAlgorithm.hpp"

int main()
{
#if 0
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
#endif


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



  net::Socket::StartUp();
 
  std::string in;


  while (std::cin >> in) {
    if (in == "q") {
      break;
    }
    net::SocketWin t("127.0.0.1", 9527, AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::error_code ec;
    unsigned long cc = 0;
    std::cout << t.Create(ec) << std::endl;
    std::cout << t.Control(FIONBIO, &cc, ec) << "##" << cc << std::endl;
    std::cout <<"connect" << t.Connect(ec) << std::endl;
    
    char tp[1000] = { 0 };
    std::size_t a = 0;
    std::cout << "w " << t.Write(in.data(), in.length(), a, ec) << "## " << a << std::endl;
    std::cout << "r " << t.Read(tp, sizeof(tp), a, ec) << "## " << a << std::endl;
    std::cout << "c "  << t.Close(ec) << "## " << a << std::endl;
    std::cout << tp << std::endl;
  }









#if 0
  while (std::cin >> in) {
    if (in == "q") {
      break;
    } else if (in == "1") {
      net::SocketWin t("127.0.0.1", 9528, AF_INET, SOCK_STREAM, IPPROTO_TCP);
      std::error_code ec;
      unsigned long cc = 0;
      std::cout << t.Create(ec) << std::endl;
      std::cout << t.Bind(ec) << std::endl;
      std::cout << t.Listen(1, ec) << std::endl;
      char tp[1000] = { 0 };
      std::size_t a = 0;
      while (std::cin >> in) {
        if (in == "q") {
          break;
        }
        std::cout << t.Accept((int*)&a, ec) << "##" << cc << std::endl;
        std::cout << t.Read(tp, sizeof(tp), a, ec) << "## " << a << std::endl;
        std::cout << t.Write(in.data(), in.length(), a, ec) << std::endl;
        std::cout << t.Close(ec) << "## " << a << std::endl;
        std::cout << tp << std::endl;
      }
      
    } else if (in == "2") {
      net::SocketWin t("127.0.0.1", 9527, AF_INET, SOCK_STREAM, IPPROTO_TCP);
      std::error_code ec;
      unsigned long cc = 0;
      std::cout << t.Create(ec) << std::endl;
      while (std::cin >> in) {
        if (in == "q") {
          break;
        }
        std::cout << t.Connect(ec) << std::endl;
        std::cout << t.Control(FIONBIO, &cc, ec) << "##" << cc << std::endl;
        char tp[1000] = { 0 };
        std::size_t a = 0;
        std::cout << t.Write(in.data(), in.length(), a, ec) << std::endl;
        std::cout << t.Read(tp, sizeof(tp), a, ec) << "## " << a << std::endl;
        std::cout << t.Close(ec) << "## " << a << std::endl;
        std::cout << tp << std::endl;
      }
    }

  }
#endif
  net::Socket::ClearUp();
  return 0;
}



