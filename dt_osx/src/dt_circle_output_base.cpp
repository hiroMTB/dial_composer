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

void dt_circle_output_base::setup_text(){

    if(data.rev_radius<15){
        font = &app->font_manager.font_S;
    }else{
        font = &app->font_manager.font_M;
    }

    ofRectangle bb = font->getStringBoundingBox(initial, 0,0);
    float font_w = bb.width;
    float font_h = bb.height;
    float target_w = data.rev_radius;
    float scale = target_w/font_w;
    
    text_mesh = font->getStringMesh(initial, -font_w/2-1, font_h/2);
}

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
    font->getFontTexture().bind();
    text_mesh.draw();
    font->getFontTexture().unbind();
#endif

	ofPopMatrix();
}


void dt_circle_output_base::update(){
	data.position += data.move_speed;
	data.world_position = data.position;
}

