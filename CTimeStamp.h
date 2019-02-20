#pragma once
#include "CDate.h"

#define sSTRING_TIME_REPRESENTATION_SEPARTOR string(":")
#define sDEFAULT_TIME_FORMAT string("hh:mm")
#define sFORMAT_HOUR string("hh")
#define sFORMAT_MINUTE string("mm")

class CTimeStamp : public CDate {
public:
	CTimeStamp();
	CTimeStamp(double dSecondsSinceEpoch);
	CTimeStamp(int iYear, int iMonth, int iDay, int iHour, int iMinute);
	CTimeStamp(CTimeStamp & ctDifferentTimeStamp);

	int operator-(CTimeStamp & ctDifferentTimeStamp);
	CTimeStamp & operator-(int iHourDifference);
	CTimeStamp & operator+(int iHourDifference);

	friend ostream & operator<<(ostream & osOut, CTimeStamp & ctTimeStamp);

	string sFormat(string sFormat);

private:
	string sConvertToString();
	string sConvertToTimeAfterEpoch(string sFormat);
	string sConvertToTimeBeforeEpoch(string sFormat);

	string sConvertToFormat(string sFormat, string sHour, string sMinute);
};

ostream & operator<<(ostream & osOut, CTimeStamp & ctTimeStamp);
