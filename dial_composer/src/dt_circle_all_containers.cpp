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
	
	app = ofApp::app;
	
	circle_base_container	= shared_ptr<dt_circle_base_container>( new dt_circle_base_container() );
	note_on_container		= make_shared<dt_circle_note_on_container>( new dt_circle_note_on_container());
	param_container			= make_shared<dt_circle_param_container>( new dt_circle_param_container());
	
    indicators.setUsage( GL_DYNAMIC_DRAW );
    indicators.setMode( OF_PRIMITIVE_POINTS );
    
    connection_lines.setUsage( GL_DYNAMIC_DRAW );
    connection_lines.setMode( OF_PRIMITIVE_LINES );
}

void dt_circle_all_containers::update(){
    param_container->update();
	note_on_container->update();
	note_on_container->process_collision();
}

void dt_circle_all_containers::draw(){
	
    param_container->draw();
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
    param_container->step();
	note_on_container->step();
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
