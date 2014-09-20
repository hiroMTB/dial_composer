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
#include "dt_config.h"
#import "OscInViewController.h"

@implementation OscInViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
        my_ip_address = @"unknown";
    }
    return self;
}

- (void)awakeFromNib {

}

- (IBAction)change_enable:(id)sender {
    dt_config::DT_OSC_IN_ENABLE = [(NSSegmentedControl*)sender selectedSegment];
}

- (IBAction)change_address:(id)sender {
    string address = [[sender stringValue] UTF8String];
    ofApp::app->osc_sender.setTargetAddress( address );
}

- (IBAction)change_port:(id)sender {
    int port = [sender intValue];
    ofApp::app->osc_sender.setTargetPort( port );
}

- (IBAction)check_ip_address:(id)sender {
    my_ip_address = [self getIPWithNSHost];
    [self update_ui];
}


- (void)add_input_message:(std::string)m {
    NSString * line = [NSString stringWithUTF8String:m.c_str()];
    NSString * current = [input_tx string];
    NSString * all = [NSString stringWithFormat:@"%@\n\%@", current, line];
   [input_tx setString:all];
}

- (NSString*) getIPWithNSHost{
    NSArray *addresses = [[NSHost currentHost] addresses];
    
    for (NSString *anAddress in addresses) {
        if (![anAddress hasPrefix:@"127"] && [[anAddress componentsSeparatedByString:@"."] count] == 4) {
            return anAddress;
        }
    }
    return @"not available";
}

- (void) update_ui{
    ofApp * app = ofApp::app;
    if( app ){
        [enable_sc setSelectedSegment: (int)dt_config::DT_OSC_IN_ENABLE];
        [address_tx setStringValue: my_ip_address];
        [port_tx setStringValue:[NSString stringWithUTF8String: ofToString(dt_config::DT_OSC_IN_PORT).c_str() ]];
        [top_address setStringValue:[NSString stringWithUTF8String: ofToString(dt_config::DT_OSC_IN_TOP_ADDRESS).c_str() ]];
    }
}

- (void) update_ui_every_frame{
    
}

@end
