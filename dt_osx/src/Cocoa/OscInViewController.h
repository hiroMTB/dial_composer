//
//  OscViewController.h
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#import <Cocoa/Cocoa.h>

#include <string>

@interface OscInViewController : NSViewController {
    IBOutlet NSSegmentedControl *enable_sc;
    IBOutlet NSTextField *address_tx;
    IBOutlet NSTextField *port_tx;
    IBOutlet NSTextView *input_tx;
    IBOutlet NSTextField *top_address;
    IBOutlet NSButton *address_check;
    NSString * my_ip_address;
}

- (IBAction)change_enable:(id)sender;
- (IBAction)change_address:(id)sender;
- (IBAction)change_port:(id)sender;
- (IBAction)check_ip_address:(id)sender;

- (void)add_input_message:(std::string) m;
- (void)update_ui;
- (NSString*) getIPWithNSHost;
- (void)update_ui_every_frame;

@end
