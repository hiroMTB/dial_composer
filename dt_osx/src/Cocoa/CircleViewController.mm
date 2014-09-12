//
//  CircleViewController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_base.h"

#import "CircleViewController.h"

#import "AppDelegate.h"

@interface CircleViewController ()
@end

@implementation CircleViewController

@synthesize beat_sl, speed_sl, rotate_sl, shape_sl, edge_sl, side_sl, ch_sl;
@synthesize beat_tx, speed_tx, rotate_tx, shape_tx, edge_tx, side_tx, ch_tx;
@synthesize color;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (IBAction)change_beat:(id)sender {
    int beat = [sender intValue];
    [self.beat_sl setIntValue: beat];
    [self.beat_tx setIntValue: beat];
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ) c->change_beat( beat );
}

- (IBAction)change_speed:(id)sender {
    int speed = [sender intValue];
    [self.speed_sl setIntValue:speed];
    [self.speed_tx setIntValue:speed];
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ) c->change_speed( speed );
}

- (IBAction)change_rotate:(id)sender {
    int rotate = [sender intValue];
    [self.rotate_sl setIntValue:rotate];
    [self.rotate_tx setIntValue:rotate];
    dt_circle_base * c = dt_circle_base::selected_circle;
//    if( c ) c->change_rotate( rotate );
}

- (IBAction)change_shape:(id)sender {
    int shape = [sender intValue];
    [self.shape_sl setIntValue:shape];
    [self.shape_tx setIntValue:shape];
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ) c->change_shape( shape );
}

- (IBAction)change_edge:(id)sender {
    int edge = [sender intValue];
    [self.edge_sl setIntValue:edge];
    [self.edge_tx setIntValue:edge];
    dt_circle_base * c = dt_circle_base::selected_circle;
}

- (IBAction)change_side:(id)sender {
    int side = [sender intValue];
    [self.side_sl setIntValue:side];
    [self.side_tx setIntValue:side];
    dt_circle_base * c = dt_circle_base::selected_circle;
}

- (IBAction)change_ch:(id)sender {
    int ch = [sender intValue];
    [self.ch_sl setIntValue:ch];
    [self.ch_tx setIntValue:ch];
    dt_circle_base * c = dt_circle_base::selected_circle;
}

- (IBAction)change_color:(id)sender {
    float r = ( (NSColorWell*)sender ).color.redComponent;
    float g = ( (NSColorWell*)sender ).color.greenComponent;
    float b = ( (NSColorWell*)sender ).color.blueComponent;
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ) c->change_circle_color( r, g, b, 1.0 );
}

- (void)update_ui{
    dt_circle_base * c = dt_circle_base::dt_circle_base::selected_circle;
    if( c ){
        [self.beat_sl setIntValue: c->seq->total_beats];
        [self.beat_tx setIntValue: c->seq->total_beats];
    }
}

@end
