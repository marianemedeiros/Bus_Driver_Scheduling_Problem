#ifndef DATE_TIME_H
#define DATE_TIME_H

#include <stdlib.h>
#include <stdio.h>

typedef struct dateTime{
	int day;
	int hour;
	int minute;
	int hours2minutes;

}DateTime;

DateTime* inicializeDateTime();
int compareDateTime(DateTime* d1, DateTime* d2);
DateTime* setDateTime(DateTime* new, DateTime* d);
void setData2DateTime(DateTime* dateTime, int hour, int minute);
void writeDateTime(DateTime* time, FILE* f);
void showDateTime(DateTime* time);
int verifyToAddDay(int start_time, int end_time);

#endif