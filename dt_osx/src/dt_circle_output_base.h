//
//  dt_circle_output_base.h
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#pragma once


#include "ofMain.h"
#include "dt_circle_base.h"

class dt_circle_output_base : public dt_circle_base{
	
public:
	dt_circle_output_base(){};
	~dt_circle_output_base(){};
	
  	// empty
	virtual void setup(int beat_num){};
	virtual void update();
	virtual void fire(){};
	
    
	// override
	virtual void draw();

	int ch;
};

