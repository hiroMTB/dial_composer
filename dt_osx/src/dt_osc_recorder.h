//
//  dt_osc_recorder.h
//  dt_
//
//  Created by mtb on 2014/07/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp;

class dt_osc_recorder{

public:
	dt_osc_recorder();
	
	void setup();
	void update(int x, int y, int w, int h);
	void add_osc_message(const ofxOscMessage &m, int ch);
	void step_fragment();
	void toggle_play_fragment();
	void play_fragment();

	ofApp * app;
	typedef vector<ofxOscMessage> fragment;
	vector<fragment> fragment_ring;
	static const int fragment_ring_max = 256;
	
	
private:
	int current_fragment;
};
