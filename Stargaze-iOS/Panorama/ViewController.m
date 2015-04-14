//
//  ViewController.m
//  Panorama
//
//  Created by Robby Kraft on 8/24/13.
//  Copyright (c) 2013 Robby Kraft. All Rights Reserved.
//

#import "ViewController.h"
#import "PanoramaView.h"


@interface ViewController (){
    PanoramaView *panoramaView;
}
@end

@implementation ViewController

- (void)viewDidLoad{
    [super viewDidLoad];
    panoramaView = [[PanoramaView alloc] init];
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

-(void) glkView:(GLKView *)view drawInRect:(CGRect)rect{
    [panoramaView draw];
//    static int counter = 0;
//    counter++;
//    if(counter % 20 == 0){
//        [self calculateOrientation];
//    }
}

@end