#include <iostream>
#include <vector>
#include <thread>
#include <functional> 

class MergeSort {
public:
    void Sort(std::vector<int>& array) {
        if (array.size() <= 1) return;
        mergeSort(array, 0, array.size() - 1);
    }

private:
    void mergeSort(std::vector<int>& array, int left, int right) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid, right);
    }

    void merge(std::vector<int>& array, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i) L[i] = array[left + i];
        for (int i = 0; i < n2; ++i) R[i] = array[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k++] = L[i++];
            }
            else {
                array[k++] = R[j++];
            }
        }

        while (i < n1) array[k++] = L[i++];
        while (j < n2) array[k++] = R[j++];
    }
};

int main() {
    std::vector<int> array(10);
    std::cout << "Enter 10 integers: ";
    for (int i = 0; i < 10; ++i) {
        std::cin >> array[i];
    }

    MergeSort mergeSort;

    auto sortFunction = [&mergeSort](std::vector<int>& arr) {
        mergeSort.Sort(arr);
        };

    std::thread sortThread(sortFunction, std::ref(array));

    sortThread.join();

    std::cout << "Sorted array: ";
    for (const int& num : array) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
