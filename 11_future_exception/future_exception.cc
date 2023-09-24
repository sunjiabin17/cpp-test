#include <future>
#include <iostream>

double square_root(double x) {
    if (x < 0) {
        throw std::out_of_range("x < 0");
    }
    return sqrt(x);
}

int main() {
    double x = -1;
    std::packaged_task<double(double)> task(square_root);
    std::future<double> f = task.get_future();
    std::thread t(std::move(task), x);

    try {
        double result = f.get();
        std::cout << "result: " << result << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    t.join();
    return 0;
}