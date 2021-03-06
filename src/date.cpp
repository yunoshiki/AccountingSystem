#include "../inc/date.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <time.h>
using namespace std;
bool checkYear(int x)
{
	return x % 4 == 0 && (x % 100 != 0 || x % 400 == 0);
}
int getYearDay(int y)
{
	return checkYear(y) ? 366 : 365;
}
int getMonthDay(int y, int x)
{
	if (x == 2 && checkYear(y)) return monthDay[2] + 1;
	return monthDay[x];
}
void Date::init()
{
	tothour = hour + (day - 1) * 24;
	for (int i = 1; i < month; i++) tothour += getMonthDay(year, i) * 24;
	for (int i = 1; i < year; i++) tothour += getYearDay(i) * 24;
}
Date::Date()
{
	time_t t = time(NULL);
	struct tm* stime = localtime(&t);
	year = 1900 + stime->tm_year;
	month = 1 + stime->tm_mon;
	day = stime->tm_mday;
	hour = stime->tm_hour;
	init();
}
Date::Date(int y, int m, int d, int h)
{
	time_t t = time(NULL);
	struct tm* stime = localtime(&t);
	year = y;
	month = m;
	day = d;
	hour = h;
	init();
}
Date::Date(long long t)
{
	tothour = t;
	long long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	for (int s1 = 0, i = 1; i <= 2500; s1 += getYearDay(i++) * 24)
		if (s1 + getYearDay(i) * 24 > t)
		{
			t -= s1;
			year = i;
			for (int j = 1; j <= 12; s2 += getMonthDay(i, j++) * 24)
				if (s2 + getMonthDay(i, j) * 24 > t)
				{
					t -= s2;
					month = j;
					for (int k = 1; k <= 31; s3 += 24, k++)
						if (s3 + 24 > t)
						{
							day = k;
							hour = (int)(t - s3);
							break;
						}
					break;
				}
			break;
		}
}
bool Date::operator <(const Date &a) const
{
	cout << tothour << " " << a.tothour << endl;
	return tothour < a.tothour;
}
bool Date::operator <=(const Date &a) const 
{
	return tothour <= a.tothour;
}
bool Date::operator >(const Date &a) const
{
	return tothour > a.tothour;
}
bool Date::operator >=(const Date &a) const
{
	return tothour >= a.tothour;
}
ostream& operator<< (ostream&out, const Date &x)
{
	out << x.year << " " << x.month << " " << x.day << " " << x.hour << " " << x.tothour;
	return out;
}
istream& operator>> (istream&in, Date &x)
{
	in >> x.year >> x.month >> x.day >> x.hour;
	x.init();
	return in;
}
TimeLen::TimeLen(int y, int m, int d, int h)
{
	year = y;
	month = m;
	day = d;
	hour = h;
	init();
}
void TimeLen::init()
{
	tothour = hour + day * 24;
	for (int i = 1; i <= month; i++) tothour += getMonthDay(year, i) * 24;
	for (int i = 1; i <= year; i++) tothour += getYearDay(i) * 24;
}
TimeLen::TimeLen(long long t)
{
	tothour = t;
	long long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
	for (int s1 = 0, i = 1; i <= 2500; s1 += getYearDay(i++) * 24)
		if (s1 + getYearDay(i) * 24 > t)
		{
			t -= s1;
			year = i - 1;
			for (int j = 1; j <= 12; s2 += getMonthDay(i, j++) * 24)
				if (s2 + getMonthDay(i, j) * 24 > t)
				{
					t -= s2;
					month = j - 1;
					for (int k = 1; k <= 31; s3 += 24, k++)
						if (s3 + 24 > t)
						{
							day = k - 1;
							hour = (int)(t - s3);
							break;
						}
					break;
				}
			break;
		}
}
ostream& operator<< (ostream&out, const TimeLen &x)
{
	out << x.year << " " << x.month << " " << x.day << " " << x.hour << " " << x.tothour;
	return out;
}
istream& operator>> (istream&in, TimeLen &x)
{
	in >> x.year >> x.month >> x.day >> x.hour;
	x.init();
	return in;
}
Date operator -(const Date &a, const TimeLen &b)
{
	return Date(a.tothour - b.tothour);
}
Date operator +(const Date &a, const TimeLen &b)
{
	return Date(a.tothour + b.tothour);
}
Date operator +(const TimeLen &a, const Date &b)
{
	return Date(a.tothour + b.tothour);
}
TimeLen operator -(const Date &a, const Date &b)
{
	return TimeLen(a.tothour - b.tothour);
}
bool operator ==(const Date&a, const Date &b)
{
	return a.tothour == b.tothour;
}
bool operator ==(const TimeLen &a, const TimeLen &b)
{
	return a.tothour == b.tothour;
}