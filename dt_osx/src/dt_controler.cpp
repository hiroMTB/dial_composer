//
//  dt_controler.cpp
//  dt_osx
//
//  Created by hiroshi matoba on 7/11/14.
//
//

#include "dt_controler.h"
#include "ofApp.h"
#include "dt_circle_all_containers.h"
#include "dt_circle_base.h"
#include "dt_circle_container.h"


/*
 *
 *		dt_controler
 *
 */

dt_controler::dt_controler()
:bShow(false){
    panel.setDefaultWidth(300);
    panel.setDefaultHeight(25);
    panel.setDefaultTextColor(160);
    panel.setup();
    
    panel.add(fps.setup("fps", ""));
	panel.add(circle_num.setup("circle num", ""));
	panel.add(noteOn_num.setup("noteOn num", ""));
	panel.add(param_num.setup("param num", ""));
	panel.add(output_num.setup("output num", ""));
	
    panel.add(rhyth_shape_min_slot.setup("rhyth shape min slot", ""));
    panel.add(rhyth_shape_max_slot.setup("rhyth shape max slot", ""));
    panel.add(quantize_resolution.setup("quantize resolution", ""));
    panel.add(beat_resolution.setup("beat resolution", ""));
    panel.add(max_circle_num.setup("max circle num", ""));
    panel.add(connection_num_input_max.setup("connection num input max", ""));
    panel.add(connection_num_output_max.setup("connection_num_output_max", ""));
    panel.add(max_osc_ch.setup("max osc ch", ""));
    panel.add(osc_out_address.setup("osc out address", ""));
    panel.add(osc_out_port.setup("osc out port", ""));
    
    panel.add(sleep_ms.setup("sleep ms", ""));

    app = ofApp::getInstance();
	
	
	osc_r.setup(10000);
}


void dt_controler::draw(){
    if(bShow){
        app = ofApp::getInstance();

        // status
        fps = ofToString(ofGetFrameRate());
		circle_num = ofToString(app->all_containers.circle_base_container->circles.size());
		noteOn_num = ofToString(app->all_containers.note_on_container->circles.size());
		param_num = ofToString(app->all_containers.param_container->circles.size());
		output_num = ofToString(app->all_containers.output_container->circles.size());

		
        rhyth_shape_min_slot = ofToString( dt_config::DT_RHYTHM_SHAPE_MIN_SLOT );
        rhyth_shape_max_slot = ofToString( dt_config::DT_RHYTHM_SHAPE_MAX_SLOT );
        quantize_resolution = ofToString( dt_config::DT_QUANTIZE_RESOLUTION );
        beat_resolution = ofToString( dt_config::DT_BEAT_RESOLUTION );
        
        max_circle_num = ofToString( dt_config::DT_MAX_CIRCLE_NUM );
        connection_num_input_max = ofToString( dt_config::DT_CONNECTION_NUM_INPUT_MAX );
        connection_num_output_max = ofToString( dt_config::DT_CONNECTION_NUM_OUTPUT_MAX );

        max_osc_ch = ofToString( dt_config::DT_MAX_OSC_CH );
        osc_out_address = ofToString( dt_config::DT_OSC_OUT_ADDRESS );
        osc_out_port = ofToString( dt_config::DT_OSC_OUT_PORT );
        
        sleep_ms = ofToString(app->sequence_thread.sleep_microsec*0.001);
        
        ofSetColor(200);
        panel.draw();
    }
}


void dt_controler::toggle(){
    bShow = !bShow;
}


/*

fps

rhyth_shape_min_slot
rhyth_shape_max_slot
quantize_resolution
beat_resolution

max_circle_num
connection_num_input_max
connection_num_output_max

max_osc_ch
osc_out_address
osc_out_port

sleep_us
sleep_freq


*/