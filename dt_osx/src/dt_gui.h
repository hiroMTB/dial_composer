//
//  dt_gui.h
//  dialt_osx
//
//  Created by mtb on 2014/07/07.
//
//

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class dt_gui{

public:

	bool bShow;
	
	ofxPanel panel;
	ofxLabel fps;
	ofxIntSlider sleep_us;
	ofxIntSlider sleep_freq;
	
	
	
	ofxFloatSlider fl;
	ofxColorSlider col;
	ofxVec2Slider vec2;
	ofxToggle tgl;
	ofxButton btn;

	dt_gui()
	:bShow(false){
		panel.setup();
		panel.add(fps.setup("fps", ""));
		panel.add(sleep_us.setup("sleep us", 100, 1000, 10000000));
	};
	
	
	void draw(){
		if(bShow){
			fps = ofToString(ofGetFrameRate());
			panel.draw();
		}
	}

	
	void toggle(){
		bShow = !bShow;
	}
};