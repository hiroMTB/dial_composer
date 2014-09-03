//
//  dt_circle_param_base.cpp
//  dialt
//
//  Created by mtb on 5/12/14.
//
//

#include "dt_circle_param.h"
#include "dt_dial_ui.h"
#include "dt_sequence_thread.h"
#include "ofApp.h"
#include "dt_font_manager.h"
#include "dt_circle_drawer.h"

dt_circle_param_base::dt_circle_param_base()
:
param_on( ofRandom(0.2, 0.3) ),
param_off( ofRandom(0.001, 0.1) ),
param_max( 1 ),
param_min( 0 )
{
	initial = "BASE";
}

dt_circle_param_base::~dt_circle_param_base(){
	if( ui ){
	   delete ui;
		ui = 0;
	}
}

void dt_circle_param_base::setup( int beat_num ){
	data.rev_radius = 25;
	data.collision_radius = 20;
	data.bCollide = true;
    setup_text( initial );
}

void dt_circle_param_base::change_rshape( int type ){
	seq->setRhythmShape( type );
	make_vbo();
}

void dt_circle_param_base::update(){
	data.fire_rate *= 0.8;
	
	if( dt_config::DT_PLAY_GEN_RHYTHM ){
		data.position += data.move_speed;
		data.world_position = data.position;
	}
}

void dt_circle_param_base::draw(){
	
	ofPushStyle();
	ofPushMatrix();
	ofTranslate( data.position.x, data.position.y );
		
	bool fired = data.fire_rate>0.5;
	bool selected = selected_circle == this;
	
	// Circle
	ofSetColor( data.circle_color - data.fire_rate*0.2 );
	ofNoFill();
	ofSetLineWidth( 1 );
	glPointSize( 1 );
	app->circle_drawer.draw(data.rev_radius);
	
#ifndef NOT_USE_OF_DRAW_TEXT
	draw_initial();
#endif
	
	draw_vbo();
	
	if( data.bShowUI )
		ui->draw();
	
	ofPopStyle();
	ofPopMatrix();
}

void dt_circle_param_base::draw_vbo(){
	glLineWidth( 1 );
	rshape_vbo.bind();
	rshape_vbo.draw( GL_LINES, 0, rshape_points.size() );
	rshape_vbo.unbind();
}

void dt_circle_param_base::make_vbo(){
	rshape_points.clear();
	
	int beat_num = seq->total_beats;
	int beat_res = dt_config::DT_BEAT_RESOLUTION;
	float start_angle = 0;
	float r = data.rev_radius;
	float lenght = 3;
	
	for( int i=0; i<beat_num; i++ ){
		bool on = seq->getDataFromBeat( i );
		if( !on )
			continue;
		
		float angle = start_angle + ( i*data.rev_speed * beat_res );
		float sx = r * cosf( angle*DEG_TO_RAD );
		float sy = r * sinf( angle*DEG_TO_RAD );
		float ex = ( r+lenght ) * cosf( angle*DEG_TO_RAD );
		float ey = ( r+lenght ) * sinf( angle*DEG_TO_RAD );
			
		rshape_points.push_back( ofVec2f(sx,sy) );
		rshape_points.push_back( ofVec2f(ex,ey) );
	}
	
	rshape_vbo.setVertexData( &rshape_points[0], rshape_points.size(), GL_DYNAMIC_DRAW );
}

void dt_circle_param_base::fire(){
	data.fire_rate = 1.0;
}

ofColor dt_circle_param_base::noteNum_color =	ofColor( 184,  88,  32 );
ofColor dt_circle_param_base::velocity_color =	ofColor( 247, 106, 129 );
ofColor dt_circle_param_base::duration_color =	ofColor(  52,  78, 168 );
ofColor dt_circle_param_base::pan_color =		ofColor(  30, 141,  25 );
ofColor dt_circle_param_base::cc1_color =		ofColor( 133, 135,  65 );
ofColor dt_circle_param_base::cc2_color =		ofColor( 160, 163,  79 );
ofColor dt_circle_param_base::cc3_color =		ofColor( 201, 204,  98 );
ofColor dt_circle_param_base::cc4_color =		ofColor( 241, 244,  138 );
