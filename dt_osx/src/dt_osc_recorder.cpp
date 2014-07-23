//
//  dt_osc_recorder.cpp
//  dt_
//
//  Created by mtb on 2014/07/13.
//
//

#include "dt_osc_recorder.h"
#include "dt_config.h"
#include "dt_circle_drawer.h"
#include "ofApp.h"

dt_osc_recorder::dt_osc_recorder()
:current_fragment(0)
{}

void dt_osc_recorder::setup(){
	
	for(int i=0; i<fragment_ring_max; i++){
		fragment frag;

		for(int j=0; j<dt_config::DT_OSC_OUT_CH_SYSTEM_MAX; j++){
			
			ofxOscMessage m;
			m.clear();
			frag.push_back(m);
		}
		fragment_ring.push_back(frag);
	}
	
	app = ofApp::getInstance();
}


void dt_osc_recorder::update(int _x, int _y, int _w, int _h){
	if(!dt_config::DT_SHOW_BUFFERED_RHYTHM) return;
		
	int x = 0;
	int y = 0;
	int frag_w = (float)_w / fragment_ring_max;
	int ch_h = (float)_h /32.0;
	
	//
	//	we should start from current fragment position
	//

	for(int i=0; i<fragment_ring.size(); i++){

		x = i * frag_w;
				
		for(int j=0; j<dt_config::DT_OSC_OUT_CH_SYSTEM_MAX; j++){
			
			if(fragment_ring[i][j].getNumArgs() > 0){
				int ch = j;
				y = ch * ch_h;
				app->all_containers.add_point_to_all_points(ofVec2f(x+_x, y+_y), ofFloatColor(0.4, 0.9, 0.1));
			}
		}
	}
	
	if(dt_config::DT_PLAY_BUFFERED_RHYTHM){
		x = dt_config::DT_BUFFERED_RHYTHM_INDICATOR * frag_w;
		y = dt_config::DT_OSC_OUT_CH_SYSTEM_MAX * ch_h + 5;
		app->all_containers.add_line_to_all_lines(ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(1, 0, 0.5), ofFloatColor(1, 0, 0.5));
		
		// start, dynamic
		x = dt_config::DT_BUFFERED_RHYTHM_LOOP_START * frag_w;
		app->all_containers.add_line_to_all_lines(ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(0, 0.4, 0.7), ofFloatColor(0, 0.4, 0.7));
		
		// end, fixed
		x = dt_config::DT_BUFFERED_RHYTHM_LOOP_END * frag_w;
		app->all_containers.add_line_to_all_lines(ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(0, 0.4, 0.7), ofFloatColor(0, 0.4, 0.7));
		
	}
	
	x = current_fragment * frag_w;
	y = (dt_config::DT_OSC_OUT_CH_SYSTEM_MAX-1) * ch_h;
	app->all_containers.add_line_to_all_lines(ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y-5), ofFloatColor(1, 1, 1), ofFloatColor(1, 1, 1));
	app->all_containers.add_line_to_all_lines(ofVec2f(_x+x, _y+y+5), ofVec2f(_x+x, _y+y+10), ofFloatColor(1, 1, 1), ofFloatColor(1, 1, 1));
	
}

void dt_osc_recorder::add_osc_message(const ofxOscMessage &m, int ch){

	if(dt_config::DT_PLAY_BUFFERED_RHYTHM != 0) return;
	
	// delete first
	fragment_ring[current_fragment][ch-1] = m;
}


void dt_osc_recorder::step_fragment(){

	if(dt_config::DT_PLAY_BUFFERED_RHYTHM) return;
	
	if(current_fragment == fragment_ring_max-1){
		current_fragment = 0;
	}else{
		current_fragment++;
	}
	
	// clear
	for(int i=0; i<dt_config::DT_OSC_OUT_CH_SYSTEM_MAX; i++){
		fragment_ring[current_fragment][i].clear();
	}
}


void dt_osc_recorder::toggle_play_fragment(){
	
	dt_config::DT_PLAY_BUFFERED_RHYTHM = !dt_config::DT_PLAY_BUFFERED_RHYTHM;

	if(dt_config::DT_PLAY_BUFFERED_RHYTHM){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = dt_config::DT_BUFFERED_RHYTHM_LOOP_START;
	}else{
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
	}
}

void dt_osc_recorder::play_fragment(){

	int rate = dt_config::DT_BUFFERED_RHYTHM_RATE;
	
	for(int i=0; i<dt_config::DT_OSC_OUT_CH_SYSTEM_MAX; i++){
		
		if( rate==100 || ofRandom(0, 100) < rate ){
			app->osc_sender.send_message(fragment_ring[dt_config::DT_BUFFERED_RHYTHM_INDICATOR][i]);
		}
	}
		
	if(dt_config::DT_BUFFERED_RHYTHM_INDICATOR+1 == dt_config::DT_BUFFERED_RHYTHM_LOOP_END){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = dt_config::DT_BUFFERED_RHYTHM_LOOP_START;
	}else if(dt_config::DT_BUFFERED_RHYTHM_INDICATOR+1 >= fragment_ring_max){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
	}else{
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR++;
	}
}

