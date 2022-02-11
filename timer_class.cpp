#include <iostream>
#include <chrono>
#include <cmath>
#include <stdio.h>
using namespace std::chrono;

constexpr auto factorial(unsigned n) {
    auto result = 1.;
    for (auto i = 1u; i <= n; i++) { result *= i; }
    return result;}

auto X_to_the_power_of_int(double x,int n){
    if (n == 0){return 1.;}
    else {return x * X_to_the_power_of_int(x, n-1);}
}

template<typename T>
class Timer{
public:
    Timer(): start(steady_clock::now()), time(0)  {}
    ~Timer() {}
    void Pause(){
        time = steady_clock::duration(steady_clock::now() - start);
        std::cout << "Current process duration is " << duration_cast<T>(time).count() << std::endl;
    }
    void Start(){
        start = steady_clock::now();
    }
private:
    steady_clock::time_point start;
    steady_clock::duration time;
};

int main() {
    auto result = 0.;
    Timer<nanoseconds> t1;
    Timer<milliseconds> t2;
    constexpr double just_check = factorial(15);
    std::cout << "Constexpr was calculated during compilation, so, obviously:" << std::endl;
    t1.Pause();
    std::cout << ' ' << std::endl;
    t1.Start();

    result = X_to_the_power_of_int(242.748, 8);
    std::cout << result << std::endl;
    t1.Pause();
    std::cout << "wat?" << std::endl;
    std::cout << ' ' << std::endl;
    t1.Start();
    t2.Start();

    for(auto i = 0u; i < 1'000'000u; i++) { result += sin(i) * cos(i);}
    t1.Pause();
    t2.Pause();
    std::cout << "Calculation duration in different measures" << std::endl;
    std::cout << ' ' << std::endl;
    t1.Start();
    t2.Start();
    for(auto i = 0u; i < 1'000'000u; i++) { result += sin(i) * cos(i);}
    t1.Pause();
    std::cout << "Time won't stop if we dont say 'Start' " << std::endl;
    for(auto i = 0u; i < 1'000'000u; i++) { result += sin(i) * cos(i);}
    t1.Pause();
    return 0;
}