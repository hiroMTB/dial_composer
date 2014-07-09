//
//  dt_circle_synth.h
//  dialt
//
//  Created by mtb on 5/7/14.
//
//

#pragma once


#include "ofMain.h"
#include "dt_circle_output_base.h"
#include "ofxTonic.h"

using namespace Tonic;

class dt_circle_synth : public dt_circle_output_base{
	
public:
	ofxTonicSynth oftSynth;
	Generator finalTone;
	ControlGenerator midiNote;
	ControlGenerator noteFreq;
	ControlGenerator trigger;
	ADSR adsr;

	
	dt_circle_synth();
	
	virtual void setup(int beat=0);
	virtual void update();
	virtual void draw();

	/*
	 * override with empty function because we dont need step sequence
	 */
	virtual void fire(){};
	virtual void step(){};
	
	
	// shape
	static const int vertex_num_max = 20;
	int vertex_num;
	ofVec2f shape_points[vertex_num_max];
	ofVbo vbo;
	void make_vbo();

	
	// synth controll
	void make_note(float noteNum, float velocity, float duration, float pan, float cc12, float cc13, float cc14);

	float base_freq;
	
	static void note_off_all_synth();
	
	
	static Mixer mixer;
};

