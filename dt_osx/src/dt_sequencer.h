//
//  dt_sequencer.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

class ofApp;

class dt_sequencer{

public:
	
	dt_sequencer();
	~dt_sequencer(){};
	
	void setup(float beats);
	void updateIndicator();
	void updateIndicator(bool forward);
	void setRhythmShape(int type);
	void incRhythmShape(int n);
	
	int	getCurrentBeat();
	bool getDataFromBeat(int beat);
	bool getDataFromStep(int step);
	bool getDataNow();
	bool isOnBeat();

	ofApp * app;
	
	bool bCounter_clockwise;
	int rhythm_shape_type;
	int beat_resolution;
	
	unsigned int total_steps;
	unsigned int total_beats;
	unsigned int indicator;
};