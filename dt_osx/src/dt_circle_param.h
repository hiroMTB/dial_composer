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
	virtual void change_rshape(int type);

    float param;

	ofVboMesh rshape;
};
