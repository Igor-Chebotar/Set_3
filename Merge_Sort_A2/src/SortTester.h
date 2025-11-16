#pragma once
#include <chrono>
#include <fstream>

class SortTester {
public:
    static long long measureTime(std::vector<int> arr,
                                   void (*sortFunc)(int*, int, int)) {
        auto start = std::chrono::high_resolution_clock::now();

        sortFunc(arr.data(), 0, arr.size() - 1);

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        return elapsed.count();
    }

    static double measureAverage(std::vector<int> arr,
                                   void (*sortFunc)(int*, int, int),
                                   int runs = 5) {
        std::vector<long long> times;

        for (int i = 0; i < runs; i++) {
            std::vector<int> copy = arr;
            long long time = measureTime(copy, sortFunc);
            times.push_back(time);
        }

        std::sort(times.begin(), times.end());
        return times[times.size() / 2];
    }

    static void saveResults(const std::string& filename,
                           const std::vector<std::pair<int, double>>& results) {
        std::ofstream file(filename);

        file << "size,time_us\n";

        for (const auto& [size, time] : results) {
            file << size << "," << time << "\n";
        }

        file.close();
    }
};
