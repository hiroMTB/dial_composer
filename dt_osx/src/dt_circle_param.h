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
#include "dt_circle_drawer.h"

class dt_circle_param : public dt_circle_base{

public:
	dt_circle_param();
	~dt_circle_param();
	
	virtual void setup(int beat_num);
	virtual void fire();

    void change_param_type( dt_circle_type t );
	void update();
	void draw();
    
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

    static dt_circle_drawer	circle_drawer;

};
