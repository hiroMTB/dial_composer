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
param_min( 0 )
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
    
	//set_beats( beat_num );
	//set_speed( 1 );
    
	data.rev_radius = 40;
	data.collision_radius = 20;
	data.bCollide = true;
    setup_text( initial );
}

void dt_circle_param::update(){
	data.fire_rate *= 0.8;
	
	data.indi_position = calc_indi_position();
	ofApp::getInstance()->all_containers.add_indicator( data.indi_position, data.circle_color );

    /*
     *
     *  change type
     *  should be mode to another function
     *
     */
    switch ( data.circle_type ) {
        case DT_CIRCLE_NOTE_NUM:
            data.circle_color = noteNum_color;
            initial = "N";
            break;
        case DT_CIRCLE_VELOCITY:
            data.circle_color = velocity_color;
            initial = "V";
            break;
        case DT_CIRCLE_DURATION:
            data.circle_color = duration_color;
            initial = "D";
            break;
        case DT_CIRCLE_PAN:
            data.circle_color = pan_color;
            initial = "P";
            break;
        case DT_CIRCLE_CC1:
            data.circle_color = cc1_color;
            initial = "CC1";
            break;
        case DT_CIRCLE_CC2:
            data.circle_color = cc2_color;
            initial = "CC2";
            break;
        case DT_CIRCLE_CC3:
            data.circle_color = cc3_color;
            initial = "CC3";
            break;
        case DT_CIRCLE_CC4:
            data.circle_color = cc4_color;
            initial = "CC4";
            break;

        default:
            break;
    }
}

void dt_circle_param::draw(){
	
	ofPushMatrix();
	ofTranslate( data.position.x, data.position.y );
		
	bool fired = data.fire_rate>0.5;
	bool selected = selected_circle == this;
	
	// Circle
    
	ofSetColor( data.circle_color - data.fire_rate*0.2 );
	ofNoFill();
	ofSetLineWidth( 2 );
	glPointSize( 3 );
	app->circle_drawer.draw( data.rev_radius );
	
#ifndef NOT_USE_OF_DRAW_TEXT
	draw_initial();
#endif
	
	draw_vbo();
	
	if( data.bShowUI )
		ui->draw();
	
	ofPopMatrix();
}

void dt_circle_param::draw_vbo(){
	glLineWidth( 2 );
	rshape.draw( OF_MESH_WIREFRAME );
}

void dt_circle_param::make_vbo(){
	rshape.clear();
	
	int beat_num = seq->total_beats;
	int beat_res = dt_config::DT_BEAT_RESOLUTION;
	float start_angle = 0;
	float r = data.rev_radius;
	float lenght = 3;
	
    int vertIndex = 0;
	for( int i=0; i<beat_num; i++ ){
		bool on = seq->getDataFromBeat( i );
		if( !on )
			continue;
		
		float angle = start_angle + ( i*data.rev_speed * beat_res );
		float sx = r * cosf( angle*DEG_TO_RAD );
		float sy = r * sinf( angle*DEG_TO_RAD );
		float ex = ( r+lenght ) * cosf( angle*DEG_TO_RAD );
		float ey = ( r+lenght ) * sinf( angle*DEG_TO_RAD );
			
		rshape.addVertex( ofVec3f(sx,sy,0) );
        rshape.addVertex( ofVec3f(ex,ey,0) );
		rshape.addIndex( vertIndex++ );
		rshape.addIndex( vertIndex++ );
        
        rshape.addColor( ofFloatColor(1) );
        rshape.addColor( ofFloatColor(1) );
	}
	
    rshape.setUsage( GL_DYNAMIC_DRAW );
    rshape.setMode( OF_PRIMITIVE_POINTS );
}

void dt_circle_param::fire(){
	data.fire_rate = 1.0;
}
