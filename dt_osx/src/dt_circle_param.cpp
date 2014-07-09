//
//  dt_circle_param_base.cpp
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#include "dt_circle_param.h"
#include "dt_dial_ui.h"
#include "dt_sequence_thread.h"
#include "ofApp.h"
#include "dt_font_manager.h"
#include "dt_circle_drawer.h"

dt_circle_param_base::dt_circle_param_base()
:param_on(ofRandom(0.2, 0.3)),param_off(ofRandom(0.001, 0.1)), param_max(1), param_min(0)
{
//	ui = new dt_dial_ui(this);
	initial = "BASE";
}

dt_circle_param_base::~dt_circle_param_base(){
	if(ui){
	   delete ui;
		ui = 0;
	}
}

void dt_circle_param_base::setup(int beat_num){
//	seq->setup(beat_num);
//	
//	data.rev_speed = (float)360.0 / (float)seq->total_steps;
//	data.rev_angle = seq->indicator * data.rev_speed;
//	data.rev_radius = 6.0 + (float)beat_num * 0.4;
//	data.collision_radius = data.rev_radius + ofRandom(3, 30);
//
//	change_rshape(ofRandom(30, 60));
	
	data.collision_radius = 20;
	data.bCollide = false;

}

void dt_circle_param_base::change_rshape(int type){
	seq->setRhythmShape(type);
	make_vbo();
}


void dt_circle_param_base::update(){
	data.fire_rate*=0.8;
	
	data.position += data.move_speed;

	//	float ind = seq->indicator;
	//	data.rev_angle = TWO_PI * ind / (float)seq->total_steps;
	//	ofVec2f p(cosf(data.rev_angle), sinf(data.rev_angle));
	data.world_position = data.position; // + p * data.rev_radius;
	
}

void dt_circle_param_base::draw(){
	/*
	float waiting_rate = (float)(dt_sequencer::beat_resolution-wait_step) / (float)dt_sequencer::beat_resolution;
	
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(data.position.x, data.position.y);
	
	float waiting_animation_rate = 0.5 + waiting_rate*0.5;
	ofScale(waiting_animation_rate, waiting_animation_rate);
	
	bool fired = data.fire_rate>0.5;
	bool selected = selected_circle == this;
	
	// Circle
	ofSetColor(data.circle_color - data.fire_rate*0.2);
	ofNoFill();
	ofSetLineWidth(1);
	glPointSize(1);
#ifndef NOT_USE_OF_CIRCLE
	ofCircle(0, 0, data.rev_radius);
#else
	//app->circle_drawer->draw(data.rev_radius);
#endif
	
#ifndef NOT_USE_OF_DRAW_TEXT
	// Text
	ofTrueTypeFont *f;
	if(data.rev_radius<15){
		f = &app->font_manager->font_S;
	}else{
		f = &app->font_manager->font_M;
	}
	
	ofRectangle bb = f->getStringBoundingBox(initial, 0,0);
	float font_w = bb.width;
	float font_h = bb.height;
	float target_w = data.rev_radius/1.8;
	float scale = target_w/font_w;
	
	ofFill();
	f->drawStringAsShapes(initial, -font_w/2, font_h/2);
#endif
	
	
	// shape
	draw_vbo();
	
	//if(data.bShowUI) ui->draw();
	
	ofPopStyle();
	ofPopMatrix();
	 */
}


void dt_circle_param_base::draw_vbo(){
	glLineWidth(1);
	rshape_vbo.bind();
	rshape_vbo.draw(GL_LINES, 0, rshape_points.size());
	rshape_vbo.unbind();
}

void dt_circle_param_base::make_vbo(){
	rshape_points.clear();
	
	int beat_num = seq->total_beats;
	int beat_res = DT_BEAT_RESOLUTION;
	float start_angle = 0;
	float r = data.rev_radius;
	float lenght = 3;
	
	for(int i=0; i<beat_num; i++){
		bool on = seq->getDataFromBeat(i);
		if(!on) continue;
		
		float angle = start_angle + (i*data.rev_speed * beat_res);
		float sx = r * cosf(angle*DEG_TO_RAD);
		float sy = r * sinf(angle*DEG_TO_RAD);
		float ex = (r + lenght) * cosf(angle*DEG_TO_RAD);
		float ey = (r + lenght)* sinf(angle*DEG_TO_RAD);
			
		rshape_points.push_back(ofVec2f(sx,sy));
		rshape_points.push_back(ofVec2f(ex,ey));
	}
	
	rshape_vbo.setVertexData(&rshape_points[0], rshape_points.size(), GL_DYNAMIC_DRAW);
}


void dt_circle_param_base::fire(){
	data.fire_rate = 1.0;
}



ofColor dt_circle_param_base::noteNum_color =	ofColor(184,  88,  32);
ofColor dt_circle_param_base::velocity_color =	ofColor(247, 106, 129);
ofColor dt_circle_param_base::duration_color =	ofColor( 52,  78, 168);
ofColor dt_circle_param_base::L_color =			ofColor( 30, 141,  25);
ofColor dt_circle_param_base::R_color =			ofColor( 30, 141,  25);
ofColor dt_circle_param_base::cc12_color =		ofColor(133, 135,  65);
ofColor dt_circle_param_base::cc13_color =		ofColor(160, 163,  79);
ofColor dt_circle_param_base::cc14_color =		ofColor(201, 204,  98);

