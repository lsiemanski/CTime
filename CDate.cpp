#include "CDate.h"
#include <iostream>
#include<iomanip>

using namespace std;

CDate::CDate() : d_seconds_since_epoch(0.0), b_tmp(false) { vInitDaysInMonthMap(); }

CDate::CDate(double dSecondsSinceEpoch) : CDate() {
	d_seconds_since_epoch = dSecondsSinceEpoch - (unsigned long)dSecondsSinceEpoch % (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);
}

CDate::CDate(int iYear, int iMonth, int iDay) : CDate() {

	if (!(iMonth > iMONTHS_IN_YEAR || (iYear % iLEAP_YEAR_DIVIDER == 0 && iDay > mi_days_in_month[iMonth] + 1) || (iYear % iLEAP_YEAR_DIVIDER != 0 && iDay > mi_days_in_month[iMonth]))) 
		d_seconds_since_epoch = dCountDaysSinceEpoch(iYear, iMonth, iDay) * iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE;
	
}

CDate::CDate(CDate & cdDifferentDate) : CDate() {
	d_seconds_since_epoch = cdDifferentDate.d_seconds_since_epoch - (unsigned long) cdDifferentDate.d_seconds_since_epoch % (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	if (cdDifferentDate.b_tmp) delete &cdDifferentDate;
}

int CDate::operator-(CDate & cdDifferentDate) {
	return (d_seconds_since_epoch - cdDifferentDate.d_seconds_since_epoch) / (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);
}

string CDate::sFormat(string sFormat) {
	if (d_seconds_since_epoch >= 0)
		return sConvertDateAfterEpochToString(sFormat);
	return sConvertDateBeforeEpochToString(sFormat);
}

double CDate::dCountDaysSinceEpoch(int iYear, int iMonth, int iDay) {
	if (iYear > iEPOCH_YEAR || (iYear == iEPOCH_YEAR && iMonth > iEPOCH_MONTH) || (iYear == iEPOCH_YEAR && iMonth == iEPOCH_MONTH && iDay >= iEPOCH_DAY))
		return dCountDaysAfterEpoch(iYear, iMonth, iDay);
	return dCountDaysBeforeEpoch(iYear, iMonth, iDay);
}

double CDate::dCountDaysAfterEpoch(int iYear, int iMonth, int iDay) {
	int i_leap_days_since_epoch = iCountLeapYearsSinceEpoch(iYear);

	if (iYear % iLEAP_YEAR_DIVIDER == 1 || (iYear % iLEAP_YEAR_DIVIDER == 0 && (iMonth > iLEAP_DATE_MONTH || (iMonth == iLEAP_DATE_MONTH && iDay > iLEAP_DATE_DAY))))
		i_leap_days_since_epoch++;

	int i_days_in_past_months = 0;

	for (int i = 1; i < iMonth; i++) {
		i_days_in_past_months += mi_days_in_month[i];
	}

	return iDAYS_IN_YEAR * (iYear - iEPOCH_YEAR) + i_leap_days_since_epoch + i_days_in_past_months + iDay - 1;
}

double CDate::dCountDaysBeforeEpoch(int iYear, int iMonth, int iDay) {
	int i_leap_days_since_epoch = iCountLeapYearsSinceEpoch(iYear) * (-1);

	if (iYear % iLEAP_YEAR_DIVIDER == 3 || (iYear % iLEAP_YEAR_DIVIDER == 0 && (iMonth < iLEAP_DATE_MONTH || (iMonth == iLEAP_DATE_MONTH && iDay <= iLEAP_DATE_DAY))))
		i_leap_days_since_epoch++;

	int i_days_in_past_months = 0;

	for (int i = 12; i > iMonth; i--) {
		i_days_in_past_months += mi_days_in_month[i];
	}

	return (iDAYS_IN_YEAR * (iEPOCH_YEAR - iYear - 1) + i_leap_days_since_epoch + i_days_in_past_months + mi_days_in_month[iMonth] - iDay + 1) * (-1);
}

void CDate::vInitDaysInMonthMap() {
	mi_days_in_month[iJANUARY_INDEX] = iDAYS_IN_JANUARY;
	mi_days_in_month[iFEBRUARY_INDEX] = iDAYS_IN_FEBRUARY;
	mi_days_in_month[iMARCH_INDEX] = iDAYS_IN_MARCH;
	mi_days_in_month[iAPRIL_INDEX] = iDAYS_IN_APRIL;
	mi_days_in_month[iMAY_INDEX] = iDAYS_IN_MARCH;
	mi_days_in_month[iJUNE_INDEX] = iDAYS_IN_JUNE;
	mi_days_in_month[iJULY_INDEX] = iDAYS_IN_JULY;
	mi_days_in_month[iAUGUST_INDEX] = iDAYS_IN_AUGUST;
	mi_days_in_month[iSEPTEMBER_INDEX] = iDAYS_IN_SEPTEMBER;
	mi_days_in_month[iOCTOBER_INDEX] = iDAYS_IN_OCTOBER;
	mi_days_in_month[iNOVEMBER_INDEX] = iDAYS_IN_NOVEMBER;
	mi_days_in_month[iDECEMBER_INDEX] = iDAYS_IN_DECEMBER;
}

int CDate::iCountLeapYearsSinceEpoch(int iYear) {
	return (iYear - iEPOCH_YEAR) / iLEAP_YEAR_DIVIDER;
}

string CDate::sConvertToString() {
	if (d_seconds_since_epoch >= 0)
		return sConvertDateAfterEpochToString(sDEFAULT_DATE_FORMAT);
	return sConvertDateBeforeEpochToString(sDEFAULT_DATE_FORMAT);
}

string CDate::sConvertDateBeforeEpochToString(string sFormat) {
	int i_year, i_month, i_day;

	int i_days_since_epoch = (-1) * d_seconds_since_epoch / (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	i_year = iEPOCH_YEAR;

	int i_days_to_start_of_gregorian_year = 0;

	i_days_to_start_of_gregorian_year += iEPOCH_DAY - 1;

	for (int i = iEPOCH_MONTH - 1; i > 0; i--) {
		i_days_to_start_of_gregorian_year += mi_days_in_month[i];

		if (iEPOCH_YEAR % iLEAP_YEAR_DIVIDER == 0 && i == iLEAP_DATE_MONTH)
			i_days_to_start_of_gregorian_year++;

	}

	if (i_days_to_start_of_gregorian_year <= i_days_since_epoch) {
		i_days_since_epoch -= i_days_to_start_of_gregorian_year;
		i_year--;

		while ((i_year % iLEAP_YEAR_DIVIDER != 0 && i_days_since_epoch >= iDAYS_IN_YEAR) || (i_year % iLEAP_YEAR_DIVIDER == 0 && i_days_since_epoch >= iDAYS_IN_LEAP_YEAR)) {
			if (i_year % iLEAP_YEAR_DIVIDER != 0) {
				i_days_since_epoch -= iDAYS_IN_YEAR;
			} else {
				i_days_since_epoch -= iDAYS_IN_LEAP_YEAR;
			}

			i_year--;
		}
	}

	i_month = 12;

	while ((i_year % iLEAP_YEAR_DIVIDER == 0 && i_month == iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month] + 1) || (i_month != iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month]) || (i_year % iLEAP_YEAR_DIVIDER != 0 && i_month == iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month])) {
		i_days_since_epoch -= mi_days_in_month[i_month];

		if (i_month == iLEAP_DATE_MONTH && i_year % iLEAP_YEAR_DIVIDER == 0)
			i_days_since_epoch--;

		i_month--;
	}

	i_day = mi_days_in_month[i_month] - i_days_since_epoch;

	if (i_year % iLEAP_YEAR_DIVIDER == 0 && i_month == iLEAP_DATE_MONTH)
		i_day++;

	string s_month, s_day;

	if (i_month / 10 == 0) {
		s_month = "0" + to_string(i_month);
	} else {
		s_month = to_string(i_month);
	}

	if (i_day / 10 == 0) {
		s_day = "0" + to_string(i_day);
	} else {
		s_day = to_string(i_day);
	}

	return sConvertToFormat(sFormat, to_string(i_year), s_month, s_day);
}

string CDate::sConvertDateAfterEpochToString(string sFormat) {
	int i_year, i_month, i_day;
	
	int i_days_since_epoch = d_seconds_since_epoch / (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	i_year = iEPOCH_YEAR;

	int i_days_to_end_of_gregorian_year = 0;

	i_days_to_end_of_gregorian_year += mi_days_in_month[iEPOCH_MONTH] - iEPOCH_DAY + 1;

	for (int i = iEPOCH_MONTH + 1; i <= 12; i++) {
		i_days_to_end_of_gregorian_year += mi_days_in_month[i];

		if (iEPOCH_YEAR % iLEAP_YEAR_DIVIDER == 0 && i == iLEAP_DATE_MONTH)
			i_days_to_end_of_gregorian_year++;

	}

	if (i_days_to_end_of_gregorian_year <= i_days_since_epoch) {
		i_days_since_epoch -= i_days_to_end_of_gregorian_year;
		i_year++;

		while ((i_year % iLEAP_YEAR_DIVIDER != 0 && i_days_since_epoch >= iDAYS_IN_YEAR) || (i_year % iLEAP_YEAR_DIVIDER == 0 && i_days_since_epoch >= iDAYS_IN_LEAP_YEAR)) {
			if (i_year % iLEAP_YEAR_DIVIDER != 0) {
				i_days_since_epoch -= iDAYS_IN_YEAR;
			} else {
				i_days_since_epoch -= iDAYS_IN_LEAP_YEAR;
			}
			i_year++;
		}

	}

	i_month = 1;

	while ((i_year % 4 == 0 && i_month == iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month] + 1) || (i_month != iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month]) || (i_year % 4 != 0 && i_month == iLEAP_DATE_MONTH && i_days_since_epoch >= mi_days_in_month[i_month])) {
		i_days_since_epoch -= mi_days_in_month[i_month];

		if (i_month == iLEAP_DATE_MONTH && i_year % iLEAP_YEAR_DIVIDER == 0)
			i_days_since_epoch--;

		i_month++;
	}

	i_day = i_days_since_epoch + 1;

	string s_month, s_day;

	if (i_month / 10 == 0) {
		s_month = "0" + to_string(i_month);
	} else {
		s_month = to_string(i_month);
	}

	if (i_day / 10 == 0) {
		s_day = "0" + to_string(i_day);
	} else {
		s_day = to_string(i_day);
	}

	return sConvertToFormat(sFormat, to_string(i_year), s_month, s_day);
}

string CDate::sConvertToFormat(string sFormat, string sYear, string sMonth, string sDay) {
	int i_year_index = sFormat.find(sFORMAT_YEAR);
	int i_month_index = sFormat.find(sFORMAT_MONTH);
	int i_day_index = sFormat.find(sFORMAT_DAY);
	
	string s_result = sFormat;

	if (i_year_index != -1)
		s_result.replace(i_year_index, sFORMAT_YEAR.length(), sYear);

	if (i_month_index != -1)
		s_result.replace(i_month_index, sFORMAT_MONTH.length(), sMonth);

	if (i_day_index != -1)
		s_result.replace(i_day_index, sFORMAT_DAY.length(), sDay);

	return s_result;
}

CDate & CDate::operator-(int iDaysDifference) {
	CDate* cd_result = new CDate(d_seconds_since_epoch - iDaysDifference * iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	cd_result->b_tmp = true;

	return *cd_result;
}

CDate & CDate::operator+(int iDaysDifference) {
	CDate* cd_result = new CDate(d_seconds_since_epoch + iDaysDifference * iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	cd_result->b_tmp = true;

	return *cd_result;
}

bool CDate::operator<(CDate & cdDifferentDate) {
	return d_seconds_since_epoch < cdDifferentDate.d_seconds_since_epoch;
}

bool CDate::operator<=(CDate & cdDifferentDate) {
	return d_seconds_since_epoch <= cdDifferentDate.d_seconds_since_epoch;
}

bool CDate::operator>(CDate & cdDifferentDate) {
	return d_seconds_since_epoch > cdDifferentDate.d_seconds_since_epoch;
}

bool CDate::operator>=(CDate & cdDifferentDate) {
	return d_seconds_since_epoch >= cdDifferentDate.d_seconds_since_epoch;
}

bool CDate::operator==(CDate & cdDifferentDate) {
	return d_seconds_since_epoch == cdDifferentDate.d_seconds_since_epoch;
}

ostream & operator<<(ostream & osOut, CDate & cdDate) {
	osOut << cdDate.sConvertToString();
	return osOut;
}
