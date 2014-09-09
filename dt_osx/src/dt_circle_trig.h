//
//  dt_circle_trig.h
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


class dt_circle_trig : public dt_circle_base{

public:
	dt_circle_trig();
	~dt_circle_trig();
		
	// override
	virtual void setup( int beat_num );
	virtual void update();
	virtual void draw();
	virtual void fire();

	void set_beats( int beat_num );
	void set_speed( int speed );
	void check_connection();
	virtual void change_rshape( int type );
	virtual void make_vbo();
	void update_world_position();
	
	ofVboMesh rshape;
    ofVboMesh rguid;
  
	vector<dt_circle_base*> input_circles;
	vector<dt_circle_base*> output_circles;

};