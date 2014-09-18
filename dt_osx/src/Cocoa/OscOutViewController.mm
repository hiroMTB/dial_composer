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
#import "OscOutViewController.h"

@implementation OscOutViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)awakeFromNib {

}

- (IBAction)change_enable:(id)sender {
    dt_config::DT_OSC_OUT_ENABLE = [(NSSegmentedControl*)sender selectedSegment];
}

- (IBAction)change_address:(id)sender {
    string address = [[sender stringValue] UTF8String];
    ofApp::app->osc_sender.setTargetAddress( address );
}

- (IBAction)change_port:(id)sender {
    int port = [sender intValue];
    ofApp::app->osc_sender.setTargetPort( port );
}

- (IBAction)change_top_address:(id)sender {
    NSString * address = [sender stringValue];
    dt_config::DT_OSC_OUT_TOP_ADDRESS = address.UTF8String;
}

- (IBAction)change_pack_rhythm_param:(id)sender {
    dt_config::DT_OSC_OUT_PACK_RHYTHM_PARAM = [sender state];
}

- (void)add_output_message:(std::string)m {
    NSString * line = [NSString stringWithUTF8String:m.c_str()];
    NSString * current = [output_tx string];
    NSString * all = [NSString stringWithFormat:@"%@\%@", line, current];
    [output_tx setString:all];
}


- (void)update_out_messages{
    /*
     *      dont call me often
     */
    
    // clear
//    [output_tx setString:@""];
    
    string ms = "";
    vector<ofxOscMessage> &msgs = ofApp::app->osc_sender.print_buffer;
    for( int i=0; i<msgs.size(); i++ ){
        int index = msgs.size()-1-i;
        ofxOscMessage &m = msgs[ index ];
        ms += m.getAddress();

        for( int i=0; i<m.getNumArgs(); i++ ){
            ofxOscArgType t = m.getArgType( i );
            switch( t ){
                case OFXOSC_TYPE_INT32:
                {
                    int int32Arg = m.getArgAsInt32( i );
                    ms += " " + ofToString( int32Arg );
                    break;
                }
                case OFXOSC_TYPE_INT64:
                {
                    int int64Arg = m.getArgAsInt64( i );
                    ms += " " + ofToString( int64Arg );
                    break;
                }
                case OFXOSC_TYPE_FLOAT:
                {
                    float floatArg = m.getArgAsFloat( i );
                    ms += " " + ofToString( floatArg );
                    break;
                }
                case OFXOSC_TYPE_STRING:
                {
                    string stringArg = m.getArgAsString( i );
                    ms += " " + stringArg;
                    break;
                }
                default:
                    ms += " error";
                    break;
            }
        }
        ms += "\n";
    }
    
    msgs.clear();
    
    if(ms != "")
        [self add_output_message:ms];
}

- (void)update_ui{
    ofApp * app = ofApp::app;
    if( app ){
        [enable_sc setSelectedSegment: (int)dt_config::DT_OSC_OUT_ENABLE];
        [address_tx setStringValue: [NSString stringWithUTF8String: dt_config::DT_OSC_OUT_IP_ADDRESS.c_str()] ];
        [port_tx setStringValue: [NSString stringWithUTF8String: ofToString(dt_config::DT_OSC_OUT_PORT).c_str()] ];
        [top_address setStringValue: [NSString stringWithUTF8String:ofToString(dt_config::DT_OSC_OUT_TOP_ADDRESS).c_str()] ];

        [self update_out_messages];
    }
}

@end
