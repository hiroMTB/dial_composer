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

- (IBAction)change_midi_ch:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int ch = [sender intValue];
        c->data.midi_cc_num = ch;
        [midi_ch_sl setIntValue:ch];
        [midi_ch_tx setIntValue:ch];
    }
}

- (IBAction)change_midi_cc:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int cc = [sender intValue];
        c->data.midi_cc_num = cc;
        [midi_cc_number_sl setIntValue:cc];
        [midi_cc_number_tx setIntValue:cc];
    }
}

- (IBAction)change_midi_output_value:(id)sender {
    dt_circle_base * c = dt_circle_base::selected_circle;
    if( c ){
        int v = [sender intValue];
        c->data.midi_output_value = v;
        [midi_out_value_sl setIntValue:v];
        [midi_out_value_tx setIntValue:v];
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

        string non_editable_address = ofToString(dt_config::DT_OSC_OUT_TOP_ADDRESS);
        if( c->parent ){
            non_editable_address += c->parent->data.address;
        }
        [top_address setStringValue:[NSString stringWithUTF8String:non_editable_address.c_str() ]];
        [address_lb setStringValue: [NSString stringWithUTF8String: c->data.address.c_str() ]];
        [output_value_sl setFloatValue: c->data.output_value];
        [output_value_tx setFloatValue: c->data.output_value];

        [midi_ch_sl setIntValue:c->data.midi_ch];
        [midi_ch_tx setIntValue:c->data.midi_ch];
        [midi_cc_number_sl setIntValue:c->data.midi_cc_num];
        [midi_cc_number_tx setIntValue:c->data.midi_cc_num];
        [midi_out_value_sl setIntValue:c->data.midi_output_value];
        [midi_out_value_tx setIntValue:c->data.midi_output_value];
        
        ofFloatColor &col = c->data.circle_color;
        [color setColor: [NSColor colorWithCalibratedRed:col.r green:col.g blue:col.b alpha:col.a] ];
        
        /*
         *
         *      Hide & Show gui parts
         *
         */
        if( c->data.circle_type == DT_CIRCLE_NOTE_ON ){
            [output_value_sl setEnabled:false];
            [output_value_stp setEnabled:false];
            [type_cb setEnabled:false];
            
        }else{
            [output_value_sl setEnabled:true];
            [output_value_stp setEnabled:true];
            [type_cb setEnabled:true];
        }
        
        // hide midi cc number control
        if( c->data.circle_type == DT_CIRCLE_NOTE_ON ||
           c->data.circle_type == DT_CIRCLE_VELOCITY ||
           c->data.circle_type == DT_CIRCLE_NOTE_NUM ||
           c->data.circle_type == DT_CIRCLE_DURATION  )
        {
            [midi_cc_number_sl setEnabled:false];
            [midi_cc_number_tx setEnabled:false];
            [midi_cc_number_stp setEnabled:false];
            [midi_out_value_sl setEnabled:false];
            [midi_out_value_tx setEnabled:false];
        }else{
            [midi_cc_number_sl setEnabled:true];
            [midi_cc_number_tx setEnabled:true];
            [midi_cc_number_stp setEnabled:true];
            [midi_out_value_sl setEnabled:true];
            [midi_out_value_tx setEnabled:true];
        }
    }
}
@end
