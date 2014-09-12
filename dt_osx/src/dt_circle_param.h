//
//  dt_circle_param.h
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#pragma once

#include "ofMain.h"
#include "dt_circle_base.h"

class dt_circle_param : public dt_circle_base{

public:
	dt_circle_param();
	~dt_circle_param();
	
	virtual void setup(int beat_num);
	virtual void fire();
	void update();
	void draw();
	void draw_vbo();
	virtual void make_vbo();

	static ofColor noteNum_color;
	static ofColor velocity_color;
	static ofColor duration_color;
	static ofColor pan_color;
	static ofColor cc1_color;
	static ofColor cc2_color;
	static ofColor cc3_color;
	static ofColor cc4_color;
	
    float param_on;
	float param_off;
	float param_min;
	float param_max;

	ofVboMesh rshape;
};
