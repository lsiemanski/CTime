/* PLIK STWORZONY W CELU ZACHOWANIA PIERWSZEGO KODU PRACUJ¥CEGO ZE ZNACZNIKAMI CZASOWYMI I DATAMI
	W£AŒCIWIE ZAIMPLEMENTOWANE ALGORYTMY ZOSTA£Y DODANE DO KLASY CDATE */
#include <float.h>
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

double d_seconds_since_epoch(int day, int month, int year, int hour, int minute, int second) {
	int iEPOCH_DAY = 1;
	int iEPOCH_MONTH = 1;
	int iEPOCH_YEAR = 1970;
	int iEPOCH_HOUR = 0;
	int iEPOCH_MINUTE = 0;
	int iEPOCH_SECOND = 0;
	int iLEAP_DATE_DAY = 29;
	int iLEAP_DATE_MONTH = 2;
	map<int, int> days_in_month;
	days_in_month[1] = 31;
	days_in_month[2] = 28;
	days_in_month[3] = 31;
	days_in_month[4] = 30;
	days_in_month[5] = 31;
	days_in_month[6] = 30;
	days_in_month[7] = 31;
	days_in_month[8] = 31;
	days_in_month[9] = 30;
	days_in_month[10] = 31;
	days_in_month[11] = 30;
	days_in_month[12] = 31;

	int iLeapYearsSinceEpoch;

	iLeapYearsSinceEpoch = (year - iEPOCH_YEAR) / 4;

	if (year % 4 == 1 || (year % 4 == 0 && (month > iLEAP_DATE_MONTH || (month == iLEAP_DATE_MONTH && day > iLEAP_DATE_DAY))))
		iLeapYearsSinceEpoch++;

	cout << year << ", " << iLeapYearsSinceEpoch << endl;

	int days_since_epoch = 365 * (year - iEPOCH_YEAR) + iLeapYearsSinceEpoch;

	for (int i = 1; i < month; i++) {
		days_since_epoch += days_in_month[i];
	}

	days_since_epoch += day - 1;

	double seconds_since_epoch = days_since_epoch * 60.0 * 60.0 * 24.0 + hour * 60.0 * 60.0 + minute * 60.0 + second;

	return seconds_since_epoch;

}

double d_seconds_before_epoch(int day, int month, int year, int hour, int minute, int second) {
	int iEPOCH_DAY = 1;
	int iEPOCH_MONTH = 1;
	int iEPOCH_YEAR = 1970;
	int iEPOCH_HOUR = 0;
	int iEPOCH_MINUTE = 0;
	int iEPOCH_SECOND = 0;
	int iLEAP_DATE_DAY = 29;
	int iLEAP_DATE_MONTH = 2;
	map<int, int> days_in_month;
	days_in_month[1] = 31;
	days_in_month[2] = 28;
	days_in_month[3] = 31;
	days_in_month[4] = 30;
	days_in_month[5] = 31;
	days_in_month[6] = 30;
	days_in_month[7] = 31;
	days_in_month[8] = 31;
	days_in_month[9] = 30;
	days_in_month[10] = 31;
	days_in_month[11] = 30;
	days_in_month[12] = 31;

	int iLeapYearsSinceEpoch;

	iLeapYearsSinceEpoch = (iEPOCH_YEAR - year) / 4;

	if (year % 4 == 3 || (year % 4 == 0 && (month < iLEAP_DATE_MONTH || (month == iLEAP_DATE_MONTH && day <= iLEAP_DATE_DAY))))
		iLeapYearsSinceEpoch++;

	cout << year << ", " << iLeapYearsSinceEpoch << endl;

	int days_since_epoch = 365 * (iEPOCH_YEAR - year - 1) + iLeapYearsSinceEpoch;

	for (int i = 12; i > month; i--) {
		days_since_epoch += days_in_month[i];
	}

	days_since_epoch += days_in_month[month] - day;

	double seconds_since_epoch = days_since_epoch * 60.0 * 60.0 * 24.0 + (24 - 1 - hour) * 60.0 * 60.0 + (60 - 1 - minute) * 60.0 + (60 - second);

	return seconds_since_epoch * (-1);

}

double d_count_time(int day, int month, int year, int hour, int minute, int second) {
	int iEPOCH_DAY = 1;
	int iEPOCH_MONTH = 1;
	int iEPOCH_YEAR = 1970;
	if (year > iEPOCH_YEAR) {

		return d_seconds_since_epoch(day, month, year, hour, minute, second);

	}
	else if (year < iEPOCH_YEAR) {

		return d_seconds_before_epoch(day, month, year, hour, minute, second);

	}
	else {

		if (month > iEPOCH_MONTH) {

			return d_seconds_since_epoch(day, month, year, hour, minute, second);

		}
		else if (month < iEPOCH_MONTH) {

			return d_seconds_before_epoch(day, month, year, hour, minute, second);

		}
		else {

			if (day >= iEPOCH_DAY)
				return d_seconds_since_epoch(day, month, year, hour, minute, second);
			return d_seconds_before_epoch(day, month, year, hour, minute, second);

		}

	}
}

void count_date_after(double d_time) {
	int iEPOCH_DAY = 1;
	int iEPOCH_MONTH = 1;
	int iEPOCH_YEAR = 1970;
	int iEPOCH_HOUR = 0;
	int iEPOCH_MINUTE = 0;
	int iEPOCH_SECOND = 0;
	int iLEAP_DATE_DAY = 29;
	int iLEAP_DATE_MONTH = 2;
	map<int, int> days_in_month;
	days_in_month[1] = 31;
	days_in_month[2] = 28;
	days_in_month[3] = 31;
	days_in_month[4] = 30;
	days_in_month[5] = 31;
	days_in_month[6] = 30;
	days_in_month[7] = 31;
	days_in_month[8] = 31;
	days_in_month[9] = 30;
	days_in_month[10] = 31;
	days_in_month[11] = 30;
	days_in_month[12] = 31;

	int year, month, day, hour, minute, second;

	int days_since_epoch = d_time / (24 * 60 * 60);
	int dayclock = (unsigned long)d_time % (24 * 60 * 60);

	second = dayclock % 60;
	minute = (dayclock % (60 * 60)) / 60;
	hour = dayclock / 3600;

	year = iEPOCH_YEAR;

	int days_to_end_of_gregorian_year = 0;

	days_to_end_of_gregorian_year += days_in_month[iEPOCH_MONTH] - iEPOCH_DAY + 1;

	for (int i = iEPOCH_MONTH + 1; i <= 12; i++) {
		days_to_end_of_gregorian_year += days_in_month[i];

		if (iEPOCH_YEAR % 4 == 0 && i == iLEAP_DATE_MONTH)
			days_to_end_of_gregorian_year++;

	}

	if (days_to_end_of_gregorian_year <= days_since_epoch) {
		days_since_epoch -= days_to_end_of_gregorian_year;
		year++;

		while (days_since_epoch >= 365) {
			if (year % 4 == 0) {
				days_since_epoch -= 366;
			}
			else {
				days_since_epoch -= 365;
			}
			year++;
		}

	}

	month = 1;

	while ((year % 4 == 0 && month == iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month] + 1) || (month != iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month]) || (year % 4 != 0 && month == iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month])) {
		days_since_epoch -= days_in_month[month];

		if (month == iLEAP_DATE_MONTH && year % 4 == 0)
			days_since_epoch--;

		month++;
	}

	day = days_since_epoch + 1;

	printf("%d.%d.%d %d::%d::%d", day, month, year, hour, minute, second);

	cout << endl;
}

void count_date_before(double d_time) {
	int iEPOCH_DAY = 1;
	int iEPOCH_MONTH = 1;
	int iEPOCH_YEAR = 1970;
	int iEPOCH_HOUR = 0;
	int iEPOCH_MINUTE = 0;
	int iEPOCH_SECOND = 0;
	int iLEAP_DATE_DAY = 29;
	int iLEAP_DATE_MONTH = 2;
	map<int, int> days_in_month;
	days_in_month[1] = 31;
	days_in_month[2] = 28;
	days_in_month[3] = 31;
	days_in_month[4] = 30;
	days_in_month[5] = 31;
	days_in_month[6] = 30;
	days_in_month[7] = 31;
	days_in_month[8] = 31;
	days_in_month[9] = 30;
	days_in_month[10] = 31;
	days_in_month[11] = 30;
	days_in_month[12] = 31;

	int year, month, day, hour, minute, second;

	d_time = abs(d_time);

	int days_since_epoch = d_time / (24 * 60 * 60);
	int dayclock = (unsigned long)(abs(d_time)) % (24 * 60 * 60);

	second = 60 - dayclock % 60;
	minute = 60 - 1 - ((dayclock % (60 * 60)) / 60);
	hour = 24 - 1 - dayclock / 3600;

	year = iEPOCH_YEAR;

	int days_to_start_of_gregorian_year = 0;

	days_to_start_of_gregorian_year += iEPOCH_DAY - 1;

	for (int i = iEPOCH_MONTH - 1; i > 0; i--) {
		days_to_start_of_gregorian_year += days_in_month[i];

		if (iEPOCH_YEAR % 4 == 0 && i == iLEAP_DATE_MONTH)
			days_to_start_of_gregorian_year++;

	}

	if (days_to_start_of_gregorian_year <= days_since_epoch) {
		days_since_epoch -= days_to_start_of_gregorian_year;
		year--;

		while (days_since_epoch >= 365) {
			if (year % 4 == 0) {
				days_since_epoch -= 366;
			}
			else {
				days_since_epoch -= 365;
			}
			year--;
		}
	}

	month = 12;

	while ((year % 4 == 0 && month == iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month] + 1) || (month != iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month]) || (year % 4 != 0 && month == iLEAP_DATE_MONTH && days_since_epoch >= days_in_month[month])) {
		days_since_epoch -= days_in_month[month];

		if (month == iLEAP_DATE_MONTH && year % 4 == 0)
			days_since_epoch--;

		month--;
	}

	day = days_in_month[month] - days_since_epoch;

	if (year % 4 == 0 && month == iLEAP_DATE_MONTH)
		day++;

	printf("%d.%d.%d %d::%d::%d", day, month, year, hour, minute, second);

	cout << endl;
}

void count_date(double d_time) {
	if (d_time >= 0) {
		count_date_after(d_time);
	}
	else {
		count_date_before(d_time);
	}
}