#ifndef AM_DUONG_LICH_H
#define AM_DUONG_LICH_H

#include <array>
#include <cmath>
#include <stdexcept>

#define PI 3.14159265358979323846

//the number of days since 1 January 4713 BC (Julian calendar)
int jdFromDate(const int& dd, const int& mm, const int& yy);

//Is there a formula for calculating the Julian day number
//jd - the number of days since 1 January 4713 BC (Julian calendar)
std::array<int, 3> jdToDate(const int& jd);

//Solar longitude in degrees
//Algorithm from: Astronomical Algorithms, by Jean Meeus, 1998
//jdn - number of days since noon UTC on 1 January 4713 BC
double SunLongitude(const double& jdn);

double SunLongitudeAA98(const double& jdn);

double NewMoon(const int& k);

//Julian day number of the kth new moon after (or before) the New Moon of 1900-01-01 13:51 GMT.
//Accuracy: 2 minutes
//Algorithm from: Astronomical Algorithms, by Jean Meeus, 1998
//return the Julian date number (number of days since noon UTC on 1 January 4713 BC) of the New Moon
double NewMoonAA98(const int& k);

double getSunLongitude(const int& dayNumber, const double& timeZone);

int getNewMoonDay(const int& k, const double& timeZone);

int getLunarMonth11(const int& yy, const double& timeZone);

int getLeapMonthOffset(const int& a11, const double& timeZone);

//return array of [lunarDay, lunarMonth, lunarYear, leapOrNot]
std::array<int, 4> convertSolar2Lunar(const int& dd, const int& mm, const int& yy, const double& timeZone);

std::array<int, 3> convertLunar2Solar(const int& lunarDay, const int& lunarMonth, const int& lunarYear, const int& lunarLeap, const double& timeZone);

//return array of [lunarDay, lunarMonth, lunarYear, leapOrNot]
std::array<int, 4> convertToLunarCalendar(const int& dd, const int& mm, const int& yyyy, const double& timezones);

#endif //!AM_DUONG_LICH_H