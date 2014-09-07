//
//  OscOutViewController.m
//  dial
//
//  Created by hiroshi matoba on 9/4/14.
//
//

#include "ofMain.h"
#include "ofApp.h"
#include "dt_osc_sender.h"

#import "OscInViewController.h"

@implementation OscInViewController
@synthesize enable_sc;
@synthesize address_tx;
@synthesize port_tx;
@synthesize input_tx;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)awakeFromNib
{

}

- (IBAction)change_enable:(id)sender {
    
}

- (IBAction)change_address:(id)sender {
    string address = [[sender stringValue] UTF8String];
    ofApp::getInstance()->osc_sender.setTargetAddress( address );
}

- (IBAction)change_port:(id)sender {
    int port = [sender intValue];
    ofApp::getInstance()->osc_sender.setTargetPort( port );
}


- (void)add_input_message:(std::string)m {
    NSString * line = [NSString stringWithUTF8String:m.c_str()];
    NSString * current = [input_tx string];
    NSString * all = [NSString stringWithFormat:@"%@\n\%@", current, line];
   [input_tx setString:all];
}
@end