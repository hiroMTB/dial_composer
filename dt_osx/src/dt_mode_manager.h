//
//  dt_mode_manager.cpp
//  dial
//
//  Created by mtb on 2014/09/11.
//
//

#pragma once

enum dt_mode{
	DT_MODE_HOME = 0,
	DT_MODE_ZOOM = 1,
	DT_MODE_HOME2ZOOM = 2,
	DT_MODE_ZOOM2HOME = 3
};

class ofApp;

class dt_mode_manager{
	
public:
	
	dt_mode_manager(){};
	void setup();
	void change_mode( dt_mode mode );
	
	void debug_draw();
	
	ofApp * app;
	dt_mode mode;
};