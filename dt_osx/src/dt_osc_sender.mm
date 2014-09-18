//
//  dt_osc_sender.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "def.h"
#include "dt_osc_sender.h"
#include "dt_config.h"
#import "ofxOsc.h"

#import "AppDelegate.h"
#import "MainWindowController.h"
#import "OscOutViewController.h"

/*
 *
 *	default settings
 *
 */
dt_osc_sender::dt_osc_sender()
:
address( dt_config::DT_OSC_OUT_IP_ADDRESS ),
port( dt_config::DT_OSC_OUT_PORT )
{
	reset();
	ofLogNotice( "dt_osc_dender", "setup address:"+address+", port:"+ofToString(port) );
}

void dt_osc_sender::reset(){
	sender.setup( address, port );
}

void dt_osc_sender::setTargetAddress( string _address ){
    if( _address!= "" ){
        address = _address;
        reset();
    }
}

void dt_osc_sender::setTargetPort( int _port ){
    if( 0<_port ){
        port = _port;
        reset();
    }
}

void dt_osc_sender::send_message( ofxOscMessage &m ){
	sender.sendMessage( m );
    
    
#pragma mark TASK
    /*
     *      It seems heavy for Cocoa gui display.
     *      put a side in the meantime...
     *
     
    string ms = m.getAddress();
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
    AppDelegate * d = [[NSApplication sharedApplication] delegate];
    [[[d mainWindowController] oscOutViewController] add_output_message: ms];
     */
}

void dt_osc_sender::send_bundle( ofxOscBundle &b ){
	sender.sendBundle( b );
}
