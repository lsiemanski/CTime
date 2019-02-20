#include "CTimeStamp.h"
#include <iostream>
#include <iomanip>

using namespace std;

CTimeStamp::CTimeStamp() : CDate(0.0) {}

CTimeStamp::CTimeStamp(double dSecondsSinceEpoch) : CTimeStamp() {
	d_seconds_since_epoch = dSecondsSinceEpoch;
}

CTimeStamp::CTimeStamp(int iYear, int iMonth, int iDay, int iHour, int iMinute) : CTimeStamp() {
	if (!(iMonth > iMONTHS_IN_YEAR || (iYear % iLEAP_YEAR_DIVIDER == 0 && iDay > mi_days_in_month[iMonth] + 1) || (iYear % iLEAP_YEAR_DIVIDER != 0 && iDay > mi_days_in_month[iMonth]) || iHour > iHOURS_IN_DAY || iMinute > iMINUTES_IN_HOUR))
		d_seconds_since_epoch = dCountDaysSinceEpoch(iYear, iMonth, iDay) * iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE + iHour * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE + iMinute * iSECONDS_IN_MINUTE;
}

CTimeStamp::CTimeStamp(CTimeStamp & ctDifferentTimeStamp) {
	d_seconds_since_epoch = ctDifferentTimeStamp.d_seconds_since_epoch;
	vInitDaysInMonthMap();
	b_tmp = false;

	if (ctDifferentTimeStamp.b_tmp) delete &ctDifferentTimeStamp;
}

int CTimeStamp::operator-(CTimeStamp & ctDifferentTimeStamp) {
	return ((long)(d_seconds_since_epoch - ctDifferentTimeStamp.d_seconds_since_epoch)) / (iSECONDS_IN_MINUTE);
}

CTimeStamp & CTimeStamp::operator-(int iHourDifference) {
	CTimeStamp* ct_result = new CTimeStamp(d_seconds_since_epoch - iHourDifference * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	ct_result->b_tmp = true;

	return *ct_result;
}

CTimeStamp & CTimeStamp::operator+(int iHourDifference) {
	CTimeStamp* ct_result = new CTimeStamp(d_seconds_since_epoch + iHourDifference * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	ct_result->b_tmp = true;

	return *ct_result;
}

string CTimeStamp::sFormat(string sFormat) {
	if (d_seconds_since_epoch >= 0)
		return sConvertToTimeAfterEpoch(sConvertDateAfterEpochToString(sFormat));
	return sConvertToTimeBeforeEpoch(sConvertDateBeforeEpochToString(sFormat));
}

string CTimeStamp::sConvertToString() {
	if (d_seconds_since_epoch >= 0)
		return sConvertToTimeAfterEpoch(sConvertDateAfterEpochToString(sDEFAULT_DATE_FORMAT + " " + sDEFAULT_TIME_FORMAT));
	return sConvertToTimeBeforeEpoch(sConvertDateBeforeEpochToString(sDEFAULT_DATE_FORMAT + " " + sDEFAULT_TIME_FORMAT));
}

string CTimeStamp::sConvertToTimeAfterEpoch(string sFormat) {
	int i_hour, i_minute;

	int i_dayclock = (unsigned long)d_seconds_since_epoch % (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	i_hour = i_dayclock / (iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);
	i_minute = (i_dayclock % (iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE)) / iSECONDS_IN_MINUTE;

	string s_hour_to_return, s_minute_to_return;

	if (i_hour / 10 == 0) {
		s_hour_to_return = "0" + to_string(i_hour);
	} else {
		s_hour_to_return = to_string(i_hour);
	}
	
	if (i_minute / 10 == 0) {
		s_minute_to_return = "0" + to_string(i_minute);
	} else {
		s_minute_to_return = to_string(i_minute);
	}

	return sConvertToFormat(sFormat, s_hour_to_return, s_minute_to_return);
}

string CTimeStamp::sConvertToTimeBeforeEpoch(string sFormat) {
	int i_hour, i_minute;

	int i_dayclock = (-1) * (unsigned long)d_seconds_since_epoch % (iHOURS_IN_DAY * iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE);

	i_hour = iHOURS_IN_DAY - (i_dayclock / (iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE));
	i_minute = iMINUTES_IN_HOUR - (i_dayclock % (iMINUTES_IN_HOUR * iSECONDS_IN_MINUTE)) / iSECONDS_IN_MINUTE;

	string s_hour_to_return, s_minute_to_return;

	if (i_hour / 10 == 0) {
		s_hour_to_return = "0" + to_string(i_hour);
	} else {
		s_hour_to_return = to_string(i_hour);
	}

	if (i_minute / 10 == 0) {
		s_minute_to_return = "0" + to_string(i_minute);
	} else {
		s_minute_to_return = to_string(i_minute);
	}

	return sConvertToFormat(sFormat, s_hour_to_return, s_minute_to_return);
}

string CTimeStamp::sConvertToFormat(string sFormat, string sHour, string sMinute) {
	int i_hour_index = sFormat.find(sFORMAT_HOUR);
	int i_minute_index = sFormat.find(sFORMAT_MINUTE);

	string s_result = sFormat;

	if (i_hour_index != -1)
		s_result.replace(i_hour_index, sFORMAT_HOUR.length(), sHour);

	if (i_minute_index != -1)
		s_result.replace(i_minute_index, sFORMAT_MINUTE.length(), sMinute);

	return s_result;
}

ostream & operator<<(ostream & osOut, CTimeStamp & ctTimeStamp) {
	osOut << ctTimeStamp.sConvertToString();
	return osOut;
}
