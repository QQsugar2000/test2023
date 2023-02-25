#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

void bitonicMerge(float *arr, int len, bool up) {
    if (len > 1) {
        int m = 1; //m是小于len的2的最大幂次
        while (m<len)
        {
           m = m<<1;
        }
        m = m>>1;
        for (int i = 0; i < len - m; ++i) {
            if (arr[i] > arr[i + m] == up){
                float temp = arr[i];
                arr[i] = arr[i+m];
                arr[i+m] = temp;
            }
        }
        bitonicMerge(arr, m, up); 
        bitonicMerge(arr + m, len - m, up);
    }
}

// 对任意长度的序列进行递归双调排序
void bitonicSort(float *a, int len, bool up) { // up控制升序
    if (len > 1) {
        int m = len / 2;
        bitonicSort(a, m, !up); // 前半段降序排列
        bitonicSort(a + m, len - m, up); // 后半段升序排列
        bitonicMerge(a, len, up);//归并处理
    }
}

//对指定的输入格式进行分段的双调排序
void segmentedBitonicSort(float* data, int* seg_id, int* seg_start, int n, int m) {
    for (int i = 0; i < m; i++) {
        int start = seg_start[i];
        int end = seg_start[i+1];
        int size = end - start;
        bitonicSort(data+start,size,1);
    }
}
// void hBitonicSort(float* a, int n, bool descending)
// {
//     float t = 0;
//     int half_stride = 1, hs = 1, s = 2;
//     int hn = n >> 1;
//     for (int stride = 2; stride <= n; stride <<= 1)
//     {
//         s = stride;
//         while (s >= 2)
//         {
//             hs = s >> 1;
//             for (int i = 0; i < hn; i++)
//             {
//                 bool orange = (i / half_stride) % 2 == 0;
//                 int j = (i / hs) * s + (i % hs);
//                 int k = j + hs;
//                 //printf("Stride: %d, s: %d, i: %d, j: %d, k: %d\n", stride, s, i, j, k);
//                 if ((descending && ((orange && a[j] < a[k]) || (!orange && a[j] > a[k]))) ||
//                     (!descending && ((orange && a[j] > a[k]) || (!orange && a[j] < a[k]))))
//                 {
//                     t = a[k];
//                     a[k] = a[j];
//                     a[j] = t;
//                 }
//             }
//             s = hs;
//         }
//         half_stride = stride;
//     }
// }


int main() {
    // const int n = 20;
    // const int m = 5;
    // float data[n] = {1.1, 3.3, 2.2, 4.4, 5.5, 1.2, 3.4, 2.3, 4.5, 1.3, 3.5, 2.4, 4.6, 1.4, 3.6, 2.5, 4.7, 1.5, 3.7, 2.6};
    // int seg_id[n] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4};
    // int seg_start[m + 1] = {0, 5, 9, 13, 17, 20};
    srand(time(0));
    const int n = 100;
    const int m = 10;
    float data[n];
    int seg_id[n];
    int seg_start[m + 1];

    // 随机生成测试数据
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 10000 / 10.0;
        seg_id[i] = rand() % m;
    }
    std::sort(seg_id, seg_id + n);
    for (int i = 0; i <= m; i++) {
        seg_start[i] = std::lower_bound(seg_id, seg_id + n, i) - seg_id;
    }

    // 打印未排序的测试数据
    std::cout << "Unsorted data:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }
    std::cout<<"\nsed_start: ";
    for (int i = 0; i < m+1; i++) {
        std::cout << seg_start[i] << " ";
    }
    std::cout << std::endl;

    // 对测试数据进行分段双调排序
    segmentedBitonicSort(data, seg_id, seg_start, n, m);

    // 打印排序后的测试数据
    std::cout << "Sorted data:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}