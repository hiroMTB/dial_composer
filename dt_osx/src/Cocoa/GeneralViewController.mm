//
//  GeneralViewController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//
#include "ofMain.h"
#include "ofApp.h"
#import "GeneralViewController.h"

@interface GeneralViewController ()
@end

@implementation GeneralViewController
@synthesize bpm_sl;
@synthesize bpm_tx;
@synthesize bg_color;
@synthesize fps_tx;
@synthesize circle_num_tx;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (IBAction)change_bpm:(id)sender {
    float bpm = [sender floatValue];
    [bpm_sl setFloatValue:bpm];
    [bpm_tx setFloatValue:bpm];
    ofApp * app = ofApp::getInstance();
    if( app ) app->sequence_thread.change_bpm( bpm );
}

- (IBAction)change_bg_color:(id)sender {
    float r = ( (NSColorWell*)sender ).color.redComponent;
    float g = ( (NSColorWell*)sender ).color.greenComponent;
    float b = ( (NSColorWell*)sender ).color.blueComponent;
    ofApp * app = ofApp::getInstance();
    if( app )app->bg.set( r, g, b, 1.0 );
}

- (void)update_fps:(float)fps {
    [fps_tx setFloatValue:fps];
}

- (void)update_circle_num:(int)n {
    [circle_num_tx setIntValue:n];
}

@end
