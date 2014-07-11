//
//  dt_circle_osc.h
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#pragma once

#include "ofMain.h"
#include "dt_circle_output_base.h"
#include "dt_circle_osc.h"
#include "ofxOsc.h"
#include "dt_osc_sender.h"
#include "ofApp.h"

class dt_circle_osc : public dt_circle_output_base{
	
	
public:
	

    string address_prefix;
    ofxOscMessage noteOn, noteNum, vel, dur, chPan, cc12, cc13, cc14, cc16;

	dt_circle_osc(){}
	
	virtual void setup(int beat_num){
		data.circle_color = data.indi_color = ofFloatColor(0.5);
		data.line_color = ofFloatColor(0.2);
		
		data.radius = 3;
		data.rev_radius = 12;
		data.bCollide = true;
		data.collision_radius = data.rev_radius + ofRandom(10, 30);
		
		data.circle_type = DT_CIRCLE_OSC;
		ch = (int)ceil(ofRandom(0, DT_MAX_OSC_CH));
		initial = ofToString(ch);
        
        address_prefix = DT_OSC_OUT_ADDRESS_PREFIX + ofToString(ch) + "/";	// eg /dt/1/
        noteOn.setAddress	(address_prefix + "noteOn");
		noteNum.setAddress	(address_prefix + "noteNum");
		vel.setAddress		(address_prefix + "vel");
		dur.setAddress		(address_prefix + "dur");
		chPan.setAddress	(address_prefix + "chPan");
		cc12.setAddress		(address_prefix + "cc12");
		cc13.setAddress		(address_prefix + "cc13");
		cc14.setAddress		(address_prefix + "cc14");
		cc16.setAddress		(address_prefix + "cc16");
        
        noteOn.addIntArg(1);
        
        setup_text();
	}
	
	
	/*
	 * override with empty function because we dont need step sequence
	 */
	virtual void fire(){};
	virtual void step(){};

	
	// send osc
	void send_osc(int _ch, int _noteNum, int _vel, int _dur, int _pan,  int _cc12, int _cc13, int _cc14, int _cc16){
		ofxOscBundle all;
        clear_osc_message();
        
		noteNum.addIntArg(_noteNum);
		vel.addIntArg(_vel);
		dur.addIntArg(_dur);
		chPan.addIntArg(_pan);
		cc12.addIntArg(_cc12);
		cc13.addIntArg(_cc13);
		cc14.addIntArg(_cc14);
		cc16.addIntArg(_cc16);
		
		all.addMessage(cc12);
		all.addMessage(cc13);
		all.addMessage(cc14);
        all.addMessage(cc16);
        
		all.addMessage(chPan);
		all.addMessage(dur);
		all.addMessage(vel);
		all.addMessage(noteNum);
		all.addMessage(noteOn);
		
		app->osc_sender.send_bundle(all);
	};

    
    void clear_osc_message(){
        vel.clear();
        dur.clear();
		chPan.clear();
		cc12.clear();
		cc13.clear();
		cc14.clear();
		cc16.clear();
    }
};