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
	
	dt_config();
	
	void setup();
	void update();

	inline static string toOnOff( bool b ){ return b ? "On" : "Off"; };
	
	ofApp * app;
		
	ofxOscReceiver osc_r;
	
	// OSC out
  	static int      DT_OSC_OUT_CH_MAX;
	static string	DT_OSC_OUT_ADDRESS_PREFIX;
	static string	DT_OSC_OUT_ADDRESS;
	static int		DT_OSC_OUT_PORT;
	static bool     DT_OSC_OUT_PACK_RHYTHM_PARAM;
    
	// OSC in
	static string	DT_OSC_IN_ADDRESS_PREFIX;
	static int		DT_OSC_IN_PORT;
	
	// Generative Rhythm
	static bool     DT_PLAY_GEN_RHYTHM;
	static int      DT_GEN_RHYTHM_RATE;
	static int      DT_RHYTHM_SHAPE_SLOT_MIN;
	static int      DT_RHYTHM_SHAPE_SLOT_MAX;
	static int      DT_QUANTIZE_RESOLUTION;
	static int      DT_BEAT_RESOLUTION;
	static int      DT_BEAT_SPEED_MAX;
	static int      DT_CONNECTION_NUM_INPUT_MAX;
	static int      DT_CONNECTION_NUM_OUTPUT_MAX;
	
	// Buffered Rhythm
	static bool     DT_PLAY_BUFFERED_RHYTHM;
	static int      DT_BUFFERED_RHYTHM_RATE;
	static int      DT_BUFFERED_RHYTHM_INDICATOR;
	static int      DT_BUFFERED_RHYTHM_LOOP_START;
	static int      DT_BUFFERED_RHYTHM_LOOP_END;
	static bool     DT_SHOW_BUFFERED_RHYTHM;
	
	// draw mode
	static bool     DT_SHOW_LINER_DRAWER;
    static float    DT_SIZE_BASE;
};
