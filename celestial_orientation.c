#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double UTCTimeInJ2000(int year, int month, int day, int hour, int minute, int second){
	int wholePart = 367 * year - floor(7 * (year + floor(month+9)/12.0)/4.0) 
				+ floor(275 * month/9.0) + day - 730531.5; 
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	return wholePart + fractionalPart;
}

double timeInJ2000(int timeZone, int year, int month, int day, int hour, int minute, int second){
	return UTCTimeInJ2000(year, month, day, hour + timeZone, minute, second);
}

int main(){
	double J2000 = timeInJ2000(2015, 3, 10, 12, 33, 10);
	printf("%f\n",J2000);
	return 0;
}