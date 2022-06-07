#include <iostream>
#include <ctime>
#include "am-duong-lich.h"

int main()
{
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    int dd = now->tm_mday;
    int mm = now->tm_mon + 1;
    int yyyy = now->tm_year + 1900;

    std::cout << "Current date: " << dd << '/' << mm << '/' << yyyy << std::endl;

    auto lunar = convertToLunarCalendar(dd, mm, yyyy, 7.0);
    std::cout << "Vietnamese lunar date: " << lunar[0] << '/' << lunar[1] << '/' << lunar[2] << '(' << ((lunar[3] == 0) ? "Not " : "") << "leap)" << std::endl;
    return 0;
}