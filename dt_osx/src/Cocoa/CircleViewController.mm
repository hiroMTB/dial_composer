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

- (IBAction)change_type:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
		int tag = [(NSComboBox*)sender indexOfSelectedItem];
		c->change_type( (dt_circle_type)tag );
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
        [beat_sl setIntValue: beat];
        [beat_tx setIntValue: beat];
        c->change_beat( beat );
    }
}

- (IBAction)change_speed:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int speed = [sender intValue];
        [speed_sl setIntValue:speed];
        [speed_tx setIntValue:speed];
        c->change_speed( speed );
    }
}

- (IBAction)change_rotate:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        float rotate = [sender floatValue];
        [rotate_sl setFloatValue:rotate];
        [rotate_tx setFloatValue:rotate];
		c->change_rotation( rotate );
    }
}

- (IBAction)change_shape:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int shape = [sender intValue];
        c->change_shape( shape );
        shape = c->seq->rhythm_shape_type;
        [shape_sl setIntValue:shape];
        [shape_tx setIntValue:shape];
    }
}

- (IBAction)change_address:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        c->data.address = [sender stringValue].UTF8String;
    }
}

- (IBAction)change_output_value:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        float ov = [sender floatValue];
        [output_value_sl setFloatValue:ov];
        [output_value_tx setFloatValue:ov];
        c->data.output_value = ov;
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
		[type_cb selectItemAtIndex: (int)c->data.circle_type];
        [name_tx setStringValue: [NSString stringWithUTF8String: c->data.name.c_str()] ];
        [solo_bt setState: NSOffState];
        [mute_bt setState: c->data.bMute];
        [beat_sl setIntValue: c->seq->total_beats];
        [beat_tx setIntValue: c->seq->total_beats];
        [speed_sl setIntValue: c->data.speed];
        [speed_tx setIntValue: c->data.speed];
        [rotate_sl setFloatValue: c->data.phase_step];
        [rotate_tx setFloatValue: c->data.phase_step];
        [shape_sl setIntValue: c->seq->rhythm_shape_type];
        [shape_tx setIntValue: c->seq->rhythm_shape_type];
        [top_address setStringValue:[NSString stringWithUTF8String:ofToString(dt_config::DT_OSC_OUT_TOP_ADDRESS).c_str() ]];
        [output_value_sl setFloatValue: c->data.output_value];
        [output_value_tx setFloatValue: c->data.output_value];

        string adrs = c->data.address;
        [address_lb setStringValue: [NSString stringWithUTF8String: adrs.c_str() ]];
        
        ofFloatColor &col = c->data.circle_color;
        [color setColor: [NSColor colorWithCalibratedRed:col.r green:col.g blue:col.b alpha:col.a] ];
    }
}

@end
