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
#include "dt_sequencer.h"

#import "CircleViewController.h"
#import "AppDelegate.h"

@interface CircleViewController ()
@end

@implementation CircleViewController
@synthesize circle_type_lb;
@synthesize name_tx;
@synthesize solo_bt, mute_bt;
@synthesize beat_sl, speed_sl, rotate_sl, shape_sl, output_value_sl, ch_sl;
@synthesize beat_tx, speed_tx, rotate_tx, shape_tx, output_value_tx, ch_tx;
@synthesize address_lb;
@synthesize color;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (IBAction)change_name:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        string name = [[sender stringValue] UTF8String];
        c->data.name = name;
    }
}

- (IBAction)change_solo:(id)sender {

}


- (IBAction)change_mute:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int mute = [sender state];
        c->data.bMute = mute;
    }
}

- (IBAction)change_beat:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int beat = [sender intValue];
        [self.beat_sl setIntValue: beat];
        [self.beat_tx setIntValue: beat];
        c->change_beat( beat );
    }
}

- (IBAction)change_speed:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int speed = [sender intValue];
        [self.speed_sl setIntValue:speed];
        [self.speed_tx setIntValue:speed];
        c->change_speed( speed );
    }
}

- (IBAction)change_rotate:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        float rotate = [sender floatValue];
        [self.rotate_sl setFloatValue:rotate];
        [self.rotate_tx setFloatValue:rotate];
		c->change_rotation( rotate );
    }
}

- (IBAction)change_shape:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int shape = [sender intValue];
        c->change_shape( shape );
        shape = c->seq->rhythm_shape_type;
        [self.shape_sl setIntValue:shape];
        [self.shape_tx setIntValue:shape];
    }
}

- (IBAction)change_output_value:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        float ov = [sender floatValue];
        [self.output_value_sl setFloatValue:ov];
        [self.output_value_tx setFloatValue:ov];
        c->data.output_value = ov;
    }
}

- (IBAction)change_ch:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int ch = [sender intValue];
        [self.ch_sl setIntValue:ch];
        [self.ch_tx setIntValue:ch];
        c->data.ch = ch;
    }
}

- (IBAction)change_color:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        NSColorWell * cw = (NSColorWell*) sender;
        float r = cw.color.redComponent;
        float g = cw.color.greenComponent;
        float b = cw.color.blueComponent;
        c->change_circle_color( r, g, b, 1.0 );
    }
}

- (void)update_ui{
    dt_circle_base * c = dt_circle_base::dt_circle_base::selected_circle;
    if( c ){
        [self.circle_type_lb setStringValue:[NSString stringWithUTF8String: getEnumString(c->data.circle_type).c_str() ]];
        [self.name_tx setStringValue: [NSString stringWithUTF8String: c->data.name.c_str()] ];
        [self.solo_bt setState: NSOffState];
        [self.mute_bt setState: c->data.bMute];
        [self.beat_sl setIntValue: c->seq->total_beats];
        [self.beat_tx setIntValue: c->seq->total_beats];
        [self.speed_sl setIntValue: c->data.speed];
        [self.speed_tx setIntValue: c->data.speed];
        [self.rotate_sl setFloatValue: 123];
        [self.rotate_tx setFloatValue: 123];
        [self.shape_sl setIntValue: c->seq->rhythm_shape_type];
        [self.shape_tx setIntValue: c->seq->rhythm_shape_type];
        [self.output_value_sl setFloatValue: c->data.output_value];
        [self.output_value_tx setFloatValue: c->data.output_value];
        [self.ch_sl setIntValue: c->data.ch];
        [self.ch_tx setIntValue: c->data.ch];

        string adrs = "/" + ofToString( c->data.ch );
        [self.address_lb setStringValue: [NSString stringWithUTF8String: adrs.c_str() ]];
        
        ofFloatColor &col = c->data.circle_color;
        [self.color setColor: [NSColor colorWithCalibratedRed:col.r green:col.g blue:col.b alpha:col.a] ];
    }
}

@end
