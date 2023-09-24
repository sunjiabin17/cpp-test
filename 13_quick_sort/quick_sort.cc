#include <vector>
#include <iostream>

#include <future>
#include <chrono>
#include <random>

template <typename T>
void async_quick_sort(std::vector<T>& v, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot_idx = rand() % (right - left + 1) + left;
    T pivot = v[pivot_idx];
    std::swap(v[pivot_idx], v[left]);

    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= j and v[i] <= pivot) {
            ++i;
        }
        while (i <= j and v[j] > pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(v[i], v[j]);
            ++i;
            --j;
        }
    }
    std::swap(v[left], v[j]);

    std::future<void> f1 = std::async(std::launch::async, async_quick_sort<T>, std::ref(v), left, j - 1);
    std::future<void> f2 = std::async(std::launch::async, async_quick_sort<T>, std::ref(v), j + 1, right);

    f1.get();
    f2.get();
}

template <typename T>
void quick_sort(std::vector<T>& v, int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot_idx = rand() % (right - left + 1) + left;
    T pivot = v[pivot_idx];
    std::swap(v[pivot_idx], v[left]);

    int i = left + 1;
    int j = right;

    while (i <= j) {
        while (i <= j and v[i] <= pivot) {
            ++i;
        }
        while (i <= j and v[j] > pivot) {
            --j;
        }
        if (i <= j) {
            std::swap(v[i], v[j]);
            ++i;
            --j;
        }
    }
    std::swap(v[left], v[j]);

    quick_sort(v, left, j - 1);
    quick_sort(v, j + 1, right);
}

int main() {
    std::vector<int> v1;
    for (int i = 0; i < 1000; ++i) {
        v1.push_back(rand() % 100);
        if (i < 20) {
            std::cout << v1[i] << " ";
        }
    }
    std::cout << std::endl;
    std::vector<int> v2(v1);

        auto start1 = std::chrono::high_resolution_clock::now();
    quick_sort(v2, 0, v2.size() - 1);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
    std::cout << "quick_sort duration: " << duration1.count() << " microseconds" << std::endl;

    for (int i = 0; i < v2.size(); ++i) {
        if (i < 20) {
            std::cout << v2[i] << " ";
        }
    }
    std::cout << std::endl;


    auto start = std::chrono::high_resolution_clock::now();
    async_quick_sort(v1, 0, v1.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "async_quick_sort duration: " << duration.count() << " microseconds" << std::endl;

    for (int i = 0; i < v1.size(); ++i) {
        if (i < 20) {
            std::cout << v1[i] << " ";
        }
    }
    std::cout << std::endl;


    return 0;
}