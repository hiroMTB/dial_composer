//
//  dt_osc_sender.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class dt_osc_sender{
	
public:
	dt_osc_sender();
	
	void setTargetAddress( string address );
	void setTargetPort( int port );
	void reset();
	void send_message( ofxOscMessage &m );
	void send_bundle( ofxOscBundle &b );
	
	string address;
	int port;

	vector<ofxOscMessage> print_buffer;
    
private:
	ofxOscSender sender;
};