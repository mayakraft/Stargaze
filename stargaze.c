#include <math.h>
#include <stdlib.h>
#include <time.h>

#define D2R 0.01745329251994 // degrees to radians

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

float* float9ToFloat16(float *a){
	float *m = malloc(sizeof(float)*16);
	m[0] = a[0];	m[1] = a[1];	m[2] = a[2];	m[3] = 0.0f;
	m[4] = a[3];	m[5] = a[4];	m[6] = a[5];	m[7] = 0.0f;
	m[8] = a[6];	m[9] = a[7];	m[10] = a[8];	m[11] = 0.0f;
	m[12] = 0.0f;	m[13] = 0.0f;	m[14] = 0.0f;	m[15] = 1.0f;
	return m;
}

// OPEN FRAMEWORKS
// Multiply a 3x3 matrix with a 3x3 matrix
 
float* mat3x3Mult(const float* A, const float* B) {
	float *C = malloc(sizeof(float)*9);
	C[0] = A[0] * B[0] + A[1] * B[3] + A[2] * B[6];
	C[1] = A[0] * B[1] + A[1] * B[4] + A[2] * B[7];
	C[2] = A[0] * B[2] + A[1] * B[5] + A[2] * B[8];
	C[3] = A[3] * B[0] + A[4] * B[3] + A[5] * B[6];
	C[4] = A[3] * B[1] + A[4] * B[4] + A[5] * B[7];
	C[5] = A[3] * B[2] + A[4] * B[5] + A[5] * B[8];
	C[6] = A[6] * B[0] + A[7] * B[3] + A[8] * B[6];
	C[7] = A[6] * B[1] + A[7] * B[4] + A[8] * B[7];
	C[8] = A[6] * B[2] + A[7] * B[5] + A[8] * B[8];
	return C;
}

// ASTRONOMY

void getTime(int *year, int *month, int *day, int *hour, int *minute, int *second){
	time_t current;
	time(&current);
	struct tm GMT;
	GMT = *gmtime(&current);
	*year = GMT.tm_year + 1900;
	*month = GMT.tm_mon + 1;
	*day = GMT.tm_mday;
	*hour = GMT.tm_hour;
	*minute = GMT.tm_min;
	*second = GMT.tm_sec;
}

// time since january 1st, at 12:00 (noon)
double UTCDaysSinceJ2000(){
	int year, month, day, hour, minute, second;
	getTime(&year, &month, &day, &hour, &minute, &second);
	double wholePart = 367*year-floor(7*(year+floor((month+9)/12.0))/4.0)+floor(275*month/9.0)+day-730531.5;
	double fractionalPart = (hour + minute/60.0 + second/3600.0)/24.0;
	return (double)wholePart + fractionalPart;
}

// time since january 1st, at 12:00 (noon)
double UTCDaysSinceJ2000WithInput(int year, int month, int day, int hour, int minute, int second){
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

void rotation(float degrees, float x, float y, float z){

}

float earthRotation(){
	float sidereal;
	rotation(sidereal, 0, 0, 1);
	rotation(23.4, 1, 0 ,0);
	return 0.0f;
} 

//90 degree rotation around Y (second axis)
//180 degree rotation around Z (third axis)
float phoneToHorizonal3x3[9] = {
	0.0f, 0.0f, 1.0f,
	0.0f, -1.0f, 0.0f,
	1.0f, 0.0f, 0.0f };

float phoneToHorizonal4x4[16] = {
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,1.0f, 
};

float* latitudeLongitudeDisplacement(float latitude, float longitude){
	float *m = malloc(sizeof(float) * 9 );
	m[0] = cosf(latitude*D2R)*cosf(longitude*D2R);      m[1] = sinf(longitude*D2R);     m[2] = -sinf(latitude*D2R)*cosf(longitude*D2R);
	m[3] = cosf(latitude*D2R)*-sinf(longitude*D2R);     m[4] = cosf(longitude*D2R);     m[5] = -sinf(latitude*D2R)*-sinf(longitude*D2R);
	m[6] = sinf(latitude*D2R);                          m[7] = 0.0f;                    m[8] = cosf(latitude*D2R);
	return m;
}


void horizonalOrientation(float longitude, float latitude){

}

// your displacement from 0°N, 0°E, in the Gulf of Guinea off the coast of Africa, expressed a Rotation matrix.
float* celestialOrientation(float longitude, float latitude, int year, int month, int day, int hour, int minute, int second){
	float axT = 23.4;

	double J2000 = UTCDaysSinceJ2000();
	// double sidereal = greenwichMeanSiderealTime(J2000);
	double sidereal = localMeanSiderealTime(J2000, -97.73);

	float *r = malloc(sizeof(float) * 9);
	return r;
}
