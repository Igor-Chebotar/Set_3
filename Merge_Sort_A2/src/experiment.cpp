#include <iostream>
#include "ArrayGenerator.h"
#include "SortTester.h"
#include "sorting_algorithms.cpp"

int main() {
    ArrayGenerator generator;

    std::cout << "Начало экспериментов\n";

    std::vector<std::pair<int, double>> results_random_merge;
    std::vector<std::pair<int, double>> results_reversed_merge;
    std::vector<std::pair<int, double>> results_nearly_sorted_merge;

    std::vector<std::pair<int, double>> results_random_hybrid;
    std::vector<std::pair<int, double>> results_reversed_hybrid;
    std::vector<std::pair<int, double>> results_nearly_sorted_hybrid;

    for (int size = 500; size <= 100000; size += 100) {
        std::cout << "Обработка размера: " << size << std::endl;

        auto randomArray = generator.getRandom(size);
        auto reversedArray = generator.getReversed(size);
        auto nearlySortedArray = generator.getNearlySorted(size);

        // Случайные массивы
        double timeMerge = SortTester::measureAverage(randomArray, mergeSort);
        double timeHybrid = SortTester::measureAverage(randomArray, hybridMergeSort);

        results_random_merge.push_back({size, timeMerge});
        results_random_hybrid.push_back({size, timeHybrid});

        // Обратно отсортированные
        timeMerge = SortTester::measureAverage(reversedArray, mergeSort);
        timeHybrid = SortTester::measureAverage(reversedArray, hybridMergeSort);

        results_reversed_merge.push_back({size, timeMerge});
        results_reversed_hybrid.push_back({size, timeHybrid});

        // Почти отсортированные
        timeMerge = SortTester::measureAverage(nearlySortedArray, mergeSort);
        timeHybrid = SortTester::measureAverage(nearlySortedArray, hybridMergeSort);

        results_nearly_sorted_merge.push_back({size, timeMerge});
        results_nearly_sorted_hybrid.push_back({size, timeHybrid});
    }

    std::cout << "\nСохранение результатов в CSV файлы\n";

    SortTester::saveResults("Merge_Sort_A2/data/random_merge.csv", results_random_merge);
    SortTester::saveResults("Merge_Sort_A2/data/random_hybrid.csv", results_random_hybrid);

    SortTester::saveResults("Merge_Sort_A2/data/reversed_merge.csv", results_reversed_merge);
    SortTester::saveResults("Merge_Sort_A2/data/reversed_hybrid.csv", results_reversed_hybrid);

    SortTester::saveResults("Merge_Sort_A2/data/nearly_sorted_merge.csv", results_nearly_sorted_merge);
    SortTester::saveResults("Merge_Sort_A2/data/nearly_sorted_hybrid.csv", results_nearly_sorted_hybrid);

    std::cout << "\nЭксперименты завершены!\n";
    std::cout << "Результаты успешно записаны в файлы\n";

    return 0;
}
