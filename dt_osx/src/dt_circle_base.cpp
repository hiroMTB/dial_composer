//
//  dt_circle_base.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_circle_base.h"
#include "dt_sequencer.h"
#include "ofApp.h"
#include "dt_sequence_thread.h"

/*
 *
 *		data
 *
 */
ofFloatColor dt_circle_data::defaultColor = ofFloatColor(0);

dt_circle_data::dt_circle_data():
name("def"), bStop(false), bMute(false), position(ofVec2f(-1,-1)), radius(12), rev_angle(0), rev_radius(20), rev_speed(0), phase_step(0), collision_radius(10), bCollide(true), input_connection_radius(0), output_connection_radius(0), bShowUI(false), circle_type(DT_CIRCLE_BASE),speed(1),step_age(0), bFired(false), fire_rate(0), fired_ch(-1)
{
	move_speed.set(0,0);
}


/*
 *
 *		circle
 *
 */
dt_circle_base * dt_circle_base::selected_circle = NULL;

dt_circle_base::dt_circle_base(){
	data.circle_type = DT_CIRCLE_BASE;
	app = ofApp::getInstance();
}


void dt_circle_base::step(){
	
	if(wait_step > 0){
		wait_step--;
		return;
	}
	
	if(app->sequence_thread.master_step % data.speed == 0){
		pre_srep();
		
		if(data.bStop) return;
		
		check_sequencer();
		
		post_step();
	}
}

void dt_circle_base::check_sequencer(){

	seq->updateIndicator();	
	data.rev_speed = (float)360.0 / (float)seq->total_steps;
	data.rev_angle = seq->indicator * data.rev_speed;

	if (!data.bMute){
		bool is_on_Beat = seq->isOnBeat();
		
		if(is_on_Beat){
			if(seq->getDataNow()){
				data.bFired = true;
				fire();
			}else{
				data.bFired = false;
			}
		}
	}
}

void dt_circle_base::change_beat(int beat){
	delete seq;
	seq = new dt_sequencer();
	seq->setup(beat);
}

void dt_circle_base::setup_text(string initial){
	
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


void dt_circle_base::draw_initial(){
	font->getFontTexture().bind();
    text_mesh.draw();
    font->getFontTexture().unbind();
}
