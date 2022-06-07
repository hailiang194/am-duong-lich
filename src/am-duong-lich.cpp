#include "am-duong-lich.h"

int jdFromDate(const int& dd, const int& mm, const int& yy)
{
    int a = (14 - mm) / 12;
    int y = yy + 4800 - a;
    int m = mm + 12 * a - 3;
    int jd = dd + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
    if (jd < 2299161)
    {
        jd = dd + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083;
    }
    return jd;
}

std::array<int, 3> jdToDate(const int& jd)
{
    int a, b, c;
    if (jd > 2299160)
    { // After 5/10/1582, Gregorian calendar
        a = jd + 32044;
        b = (4 * a + 3) / 146097;
        c = a - (b * 146097) / 4;
    }
    else
    {
        b = 0;
        c = jd + 32082;
    }
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;
    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = b * 100 + d - 4800 + m / 10;
    return {day, month, year};
}

double SunLongitude(const double& jdn)
{
    return SunLongitudeAA98(jdn);
}

double SunLongitudeAA98(const double& jdn)
{
    double T = (jdn - 2451545.0) / 36525; // Time in Julian centuries from 2000-01-01 12:00:00 GMT
    double T2 = T * T;
    double dr = PI / 180;                                                          // degree to radian
    double M = 357.52910 + 35999.05030 * T - 0.0001559 * T2 - 0.00000048 * T * T2; // mean anomaly, degree
    double L0 = 280.46645 + 36000.76983 * T + 0.0003032 * T2;                      // mean longitude, degree
    double DL = (1.914600 - 0.004817 * T - 0.000014 * T2) * sin(dr * M);
    DL = DL + (0.019993 - 0.000101 * T) * sin(dr * 2 * M) + 0.000290 * sin(dr * 3 * M);
    double L = L0 + DL;                        // true longitude, degree
    L = L - 360 * (static_cast<int>(L / 360)); // Normalize to (0, 360)
    return L;
}

double NewMoon(const int& k)
{
    return NewMoonAA98(k);
}

double NewMoonAA98(const int& k)
{
    double T = k / 1236.85; // Time in Julian centuries from 1900 January 0.5
    double T2 = T * T;
    double T3 = T2 * T;
    double dr = PI / 180;
    double Jd1 = 2415020.75933 + 29.53058868 * k + 0.0001178 * T2 - 0.000000155 * T3;
    Jd1 = Jd1 + 0.00033 * sin((166.56 + 132.87 * T - 0.009173 * T2) * dr);       // Mean new moon
    double M = 359.2242 + 29.10535608 * k - 0.0000333 * T2 - 0.00000347 * T3;    // Sun's mean anomaly
    double Mpr = 306.0253 + 385.81691806 * k + 0.0107306 * T2 + 0.00001236 * T3; // Moon's mean anomaly
    double F = 21.2964 + 390.67050646 * k - 0.0016528 * T2 - 0.00000239 * T3;    // Moon's argument of latitude
    double C1 = (0.1734 - 0.000393 * T) * sin(M * dr) + 0.0021 * sin(2 * dr * M);
    C1 = C1 - 0.4068 * sin(Mpr * dr) + 0.0161 * sin(dr * 2 * Mpr);
    C1 = C1 - 0.0004 * sin(dr * 3 * Mpr);
    C1 = C1 + 0.0104 * sin(dr * 2 * F) - 0.0051 * sin(dr * (M + Mpr));
    C1 = C1 - 0.0074 * sin(dr * (M - Mpr)) + 0.0004 * sin(dr * (2 * F + M));
    C1 = C1 - 0.0004 * sin(dr * (2 * F - M)) - 0.0006 * sin(dr * (2 * F + Mpr));
    C1 = C1 + 0.0010 * sin(dr * (2 * F - Mpr)) + 0.0005 * sin(dr * (2 * Mpr + M));
    double deltat;
    if (T < -11)
    {
        deltat = 0.001 + 0.000839 * T + 0.0002261 * T2 - 0.00000845 * T3 - 0.000000081 * T * T3;
    }
    else
    {
        deltat = -0.000278 + 0.000265 * T + 0.000262 * T2;
    };
    double JdNew = Jd1 + C1 - deltat;
    return JdNew;
}

double getSunLongitude(const int& dayNumber, const double& timeZone)
{
    return SunLongitude(dayNumber - 0.5 - timeZone / 24);
}

int getNewMoonDay(const int& k, const double& timeZone)
{
    double jd = NewMoon(k);
    return static_cast<int>(jd + 0.5 + timeZone / 24);
}

int getLunarMonth11(const int& yy, const double& timeZone)
{
    double off = jdFromDate(31, 12, yy) - 2415021.076998695;
    int k = static_cast<int>(off / 29.530588853);
    int nm = getNewMoonDay(k, timeZone);
    int sunLong = static_cast<int>(getSunLongitude(nm, timeZone) / 30);
    if (sunLong >= 9)
    {
        nm = getNewMoonDay(k - 1, timeZone);
    }
    return nm;
}

int getLeapMonthOffset(const int& a11, const double& timeZone)
{
    int k = static_cast<int>(0.5 + (a11 - 2415021.076998695) / 29.530588853);
    int last;  // Month 11 contains point of sun longutide 3*PI/2 (December solstice)
    int i = 1; // We start with the month following lunar month 11
    int arc = static_cast<int>(getSunLongitude(getNewMoonDay(k + i, timeZone), timeZone) / 30);
    do
    {
        last = arc;
        i++;
        arc = static_cast<int>(getSunLongitude(getNewMoonDay(k + i, timeZone), timeZone) / 30);
    } while (arc != last && i < 14);
    return i - 1;
}

std::array<int, 4> convertSolar2Lunar(const int& dd, const int& mm, const int& yy, const double& timeZone)
{
    int lunarDay, lunarMonth, lunarYear, lunarLeap;
    int dayNumber = jdFromDate(dd, mm, yy);
    int k = static_cast<int>((dayNumber - 2415021.076998695) / 29.530588853);
    int monthStart = getNewMoonDay(k + 1, timeZone);
    if (monthStart > dayNumber)
    {
        monthStart = getNewMoonDay(k, timeZone);
    }
    int a11 = getLunarMonth11(yy, timeZone);
    int b11 = a11;
    if (a11 >= monthStart)
    {
        lunarYear = yy;
        a11 = getLunarMonth11(yy - 1, timeZone);
    }
    else
    {
        lunarYear = yy + 1;
        b11 = getLunarMonth11(yy + 1, timeZone);
    }
    lunarDay = dayNumber - monthStart + 1;
    int diff = static_cast<int>((monthStart - a11) / 29);
    lunarLeap = 0;
    lunarMonth = diff + 11;
    if (b11 - a11 > 365)
    {
        int leapMonthDiff = getLeapMonthOffset(a11, timeZone);
        if (diff >= leapMonthDiff)
        {
            lunarMonth = diff + 10;
            if (diff == leapMonthDiff)
            {
                lunarLeap = 1;
            }
        }
    }
    if (lunarMonth > 12)
    {
        lunarMonth = lunarMonth - 12;
    }
    if (lunarMonth >= 11 && diff < 4)
    {
        lunarYear -= 1;
    }
    return {lunarDay, lunarMonth, lunarYear, lunarLeap};
}

std::array<int, 3> convertLunar2Solar(const int& lunarDay, const int& lunarMonth, const int& lunarYear, const int& lunarLeap, const double& timeZone)
{
    int a11, b11;
    if (lunarMonth < 11)
    {
        a11 = getLunarMonth11(lunarYear - 1, timeZone);
        b11 = getLunarMonth11(lunarYear, timeZone);
    }
    else
    {
        a11 = getLunarMonth11(lunarYear, timeZone);
        b11 = getLunarMonth11(lunarYear + 1, timeZone);
    }
    int k = static_cast<int>(0.5 + (a11 - 2415021.076998695) / 29.530588853);
    int off = lunarMonth - 11;
    if (off < 0)
    {
        off += 12;
    }
    if (b11 - a11 > 365)
    {
        int leapOff = getLeapMonthOffset(a11, timeZone);
        int leapMonth = leapOff - 2;
        if (leapMonth < 0)
        {
            leapMonth += 12;
        }
        if (lunarLeap != 0 && lunarMonth != leapMonth)
        {
            return {0, 0, 0};
        }
        else if (lunarLeap != 0 || off >= leapOff)
        {
            off += 1;
        }
    }
    int monthStart = getNewMoonDay(k + off, timeZone);
    return jdToDate(monthStart + lunarDay - 1);
}

std::array<int, 4> convertToLunarCalendar(const int& dd, const int& mm, const int& yyyy, const double& timezones)
{
    int start = jdFromDate(dd, mm, yyyy);
    auto s = jdToDate(start);
    auto l = convertSolar2Lunar(s[0], s[1], s[2], timezones);
    auto s2 = convertLunar2Solar(l[0], l[1], l[2], l[3], timezones);
    // if (s[0] == s2[0] && s[1] == s2[1] && s[2] == s2[2]) {
    //     std::cout << "OK! " << s[0] << "/" << s[1] << "/" << s[2] << " -> " << l[0] << "/" << l[1] << "/" << l[2] << (l[3] == 0 ? "" : " leap") << std::endl;
    // } else {
    //     std::cout << "ERROR! " << s[0] << "/" << s[1] << "/" << s[2] << " -> " << l[0] << "/" << l[1] << "/" << l[2] << (l[3] == 0 ? "" : " leap") << std::endl;
    // }
    if(s[0] != s2[0] || s[1] != s2[1] || s[2] != s2[2])
    {
        throw std::invalid_argument("Invalid date");
    }

    return l;
}