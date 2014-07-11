//
//  dt_gui.h
//  dialt_osx
//
//  Created by mtb on 2014/07/07.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp;

// Rhythm
static int DT_RHYTHM_SHAPE_MIN_SLOT = 3;
static int DT_RHYTHM_SHAPE_MAX_SLOT = 12;
static int DT_QUANTIZE_RESOLUTION = 128;
static int DT_BEAT_RESOLUTION = 128;		// hwo many steps per 1 beat

// Circle
static int DT_MAX_CIRCLE_NUM = 50000;
static int DT_CONNECTION_NUM_INPUT_MAX = 10;
static int DT_CONNECTION_NUM_OUTPUT_MAX = 1;

// OSC
static int DT_MAX_OSC_CH = 32;
static string DT_OSC_OUT_ADDRESS_PREFIX = "/dt/";
static const string DT_OSC_OUT_ADDRESS = "localhost";
static const int DT_OSC_OUT_PORT = 9999;


class dt_controler{

public:

    ofApp * app;
    
	bool bShow;
	
	ofxPanel panel;
	ofxLabel fps;
    ofxLabel rhyth_shape_min_slot, rhyth_shape_max_slot, quantize_resolution, beat_resolution;
	ofxLabel max_circle_num, connection_num_input_max, connection_num_output_max;
    ofxLabel max_osc_ch, osc_out_address, osc_out_port;
    
    
    ofxLabel sleep_us, sleep_freq;
    
	dt_controler();
	
	void draw();
	void toggle();
    
};



/*
 ofxFloatSlider fl;
 ofxColorSlider col;
 ofxVec2Slider vec2;
 ofxToggle tgl;
 ofxButton btn;
*/