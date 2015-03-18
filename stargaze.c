#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// MATH

double mod360(double input){
	if(input > 360.0){
		int n = input / 360.0;
		return input - n*360;
	}
	if(input < 0.0){
		int n = input / 360.0;
		return input - (n-1)*360;
	}
	return input;
}

// ASTRONOMY

// time since january 1st, at 12:00 (noon)
double UTCDaysSinceJ2000(int year, int month, int day, int hour, int minute, int second){
	double wholePart = 367*year-floor(7*(year+floor((month+9)/12.0))/4.0)+floor(275*month/9.0)+day-730531.5;
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	return (double)wholePart + fractionalPart;
}

// double daysSinceJ2000(int timeZone, int year, int month, int day, int hour, int minute, int second){
// 	return UTCDaysSinceJ2000(year, month, day, hour + timeZone, minute, second);
// }

double greenwichMeanSiderealTime(double J2000Day){
	// In 10 years, the approximation error will be 0.001 seconds. 30
	// years from now the error will still be better than 0.01 seconds.
	// A century from now, the approximation error will be 0.1 seconds.
	// However, 10 centuries from now the error will be 10 seconds....

	// longer time reach, or set to 0 for quick calculation
	// double LTR = 0.0;
	double LTR = 0.000388 * pow(J2000Day/36525.0, 2);
	// Errors through truncation with longer time reach amount to 0.008
	// seconds 1000 years into the future or past, and 0.0003 seconds
	// 300 years into the future or past. With this kind of calculation,
	// you must be very careful about time. The formulas here use UT,
	// not dynamical time, known as TDT. Formulas used to predict the
	// positions of planets, the Moon, eclipses and so on use TDT. 

	return mod360(280.46061837 + 360.98564736629 * J2000Day + LTR);
}

// J2000 time must be from GMT time zone
double localMeanSiderealTime(double J2000Day, double longitude){
	double LTR = 0.000388 * pow(J2000Day/36525.0, 2);
	return mod360(280.46061837 + 360.98564736629 * J2000Day + LTR + longitude);
}

// incorporates the wobble caused by the moon's pull, the barycenter is not at the center of the Earth
double apparentSiderealTime(double J2000Day){
	double t = J2000Day / 36525.0;
	// GMST = greenwichMeanSiderealTime();

	double Om = mod360(125.04452 - 1934.136261 * t);
	double L = mod360(280.4665 + 36000.7698 * t);
	double L1 = mod360(218.3165 + 481267.8813 * t);
	double e = mod360(23.439 - 0.0000004 * t);

	double dp = -17.2*sin(Om) -1.32*sin(2*L) -0.23*sin(2*L1) +0.21*sin(2*Om);
	double de =   9.2*cos(Om) +0.57*cos(2*L) + 0.1*cos(2*L1) -0.09 *cos(2*Om);
	// e = eps + de;
	e = dp + de;

	// double correction = dp * cos(e) / 15;
	double correction = dp * cos(e) / 3600.0;
	return correction;
}

int main(){
	int year, month, day, hour, minute, second;
	// year = 2015; month = 3; day = 18; hour = 5; minute = 20; second = 0;
	time_t current;
	time(&current);
	struct tm GMT;
	GMT = *gmtime(&current);
	year = GMT.tm_year + 1900;
	month = GMT.tm_mon + 1;
	day = GMT.tm_mday;
	hour = GMT.tm_hour;
	minute = GMT.tm_min;
	second = GMT.tm_sec;


	// input year in UTC time
	double J2000 = UTCDaysSinceJ2000(year, month, day, hour, minute, second);
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

