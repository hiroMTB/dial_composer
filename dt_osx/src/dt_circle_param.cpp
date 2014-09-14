//
//  dt_circle_param.cpp
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#include "ofApp.h"
#include "dt_circle_param.h"
#include "dt_dial_ui.h"
#include "dt_sequence_thread.h"
#include "dt_font_manager.h"
#include "dt_circle_drawer.h"

ofColor dt_circle_param::noteNum_color =	ofColor( 184,  88,  32 );
ofColor dt_circle_param::velocity_color =	ofColor( 247, 106, 129 );
ofColor dt_circle_param::duration_color =	ofColor(  52,  78, 168 );
ofColor dt_circle_param::pan_color =		ofColor(  30, 141,  25 );
ofColor dt_circle_param::cc1_color =		ofColor( 133, 135,  65 );
ofColor dt_circle_param::cc2_color =		ofColor( 160, 163,  79 );
ofColor dt_circle_param::cc3_color =		ofColor( 201, 204,  98 );
ofColor dt_circle_param::cc4_color =		ofColor( 241, 244,  138 );

dt_circle_drawer dt_circle_param::circle_drawer;

dt_circle_param::dt_circle_param()
:
param_on( ofRandom(0.2, 0.3) ),
param_off( ofRandom(0.001, 0.1) ),
param_max( 1 ),
param_min( 0 )
{
	initial = "";
    if( !circle_drawer.bInitialized ){
        circle_drawer.initialize( 30 );
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
	data.fire_rate *= 0.8;
    
    data.indi_position = calc_indi_position();

	if( parent ){
        data.indi_position +=  parent->data.position;
    }
    
	ofApp::getInstance()->all_containers.add_indicator( data.indi_position, data.circle_color );

    // size update
    data.rev_radius = dt_config::DT_SIZE_BASE * 0.23;
	data.collision_radius = data.rev_radius * 1.2;
	data.input_connection_radius = data.collision_radius + 100;
	data.output_connection_radius = data.collision_radius + 100;
}

void dt_circle_param::draw(){
	
	bool blink = data.fire_rate > 0.3;
	bool selected = selected_circle == this;
    float scale = blink ? 1.0+data.fire_rate*0.05 : 1.0;

	ofPushMatrix();{
        ofTranslate( data.position.x, data.position.y );
        ofPushMatrix();{
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
            circle_drawer.draw( data.rev_radius * 1.26, OF_MESH_POINTS );
            
            // shape
            ofPushMatrix();{
                float shape_scale = data.rev_radius * 0.01;
                ofScale( shape_scale, shape_scale, 1 );
                
                // guid
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

void dt_circle_param::fire(){
	data.fire_rate = 1.0;
}

void dt_circle_param::change_param_type( dt_circle_type type ){

    data.circle_type = type;
    
    switch ( type ) {
        case DT_CIRCLE_NOTE_NUM:
            change_circle_color( noteNum_color );
            initial = "N";
            break;
        case DT_CIRCLE_VELOCITY:
            change_circle_color( velocity_color );
            initial = "V";
            break;
        case DT_CIRCLE_DURATION:
            change_circle_color( duration_color );
            initial = "D";
            break;
        case DT_CIRCLE_PAN:
            change_circle_color( pan_color );
            initial = "P";
            break;
        case DT_CIRCLE_CC1:
            change_circle_color( cc1_color );
            initial = "C1";
            break;
        case DT_CIRCLE_CC2:
            change_circle_color( cc2_color );
            initial = "C2";
            break;
        case DT_CIRCLE_CC3:
            change_circle_color( cc3_color );
            initial = "C3";
            break;
        case DT_CIRCLE_CC4:
            change_circle_color( cc4_color );
            initial = "C4";
            break;
            
        default:
            break;
    }
    
    setup_text( initial );
}