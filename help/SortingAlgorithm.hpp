#pragma once
#include <vector>
#include <array>
#include <cstddef>
class SortingAlgorithm {
public:
  
  /************************************************************************/
  /*                         交换                                             */
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
  /*      其中EPSINON 是允许的误差（即精度）。                                                                */
  /************************************************************************/
  template<typename T> static bool Zero(T x/*,size_t eps = 6*/) {
    if (typeid(T) == typeid(float)) {
      float EPSINON = 1e-6;
      return (x >= -EPSINON) && (x <= EPSINON);
    } else if (typeid(T) == typeid(double)) {
      double EPSINON = 1e-13;
      return (x >= -EPSINON) && (x <= EPSINON);
    }
    throw std::runtime_error("0值比较函数类型不匹配");
  }


  
  /************************************************************************/
  /*                 冒泡排序                                             */
  /*比较相邻的元素。如果第一个比第二个大，就交换它们两个；
    对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
    针对所有的元素重复以上的步骤，除了最后一个；
    重复步骤1~3，直到排序完成。*/
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
  /*                    选择排序 (默认升序)                               */
  /*n个记录的直接选择排序可经过n - 1趟直接选择排序得到有序结果。具体算法描述如下：
    初始状态：无序区为R[1..n]，有序区为空；
    第i趟排序(i = 1, 2, 3…n - 1)开始时，当前有序区和无序区分别为R[1..i - 1]和R(i..n）。该趟排序从当前无序区中 - 选出关键字最小的记录 R[k]，将它与无序区的第1个记录R交换，使R[1..i]和R[i + 1..n)分别变为记录个数增加1个的新有序区和记录个数减少1个的新无序区；
    n - 1趟结束，数组有序化了。*/
  /************************************************************************/
  static void SelectionSort(int arr[], size_t len,bool desc = false) {
    if (!arr || len == 0 || len == 1) return;
    size_t temp = 0;
    for (auto i = 0; i < len - 1; i++) {
      temp = i;
      for (auto j = i + 1; j < len; j++) {
        if (desc) {
          if (arr[j] > arr[temp]) {
            Swap(arr[j],arr[temp]);//最大数
          }
        } else {
          if (arr[j] < arr[temp]) {
            Swap(arr[j], arr[temp]); //最小数
          }
        }
      }
    }
  }

  static void SelectionSort(std::vector<int>& v,bool desc) noexcept {
    SelectionSort(v.data(), v.size(), desc);
  }


  /************************************************************************/
  /*             快速排序                                           */
  /************************************************************************/
  static void QuickSort(int arr[],size_t left,size_t right) {
    /*if (left < right) {
      auto i = left, j = right;
      auto x = arr[left];
      while (i < j) {
        while (i < j && arr[j] >= x) // 从右向左找第一个小于x的数
          j--;
        if (i < j)
          arr[i++] = arr[j];

        while (i < j && arr[i] < x) // 从左向右找第一个大于等于x的数
          i++;
        if (i < j)
          arr[j--] = arr[i];
      }
      arr[i] = x;
      QuickSort(arr, left, i - 1); // 递归调用 
      QuickSort(arr, i + 1, right);
    }*/
  }

};