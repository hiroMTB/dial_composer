//
//  dt_circle_all_containers.cpp
//  dialt
//
//  Created by mtb on 30/05/14.
//
//

#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_param.h"

dt_circle_all_containers::dt_circle_all_containers(){
	setup();
}

void dt_circle_all_containers::setup(){
	
	
	// container
	circle_base_container	= new dt_circle_base_container();
	note_on_container		= new dt_circle_note_on_container();
	param_container			= new dt_circle_param_container();
	output_container		= new dt_circle_output_container();
	
	// all points
	for(int i=0; i<DT_MAX_CIRCLE_NUM; i++){
		all_points_pos.push_back(ofVec2f(-123,-123));
		all_points_color.push_back(ofFloatColor(1, 0.3,0.2));
	}
	all_points_vbo.setVertexData(&all_points_pos[0], all_points_pos.size(), GL_DYNAMIC_DRAW);
	all_points_vbo.setColorData(&all_points_color[0], all_points_color.size(), GL_DYNAMIC_DRAW);
	
	
	// all lines
	for(int i=0; i<DT_MAX_CIRCLE_NUM*3; i++){
		all_lines_pos.push_back(ofVec2f(-123,-123));
		all_lines_pos.push_back(ofVec2f(-123,-123));
		all_lines_color.push_back(ofFloatColor(0,1,0));
		all_lines_color.push_back(ofFloatColor(0,1,0));
	}
	
	all_lines_vbo.setVertexData(&all_lines_pos[0], all_lines_pos.size(), GL_DYNAMIC_DRAW);
	all_lines_vbo.setColorData(&all_lines_color[0], all_lines_color.size(), GL_DYNAMIC_DRAW);
}




void dt_circle_all_containers::update(){
	all_points_pos.clear();
	all_points_color.clear();
	
	all_lines_pos.clear();
	all_lines_color.clear();
	
	circle_base_container->update();

	circle_base_container->process_collision();
	
}

void dt_circle_all_containers::add_point_to_all_points(const ofVec2f& p, const ofFloatColor& c){
	all_points_pos.push_back(p);
	all_points_color.push_back(c);
}

void dt_circle_all_containers::add_line_to_all_lines(const ofVec2f& p1, const ofVec2f& p2, const ofFloatColor& c1, const ofFloatColor& c2){
	all_lines_pos.push_back(p1);
	all_lines_pos.push_back(p2);
	all_lines_color.push_back(c1);
	all_lines_color.push_back(c2);
}


void dt_circle_all_containers::draw(){
    
    ofEnableAlphaBlending();
	param_container->draw();
	output_container->draw();
	note_on_container->draw();
	ofDisableAlphaBlending();
    
	// all lines
	ofEnableAlphaBlending();
	glLineWidth(1);
	all_lines_vbo.bind();
	all_lines_vbo.updateColorData(&all_lines_color[0], all_lines_color.size());
	all_lines_vbo.updateVertexData(&all_lines_pos[0], all_lines_pos.size());
	all_lines_vbo.draw(GL_LINES, 0, all_lines_pos.size());
	all_lines_vbo.unbind();
	ofDisableAlphaBlending();

	// all points
	glPointSize(1);
	all_points_vbo.bind();
	all_points_vbo.updateColorData(&all_points_color[0], all_points_color.size());
	all_points_vbo.updateVertexData(&all_points_pos[0], all_points_pos.size());
	all_points_vbo.draw(GL_POINTS, 0, all_points_pos.size());
	all_points_vbo.unbind();

}


void dt_circle_all_containers::step(){
	//param_container->step();
	// output_container->step();	dont need
	
	note_on_container->step();
}


void dt_circle_all_containers::change_speed_all(int speed){
	
	for(int i=0; i<note_on_container->circles.size(); i++){
		note_on_container->circles[i]->data.speed = speed;
	}
}

void dt_circle_all_containers::change_speed_random_all(int min, int max){
	if (min<1) min = 1;

	for(int i=0; i<note_on_container->circles.size(); i++){
		int speed = ofRandom(min, max);
		note_on_container->circles[i]->set_speed(speed);
		
	}
}

void dt_circle_all_containers::change_beat_all(int beat){
	for(int i=0; i<note_on_container->circles.size(); i++){
		dt_circle_note_on * n = note_on_container->circles[i];
		n->setup(beat);

		int quantize_step = DT_BEAT_RESOLUTION / DT_QUANTIZE_RESOLUTION;
		n->seq->indicator = quantize_step * (int)round(ofRandom(0, DT_QUANTIZE_RESOLUTION-1));
	}
}


void dt_circle_all_containers::change_position_all(){
	ofApp * app = ofApp::getInstance();
	for(int i=0; i<circle_base_container->circles.size(); i++){
		dt_circle_base * b =  circle_base_container->circles[i];
		b->data.position.set(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		if(ofRandom(1)<0.01) b->fire();
	}
}



