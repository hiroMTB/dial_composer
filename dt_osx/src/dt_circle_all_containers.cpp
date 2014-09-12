//
//  dt_circle_all_containers.cpp
//  dialt
//
//  Created by mtb on 30/05/14.
//
//

#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include "dt_circle_param.h"
#include "dt_config.h"

dt_circle_all_containers::dt_circle_all_containers(){
}

void dt_circle_all_containers::setup(){
	
	app = ofApp::getInstance();
	
	// container
	circle_base_container	= new dt_circle_base_container();
	note_on_container		= new dt_circle_note_on_container();
	param_container			= new dt_circle_param_container();
	output_container		= new dt_circle_output_container();

	
    indicators.setUsage( GL_DYNAMIC_DRAW );
    indicators.setMode( OF_PRIMITIVE_POINTS );
    
    connection_lines.setUsage( GL_DYNAMIC_DRAW );
    connection_lines.setMode( OF_PRIMITIVE_LINES );
}

void dt_circle_all_containers::update(){
	circle_base_container->update();
	circle_base_container->process_collision();
}

void dt_circle_all_containers::add_indicator( const ofVec2f& p, const ofFloatColor& c ){
    indicators.addVertex( p );
    indicators.addColor( c );
}

void dt_circle_all_containers::add_connection_line( const ofVec2f& p1, const ofVec2f& p2, const ofFloatColor& c1, const ofFloatColor& c2 ){
    connection_lines.addVertex( p1 );
    connection_lines.addVertex( p2 );
    connection_lines.addColor( c1 );
    connection_lines.addColor( c2 );
}

void dt_circle_all_containers::draw(){
    
	if( param_container->circles.size()<300 )
		param_container->draw();

	if( output_container->circles.size()<100 )
		output_container->draw();
	
	note_on_container->draw();
    
    // all lines
    glLineWidth( 1 );
    connection_lines.draw( OF_MESH_WIREFRAME );
    
    // all points
    glPointSize( 6 );
    indicators.draw( OF_MESH_POINTS );

    indicators.clear();
    connection_lines.clear();
}

void dt_circle_all_containers::step(){
	note_on_container->step();
}

void dt_circle_all_containers::change_speed_random_all( int min, int max ){
	if( min<1 ) min = 1;

	dt_config::DT_BEAT_SPEED_MAX = max;
	app->config.synch_param();
	for( int i=0; i<note_on_container->circles.size(); i++ ){
		int speed = ofRandom( min, max );
		note_on_container->circles[i]->change_speed( speed );
	}
}

void dt_circle_all_containers::change_beat_all( int beat ){
	for( int i=0; i<note_on_container->circles.size(); i++ ){
		dt_circle_note_on * n = note_on_container->circles[ i ];
		n->setup( beat );
	}
}

void dt_circle_all_containers::change_position_all(){
	for( int i=0; i<circle_base_container->circles.size(); i++ ){
		dt_circle_base * b =  circle_base_container->circles[ i ];
		b->data.position.set( ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()) );
		if( ofRandom(1)<0.01 )
			b->fire();
	}
}

void dt_circle_all_containers::change_beat_resolution_all( int res ){
	dt_config::DT_BEAT_RESOLUTION = res;
	app->config.synch_param();
	for( int i=0; i<note_on_container->circles.size(); i++ ){
		dt_circle_note_on * n = note_on_container->circles[ i ];
		int beats = n->seq->total_beats;
		n->setup( beats );
	}
}

void dt_circle_all_containers::change_osc_ch_all(){
	
//	for( int i=0; i<output_container->circles.size(); i++ ){
//		dt_circle_output_base * o = output_container->circles[ i ];
//		int ch = round( ofRandom(1, dt_config::DT_OSC_OUT_CH_MAX) );
//		o->setup_ch( ch );
//	}
}