#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <cmath>

struct Circle {
    double x, y, radius;
    bool contains(double px, double py) const {
        double dx = px - x;
        double dy = py - y;
        return (dx * dx + dy * dy) <= radius * radius;
    }
};

double monte_carlo_area(const std::vector<Circle>& circles,
                        long long N,
                        double x_min, double x_max,
                        double y_min, double y_max) {
    double rect_area = (x_max - x_min) * (y_max - y_min);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dist_x(x_min, x_max);
    std::uniform_real_distribution<double> dist_y(y_min, y_max);

    long long M = 0;
    for (long long i = 0; i < N; ++i) {
        double x = dist_x(gen);
        double y = dist_y(gen);

        if (circles[0].contains(x, y) &&
            circles[1].contains(x, y) &&
            circles[2].contains(x, y)) {
            ++M;
        }
    }

    return static_cast<double>(M) / N * rect_area;
}

int main() {
    // Круги из задачи
    std::vector<Circle> circles = {
        {1.0, 1.0, 1.0},
        {1.5, 2.0, std::sqrt(5.0)/2.0},
        {2.0, 1.5, std::sqrt(5.0)/2.0}
    };

    // Точное значение площади
    const double PI = 3.14159265358979323846;
    double exact_area = 0.25 * PI + 1.25 * std::asin(0.8) - 1.0;

    std::cout << "Exact area: " << exact_area << std::endl;

    // Широкая область
    double x_min_wide = 0.0;
    double x_max_wide = 3.0;
    double y_min_wide = 0.0;
    double y_max_wide = 3.0;

    // Узкая область (примерные границы пересечения)
    double r_avg = (1.0 + std::sqrt(5.0)/2.0 + std::sqrt(5.0)/2.0) / 3.0;
    double margin = r_avg * 0.5;
    double x_min_narrow = 1.0 - margin;
    double x_max_narrow = 2.0 + margin;
    double y_min_narrow = 1.0 - margin;
    double y_max_narrow = 2.0 + margin;

    // Открываем файлы для записи
    std::ofstream wide_file("Monte_Carlo_A1/data/wide_area.csv");
    std::ofstream narrow_file("Monte_Carlo_A1/data/narrow_area.csv");

    wide_file << "N,area_estimate,relative_error,execution_time_ms\n";
    narrow_file << "N,area_estimate,relative_error,execution_time_ms\n";

    // Эксперименты
    for (long long N = 100; N <= 100000; N += 500) {
        // Широкая область
        auto start = std::chrono::high_resolution_clock::now();
        double area_wide = monte_carlo_area(circles, N,
                                           x_min_wide, x_max_wide,
                                           y_min_wide, y_max_wide);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        double error_wide = std::abs(area_wide - exact_area) / exact_area;

        wide_file << N << "," << area_wide << ","
                 << error_wide << "," << duration.count() << "\n";

        // Узкая область
        start = std::chrono::high_resolution_clock::now();
        double area_narrow = monte_carlo_area(circles, N,
                                             x_min_narrow, x_max_narrow,
                                             y_min_narrow, y_max_narrow);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        double error_narrow = std::abs(area_narrow - exact_area) / exact_area;

        narrow_file << N << "," << area_narrow << ","
                   << error_narrow << "," << duration.count() << "\n";

        std::cout << "N = " << N << " completed" << std::endl;
    }

    wide_file.close();
    narrow_file.close();

    std::cout << "Experiments completed!" << std::endl;

    return 0;
}