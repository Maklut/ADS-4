// Copyright 2021 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>
#include <cstdlib>

int countPairs1(int *arr, int len, int value);
int countPairs2(int *arr, int len, int value);
int countPairs3(int *arr, int len, int value);

int main() {
  std::vector<int> sizes;
  std::vector<double> times1, times2, times3;

  for (int size = 100; size <= 2000; size += 100) {
    sizes.push_back(size);

    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);

    for (int i = 0; i < size; ++i) {
      arr[i] = dis(gen);
    }
    std::sort(arr.begin(), arr.end());

    int target = 500;

    auto start = std::chrono::high_resolution_clock::now();
    countPairs1(arr.data(), size, target);
    auto end = std::chrono::high_resolution_clock::now();
    double time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    times1.push_back(time1);

    start = std::chrono::high_resolution_clock::now();
    countPairs2(arr.data(), size, target);
    end = std::chrono::high_resolution_clock::now();
    double time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    times2.push_back(time2);

    start = std::chrono::high_resolution_clock::now();
    countPairs3(arr.data(), size, target);
    end = std::chrono::high_resolution_clock::now();
    double time3 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    times3.push_back(time3);

    std::cout << "Size: " << size << " | Time1: " << time1
              << " us | Time2: " << time2 << " us | Time3: " << time3 << " us\n";
  }

  std::ofstream dataFile("data.csv");
  dataFile << "size,time1,time2,time3\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    dataFile << sizes[i] << "," << times1[i] << "," << times2[i] << "," << times3[i] << "\n";
  }
  dataFile.close();

  std::ofstream gnuplotScript("plot.gnu");
  gnuplotScript << "set terminal png size 800,600\n";
  gnuplotScript << "set output 'lin.png'\n";
  gnuplotScript << "set title 'Time Complexity Comparison (Linear Scale)'\n";
  gnuplotScript << "set xlabel 'Array Size'\n";
  gnuplotScript << "set ylabel 'Time (microseconds)'\n";
  gnuplotScript << "set grid\n";
  gnuplotScript << "plot 'data.csv' using 1:2 with linespoints title 'countPairs1 (O(n²))',";
  gnuplotScript << " 'data.csv' using 1:3 with linespoints title 'countPairs2 (O(n))',";
  gnuplotScript << " 'data.csv' using 1:4 with linespoints title 'countPairs3 (O(n log n))'\n";

  gnuplotScript << "set output 'log.png'\n";
  gnuplotScript << "set title 'Time Complexity Comparison (Logarithmic Scale)'\n";
  gnuplotScript << "set logscale xy\n";
  gnuplotScript << "plot 'data.csv' using 1:2 with linespoints title 'countPairs1',";
  gnuplotScript << " 'data.csv' using 1:3 with linespoints title 'countPairs2',";
  gnuplotScript << " 'data.csv' using 1:4 with linespoints title 'countPairs3'\n";
  gnuplotScript.close();

  int result = system("gnuplot plot.gnu 2>/dev/null");

  if (result == 0) {
    std::cout << "\n✅ Graphs saved as 'lin.png' and 'log.png'\n";
    system("mkdir -p Plots 2>/dev/null");
    system("mv lin.png Plots/ 2>/dev/null");
    system("mv log.png Plots/ 2>/dev/null");
  } else {
    std::cout << "\n⚠️ Gnuplot not found. Data saved to 'data.csv'\n";
  }

  return 0;
}
