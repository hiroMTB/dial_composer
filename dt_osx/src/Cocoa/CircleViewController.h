//
//  CircleViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

@interface CircleViewController : NSViewController{
    NSSlider    *beat_sl, *speed_sl, *rotate_sl, *shape_sl, *output_value_sl, *ch_sl;
    NSTextField *beat_tx, *speed_tx, *rotate_tx, *shape_tx, *output_value_tx, *ch_tx;
    NSTextField *address_lb;
    NSColorWell *color;
    NSTextField *name_tx;
    NSButton *solo_bt;
    NSButton *mute_bt;
	NSComboBox *type_cb;
}
@property (assign) IBOutlet NSComboBox *type_cb;
@property (assign) IBOutlet NSTextField *name_tx;
@property (assign) IBOutlet NSButton *solo_bt;
@property (assign) IBOutlet NSButton *mute_bt;

@property (assign) IBOutlet NSSlider *beat_sl;
@property (assign) IBOutlet NSSlider *speed_sl;
@property (assign) IBOutlet NSSlider *rotate_sl;
@property (assign) IBOutlet NSSlider *shape_sl;
@property (assign) IBOutlet NSSlider *output_value_sl;

@property (assign) IBOutlet NSTextField *beat_tx;
@property (assign) IBOutlet NSTextField *speed_tx;
@property (assign) IBOutlet NSTextField *rotate_tx;
@property (assign) IBOutlet NSTextField *shape_tx;
@property (assign) IBOutlet NSTextField *output_value_tx;
@property (assign) IBOutlet NSTextField *address_lb;

@property (assign) IBOutlet NSColorWell *color;

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
