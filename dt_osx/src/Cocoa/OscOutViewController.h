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
    NSSegmentedControl *enable_sc;
    NSTextField *address_tx;
    NSTextField *port_tx;
    NSTextView *output_tx;
}

@property (assign) IBOutlet NSSegmentedControl *enable_sc;
@property (assign) IBOutlet NSTextField *address_tx;
@property (assign) IBOutlet NSTextField *port_tx;
@property (assign) IBOutlet NSTextView *output_tx;

- (IBAction)change_enable:(id)sender;
- (IBAction)change_address:(id)sender;
- (IBAction)change_port:(id)sender;

- (void)add_output_message:(std::string) m;

- (void)update_ui;

@end
