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

	// status
	static const int DT_CIRCLE_MAX = 20000;
	static int	DT_MASTER_CLOCK_OUT_RESOLUTION;
	
	// OSC out
	static const int	DT_OSC_OUT_CH_SYSTEM_MAX = 32;
	static int			DT_OSC_OUT_CH_MAX;
	static int			DT_OSC_OUT_CH_MIN;
	static std::string	DT_OSC_OUT_ADDRESS_PREFIX;
	static std::string	DT_OSC_OUT_ADDRESS;
	static int			DT_OSC_OUT_PORT;
	
	// OSC in
	static std::string	DT_OSC_IN_ADDRESS_PREFIX;
	static int			DT_OSC_IN_PORT;

	// Generative Rhythm
	static bool DT_PLAY_GEN_RHYTHM;
	static int DT_GEN_RHYTHM_RATE;
	static int DT_RHYTHM_SHAPE_SLOT_MIN;
	static int DT_RHYTHM_SHAPE_SLOT_MAX;
	static int DT_QUANTIZE_RESOLUTION;
	static int DT_BEAT_RESOLUTION;
	static int DT_BEAT_SPEED_MAX;
	static int DT_CONNECTION_NUM_INPUT_MAX;
	static int DT_CONNECTION_NUM_OUTPUT_MAX;
	
	// Buffered Rhythm
	static bool DT_PLAY_BUFFERED_RHYTHM;
	static int DT_BUFFERED_RHYTHM_RATE;
	static int DT_BUFFERED_RHYTHM_INDICATOR;
	static int DT_BUFFERED_RHYTHM_LOOP_START;
	static int DT_BUFFERED_RHYTHM_LOOP_END;
	static bool DT_SHOW_BUFFERED_RHYTHM;


	// draw mode
	static bool DT_MASSIVE_MODE;
	static bool DT_SHOW_LINER_DRAWER;
	static bool DT_SHOW_PARAM;
		
	
public:
	ofApp * app;
	

	/*
	 *
	 *	Why we use ofxGui for just show parameter?
	 *
	 *		->	it's faster because ofxGui use ofxVboMesh to draw text
	 *
	 */
	ofxPanel status;
	ofxLabel fps, sleep_microsec, master_clock_out_resolution;
	ofxLabel circle_num, noteOn_num, param_num, output_num;
    
    ofxPanel osc;
	ofxLabel osc_out_address, osc_out_port, osc_out_ch_max, osc_out_ch_min;
    ofxLabel osc_in_port;
	
	ofxPanel generative_rhythm;
	ofxLabel play_gen_rhythm, gen_rhythm_rate;
    ofxLabel rhythm_shape_slot_min, rhythm_shape_slot_max, quantize_resolution, beat_resolution, beat_speed_max;
	ofxLabel connection_num_input_max, connection_num_output_max;
	
	ofxPanel buffered_rhythm;
	ofxLabel play_buffered_rhythm, buffered_rhythm_rate;
	ofxLabel buffered_rhythm_indicator, buffered_rhythm_loop_start, buffered_rhythm_loop_end;
	ofxLabel show_buffered_rhythm;
	
	ofxPanel draw_mode;
	ofxLabel massive_mode;
	ofxLabel show_linear_drawer;
	ofxLabel show_param;
	
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
	
	inline static string toOnOff(bool b){ return b ? "On" : "Off"; };

	void synch_param();
};


