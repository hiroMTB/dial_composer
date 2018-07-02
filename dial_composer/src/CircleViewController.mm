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
#include "dt_circle_note_on.h"
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
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        string name = [[sender stringValue] UTF8String];
        c->data.name = name;
    }
}

- (IBAction)change_type:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
		int tag = [(NSComboBox*)sender indexOfSelectedItem];
		c->change_type( (dt_circle_type)tag );
	}
}

- (IBAction)change_solo:(id)sender {

}

- (IBAction)change_mute:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int mute = [sender state];
        c->data.bMute = mute;
    }
}

- (IBAction)change_beat:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int beat = [sender intValue];
        
        if(c->change_beat( beat )){
            [beat_sl setIntValue: beat];
            [beat_tx setIntValue: beat];
            [beat_stp setIntValue: beat];
            
            // change shape slider max value
            int max_shape = ofApp::app->rhythm_lib.getRhythmSize(c->seq->total_beats)-1;
            [shape_sl setMaxValue: max_shape];
            [[shape_tx formatter] setMaximum: [NSNumber numberWithInt: max_shape]];
            [shape_stp setMaxValue: max_shape];
            
            // shape type is changed after beat change
            int shape_type = c->seq->rhythm_shape_type;
            [shape_sl setIntValue: shape_type];
            [shape_tx setIntValue: shape_type];
            [shape_stp setIntValue: shape_type];
        }
    }
}

- (IBAction)change_speed:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int speed = [sender intValue];
        [speed_sl setIntValue:speed];
        [speed_tx setIntValue:speed];
        [speed_stp setIntValue:speed];
        c->change_speed( speed );
    }
}

- (IBAction)change_rotate:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int rotate = [sender intValue];
        [rotate_sl setIntValue:rotate];
        [rotate_tx setIntValue:rotate];
        [rotate_stp setIntValue:rotate];
        c->change_rotation( rotate );
    }
}

- (IBAction)change_shape:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int shape = [sender intValue];
        c->change_shape( shape );
        shape = c->seq->rhythm_shape_type;
        [shape_sl setIntValue:shape];
        [shape_tx setIntValue:shape];
        [shape_stp setIntValue:shape];
    }
}

- (IBAction)change_address:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        c->data.address = [sender stringValue].UTF8String;
    }
}

- (IBAction)change_output_value:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        float fov = [sender floatValue];
        int ov = round(fov); //roundFloatToInt(fov);
        [output_value_sl setIntValue:ov];
        [output_value_tx setIntValue:ov];
        [output_value_stp setIntValue:ov];
        c->data.output_value = ov;
        
        bool bSendOnChange = [send_on_change_btn state] == NSOnState;
        if(bSendOnChange){
            ofApp * app = ofApp::app;
            const dt_circle_type & type = c->data.circle_type;
            if( type == DT_CIRCLE_NOTE_ON){
                
            }else if(
                type == DT_CIRCLE_VELOCITY ||
                type == DT_CIRCLE_NOTE_NUM ||
                type == DT_CIRCLE_DURATION  )
            {
                shared_ptr<dt_circle_note_on> n = std::static_pointer_cast<dt_circle_note_on>(c->parent.lock());
                int ch = n->data.midi_ch;
                int noteNum =   type==DT_CIRCLE_NOTE_NUM ? ov : n->prms[DT_CIRCLE_NOTE_NUM];
                int vel =       type==DT_CIRCLE_VELOCITY ? ov : n->prms[DT_CIRCLE_VELOCITY];
                int dur =       type==DT_CIRCLE_DURATION ? ov : n->prms[DT_CIRCLE_DURATION];
                app->midi_sender.send_note_on(ch, noteNum, vel, dur*1000.0);
            }else if(type == DT_CIRCLE_PAN ||
                     type == DT_CIRCLE_CC1 ||
                     type == DT_CIRCLE_CC2 ||
                     type == DT_CIRCLE_CC3 ||
                     type == DT_CIRCLE_CC4 )
            {
                int ch = c->data.midi_ch;
                int cc = c->data.midi_cc_num;
                int value = c->data.output_value;
                app->midi_sender.send_cc(ch, cc, value);
            }
        }
    }
}

- (IBAction)change_color:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        NSColorWell * cw = (NSColorWell*) sender;
        float r = cw.color.redComponent;
        float g = cw.color.greenComponent;
        float b = cw.color.blueComponent;
        c->change_circle_color( r, g, b, 1.0 );
    }
}

- (IBAction)change_midi_ch:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int ch = [sender intValue];
        c->data.midi_ch = ch;
        [midi_ch_sl setIntValue:ch];
        [midi_ch_tx setIntValue:ch];
        [midi_ch_stp setIntValue:ch];
    }
}

- (IBAction)change_midi_cc:(id)sender {
    shared_ptr<dt_circle_base> c = dt_circle_base::selected_circle.lock();
    if( c ){
        int cc = [sender intValue];
        c->data.midi_cc_num = cc;
        [midi_cc_sl setIntValue:cc];
        [midi_cc_tx setIntValue:cc];
        [midi_cc_stp setIntValue:cc];
    }
}

- (void)update_ui{
    shared_ptr<dt_circle_base> c = dt_circle_base::dt_circle_base::selected_circle.lock();
    if( c ){
        [type_cb selectItemAtIndex: (int)c->data.circle_type];
        [name_tx setStringValue: [NSString stringWithUTF8String: c->data.name.c_str()] ];
        [solo_bt setState: NSOffState];
        [mute_bt setState: c->data.bMute];
        [beat_sl setIntValue: c->seq->total_beats];
        [beat_tx setIntValue: c->seq->total_beats];
        [beat_stp setIntValue:c->seq->total_beats];
        
        [speed_sl setIntValue: c->data.speed];
        [speed_tx setIntValue: c->data.speed];
        [speed_stp setIntValue: c->data.speed];
        
        [rotate_sl setFloatValue: c->data.phase_step];
        [rotate_tx setFloatValue: c->data.phase_step];
        [rotate_stp setFloatValue: c->data.phase_step];
        
        [shape_sl setIntValue: c->seq->rhythm_shape_type];
        [shape_tx setIntValue: c->seq->rhythm_shape_type];
        [shape_stp setIntValue: c->seq->rhythm_shape_type];

        int max_shape = ofApp::app->rhythm_lib.getRhythmSize(c->seq->total_beats)-1;
        [shape_sl setMaxValue: max_shape];
        [[shape_tx formatter] setMaximum: [NSNumber numberWithInt: max_shape]];
        [shape_stp setMaxValue:max_shape];
        
        string non_editable_address = ofToString(dt_config::DT_OSC_OUT_TOP_ADDRESS);
        shared_ptr<dt_circle_base> parent = c->parent.lock();
        if( parent ){
            non_editable_address += parent->data.address;
        }
        [top_address setStringValue:[NSString stringWithUTF8String:non_editable_address.c_str() ]];
        [address_lb setStringValue: [NSString stringWithUTF8String: c->data.address.c_str() ]];
        [output_value_sl setIntValue: c->data.output_value];
        [output_value_tx setIntValue: c->data.output_value];
        [output_value_stp setIntValue: c->data.output_value];
        
        [midi_ch_sl setIntValue:c->data.midi_ch];
        [midi_ch_tx setIntValue:c->data.midi_ch];
        [midi_ch_stp setIntValue:c->data.midi_ch];
        
        [midi_cc_sl setIntValue:c->data.midi_cc_num];
        [midi_cc_tx setIntValue:c->data.midi_cc_num];
        [midi_cc_stp setIntValue:c->data.midi_cc_num];
        
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
            [midi_ch_sl setEnabled:true];
            [midi_ch_tx setEnabled:true];
            [midi_ch_stp setEnabled:true];
            [send_on_change_btn setEnabled:false];
        }else{
            [output_value_sl setEnabled:true];
            [output_value_stp setEnabled:true];
            [type_cb setEnabled:true];
            [midi_ch_sl setEnabled:false];
            [midi_ch_tx setEnabled:false];
            [midi_ch_stp setEnabled:false];
            [send_on_change_btn setEnabled:true];
        }
        
        // hide midi cc number control
        if( c->data.circle_type == DT_CIRCLE_NOTE_ON ||
           c->data.circle_type == DT_CIRCLE_VELOCITY ||
           c->data.circle_type == DT_CIRCLE_NOTE_NUM ||
           c->data.circle_type == DT_CIRCLE_DURATION  )
        {
            [midi_cc_sl setEnabled:false];
            [midi_cc_tx setEnabled:false];
            [midi_cc_stp setEnabled:false];
        }else{
            [midi_cc_sl setEnabled:true];
            [midi_cc_tx setEnabled:true];
            [midi_cc_stp setEnabled:true];
        }
    }
}

@end
