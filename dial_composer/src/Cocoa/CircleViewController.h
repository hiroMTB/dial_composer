//
//  CircleViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface CircleViewController : NSViewController{
    IBOutlet NSSlider   *beat_sl;
    IBOutlet NSSlider   *speed_sl;
    IBOutlet NSSlider   *rotate_sl;
    IBOutlet NSSlider   *shape_sl;
    IBOutlet NSSlider   *output_value_sl;
    IBOutlet NSSlider   *midi_ch_sl;
    IBOutlet NSSlider   *midi_cc_sl;
    
    IBOutlet NSTextField *beat_tx;
    IBOutlet NSTextField *speed_tx;
    IBOutlet NSTextField *rotate_tx;
    IBOutlet NSTextField *shape_tx;
    IBOutlet NSTextField *output_value_tx;
    IBOutlet NSTextField *midi_ch_tx;
    IBOutlet NSTextField *midi_cc_tx;
    
    IBOutlet NSTextField *top_address;
    IBOutlet NSTextField *address_lb;
    IBOutlet NSColorWell *color;
    IBOutlet NSTextField *name_tx;
    IBOutlet NSButton *solo_bt;
    IBOutlet NSButton *mute_bt;
	IBOutlet NSComboBox *type_cb;
    IBOutlet NSTextField *output_value_lb;

    IBOutlet NSStepper *beat_stp;
    IBOutlet NSStepper *speed_stp;
    IBOutlet NSStepper *rotate_stp;
    IBOutlet NSStepper *shape_stp;
    IBOutlet NSStepper *output_value_stp;
    IBOutlet NSStepper *midi_ch_stp;
    IBOutlet NSStepper *midi_cc_stp;
}

- (IBAction)change_name:(id)sender;
- (IBAction)change_type:(id)sender;
- (IBAction)change_solo:(id)sender;
- (IBAction)change_mute:(id)sender;

- (IBAction)change_beat:(id)sender;
- (IBAction)change_speed:(id)sender;
- (IBAction)change_rotate:(id)sender;
- (IBAction)change_shape:(id)sender;
- (IBAction)change_address:(id)sender;
- (IBAction)change_output_value:(id)sender;
- (IBAction)change_color:(id)sender;
- (IBAction)change_midi_ch:(id)sender;
- (IBAction)change_midi_cc:(id)sender;

/*
- (IBAction)step_beat:(id)sender;
- (IBAction)step_speed:(id)sender;
- (IBAction)step_rotate:(id)sender;
- (IBAction)step_shape:(id)sender;
- (IBAction)step_output_value:(id)sender;
- (IBAction)step_midi_ch:(id)sender;
- (IBAction)step_midi_cc:(id)sender;
*/

- (void)update_ui;
@end
