//
//  dt_circle_param.cpp
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#include "ofApp.h"
#include "dt_circle_param.h"
#include "dt_circle_note_on.h"
#include "dt_circle_drawer.h"
#include "dt_dial_ui.h"
#include "dt_sequence_thread.h"
#include "dt_font_manager.h"

dt_circle_drawer dt_circle_param::circle_drawer;

dt_circle_param::dt_circle_param(){
	initial = "";
    if( !circle_drawer.bInitialized ){
        circle_drawer.initialize( 12*6 );
    }
}

dt_circle_param::~dt_circle_param(){
	if( ui ){
	   delete ui;
		ui = 0;
	}
}

void dt_circle_param::setup( int beat_num ){
	seq = new dt_sequencer();
    
	change_beat( beat_num );
	change_speed( 1 );
    change_shape( ofRandom(-1000, 1000) );
    
	data.bCollide = false;
    setup_text( initial );
}

void dt_circle_param::update(){
    bool targeted = app->mode_manager.zoom_mode_target == parent;
    bool zoom_mode = app->mode_manager.mode == DT_MODE_ZOOM;

    if( !targeted || !zoom_mode ) return;
	data.fire_rate *= 0.8;
    
    data.indi_position = calc_indi_position();

	if( parent ){
        data.indi_position +=  parent->data.position;
    }
    
	ofApp::app->all_containers.add_indicator( data.indi_position, data.circle_color );

    // size update
    data.rev_radius = dt_config::DT_SIZE_BASE * 0.2;
	data.collision_radius = data.rev_radius * 1.2;
	data.input_connection_radius = data.collision_radius + 100;
	data.output_connection_radius = data.collision_radius + 100;
}

void dt_circle_param::draw(){
    bool targeted = app->mode_manager.zoom_mode_target == parent;
    bool zoom_mode = app->mode_manager.mode == DT_MODE_ZOOM;
    if( !targeted || !zoom_mode ) return;

//	bool blink = data.fire_rate > 0.3;
    bool blink = false;
	bool selected = selected_circle == this;
    float scale = blink ? 1.0+data.fire_rate*0.05 : 1.0;

    ofVec2f & ppos = parent->data.position;
    
	ofPushMatrix();{
        
        ofTranslate( data.position + ppos );
        ofPushMatrix();{
			float angle = data.phase_step*data.rev_speed;
			ofRotateZ( angle );
            ofScale( scale, scale );
        
            // circle
            if( selected ){
                glPointSize( 4 );
                ofSetColor( data.circle_color );
            }else{
                glPointSize( 2 );
                float b = app->bg.getBrightness() * 255.0;
                ofSetColor( 255.0-b, 220 );
            }
            circle_drawer.draw( data.rev_radius * 1.26, OF_MESH_FILL );
            
            // guide + shape
            ofPushMatrix();{
                float shape_scale = data.rev_radius * 0.01;
                ofScale( shape_scale, shape_scale, 1 );
                
                // guide
                glPointSize( 3 );
                rguid.draw( OF_MESH_POINTS );
                
                // shape
                ofPushMatrix();{
                    ofScale( 0.8, 0.8, 1 );
                    glLineWidth( 2 );
                    if (rshape.getNumVertices() <= 2){
                        rshape.draw( OF_MESH_WIREFRAME );
                    }else{
                        if( !data.bMute ){
                            rshape.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
                            rshape.draw( OF_MESH_FILL );
                        }else{
                            rshape.setMode( OF_PRIMITIVE_LINE_LOOP );
                            rshape.draw( OF_MESH_WIREFRAME );
                        }
                    }
                }ofPopMatrix();
                
            }ofPopMatrix();
            
        }ofPopMatrix();
        
        ofSetColor( data.circle_color*0.7 );
        draw_initial();
	
	}ofPopMatrix();
}

void dt_circle_param::on_process(){
	data.fire_rate = 1.0;

    // send value to note on object
    if( parent ){
        dt_circle_note_on * n = static_cast<dt_circle_note_on*>( parent );
        n->prms[ data.circle_type ] = data.output_value;
    }

    // send osc directly
    if( !dt_config::DT_OSC_OUT_PACK_RHYTHM_PARAM ){
        ofxOscMessage m;
        m.setAddress( data.address );
        m.addFloatArg( data.output_value );
        ofApp::app->osc_sender.send_message( m );
    }
}