//
//  dt_circle_osc.h
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_circle_output_base.h"
#include "dt_circle_osc.h"
#include "dt_osc_sender.h"
#include "dt_osc_recorder.h"

class dt_circle_osc : public dt_circle_output_base{

public:
	
	dt_circle_osc(){}
	
	virtual void setup( int beat_num ){
		data.circle_color = data.indi_color = ofFloatColor( 0.5 );
		data.line_color = ofFloatColor( 0.2 );
		data.radius = 3;
		data.rev_radius = 12;
		data.bCollide = true;
		data.collision_radius = data.rev_radius + ofRandom( 10, 30 );
		data.circle_type = DT_CIRCLE_OSC;

		ch = (int)round( ofRandom(1, dt_config::DT_OSC_OUT_CH_MAX) );
		
        setup_ch(ch);
	}
	
	virtual void fire(){};
	virtual void step(){};
	
	void send_osc( int _ch, int _note, int _vel, int _dur, int _pan,  int _cc1, int _cc2, int _cc3, int _cc4 ){
		string address_prefix = dt_config::DT_OSC_OUT_ADDRESS_PREFIX + initial + "/";	// eg /dt/1/
		ofxOscMessage noteOn;
		noteOn.setAddress( address_prefix + "noteOn" );
		noteOn.addIntArg( 1 );
		noteOn.addIntArg( _note );
		noteOn.addIntArg( _vel );
		noteOn.addIntArg( _dur );
		noteOn.addIntArg( _pan );
		noteOn.addIntArg( _cc1 );
		noteOn.addIntArg( _cc2 );
		noteOn.addIntArg( _cc3 );
		noteOn.addIntArg( _cc4 );
		app->osc_sender.send_message( noteOn );
		app->osc_recorder.add_osc_message( noteOn, ch );
	}
};