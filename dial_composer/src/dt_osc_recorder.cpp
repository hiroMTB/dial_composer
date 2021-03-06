//
//  dt_osc_recorder.cpp
//  dt_
//
//  Created by mtb on 2014/07/13.
//
//

#include "dt_osc_recorder.h"
#include "dt_config.h"
#include "dt_circle_drawer.h"
#include "ofApp.h"

dt_osc_recorder::dt_osc_recorder()
:current_fragment( 0 )
{}

void dt_osc_recorder::setup(){
	
    ofLogNotice( "dt_osc_recoder", "setup" );
    
	app = ofApp::app;
    
	for( int i=0; i<fragment_ring_max; i++ ){
		fragment frag;

		for( int j=0; j<dt_config::DT_OSC_OUT_CH_MAX; j++ ){
			ofxOscMessage m;
			m.clear();
			frag.push_back( m );
		}
		fragment_ring.push_back( frag );
	}
	
    points.setUsage( GL_DYNAMIC_DRAW );
    points.setMode( OF_PRIMITIVE_POINTS );
    
    lines.setUsage( GL_DYNAMIC_DRAW );
    lines.setMode( OF_PRIMITIVE_LINES );
}

void dt_osc_recorder::draw( int _x, int _y, int _w, int _h ){
    
    points.clear();
    lines.clear();
    
	if( !dt_config::DT_SHOW_BUFFERED_RHYTHM )
		return;
	
	float x = 0;
	float y = 0;
	float frag_w = (float)_w / fragment_ring_max;
	float ch_h = (float)_h / dt_config::DT_OSC_OUT_CH_MAX;
	
	//
	//	we should start from current fragment position
	//
	for( int i=0; i<fragment_ring.size(); i++ ){

		x = i * frag_w;
				
		for( int j=0; j<dt_config::DT_OSC_OUT_CH_MAX; j++ ){
			
			if( fragment_ring[i][j].getNumArgs()>0 ){
				int ch = j;
				y = ch * ch_h;
				add_point( ofVec2f(x+_x, y+_y), ofFloatColor(0.4, 0.9, 0.1) );
			}
		}
	}
	
	if( dt_config::DT_PLAY_BUFFERED_RHYTHM ){
		x = dt_config::DT_BUFFERED_RHYTHM_INDICATOR * frag_w;
		y = dt_config::DT_OSC_OUT_CH_MAX * ch_h + 5;
		add_line( ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(1, 0, 0.5), ofFloatColor(1, 0, 0.5) );
		
		// start, dynamic
		x = dt_config::DT_BUFFERED_RHYTHM_LOOP_START * frag_w;
		add_line( ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(0, 0.4, 0.7), ofFloatColor(0, 0.4, 0.7) );
		
		// end, fixed
		x = dt_config::DT_BUFFERED_RHYTHM_LOOP_END * frag_w;
		add_line( ofVec2f(_x+x, _y-10), ofVec2f(_x+x, _y+y), ofFloatColor(0, 0.4, 0.7), ofFloatColor(0, 0.4, 0.7) );
	}
	
	x = current_fragment * frag_w;
	y = ( dt_config::DT_OSC_OUT_CH_MAX-1 ) * ch_h;
	add_line( ofVec2f(_x+x, _y-8), ofVec2f(_x+x, _y-2), ofFloatColor(1), ofFloatColor(1) );
	add_line( ofVec2f(_x+x, _y+y), ofVec2f(_x+x, _y+y+8), ofFloatColor(1), ofFloatColor(1) );

    glLineWidth( 1 );
    lines.draw( OF_MESH_WIREFRAME );

    glPointSize( 2 );
    points.draw( OF_MESH_POINTS );

}

void dt_osc_recorder::add_osc_message( const ofxOscMessage &m, int ch ){

	if( dt_config::DT_PLAY_BUFFERED_RHYTHM!=0 )
		return;
	
	// delete first
	fragment_ring[ current_fragment ][ ch-1 ] = m;
}

void dt_osc_recorder::step_fragment(){

	if( dt_config::DT_PLAY_BUFFERED_RHYTHM )
		return;
	
	if( current_fragment == fragment_ring_max-1 ){
		current_fragment = 0;
	}else{
		current_fragment++;
	}
	
	// clear
	for( int i=0; i<dt_config::DT_OSC_OUT_CH_MAX; i++ ){
		fragment_ring[ current_fragment ][ i ].clear();
	}
}

void dt_osc_recorder::toggle_play_fragment(){
	
	dt_config::DT_PLAY_BUFFERED_RHYTHM = !dt_config::DT_PLAY_BUFFERED_RHYTHM;

	if( dt_config::DT_PLAY_BUFFERED_RHYTHM ){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = dt_config::DT_BUFFERED_RHYTHM_LOOP_START;
	}else{
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
	}
}

void dt_osc_recorder::play_fragment(){

	int rate = dt_config::DT_BUFFERED_RHYTHM_RATE;
	
	for( int i=0; i<dt_config::DT_OSC_OUT_CH_MAX; i++ ){
		if( rate==100 || ofRandom(0, 100) < rate ){
			app->osc_sender.send_message(fragment_ring[ dt_config::DT_BUFFERED_RHYTHM_INDICATOR ][ i ]);
		}
	}
		
	if( dt_config::DT_BUFFERED_RHYTHM_INDICATOR+1 == dt_config::DT_BUFFERED_RHYTHM_LOOP_END ){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = dt_config::DT_BUFFERED_RHYTHM_LOOP_START;
	}else if( dt_config::DT_BUFFERED_RHYTHM_INDICATOR+1 >= fragment_ring_max ){
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR = 0;
	}else{
		dt_config::DT_BUFFERED_RHYTHM_INDICATOR++;
	}
}

void dt_osc_recorder::add_line( ofVec2f p1, ofVec2f p2, ofFloatColor c1, ofFloatColor c2 ){
    lines.addVertex( p1 );
    lines.addVertex( p2 );
    lines.addColor( c1 );
    lines.addColor( c2);
}

void dt_osc_recorder::add_point( ofVec2f p, ofFloatColor c ){
    points.addVertex( p );
    points.addColor( c );
}