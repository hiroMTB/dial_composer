//
//  GeneralViewController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"
#include "dt_sequence_thread.h"

#import "GeneralViewController.h"

@interface GeneralViewController ()
@end

@implementation GeneralViewController


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
    ofApp * app = ofApp::app;
    if( app ) app->sequence_thread.change_bpm( bpm );
}

- (IBAction)change_bg_color:(id)sender {
    float r = ( (NSColorWell*)sender ).color.redComponent;
    float g = ( (NSColorWell*)sender ).color.greenComponent;
    float b = ( (NSColorWell*)sender ).color.blueComponent;
    ofApp * app = ofApp::app;
    if( app )app->bg.set( r, g, b, 1.0 );
}

- (void)update_ui{
    ofApp * app = ofApp::app;
    
    if( app ){
     
        [bpm_sl setFloatValue:app->sequence_thread.bpm];
        [bpm_tx setFloatValue:app->sequence_thread.bpm];
        [circle_num_tx setIntValue: app->all_containers.note_on_container->circles.size()];
        [fps_tx setIntValue: ofGetFrameRate()];
        
        ofFloatColor &bg = app->bg;
        [bg_color setColor: [NSColor colorWithCalibratedRed: bg.r green:bg.g blue:bg.b alpha:bg.a] ];
    }
}

@end
