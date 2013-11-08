#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void read_arr(int *, int);
void print_arr(vector<int> &);
int partition(int *, int);
int search_reference_element(int *, int);
int search_random_element(int);
int nth_element(int *, int, int);

int main()
{
    int *array = NULL;
    int n = 0;
    int k = 0;
    scanf("%d%d", &n, &k);
    array = new int[n];
    read_arr(array, n);
    int m = nth_element(&array[0], n, k);
    printf("%d\n", m);
    return 0;
}

void read_arr(int *arr, int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

}

void print_arr(vector<int> &arr) {
    for (size_t i = 0; i < arr.size(); ++i)
        printf("%d ", arr[i]);
}

int search_reference_element(int *arr, int n) {
    if (arr[0] <= arr[n/2]) {
        if (arr[n/2] <= arr[n-1]) return n/2;
        else {
            if(arr[n-1] <= arr[0]) return 0;
            else return n-1;
        }
    }
    else {
        if (arr[0] <= arr[n-1]) return 0;
        else {
            if (arr[n-1] <= arr[n/2]) return n/2;
            else return n-1;
        }
    }
}

int search_random_element(int n) {
    srand(time(0));
    return (rand() % n);
}

int partition(int *arr, int n) {
    if (n == 1) return 0;
    swap(arr[search_reference_element(arr, n)], arr[n-1]);
    //swap(arr[search_random_element(n)], arr[n-1]);
    int i = n-2;
    int j = n-2;
    while (j > -1) {
        if (arr[j] <= arr[n - 1]) --j;
        else {
            swap(arr[i], arr[j]);
            --j; --i;
        }
    }
    ++i;
    swap(arr[i], arr[n - 1]);
    return i;
}

int nth_element(int *arr, int n, int k) {
    int m = 0; //Переменная, которая хранит то, что возвращает partition
    while (n > 1) {
        m = partition(arr, n);
        if (k > m) {
            arr = arr + m + 1;
            n = n - m - 1;
            k = k - m - 1;
            continue;
        }
        if (k < m) {
            n = m;
            continue;
        }
        if (k == m) return arr[k];
    }
    return arr[k];
}
