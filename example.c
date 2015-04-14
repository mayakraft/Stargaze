#include "stargaze.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
	int year, month, day, hour, minute, second;
	getTime(&year, &month, &day, &hour, &minute, &second);

	// input year in UTC time
	double J2000 = UTCDaysSinceJ2000();
	// double sidereal = greenwichMeanSiderealTime(J2000);
	double sidereal = localMeanSiderealTime(J2000, -97.73);
	double apparent = apparentSiderealTime(J2000);
	printf("%f\t(%d/%d/%d)\t(%d:%2d:%2d) S:%f  A:%f\n", J2000, month, day, year, hour, minute, second, sidereal, apparent);



	// for(int i = 0; i < 24; i++){
	// 	int month = 2;
	// 	int day = 21;
	// 	int hour = i;
	// 	double J2000 = UTCDaysSinceJ2000(2015, month, day, hour, 0, 0);
	// 	double sidereal = greenwichMeanSiderealTime(J2000);
	// 	double apparent = apparentSiderealTime(J2000);
	// 	printf("(%d/%d/2015)\t(%f)\t(%d:00):%f, %f\n",month + 1, day + 1, J2000, hour, sidereal, apparent);
	// }

	// printf("\n\n\n");

	// for(int i = 0; i < 30; i++){
	// 	int month = 2;
	// 	int day = i;
	// 	int hour = 0;
	// 	double J2000 = UTCDaysSinceJ2000(2015, month, day, hour, 0, 0);
	// 	double sidereal = greenwichMeanSiderealTime(J2000);
	// 	double apparent = apparentSiderealTime(J2000);
	// 	printf("(%d/%d/2015)\t(%f)\t(%d:00):%f, %f\n",month + 1, day + 1, J2000, hour, sidereal, apparent);
	// }
	// printf("\n\n\n");

	// for(int i = 0; i < 12; i++){
	// 	int month = i;
	// 	int day = 21;
	// 	int hour = 0;
	// 	double J2000 = UTCDaysSinceJ2000(2015, month, day, hour, 0, 0);
	// 	double sidereal = greenwichMeanSiderealTime(J2000);
	// 	double apparent = apparentSiderealTime(J2000);
	// 	printf("(%d/%d/2015)\t(%f)\t(%d:00):%f, %f\n",month + 1, day + 1, J2000, hour, sidereal, apparent);
	// }

	// printf("\n\n\n");

	// int minute = 50;
	// for(int i = 0; i < 10; i++){
	// 	int month = 3;//rand()%12;
	// 	int day = i+1;//rand()%28;
	// 	int hour = 12;//rand()%24;
	// 	minute -= 4;
	// 	double J2000 = UTCDaysSinceJ2000(2015, month, day, hour, minute, 0);
	// 	double sidereal = greenwichMeanSiderealTime(J2000);
	// 	double apparent = apparentSiderealTime(J2000);
	// 	printf("(%d/%d/2015)\t(%f)\t(%d:%d):%f, %f\n",month + 1, day + 1, J2000, hour, minute, sidereal, apparent);
	// }
	
	return 0;
}

