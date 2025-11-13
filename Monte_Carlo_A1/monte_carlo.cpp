#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

struct Circle {
    double x, y, radius;

    bool contains(double px, double py) const {
        double dx = px - x;
        double dy = py - y;
        return (dx * dx + dy * dy) <= radius * radius;
    }
};

int main() {
    std::vector<Circle> circles;
    int number_od_circles = 3;
    for (int i = 0; i < number_od_circles; ++i) {
        double x, y, radius;
        std::cin >> x >> y >> radius;
        circles.push_back({x, y, radius});
    }

    // Поиск границ прямоугольной области
    double x_min = std::min({circles[0].x - circles[0].radius,
                             circles[1].x - circles[1].radius,
                             circles[2].x - circles[2].radius});
    double x_max = std::max({circles[0].x + circles[0].radius,
                             circles[1].x + circles[1].radius,
                             circles[2].x + circles[2].radius});
    double y_min = std::min({circles[0].y - circles[0].radius,
                             circles[1].y - circles[1].radius,
                             circles[2].y - circles[2].radius});
    double y_max = std::max({circles[0].y + circles[0].radius,
                             circles[1].y + circles[1].radius,
                             circles[2].y + circles[2].radius});

    double rect_area = (x_max - x_min) * (y_max - y_min);

    // Настройка генератора случайных чисел
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dist_x(x_min, x_max);
    std::uniform_real_distribution<double> dist_y(y_min, y_max);

    // Метод Монте-Карло
    const long long N = 10000000;
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

    // Вычисление и вывод площади
    double s_area = (static_cast<double>(M) / N) * rect_area;

    std::cout.precision(20);
    std::cout << s_area << std::endl;
}