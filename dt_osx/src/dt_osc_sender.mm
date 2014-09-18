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
    if(dt_config::DT_OSC_OUT_ENABLE){
        sender.sendMessage( m );
        print_buffer.push_back( m );
    }
}

void dt_osc_sender::send_bundle( ofxOscBundle &b ){
    if(dt_config::DT_OSC_OUT_ENABLE)
        sender.sendBundle( b );
}
