//
//  dt_preset.hpp
//  dt_osx
//
//  Created by mtb on 2014/07/12.
//
//

#pragma once

#include "ofMain.h"

#include "ofxGui.h"
#include "ofxOsc.h"

class ofApp;

class dt_config{

public:
	
	// Rhythm
	static int DT_RHYTHM_SHAPE_SLOT_MIN;
	static int DT_RHYTHM_SHAPE_SLOT_MAX;
	static int DT_QUANTIZE_RESOLUTION;
	static int DT_BEAT_RESOLUTION;
	static int DT_BEAT_SPEED_MAX;
	
	// Circle
	static int DT_MAX_CIRCLE_NUM;
	static int DT_CONNECTION_NUM_INPUT_MAX;
	static int DT_CONNECTION_NUM_OUTPUT_MAX;

	// OSC out
	static int			DT_OSC_OUT_CH_MAX;
	static std::string	DT_OSC_OUT_ADDRESS_PREFIX;
	static std::string	DT_OSC_OUT_ADDRESS;
	static int			DT_OSC_OUT_PORT;
	
	// OSC in
	static std::string	DT_OSC_IN_ADDRESS_PREFIX;
	static int			DT_OSC_IN_PORT;

	
	static bool DT_MOVE_CIRCLE;
	static bool DT_MASSIVE_MODE;
	
	
	
	
	ofApp * app;
	bool bShow;
	

	/*
	 *
	 *	Why we use ofxGui for just show parameter?
	 *
	 *		->	it's faster because ofxGui use ofxVboMesh to draw text
	 *
	 */
	ofxPanel status, osc, control;
	
	// status
	ofxLabel fps;
	ofxLabel circle_num, noteOn_num, param_num, output_num;
	ofxLabel bMove;
    
    ofxLabel rhythm_shape_slot_min, rhythm_shape_slot_max, quantize_resolution, beat_resolution, beat_speed_max;
	ofxLabel connection_num_input_max, connection_num_output_max;
    ofxLabel osc_out_address, osc_out_port, osc_out_ch_max;
    ofxLabel osc_in_port;
	
    ofxLabel sleep_microsec;

	
	dt_config();
	
	void setup();
	void reset_position();
	void update();
	void draw();
	void toggle();

	// gui panel
	int width = 250;
	int height = 20;
	
	ofxOscReceiver osc_r;
};
