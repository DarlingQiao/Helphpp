#pragma once
#include <vector>
#include <array>
#include <cstddef>
class SortingAlgorithm {
public:
  
  /************************************************************************/
  /*                         ����                                             */
  /************************************************************************/
  template <typename T> static void Swap(T& t1, T& t2) {
    T t = t1;
    t1 = t2;
    t2 = t;
  }

//   template <typename T> static void Swap(T* t1, T* t2) {
//     T t = *t1;
//     *t1 = *t2;
//     *t2 = t;
//   }

//   template<typename T> auto pow(T x, size_t y) -> decltype() {
//     for()
//   }

  /************************************************************************/
  /*      ����EPSINON ��������������ȣ���                                                                */
  /************************************************************************/
  template<typename T> static bool Zero(T x/*,size_t eps = 6*/) {
    if (typeid(T) == typeid(float)) {
      float EPSINON = 1e-6;
      return (x >= -EPSINON) && (x <= EPSINON);
    } else if (typeid(T) == typeid(double)) {
      double EPSINON = 1e-13;
      return (x >= -EPSINON) && (x <= EPSINON);
    }
    throw std::runtime_error("0ֵ�ȽϺ������Ͳ�ƥ��");
  }


  
  /************************************************************************/
  /*                 ð������                                             */
  /*�Ƚ����ڵ�Ԫ�ء������һ���ȵڶ����󣬾ͽ�������������
    ��ÿһ������Ԫ����ͬ���Ĺ������ӿ�ʼ��һ�Ե���β�����һ�ԣ�����������Ԫ��Ӧ�û�����������
    ������е�Ԫ���ظ����ϵĲ��裬�������һ����
    �ظ�����1~3��ֱ��������ɡ�*/
  /************************************************************************/
  static void BubbleSort(int arr[],size_t len) {
    if (!arr || len == 0 || len == 1) return;
    for (auto i = 0; i < len - 1; i++) {
      for (auto j = 0; j < len - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          Swap(arr[j], arr[j + 1]);
        }
      }
    }
  }
    
  static void BubbleSort(std::vector<int>& v) noexcept {
    BubbleSort(v.data(),v.size());
  }

  /************************************************************************/
  /*                    ѡ������ (Ĭ������)                               */
  /*n����¼��ֱ��ѡ������ɾ���n - 1��ֱ��ѡ������õ��������������㷨�������£�
    ��ʼ״̬��������ΪR[1..n]��������Ϊ�գ�
    ��i������(i = 1, 2, 3��n - 1)��ʼʱ����ǰ���������������ֱ�ΪR[1..i - 1]��R(i..n������������ӵ�ǰ�������� - ѡ���ؼ�����С�ļ�¼ R[k]���������������ĵ�1����¼R������ʹR[1..i]��R[i + 1..n)�ֱ��Ϊ��¼��������1�������������ͼ�¼��������1��������������
    n - 1�˽��������������ˡ�*/
  /************************************************************************/
  static void SelectionSort(int arr[], size_t len,bool desc = false) {
    if (!arr || len == 0 || len == 1) return;
    size_t temp = 0;
    for (auto i = 0; i < len - 1; i++) {
      temp = i;
      for (auto j = i + 1; j < len; j++) {
        if (desc) {
          if (arr[j] > arr[temp]) {
            Swap(arr[j],arr[temp]);//�����
          }
        } else {
          if (arr[j] < arr[temp]) {
            Swap(arr[j], arr[temp]); //��С��
          }
        }
      }
    }
  }

  static void SelectionSort(std::vector<int>& v,bool desc) noexcept {
    SelectionSort(v.data(), v.size(), desc);
  }


  /************************************************************************/
  /*             ��������                                           */
  /************************************************************************/
  static void QuickSort(int arr[],size_t left,size_t right) {
    /*if (left < right) {
      auto i = left, j = right;
      auto x = arr[left];
      while (i < j) {
        while (i < j && arr[j] >= x) // ���������ҵ�һ��С��x����
          j--;
        if (i < j)
          arr[i++] = arr[j];

        while (i < j && arr[i] < x) // ���������ҵ�һ�����ڵ���x����
          i++;
        if (i < j)
          arr[j--] = arr[i];
      }
      arr[i] = x;
      QuickSort(arr, left, i - 1); // �ݹ���� 
      QuickSort(arr, i + 1, right);
    }*/
  }

};