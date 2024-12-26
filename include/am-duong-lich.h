#ifndef AM_DUONG_LICH_H
#define AM_DUONG_LICH_H

#include <array>
#include <cmath>
#include <stdexcept>

#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #if defined(__TINYC__)
            #define __declspec(x) __attribute__((x))
        #endif
        #define EXTENDAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define EXTENDAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef EXTENDAPI
    #define EXTENDAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

#define PI 3.14159265358979323846

//the number of days since 1 January 4713 BC (Julian calendar)
static int jdFromDate(const int& dd, const int& mm, const int& yy);

//Is there a formula for calculating the Julian day number
//jd - the number of days since 1 January 4713 BC (Julian calendar)
static std::array<int, 3> jdToDate(const int& jd);

//Solar longitude in degrees
//Algorithm from: Astronomical Algorithms, by Jean Meeus, 1998
//jdn - number of days since noon UTC on 1 January 4713 BC
static double SunLongitude(const double& jdn);

static double SunLongitudeAA98(const double& jdn);

static double NewMoon(const int& k);

//Julian day number of the kth new moon after (or before) the New Moon of 1900-01-01 13:51 GMT.
//Accuracy: 2 minutes
//Algorithm from: Astronomical Algorithms, by Jean Meeus, 1998
//return the Julian date number (number of days since noon UTC on 1 January 4713 BC) of the New Moon
static double NewMoonAA98(const int& k);

static double getSunLongitude(const int& dayNumber, const double& timeZone);

static int getNewMoonDay(const int& k, const double& timeZone);

static int getLunarMonth11(const int& yy, const double& timeZone);

static int getLeapMonthOffset(const int& a11, const double& timeZone);

//return array of [lunarDay, lunarMonth, lunarYear, leapOrNot]
static std::array<int, 4> convertSolar2Lunar(const int& dd, const int& mm, const int& yy, const double& timeZone);

static std::array<int, 3> convertLunar2Solar(const int& lunarDay, const int& lunarMonth, const int& lunarYear, const int& lunarLeap, const double& timeZone);

//return array of [lunarDay, lunarMonth, lunarYear, leapOrNot]
EXTENDAPI std::array<int, 4> convertToLunarCalendar(const int& dd, const int& mm, const int& yyyy, const double& timezones);

#endif //!AM_DUONG_LICH_H