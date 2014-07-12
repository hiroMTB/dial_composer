//
//  dt_config.cpp
//  dt_osx
//
//  Created by mtb on 2014/07/12.
//
//

#include "dt_config.h"
#include "ofApp.h"
#include "dt_circle_container.h"
#include "dt_circle_all_containers.h"

// Rhythm
int dt_config::DT_RHYTHM_SHAPE_SLOT_MIN =	  3;
int dt_config::DT_RHYTHM_SHAPE_SLOT_MAX =	 24;
int dt_config::DT_QUANTIZE_RESOLUTION =		 64;
int dt_config::DT_BEAT_RESOLUTION =			 64;
int dt_config::DT_BEAT_SPEED_MAX =			 32;

// Circle
int dt_config::DT_MAX_CIRCLE_NUM =		  50000;
int dt_config::DT_CONNECTION_NUM_INPUT_MAX = 16;
int dt_config::DT_CONNECTION_NUM_OUTPUT_MAX = 3;

// OSC
int dt_config::DT_OSC_OUT_CH_MAX =		 32;
std::string dt_config::DT_OSC_OUT_ADDRESS_PREFIX = "/dt_out/";
std::string dt_config::DT_OSC_OUT_ADDRESS = "localhost";
int dt_config::DT_OSC_OUT_PORT =		   9999;


std::string dt_config::DT_OSC_IN_ADDRESS_PREFIX = "/dt_in/";
int dt_config::DT_OSC_IN_PORT =		   8888;


bool dt_config::DT_MOVE_CIRCLE = true;

bool dt_config::DT_MASSIVE_MODE = false;

dt_config::dt_config()
:bShow(true){
}

void dt_config::setup(){
	width = 250;
	height = 20;
	int color = 110;
	
	{
		status.setDefaultWidth(width);
		status.setDefaultHeight(height);
		status.setDefaultTextColor(color);
		status.setup();
		status.setName("status");

		status.add(fps.setup("fps", ""));
		status.add(circle_num.setup("all circle num", ""));
		status.add(noteOn_num.setup("noteOn circle num", ""));
		status.add(param_num.setup("param circle num", ""));
		status.add(output_num.setup("output circle num", ""));
	}

	{
		osc.setDefaultWidth(width);
		osc.setDefaultHeight(height);
		osc.setDefaultTextColor(color);
		osc.setup();
		osc.setName("osc");
		
		osc.add(osc_out_ch_max.setup("/osc_out_ch_max", ""));
		osc.add(osc_out_address.setup("/osc_out_address", ""));
		osc.add(osc_out_port.setup("/osc_out_port", ""));
		osc.add(osc_in_port.setup("/osc_in_port", ""));
	}
	
	{
		control.setDefaultWidth(width);
		control.setDefaultHeight(height);
		control.setDefaultTextColor(color);
		control.setup();
		control.setName("control");
		
		control.add(rhythm_shape_slot_min.setup("/rhythm_shape_slot_min", ""));
		control.add(rhythm_shape_slot_max.setup("/rhythm_shape_slot_max", ""));
		control.add(beat_resolution.setup("/beat_resolution", ""));
		control.add(beat_speed_max.setup("/beat_speed_max", ""));
		
		control.add(connection_num_input_max.setup("/connection_num_input_max", ""));
		control.add(connection_num_output_max.setup("/connection_num_output_max", ""));
		control.add(sleep_microsec.setup("/sleep_microsec", ""));
	}
	
	reset_position();
}

void dt_config::reset_position(){
	app = ofApp::getInstance();
	int x = app->canvas.x + 20;
	int y = app->canvas.y + app->canvas.height + 40;
	status.setPosition(x,  y);
	osc.setPosition(x + width + 20, y);
	control.setPosition(x + width*2 + 40, y);
	
	osc_r.setup(DT_OSC_IN_PORT);
}


void dt_config::update(){
	app = ofApp::getInstance();
	
	if(bShow){
		
        // status
        fps = ofToString(ofGetFrameRate());
		circle_num = ofToString(app->all_containers.circle_base_container->circles.size());
		noteOn_num = ofToString(app->all_containers.note_on_container->circles.size());
		param_num = ofToString(app->all_containers.param_container->circles.size());
		output_num = ofToString(app->all_containers.output_container->circles.size());
		
		
        rhythm_shape_slot_min = ofToString( dt_config::DT_RHYTHM_SHAPE_SLOT_MIN );
        rhythm_shape_slot_max = ofToString( dt_config::DT_RHYTHM_SHAPE_SLOT_MAX );
        beat_resolution = ofToString( dt_config::DT_BEAT_RESOLUTION );
        beat_speed_max = ofToString( dt_config::DT_BEAT_SPEED_MAX );
        
        //max_circle_num = ofToString( dt_config::DT_MAX_CIRCLE_NUM );
        connection_num_input_max = ofToString( dt_config::DT_CONNECTION_NUM_INPUT_MAX );
        connection_num_output_max = ofToString( dt_config::DT_CONNECTION_NUM_OUTPUT_MAX );
		
        osc_out_ch_max = ofToString( dt_config::DT_OSC_OUT_CH_MAX );
        osc_out_address = ofToString( dt_config::DT_OSC_OUT_ADDRESS );
        osc_out_port = ofToString( dt_config::DT_OSC_OUT_PORT );
        osc_in_port = ofToString( dt_config::DT_OSC_IN_PORT );

        
        sleep_microsec = ofToString(app->sequence_thread.sleep_microsec);
	}
	
	
	while(osc_r.hasWaitingMessages()){
		ofxOscMessage m;
		osc_r.getNextMessage(&m);
		
		string address = m.getAddress();
		string pre = DT_OSC_IN_ADDRESS_PREFIX;
		
		if( address == pre + "sleep_microsec"){
			
			int i = m.getArgAsInt32(0);
			app->sequence_thread.change_sleep_time_microsec(i);
			
		}else if(address == pre + "connection_num_input_max"){
			
			int i = m.getArgAsInt32(0);
			DT_CONNECTION_NUM_INPUT_MAX = i;
			
		}else if(address == pre + "connection_num_output_max"){
			
			int i = m.getArgAsInt32(0);
			DT_CONNECTION_NUM_OUTPUT_MAX = i;
			
		}else if(address == pre + "osc_out_ch_max"){
			
			int i = m.getArgAsInt32(0);
			DT_OSC_OUT_CH_MAX = i;
			app->all_containers.change_osc_ch_all();
			
		}else if(address == pre + "osc_out_address"){
			
			string s = m.getArgAsString(0);
			DT_OSC_OUT_ADDRESS = s;
			app->osc_sender.setTargetAddress(s);
			
		}else if(address == pre + "osc_out_port"){
			
			int i = m.getArgAsInt32(0);
			DT_OSC_OUT_PORT = i;
			app->osc_sender.setTargetPort(i);
			
		}else if(address == pre + "osc_in_port"){
			
			int i = m.getArgAsInt32(0);
			DT_OSC_IN_PORT = i;
			osc_r.setup(i);
			
		}else if(address == pre + "beat_resolution"){
			
			int i = m.getArgAsInt32(0);
			DT_BEAT_RESOLUTION = i;
			app->all_containers.change_beat_resolution_all(i);
			
		}else if(address == pre + "beat_speed_max"){
			
			int i = m.getArgAsInt32(0);
			DT_BEAT_SPEED_MAX = i;
			app->all_containers.change_speed_random_all(1, i);
			
		}else if(address == pre + "rhythm_shape_slot_min"){
			
			int i = m.getArgAsInt32(0);
			DT_RHYTHM_SHAPE_SLOT_MIN = i;
			
		}else if(address == pre + "rhythm_shape_slot_mam"){
			
			int i = m.getArgAsInt32(0);
			DT_RHYTHM_SHAPE_SLOT_MAX = i;
			
		}else{
			cout << "Receive strange OSC address : " << address << endl;
		}
		
	}
	
}


void dt_config::draw(){
	if(bShow){
		ofSetColor(200);
		status.draw();
		osc.draw();
		control.draw();
	}
}

void dt_config::toggle(){
    bShow = !bShow;
}
