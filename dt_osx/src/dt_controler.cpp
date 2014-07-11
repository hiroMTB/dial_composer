//
//  dt_controler.cpp
//  dt_osx
//
//  Created by hiroshi matoba on 7/11/14.
//
//

#include "dt_controler.h"
#include "ofApp.h"

dt_controler::dt_controler()
:bShow(false){
    panel.setDefaultWidth(300);
    panel.setDefaultHeight(30);
    panel.setDefaultTextColor(160);
    panel.setup();
    
    panel.add(fps.setup("fps", ""));
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
    
    panel.add(sleep_us.setup("sleep us", ""));
    panel.add(sleep_freq.setup("sleep freq", ""));

    app = ofApp::getInstance();
}


void dt_controler::draw(){
    if(bShow){
        app = ofApp::getInstance();
        
        fps = ofToString(ofGetFrameRate());

        rhyth_shape_min_slot = ofToString( DT_RHYTHM_SHAPE_MIN_SLOT );
        rhyth_shape_max_slot = ofToString( DT_RHYTHM_SHAPE_MAX_SLOT );
        quantize_resolution = ofToString( DT_QUANTIZE_RESOLUTION );
        beat_resolution = ofToString( DT_BEAT_RESOLUTION );
        
        max_circle_num = ofToString( DT_MAX_CIRCLE_NUM );
        connection_num_input_max = ofToString( DT_CONNECTION_NUM_INPUT_MAX );
        connection_num_output_max = ofToString( DT_CONNECTION_NUM_OUTPUT_MAX );


        max_osc_ch = ofToString( DT_MAX_OSC_CH );
        osc_out_address = ofToString( DT_OSC_OUT_ADDRESS );
        osc_out_port = ofToString( DT_OSC_OUT_PORT );
        
        sleep_us = ofToString(app->sequence_thread.real_sleep_micro_sec, 2);
        sleep_freq = ofToString( app->sequence_thread.freq );
        
        
        
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