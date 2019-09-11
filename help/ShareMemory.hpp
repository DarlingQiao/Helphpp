#pragma once

#include <iostream>
#include <system_error>
#include <string>
#include <cstddef>
#include <atomic>

std::atomic_flag a;

class A {
protected:
  void* a;
  std::string sc;

public:
  int get() {
    return 1;
  }
};

class B : public A {
public:
  B():A() {
    a = nullptr;
    sc = "344344";
    std::cout << sc << std::endl;
  }
  int f() {
    a = nullptr;
    return get();
  }
};

class ShareMemoryInterface {
protected:
  std::string name_;
  void * ptr_;
  void * handle_;
public:
  explicit ShareMemoryInterface(const std::string& name) : name_(name),ptr_(nullptr),handle_(nullptr) {};
  ShareMemoryInterface() = delete;
  ShareMemoryInterface(const ShareMemoryInterface&) = delete;
  ShareMemoryInterface(ShareMemoryInterface&&) = delete;
  ShareMemoryInterface& operator=(const ShareMemoryInterface&) =  delete;
  ~ShareMemoryInterface() { };
public:
  std::string GetShareMemoryName() {
    return name_;
  }

  void * getPtr() {
    return ptr_;
  }
public:
  virtual std::error_code Init(std::error_code& ec) = 0;
  virtual void Close() = 0;
  //virtual void * Data() = 0;

//   virtual std::error_code Input(std::error_code& ec) { return ec; };
//   virtual std::error_code Output(std::error_code& ec) { return ec; };
 




};

#include <windows.h>
template <class T> class ShareMemoryWindows : public ShareMemoryInterface {
private:
//   T * ptr_;
//   HANDLE handle_;
public:
  explicit ShareMemoryWindows(const std::string& name) : ShareMemoryInterface(name)/*,
                                                         ptr_(nullptr),handle_(nullptr)*/ {
    std::cout << name_ << std::endl;
  };
  virtual ~ShareMemoryWindows() { Close(); };

  std::error_code Init(std::error_code& ec) override {
    ec.clear();
    if (handle_) {
      return ec;
    }
    handle_ = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, (LPCWSTR)GetShareMemoryName().c_str());
    if (!handle_) {
      handle_ = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, Size(), (LPCWSTR)GetShareMemoryName().c_str());
      if (!handle_) {
        return ec = std::error_code(::GetLastError(),std::system_category());
      }
    }
    ptr_ = (T*)::MapViewOfFile(handle_, FILE_MAP_ALL_ACCESS,0, 0, 0);
    if (!ptr_) {
      Close();
      return ec = std::error_code(::GetLastError(),std::system_category());
    }
    return ec;
  }

  void Close() override { 
    if (ptr_) {
      ::UnmapViewOfFile(ptr_);
      ptr_ = nullptr;
    }
    if (handle_) {
      ::CloseHandle(handle_);
      handle_ = nullptr;
    }
  };

  T *Data() {
    return (T*)getPtr();
  }

  auto Size() -> decltype(sizeof(T)) {
    return sizeof(T);
  }
};





// template <typename T> class ShareMemory : public ShareMemoryBase<T> {
// public:
//   ShareMemory() {};
//   ~ShareMemory() {};
// 
//   std::error_code Init(std::error_code& ec) {
//     return ec;
//   }
// 
//   std::error_code Init(std::error_code& ec) override { return ec; };
//   std::error_code Close(std::error_code& ec) override { return ec; };
// };

