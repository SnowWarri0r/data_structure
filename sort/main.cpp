#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b);

void shell_sort_swap(vector<int> &arr);

void shell_sort_selection(vector<int> &arr);

void sort_quicksort(vector<int> &arr);

void mergesort(vector<int> &arr);

void merge_sort(vector<int> &arr, int l, int r);

int main() {
    vector<int> arr{1, 4, 2, 7, 9, 8, 3, 6};
    shell_sort_swap(arr);
    for (auto &x: arr) cout << x << " ";
    cout << endl;
    vector<int> arr1{1, 4, 2, 7, 9, 8, 3, 6};
    shell_sort_selection(arr1);
    for (auto &x: arr1) cout << x << " ";
    cout << endl;
    vector<int> arr2{1, 4, 2, 7, 9, 8, 3, 6};
    sort_quicksort(arr2);
    for (auto &x: arr2) cout << x << " ";
    cout << endl;
    vector<int> arr3{1, 4, 2, 7, 9, 8, 3, 6};
    mergesort(arr3);
    for (auto &x: arr3) cout << x << " ";
    cout << endl;
    vector<int> arr4{1, 4, 2, 7, 9, 8, 3, 6};
    merge_sort(arr4, 0, (int) arr4.size() - 1);
    for (auto &x: arr4) cout << x << " ";
    cout << endl;
    return 0;
}

void shell_sort_swap(vector<int> &arr) {
    int n = (int) arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int j = i;
            while (j - gap >= 0 && arr[j] < arr[j - gap]) {
                swap(arr[j], arr[j - gap]);
                j -= gap;
            }
        }
    }
}

void shell_sort_selection(vector<int> &arr) {
    int n = (int) arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int j = i;
            int temp = arr[j];
            while (j - gap >= 0 && temp < arr[j - gap]) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void swap(int &a, int &b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void quicksort(vector<int> &arr, int start, int end) {
    if (start >= end) return;
    int key = arr[start];
    int left = start;
    int right = end + 1;
    while (true) {
        while (arr[++left] < key) {
            if (left == end) break;
        }
        while (arr[--right] > key) {
            if (right == start) break;
        }
        if (left >= right) break;
        swap(arr[left], arr[right]);
    }
    arr[start] = arr[right];
    arr[right] = key;
    quicksort(arr, start, right - 1);
    quicksort(arr, right + 1, end);
}

void sort_quicksort(vector<int> &arr) {
    quicksort(arr, 0, (int) arr.size() - 1);
}

void merge(vector<int> &arr, int low, int mid, int high) {
    int left = low, right = mid + 1, x = low;
    vector<int> tmp(arr);
    while (x <= high) {
        if (left > mid) {
            arr[x++] = tmp[right++];
        } else if (right > high) {
            arr[x++] = tmp[left++];
        } else {
            if (tmp[left] < tmp[right])
                arr[x++] = tmp[left++];
            else
                arr[x++] = tmp[right++];
        }
    }
}

void merge_sort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int m = l + ((r - l) >> 1);
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

//自底向上
void mergesort(vector<int> &arr) {
    int n = (int) arr.size();
    int len;
    for (len = 2; len < n; len <<= 1) {
        //j推动窗口移动，窗口内两个数组分别为[j,j+len/2-1],[j+len/2,j+len-1]
        for (int j = 0; j + len / 2 < n; j += len) {
            if (j + len - 1 < n) {
                //两个完整的数组归并
                merge(arr, j, j + len / 2 - 1, j + len - 1);
            } else {
                //一个完整，一个残缺
                merge(arr, j, j + len / 2 - 1, n - 1);
            }
        }
    }
    merge(arr, 0, len / 2 - 1, n - 1);
}
