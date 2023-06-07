#include <iostream>
#include <vector>
#include <algorithm>
#include "ctime"
using namespace std;
int Q = 80;

static inline uint64_t rdtsc()
{
    uint32_t low, high;
    asm volatile ("rdtsc" : "=a" (low), "=d" (high));
    return ((uint64_t)high << 32) | low;
}

int QuickSelect(int *arr, int k,int Size) {
    for(int low = 0, high = Size - 1; low < high; ) {
        int i = low, j = high, pivot = arr[low]; //随机选取pivot，这里选第一个
        while(i < j) {
            while(i < j && arr[j] >= pivot) j--; //从右向左找第一个小于pivot的数
            if(i < j) arr[i++] = arr[j]; //将该数移到低端
            while(i < j && arr[i] <= pivot) i++; //从左向右找第一个大于pivot的数
            if(i < j) arr[j--] = arr[i]; //将该数移到高端
        }
        arr[i] = pivot; // 将pivot的坑填上
        if(i == k) break;
        else if(i < k) low = i + 1; //在右边找第k大的数
        else high = i - 1; //在左边找
    }
    return arr[k];
}

int LinearSelect(int *arr, int k ,int size) {
    if(size < Q) return QuickSelect(arr, k, size); // 递归基

    int *medians = new int[size / Q]; // 分割成Q大小的子数组
    for(int i = 0; i < size / Q; i++) {
        int *subarr = new int[Q];
        for(int j = 0; j < Q; j++) {
            subarr[j] = arr[i * Q + j];
        }
        medians[i] = QuickSelect(subarr, Q / 2, Q); // 找到每组的中位数
    }

    int median = LinearSelect(medians, size / Q / 2, size / Q); // 递归找到中位数的中位数
    // 分成了三组：小于中位数的，大于中位数的，等于的没有存储
    int *low = new int[size];
    int *high = new int[size];
    int lowSize = 0, highSize = 0;
    for(int i = 0; i < size; i++) {
        if(arr[i] < median) low[lowSize++] = arr[i];
        else if(arr[i] > median) high[highSize++] = arr[i];
    }
    int res = median;
    if(k < lowSize) res = LinearSelect(low, k, lowSize); // 递归找到第k大的数
    else if(k >= size - highSize) res = LinearSelect(high, k - (size - highSize), highSize);
    delete[] low;
    delete[] high;
    delete[] medians;
    return res;
}
int main() {
    srand(time(nullptr));
    int n = 100000;
    uint64_t start, end;

    vector<int> *vec =  new vector<int>;
    vector<int> *vec_rand =  new vector<int>;
    for (int i = 0; i < n; ++i) {
        vec->push_back(i);
        vec_rand->push_back(i);
    }
    random_shuffle(vec_rand->begin(), vec_rand->end());
    int *arr = new int[n];
    int *arr_rand = new int[n];
    for(int i = 0; i < n; i++) {
        arr[i] = (*vec)[i];
        arr_rand[i] = (*vec_rand)[i];
    }
    cout<<"Sequence Case: n = "<<n<<endl;
    start = rdtsc();
    int res = LinearSelect(arr, n / 2, n);
    end = rdtsc();
    cout << "LinearSelect: res = " << res << "  time cost =" <<(end - start) << endl;
    start = rdtsc();
//    res = QuickSelect(arr, n / 2, n);
    end = rdtsc();
    cout << "QuickSelect: res = " << res << "  time cost =" << (end - start) << endl;
    cout<<"Random Case: n = "<<n<<endl;
    start = rdtsc();
    res = LinearSelect(arr_rand, n / 2, n);
    end = rdtsc();
    cout << "LinearSelect: res = " << res << "  time cost =" <<(end - start) << endl;
    start = rdtsc();
    res = QuickSelect(arr_rand, n / 2, n);
    end = rdtsc();
    cout << "QuickSelect: res = " << res << "  time cost =" << (end - start)  << endl;


    delete vec;
    delete vec_rand;
    delete[] arr;
    delete[] arr_rand;
    return 0;
}
