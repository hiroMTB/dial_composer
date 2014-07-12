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

/*
 *
 *	default settings
 *
 */
dt_osc_sender::dt_osc_sender():
address(dt_config::DT_OSC_OUT_ADDRESS),
port(dt_config::DT_OSC_OUT_PORT){
	reset();
	ofLogNotice("OSC sender setup, Address: "+address+", port: "+ofToString(port));
}

void dt_osc_sender::reset(){
	sender.setup(address, port);
}

void dt_osc_sender::setTargetAddress(string _address){
	address = _address;
}

void dt_osc_sender::setTargetPort(int _port){
	port = _port;
}


void dt_osc_sender::send_message(ofxOscMessage &m){
	sender.sendMessage(m);
}

void dt_osc_sender::send_bundle(ofxOscBundle &b){
	sender.sendBundle(b);
}
