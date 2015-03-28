//
//  ViewController.m
//  Panorama
//
//  Created by Robby Kraft on 8/24/13.
//  Copyright (c) 2013 Robby Kraft. All Rights Reserved.
//

#import "ViewController.h"
#import "PanoramaView.h"
#include "stargaze.c"

@interface ViewController (){
    PanoramaView *panoramaView;
}
@end

@implementation ViewController

- (void)viewDidLoad{
    [super viewDidLoad];
    panoramaView = [[PanoramaView alloc] init];
    [panoramaView setImage:@"Tycho_2048_city.png"];
    [panoramaView setOrientToDevice:YES];
    [panoramaView setTouchToPan:NO];
    [panoramaView setPinchToZoom:YES];
    [panoramaView setShowTouches:NO];
    
    
    float m[16];
    float axT = 23.4;
    m[0] = 1.0f;		m[1] = 0.0f;		m[2] = 0.0f;        m[3] = 0.0f;
    m[4] = 0.0f;		m[5] = cosf(axT);	m[6] = -sinf(axT);  m[7] = 0.0f;
    m[8] = 0.0f;		m[9] = sinf(axT);	m[10] = cosf(axT);  m[11] = 0.0f;
    m[12] = 0.0f;       m[13] = 0.0f;       m[14] = 0.0f;       m[15] = 1.0f;
    
    [panoramaView setOrientation1:m];
    [panoramaView setLatitude:10.2500];
    [panoramaView setLongitude:-10.7500];

    [self setView:panoramaView];
}

-(void) calculateOrientation{
    // GET TIME
    int year, month, day, hour, minute, second;
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
}

-(void) glkView:(GLKView *)view drawInRect:(CGRect)rect{
    [panoramaView draw];
    static int counter = 0;
    counter++;
    if(counter % 20 == 0){
        [self calculateOrientation];
    }
}

@end