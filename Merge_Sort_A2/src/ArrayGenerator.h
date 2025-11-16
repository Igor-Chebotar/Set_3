#pragma once
#include <random>
#include <vector>
#include <algorithm>

class ArrayGenerator {
private:
    std::mt19937 gen;
    std::vector<int> master_array_random;
    std::vector<int> master_array_reversed;
    std::vector<int> master_array_nearly_sorted;

public:
    ArrayGenerator(unsigned seed = 42) : gen(seed) {
        const int MAX_SIZE = 100000;
        const int MIN_VAL = 0;
        const int MAX_VAL = 6000;

        master_array_random = generateRandomArray(MAX_SIZE, MIN_VAL, MAX_VAL);

        master_array_reversed = generateReversedArray(MAX_SIZE, MIN_VAL, MAX_VAL);

        int swaps = MAX_SIZE / 100;
        master_array_nearly_sorted = generateNearlySortedArray(MAX_SIZE, MIN_VAL, MAX_VAL, swaps);
    }

    std::vector<int> getRandom(int size) {
        return std::vector<int>(master_array_random.begin(),
                                master_array_random.begin() + size);
    }

    std::vector<int> getReversed(int size) {
        return std::vector<int>(master_array_reversed.begin(),
                                master_array_reversed.begin() + size);
    }

    std::vector<int> getNearlySorted(int size) {
        return std::vector<int>(master_array_nearly_sorted.begin(),
                                master_array_nearly_sorted.begin() + size);
    }

private:
    std::vector<int> generateRandomArray(int size, int minVal, int maxVal) {
        std::vector<int> arr(size);
        std::uniform_int_distribution<int> dist(minVal, maxVal);

        for (int i = 0; i < size; i++) {
            arr[i] = dist(gen);
        }

        return arr;
    }

    std::vector<int> generateReversedArray(int size, int minVal, int maxVal) {
        std::vector<int> arr = generateRandomArray(size, minVal, maxVal);
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        return arr;
    }

    std::vector<int> generateNearlySortedArray(int size, int minVal, int maxVal, int swaps) {
        std::vector<int> arr = generateRandomArray(size, minVal, maxVal);
        std::sort(arr.begin(), arr.end());

        std::uniform_int_distribution<int> indexDist(0, size - 1);
        for (int i = 0; i < swaps; i++) {
            int idx1 = indexDist(gen);
            int idx2 = indexDist(gen);
            std::swap(arr[idx1], arr[idx2]);
        }

        return arr;
    }
};
