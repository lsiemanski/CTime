#pragma once
#include<string>
#include<map>

using namespace std;

#define iEPOCH_YEAR 1970
#define iEPOCH_DAY 1
#define iEPOCH_MONTH 1

#define iLEAP_DATE_DAY 29
#define iLEAP_DATE_MONTH 2
#define iLEAP_YEAR_DIVIDER 4

#define iSECONDS_IN_MINUTE 60
#define iMINUTES_IN_HOUR 60
#define iHOURS_IN_DAY 24

#define iMONTHS_IN_YEAR 12
#define iDAYS_IN_YEAR 365
#define iDAYS_IN_LEAP_YEAR 366

#define sSTRING_DATE_REPRESENTATION_SEPARATOR string("-")

#define iJANUARY_INDEX 1
#define iDAYS_IN_JANUARY 31
#define iFEBRUARY_INDEX 2
#define iDAYS_IN_FEBRUARY 28
#define iMARCH_INDEX 3
#define iDAYS_IN_MARCH 31
#define iAPRIL_INDEX 4
#define iDAYS_IN_APRIL 30
#define iMAY_INDEX 5
#define iDAYS_IN_MAY 31
#define iJUNE_INDEX 6
#define iDAYS_IN_JUNE 30
#define iJULY_INDEX 7
#define iDAYS_IN_JULY 31
#define iAUGUST_INDEX 8
#define iDAYS_IN_AUGUST 31
#define iSEPTEMBER_INDEX 9
#define iDAYS_IN_SEPTEMBER 30
#define iOCTOBER_INDEX 10
#define iDAYS_IN_OCTOBER 31
#define iNOVEMBER_INDEX 11
#define iDAYS_IN_NOVEMBER 30
#define iDECEMBER_INDEX 12
#define iDAYS_IN_DECEMBER 31

#define sDEFAULT_DATE_FORMAT string("yyyy-MM-dd")
#define sFORMAT_YEAR string("yyyy")
#define sFORMAT_MONTH string("MM")
#define sFORMAT_DAY string("dd")

class CDate {
public:
	CDate();
	CDate(double dSecondsSinceEpoch);
	CDate(int iYear, int iMonth, int iDay);
	CDate(CDate& cdDifferentDate);

	int operator-(CDate & cdDifferentDate);

	CDate & operator-(int iDaysDifference);
	CDate & operator+(int iDaysDifference);

	bool operator<(CDate & cdDifferentDate);
	bool operator<=(CDate & cdDifferentDate);
	bool operator>(CDate & cdDifferentDate);
	bool operator>=(CDate & cdDifferentDate);
	bool operator==(CDate & cdDifferentDate);

	friend ostream & operator<<(ostream & osOut, CDate & cdDate);

	string sFormat(string sFormat);

protected:
	double dCountDaysSinceEpoch(int iYear, int iMonth, int iDay);
	double dCountDaysAfterEpoch(int iYear, int iMonth, int iDay);
	double dCountDaysBeforeEpoch(int iYear, int iMonth, int iDay);

	double d_seconds_since_epoch;
	map<int, int> mi_days_in_month;
	bool b_tmp;

	void vInitDaysInMonthMap();
	int iCountLeapYearsSinceEpoch(int iYear);
	
	string sConvertToString();
	string sConvertDateBeforeEpochToString(string sFormat);
	string sConvertDateAfterEpochToString(string sFormat);

	string sConvertToFormat(string sFormat, string sYear, string sMonth, string sDay);
};

ostream & operator<<(ostream & osOut, CDate & cdDate);