#ifndef CLOCK_H
#define CLOCK_H
// #pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include "clockExcept.h"

enum amPmType
{
    AM,
    PM
};
enum clockFormatType
{
    TWELVE = 12,
    TWENTYFOUR = 24
};

class clockType
{
public:
    static std::map<clockFormatType, std::string> clockFormatToStr;
    static std::map<int, clockFormatType> intToClockFormat;
    static std::map<amPmType, std::string> amPmToStr;
    static std::map<std::string, amPmType> strToAmPmType;
    // clockType();
    clockType(int h = 0, int m = 0, int s = 0, std::string = "PM", clockFormatType = TWENTYFOUR);
    // clockType(int h, int m);
    void setTime(int h, int m, int s, std::string = "PM");

    void getTime(int &, int &, int &) const;
    int getHour() const;
    void setHour(int h);

    void incrementSeconds();
    void incrementMinutes();
    void incrementHours();

    bool operator==(const clockType &) const;
    bool operator!=(const clockType &) const;
    bool operator>(const clockType &) const;
    bool operator<(const clockType &) const;
    bool operator>=(const clockType &) const;
    bool operator<=(const clockType &) const;
    // friend bool operator==(const clockType &, const clockType &);
    friend clockType operator+(const int, const clockType &);
    clockType operator+(const int);
    friend std::ostream &operator<<(std::ostream &, const clockType &);
    friend std::istream &operator>>(std::istream &, clockType &);
    const clockType &operator=(const clockType &);
    clockType operator++();
    clockType operator++(int);
    static int count;

private:
    int hr;
    int min;
    int sec;
    amPmType timeOfDay;
    clockFormatType format;
    bool equalTime(const clockType &) const;
    std::string tostring() const;
};
#endif