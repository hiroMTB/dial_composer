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
	

	
	dt_circle_osc(){ setup(); }
	
	
	virtual void setup(int beat=0){
		data.circle_color = data.indi_color = ofFloatColor(0.5);
		data.line_color = ofFloatColor(0.2);
		
		data.radius = 3;
		data.rev_radius = 6;
		data.bCollide = false;
		data.collision_radius = data.rev_radius + ofRandom(10, 30);
		
		data.circle_type = DT_CIRCLE_OSC;
		ch = (int)ceil(ofRandom(0, DT_MAX_OSC_CH));
		initial = ofToString(ch);
	}
	
	
	/*
	 * override with empty function because we dont need step sequence
	 */
	virtual void fire(){};
	virtual void step(){};
	
	
	// send osc
	void send_osc(int _ch, int _noteNum, int _vel, int _dur, int _pan,  int _cc12, int _cc13, int _cc14){
		ofxOscBundle all;
		ofxOscMessage noteOn, noteNum, vel, dur, chPan, cc12, cc13, cc14;
		
		string prefix = "/" + ofToString(ch) + "/";	// eg /1/
		
		noteOn.setAddress	(prefix + "noteOn");
		noteNum.setAddress	(prefix + "noteNum");
		vel.setAddress		(prefix + "vel");
		dur.setAddress		(prefix + "dur");
		chPan.setAddress	(prefix + "chPan");
		cc12.setAddress		(prefix + "cc12");
		cc13.setAddress		(prefix + "cc13");
		cc14.setAddress		(prefix + "cc14");
		
		noteNum.addIntArg(_noteNum);
		vel.addIntArg(_vel);
		dur.addIntArg(_dur);
		chPan.addIntArg(_pan);
		cc12.addIntArg(_cc12);
		cc13.addIntArg(_cc13);
		cc14.addIntArg(_cc14);
		
		noteOn.addIntArg(1);
		
		all.addMessage(cc12);
		all.addMessage(cc13);
		all.addMessage(cc14);
		
		all.addMessage(chPan);
		all.addMessage(dur);
		all.addMessage(vel);
		all.addMessage(noteNum);
		all.addMessage(noteOn);
		
		app->osc_sender.send_bundle(all);
	};

};