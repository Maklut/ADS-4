// Copyright 2021 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <cmath>
#include <fstream>
#include <string>

int countPairs1(int *arr, int len, int value);
int countPairs2(int *arr, int len, int value);
int countPairs3(int *arr, int len, int value);

void generatePlotScript(const std::vector<int>& sizes,
                        const std::vector<double>& times1,
                        const std::vector<double>& times2,
                        const std::vector<double>& times3) {
  std::ofstream gnuplot("plot.gnu");
  gnuplot << "set terminal png size 800,600\n";
  gnuplot << "set output 'lin.png'\n";
  gnuplot << "set title 'Time Complexity Comparison (Linear Scale)'\n";
  gnuplot << "set xlabel 'Array Size'\n";
  gnuplot << "set ylabel 'Time (microseconds)'\n";
  gnuplot << "set grid\n";
  gnuplot << "plot '-' with linespoints title 'countPairs1 (O(n²))',";
  gnuplot << " '-' with linespoints title 'countPairs2 (O(n))',";
  gnuplot << " '-' with linespoints title 'countPairs3 (O(n log n))'\n";
  
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times1[i] << "\n";
  }
  gnuplot << "e\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times2[i] << "\n";
  }
  gnuplot << "e\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times3[i] << "\n";
  }
  gnuplot << "e\n";
  
  gnuplot << "set output 'log.png'\n";
  gnuplot << "set title 'Time Complexity Comparison (Logarithmic Scale)'\n";
  gnuplot << "set logscale xy\n";
  gnuplot << "plot '-' with linespoints title 'countPairs1',";
  gnuplot << " '-' with linespoints title 'countPairs2',";
  gnuplot << " '-' with linespoints title 'countPairs3'\n";
  
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times1[i] << "\n";
  }
  gnuplot << "e\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times2[i] << "\n";
  }
  gnuplot << "e\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    gnuplot << sizes[i] << " " << times3[i] << "\n";
  }
  gnuplot << "e\n";
  gnuplot.close();
  
  system("gnuplot plot.gnu");
}

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
    
    std::cout << "Size: " << size << ", Time1: " << time1 
              << " us, Time2: " << time2 << " us, Time3: " << time3 << " us\n";
  }
  
  generatePlotScript(sizes, times1, times2, times3);
  std::cout << "\nGraphs saved as 'lin.png' and 'log.png' in 'Plots' directory\n";
  
  return 0;
}
