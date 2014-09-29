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
	virtual void update();
	virtual void draw();
    virtual void on_process();
    void change_param_type( dt_circle_type t );

};
