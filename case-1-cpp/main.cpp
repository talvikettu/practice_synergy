#include <array>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct DateOfBirth {
    int day;
    int month;
    int year;
};

bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int daysInMonth(int month, int year) {
    static const std::array<int, 12> daysPerMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month < 1 || month > 12) {
        throw std::out_of_range("Month must be between 1 and 12.");
    }

    if (month == 2 && isLeapYear(year)) {
        return 29;
    }

    return daysPerMonth[month - 1];
}

bool isValidDate(const DateOfBirth &date) {
    if (date.year < 1900 || date.month < 1 || date.month > 12 || date.day < 1) {
        return false;
    }

    try {
        return date.day <= daysInMonth(date.month, date.year);
    } catch (const std::out_of_range &) {
        return false;
    }
}

std::string dayOfWeek(const DateOfBirth &date) {
    std::tm timeInfo = {};
    timeInfo.tm_mday = date.day;
    timeInfo.tm_mon = date.month - 1;
    timeInfo.tm_year = date.year - 1900;
    timeInfo.tm_isdst = -1;

    if (std::mktime(&timeInfo) == -1) {
        throw std::runtime_error("Unable to determine day of week for this date.");
    }

    static const std::array<std::string, 7> days = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    return days[timeInfo.tm_wday];
}

int currentAge(const DateOfBirth &date) {
    const auto now = std::chrono::system_clock::now();
    const std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm localNow = *std::localtime(&nowTime);

    int age = (localNow.tm_year + 1900) - date.year;

    if ((localNow.tm_mon + 1 < date.month) ||
        ((localNow.tm_mon + 1 == date.month) && localNow.tm_mday < date.day)) {
        --age;
    }

    return age;
}

std::vector<std::string> renderDisplayDigits(const std::string &formattedDate) {
    static const std::map<char, std::array<std::string, 5>> patterns = {
        {'0', {" *** ", "*   *", "*   *", "*   *", " *** "}},
        {'1', {"  *  ", " **  ", "  *  ", "  *  ", " *** "}},
        {'2', {" *** ", "*   *", "   * ", "  *  ", "*****"}},
        {'3', {"**** ", "    *", " *** ", "    *", "**** "}},
        {'4', {"*   *", "*   *", "*****", "    *", "    *"}},
        {'5', {"*****", "*    ", "**** ", "    *", "**** "}},
        {'6', {" *** ", "*    ", "**** ", "*   *", " *** "}},
        {'7', {"*****", "    *", "   * ", "  *  ", " *   "}},
        {'8', {" *** ", "*   *", " *** ", "*   *", " *** "}},
        {'9', {" *** ", "*   *", " ****", "    *", " *** "}},
        {' ', {"     ", "     ", "     ", "     ", "     "}}
    };

    std::vector<std::string> rows(5);

    for (char symbol : formattedDate) {
        auto found = patterns.find(symbol);
        if (found == patterns.end()) {
            throw std::runtime_error("Unsupported character for rendering.");
        }

        for (std::size_t row = 0; row < rows.size(); ++row) {
            rows[row] += found->second[row] + "  ";
        }
    }

    return rows;
}

int requestNumber(const std::string &prompt) {
    int value = 0;

    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }

        std::cout << "Please enter a valid integer value.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    std::cout << "Birth Date Style Transformer\n";
    std::cout << "----------------------------\n";

    DateOfBirth birthDate = {};

    while (true) {
        birthDate.day = requestNumber("Enter birth day: ");
        birthDate.month = requestNumber("Enter birth month: ");
        birthDate.year = requestNumber("Enter birth year: ");

        if (isValidDate(birthDate)) {
            break;
        }

        std::cout << "The entered date is invalid. Please try again.\n\n";
    }

    std::ostringstream formatted;
    formatted << std::setfill('0')
              << std::setw(2) << birthDate.day << ' '
              << std::setw(2) << birthDate.month << ' '
              << std::setw(4) << birthDate.year;

    std::cout << "\nDate of birth: " << formatted.str() << '\n';
    std::cout << "Day of week: " << dayOfWeek(birthDate) << '\n';
    std::cout << "Leap year: " << (isLeapYear(birthDate.year) ? "Yes" : "No") << '\n';
    std::cout << "Current age: " << currentAge(birthDate) << '\n';
    std::cout << "\nDigital display rendering:\n";

    for (const std::string &row : renderDisplayDigits(formatted.str())) {
        std::cout << row << '\n';
    }

    return 0;
}
