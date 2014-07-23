//
//  dt_circle_output_base.cpp
//  dialt_osx
//
//  Created by mtb on 2014/06/15.
//
//

#include "dt_circle_output_base.h"
#include "ofApp.h"
#include "dt_font_manager.h"

#include "dt_circle_drawer.h"



void dt_circle_output_base::draw(){
	
	ofPushMatrix();
	ofTranslate(data.position.x, data.position.y);		
	ofSetColor(data.circle_color);
	ofFill();
	ofSetLineWidth(1);
	glPointSize(1);
#ifndef NOT_USE_OF_CIRCLE
	ofCircle(0, 0, data.rev_radius);
#else
	app->circle_drawer.draw(data.rev_radius, GL_LINES);
#endif
	
#ifndef NOT_USE_OF_DRAW_TEXT
	// Text
    ofFill();
    ofSetColor(105);
	draw_initial();
#endif

	ofPopMatrix();
}


void dt_circle_output_base::update(){
	if(dt_config::DT_PLAY_GEN_RHYTHM){
		data.position += data.move_speed;
		data.world_position = data.position;
	}
}


void dt_circle_output_base::setup_ch(int _ch){
	ch = _ch;
	initial = ofToString(ch);
	setup_text(initial);
}