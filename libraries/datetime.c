#include "datetime.h"

#define DAY 24

DateTime* inicializeDateTime(){
	DateTime* date = (DateTime*) calloc(1, sizeof(DateTime));
	date->day = 0;
	date->hour = 0;
	date->minute = 0;
	date->hours2minutes = 0;
	return date;
}

void writeDateTime(DateTime* time, FILE* f){
	fprintf(f, "%dd:%dh:%dm (%d)", time->day, time->hour, time->minute, time->hours2minutes);
}

void showDateTime(DateTime* time){
	printf("%dd:%dh:%dm (%d)", time->day, time->hour, time->minute, time->hours2minutes);
}

int compareDateTime(DateTime* d1, DateTime* d2){
	if(d1->hours2minutes <= d2->hours2minutes)
	 	return 1;
	return 0;
}

DateTime* setDateTime(DateTime* new, DateTime* d){
	d->day = new->day;
	d->hour = new->hour;
	d->minute = new->minute;
	d->hours2minutes = new->hours2minutes;
	return d;
}

void setData2DateTime(DateTime* dateTime, int hour, int minute){
	while(minute >= 60){
		if(hour == 24)
			hour = 1;
		else
			hour++;
		minute = minute - 60;
	}
	//dateTime->day = hour / DAY;
	hour = hour % DAY;

	dateTime->hour = hour;
	dateTime->minute = minute;

	//if(hour == 0)
	//	dateTime->hours2minutes = dateTime->minute;
	//else
		dateTime->hours2minutes = (dateTime->hour * 60) + dateTime->minute;
}


int verifyToAddDay(int start_time, int end_time){
	int hours2minutes = start_time;
	if(start_time < end_time){
		hours2minutes = start_time + 1440;//soma um dia 
	}
	return hours2minutes;
}
