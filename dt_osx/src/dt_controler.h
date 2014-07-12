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
#include "ofxOsc.h"

class ofApp;


class dt_controler{

public:
	
	   ofApp * app;
    
	bool bShow;
	
	ofxPanel panel;
	
	// status
	ofxLabel fps;
	ofxLabel circle_num, noteOn_num, param_num, output_num;
	ofxLabel bMove;
    
    ofxLabel rhyth_shape_min_slot, rhyth_shape_max_slot, quantize_resolution, beat_resolution;
	ofxLabel max_circle_num, connection_num_input_max, connection_num_output_max;
    ofxLabel max_osc_ch, osc_out_address, osc_out_port;

    
    ofxLabel sleep_ms;
    
	dt_controler();
	
	void draw();
	void toggle();
    
	ofxOscReceiver osc_r;
};



/*
 ofxFloatSlider fl;
 ofxColorSlider col;
 ofxVec2Slider vec2;
 ofxToggle tgl;
 ofxButton btn;
*/