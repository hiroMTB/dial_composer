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
#include "dt_circle_drawer.h"

class dt_circle_note_on : public dt_circle_base{

public:
	dt_circle_note_on();
	~dt_circle_note_on();
		
	// override
	virtual void setup( int beat_num );
	virtual void update();
	virtual void draw();
	virtual void on_process();

	void check_connection();
	
    std::map<dt_circle_type, float> prms;
    std::map<dt_circle_type, int> CCs;

	static dt_circle_drawer	bg_circle_drawer;


};