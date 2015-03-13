#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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

double UTCDaysSinceJ2000(int year, int month, int day, int hour, int minute, int second){
	int wholePart = 367 * year - floor(7 * (year + floor(month+9)/12.0)/4.0) 
				+ floor(275 * month/9.0) + day - 730531.5; 
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	return wholePart + fractionalPart;
}

double daysSinceJ2000(int timeZone, int year, int month, int day, int hour, int minute, int second){
	return UTCDaysSinceJ2000(year, month, day, hour + timeZone, minute, second);
}

void meanSiderealTime(double J2000Day, double longitude){
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

	double greenwichMeanSiderealTime = mod360(280.46061837 + 360.98564736629 * J2000Day + LTR);

	double localMeanSiderealTime = mod360(280.46061837 + 360.98564736629 * J2000Day + LTR + longitude);
}

// incorporates the wobble caused by the moon's pull, the barycenter is not at the center of the Earth
void apparentSiderealTime(double J2000Day){
	double t = J2000Day / 36525.0;
	// GMST = greenwichMeanSiderealTime();

	double Om = mod360(125.04452 - 1934.136261 * t);
	double L = mod360(280.4665 + 36000.7698 * t);
	double L1 = mod360(218.3165 + 481267.8813 * t);
	double e = mod360(23.439 - 0.0000004 * t);

}


int main(){
	double J2000 = daysInJ2000(2015, 3, 10, 12, 33, 10);
	printf("%f\n",J2000);
	return 0;
}