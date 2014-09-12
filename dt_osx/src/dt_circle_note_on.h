//
//  dt_circle_note_on.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"
#include "dt_circle_base.h"
#include "dt_rhythm_lib.h"
#include "dt_circle_param.h"

struct dt_param_state{
public:
    dt_param_state();
    
    bool bNote, bVel, bDur, bPan, bCc1, bCc2, bCc3, bCc4;
    float note, vel, dur, pan, cc1, cc2, cc3, cc4;

    void reset();
};


class dt_circle_note_on : public dt_circle_base{

public:
	dt_circle_note_on();
	~dt_circle_note_on();
		
	// override
	virtual void setup( int beat_num );
	virtual void update();
	virtual void draw();
	virtual void fire();

	void check_connection();
	virtual void make_vbo();
	
	ofVboMesh rshape;
    ofVboMesh rguid;
  
	vector<dt_circle_base*> input_circles;
	vector<dt_circle_base*> output_circles;

    dt_param_state p_state;

};