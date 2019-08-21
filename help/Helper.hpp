#ifndef HELPER_HPP
#define HELPER_HPP


#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <sstream>
#include <exception>

using byte = unsigned char;

/*
__FILE__ ������ǰ�����ļ������ַ���
__LINE__ ��ʾ��ǰ�кŵ�����
__DATE__ ������ǰ���ڵ��ַ���
__STDC__ �����������ѭANSI C��׼�������Ǹ�����ֵ
__TIME__ ������ǰʱ����ַ���
*/

//#define PRINTF(A,...) printf("%s %s[%-30.30s:%05d]"A,##__VA)
#define PRINTF(format,...) printf("[%-30.30s][%-30.30s][%05d] "format"\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#ifdef WIN32





#endif

namespace helper {
  class Herlper {

  public:
  

  public:
    /************************************************************************/
    /* 16��������ת16���Ƹ�ʽ�ַ���                              */
    /************************************************************************/
    inline static std::string Bytes2HexString(const std::vector<byte>& v) noexcept {
      return Bytes2HexString(v.data(),v.size());
    }

    inline static std::string Bytes2HexString(const byte *pbyte, std::size_t len) noexcept {
      std::string str = "";
      for (std::size_t i = 0; i != len; ++i) {
        std::array<char, 3> temp = { 0 };
        snprintf(temp.data(), temp.size(), "%02X", pbyte[i]);
        str += temp.data();
      }
      return str;
    }

    /************************************************************************/
    /* 16�����ַ���ת16��������ת                                        */
    /************************************************************************/
    inline static std::vector<byte> HexString2Bytes(const std::string& str) throw (std::length_error) {
      std::vector<byte> v;
      if (str.length() % 2 != 0) {
        throw std::length_error("Illegal string length");
      }
      for (std::size_t i = 0; i != str.length(); ++i) {
        std::array<char, 3> arr_hex = { str[i], str[++i] };
        unsigned int b = 0;
        sscanf(arr_hex.data(), "%x", &b);
        v.push_back(b);
      }
      return v;
    }


    inline static std::vector<std::string> split_with_null(const char* pstr) {
      std::vector<std::string> vRet;
      if (pstr == nullptr) {
        return vRet;
      }
      auto pbeg = pstr;
      auto pend = pstr;
      while (true) {
        if (*pend == 0x00) {
          vRet.push_back(std::string(pbeg, pend));
          pbeg = ++pend;
          if (*pend == 0x00) {
            break;
          }
        }
        ++pend;
      }
      return vRet;
    }



  };
}



#endif HELPER_HPP
