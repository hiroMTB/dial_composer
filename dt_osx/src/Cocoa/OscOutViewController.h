//
//  OscViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

#include <string>

@interface OscOutViewController : NSViewController {
    IBOutlet NSSegmentedControl *enable_sc;
    IBOutlet NSTextField *address_tx;
    IBOutlet NSTextField *port_tx;
    IBOutlet NSButton *pack_rhythm_param_bt;
    IBOutlet NSTextView *output_tx;
    IBOutlet NSTextField *top_address;
    
    int monitor_line_num_max;
    int monitor_line_num;
}

- (IBAction)change_enable:(id)sender;
- (IBAction)change_address:(id)sender;
- (IBAction)change_port:(id)sender;
- (IBAction)change_pack_rhythm_param:(id)sender;
- (IBAction)change_top_address:(id)sender;

- (void)add_output_message:(std::string)m :(int)line_num;
- (void)update_ui;
- (void)update_ui_every_frame;

@end
