//
//  dt_circle_base.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_circle_base.h"
#include "dt_sequencer.h"


/*
 *
 *	data
 *
 */

ofFloatColor dt_circle_data::defaultColor = ofFloatColor(0);

dt_circle_data::dt_circle_data():
name("def"), bStop(false), bMute(false), position(ofVec2f(-1,-1)), radius(12), rev_angle(0), rev_radius(20), rev_speed(0), phase_step(0), collision_radius(10), bCollide(true), input_connection_radius(0), output_connection_radius(0), bShowUI(false), circle_type(DT_CIRCLE_BASE),speed(1),step_age(0), bFired(false), fire_rate(0), fired_ch(-1)
{
	move_speed.set(ofRandom(-1, 1),ofRandom(-1, 1));
	move_speed *= 2;
}


/*
 *
 *		circle
 *
 */

#include "ofApp.h"
#include "dt_sequence_thread.h"

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

////#undef check
//#include <boost/thread.hpp>
//#include <boost/chrono.hpp>
//using namespace boost;
void dt_circle_base::check_sequencer(){

	seq->updateIndicator();	
	data.rev_speed = (float)360.0 / (float)seq->total_steps;
	data.rev_angle = seq->indicator * data.rev_speed;

	if (!data.bMute){
		//bool is_sequense_on = seq.getDataNow();
		bool is_on_Beat = seq->isOnBeat();
		
		if(is_on_Beat){
			if(seq->getDataNow()){
				data.bFired = true;
				
//				boost::thread fire_thread(&dt_circle_base::fire, this);
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