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
#include "dt_circle_trig.h"
#include "dt_circle_param.h"
#include "dt_config.h"

dt_circle_all_containers::dt_circle_all_containers(){
}

void dt_circle_all_containers::setup(){
	
	app = ofApp::getInstance();
	
	// container
	circle_base_container	= new dt_circle_base_container();
	note_on_container		= new dt_circle_trig_container();
	param_container			= new dt_circle_param_container();
	output_container		= new dt_circle_output_container();
	
	// all points
	for( int i=0; i<dt_config::DT_CIRCLE_MAX; i++ ){
		all_points_pos.push_back(ofVec2f( -123,-123 ));
		all_points_color.push_back( ofFloatColor(1, 0.3,0.2) );
	}
	all_points_vbo.setVertexData( &all_points_pos[0], all_points_pos.size(), GL_DYNAMIC_DRAW );
	all_points_vbo.setColorData( &all_points_color[0], all_points_color.size(), GL_DYNAMIC_DRAW );
	
	
	// all lines
	for( int i=0; i<dt_config::DT_CIRCLE_MAX*3; i++ ){
		all_lines_pos.push_back( ofVec2f(-123,-123) );
		all_lines_pos.push_back( ofVec2f(-123,-123) );
		all_lines_color.push_back( ofFloatColor(0,1,0) );
		all_lines_color.push_back( ofFloatColor(0,1,0) );
	}
	
	all_lines_vbo.setVertexData( &all_lines_pos[0], all_lines_pos.size(), GL_DYNAMIC_DRAW );
	all_lines_vbo.setColorData( &all_lines_color[0], all_lines_color.size(), GL_DYNAMIC_DRAW );
}

void dt_circle_all_containers::update(){
	
	circle_base_container->update();
	circle_base_container->process_collision();
}

void dt_circle_all_containers::add_point_to_all_points( const ofVec2f& p, const ofFloatColor& c ){
	all_points_pos.push_back( p );
	all_points_color.push_back( c );
}

void dt_circle_all_containers::add_line_to_all_lines( const ofVec2f& p1, const ofVec2f& p2, const ofFloatColor& c1, const ofFloatColor& c2 ){
	all_lines_pos.push_back( p1 );
	all_lines_pos.push_back( p2 );
	all_lines_color.push_back( c1 );
	all_lines_color.push_back( c2 );
}

void dt_circle_all_containers::draw(){
    
	if( param_container->circles.size()<300 )
		param_container->draw();

	if( output_container->circles.size()<100 )
		output_container->draw();
	
	note_on_container->draw();
    
    // all lines
    glLineWidth( 1 );
    all_lines_vbo.bind();
    all_lines_vbo.updateColorData( &all_lines_color[0], all_lines_color.size() );
    all_lines_vbo.updateVertexData( &all_lines_pos[0], all_lines_pos.size() );
    all_lines_vbo.draw( GL_LINES, 0, all_lines_pos.size() );
    all_lines_vbo.unbind();

    // all points
    glPointSize( 6 );
    all_points_vbo.bind();
    all_points_vbo.updateColorData( &all_points_color[0], all_points_color.size() );
    all_points_vbo.updateVertexData( &all_points_pos[0], all_points_pos.size() );
    all_points_vbo.draw( GL_POINTS, 0, all_points_pos.size() );
    all_points_vbo.unbind();
    
    all_points_pos.clear();
	all_points_color.clear();
	all_lines_pos.clear();
	all_lines_color.clear();
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
		note_on_container->circles[i]->set_speed( speed );
	}
}

void dt_circle_all_containers::change_beat_all( int beat ){
	for( int i=0; i<note_on_container->circles.size(); i++ ){
		dt_circle_trig * n = note_on_container->circles[ i ];
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
		dt_circle_trig * n = note_on_container->circles[ i ];
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