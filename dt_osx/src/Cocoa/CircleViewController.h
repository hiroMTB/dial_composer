//
//  CircleViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface CircleViewController : NSViewController{
    IBOutlet NSSlider    *beat_sl, *speed_sl, *rotate_sl, *shape_sl, *output_value_sl, *ch_sl;
    IBOutlet NSTextField *beat_tx, *speed_tx, *rotate_tx, *shape_tx, *output_value_tx, *ch_tx;
    IBOutlet NSTextField *top_address;
    IBOutlet NSTextField *address_lb;
    IBOutlet NSColorWell *color;
    IBOutlet NSTextField *name_tx;
    IBOutlet NSButton *solo_bt;
    IBOutlet NSButton *mute_bt;
	IBOutlet NSComboBox *type_cb;
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

- (void)update_ui;

@end
