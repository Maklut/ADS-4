// Copyright 2021 NNTU-CS

#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <vector>
#include <fstream>
 
int countPairs1(int *arr, int len, int value);
int countPairs2(int *arr, int len, int value);
int countPairs3(int *arr, int len, int value);

int* generateSortedArray(int size, int maxValue = 1000) {
    int* arr = new int[size];
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxValue);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    std::sort(arr, arr + size);
    return arr;
}

int64_t measureTime(int (*func)(int*, int, int), int* arr,
                    int len, int value) {
    auto start = std::chrono::high_resolution_clock::now();
    func(arr, len, value);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(
        end - start).count();
}

int main() {
    std::cout << "Исследование зависимости времени выполнения "
              << "от размера массива\n";
    std::cout << "============================================\n\n";

    std::cout << "Проверка корректности работы функций:\n";
    int testArr[] = {20, 20, 30, 30, 40, 40};
    int testLen = 6;
    int testValue = 50;

    int result1 = countPairs1(testArr, testLen, testValue);
    int result2 = countPairs2(testArr, testLen, testValue);
    int result3 = countPairs3(testArr, testLen, testValue);

    std::cout << "Массив: ";
    for (int i = 0; i < testLen; i++) {
        std::cout << testArr[i] << " ";
    }
    std::cout << "\nИскомое значение: " << testValue << "\n";
    std::cout << "countPairs1: " << result1 << "\n";
    std::cout << "countPairs2: " << result2 << "\n";
    std::cout << "countPairs3: " << result3 << "\n";
    std::cout << "Результаты "
              << ((result1 == result2 && result2 == result3) ?
              "совпадают\n" : "НЕ совпадают\n");

    std::vector<int> sizes;
    for (int i = 1; i <= 20; i++) {
        sizes.push_back(i * 100);
    }

    std::vector<int64_t> times1, times2, times3;

    std::cout << "\nВыполнение измерений...\n";
    std::cout << "Размер\t\tВремя1 (мкс)\tВремя2 (мкс)\t"
              << "Время3 (мкс)\n";
    std::cout << "----------------------------------------"
              << "----------------\n";

    for (int size : sizes) {
        int* arr = generateSortedArray(size, 2000);
        int value = 1000 + rand() % 1000;

        int64_t t1 = measureTime(countPairs1, arr, size, value);
        int64_t t2 = measureTime(countPairs2, arr, size, value);
        int64_t t3 = measureTime(countPairs3, arr, size, value);

        times1.push_back(t1);
        times2.push_back(t2);
        times3.push_back(t3);

        std::cout << size << "\t\t" << t1 << "\t\t" << t2
                  << "\t\t" << t3 << "\n";

        delete[] arr;
    }

    std::ofstream dataFile("timing_data.txt");
    dataFile << "# Size Time1 Time2 Time3\n";
    for (size_t i = 0; i < sizes.size(); i++) {
        dataFile << sizes[i] << " " << times1[i] << " "
                 << times2[i] << " " << times3[i] << "\n";
    }
    dataFile.close();

    std::cout << "\nДанные сохранены в файл timing_data.txt\n";
    std::cout << "\nДля построения графиков используйте "
              << "Python скрипт plot_graphs.py\n";

    return 0;
}
