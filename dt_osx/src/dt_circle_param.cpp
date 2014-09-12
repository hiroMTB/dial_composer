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

dt_circle_param::dt_circle_param()
:
param_on( ofRandom(0.2, 0.3) ),
param_off( ofRandom(0.001, 0.1) ),
param_max( 1 ),
param_min( 0 ),
parent( NULL )
{
	initial = "";
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
    
	data.indi_position = calc_indi_position() + parent->data.position;
	ofApp::getInstance()->all_containers.add_indicator( data.indi_position, data.circle_color );

    // size update
    data.rev_radius = dt_config::DT_SIZE_BASE * 0.23;
	data.collision_radius = data.rev_radius * 1.2;
	data.input_connection_radius = data.collision_radius + 100;
	data.output_connection_radius = data.collision_radius + 100;
}

void dt_circle_param::draw(){
	
	ofPushMatrix();
	ofTranslate( data.position.x, data.position.y );
		
	bool fired = data.fire_rate>0.5;
	bool selected = selected_circle == this;
	
    {
        // Circle
        ofSetColor( data.circle_color - data.fire_rate*0.2 );
        ofNoFill();
        ofSetLineWidth( 2 );
        glPointSize( 1 );
        app->circle_drawer.draw( data.rev_radius*1.2 );
    }

    {
        // shape
        draw_vbo();
    }
    
    ofSetColor( 0 );
	draw_initial();
	
//	if( data.bShowUI )
//		ui->draw();
	
	ofPopMatrix();
}

void dt_circle_param::draw_vbo(){
	glLineWidth( 2 );
	rshape.draw( OF_MESH_FILL );
}

void dt_circle_param::make_vbo(){
	rshape.clear();
	
	int beat_num = seq->total_beats;
	int beat_res = dt_config::DT_BEAT_RESOLUTION;
	float start_angle = 0;
	float r = data.rev_radius;
	float length = 3;
	
    int vertIndex = 0;
	for( int i=0; i<beat_num; i++ ){
		bool on = seq->getDataFromBeat( i );
		if( !on )
			continue;
		
		float angle = start_angle + ( i*data.rev_speed * beat_res );
		float sx = r * cosf( angle*DEG_TO_RAD );
		float sy = r * sinf( angle*DEG_TO_RAD );
			
		rshape.addVertex( ofVec2f(sx,sy) );
		rshape.addIndex( vertIndex++ );
        rshape.addColor( data.circle_color );
	}
	
    rshape.setUsage( GL_DYNAMIC_DRAW );
    rshape.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
}

void dt_circle_param::fire(){
	data.fire_rate = 1.0;
}

void dt_circle_param::change_param_type( dt_circle_type type ){

    data.circle_type = type;
    
    switch ( type ) {
        case DT_CIRCLE_NOTE_NUM:
            change_circle_color( noteNum_color );
            initial = "Note";
            break;
        case DT_CIRCLE_VELOCITY:
            change_circle_color( velocity_color );
            initial = "Vel";
            break;
        case DT_CIRCLE_DURATION:
            change_circle_color( duration_color );
            initial = "Dur";
            break;
        case DT_CIRCLE_PAN:
            change_circle_color( pan_color );
            initial = "Pan";
            break;
        case DT_CIRCLE_CC1:
            change_circle_color( cc1_color );
            initial = "CC1";
            break;
        case DT_CIRCLE_CC2:
            change_circle_color( cc2_color );
            initial = "CC2";
            break;
        case DT_CIRCLE_CC3:
            change_circle_color( cc3_color );
            initial = "CC3";
            break;
        case DT_CIRCLE_CC4:
            change_circle_color( cc4_color );
            initial = "CC4";
            break;
            
        default:
            break;
    }
    
    setup_text( initial );
}