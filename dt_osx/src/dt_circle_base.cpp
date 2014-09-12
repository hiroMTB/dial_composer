//
//  dt_circle_base.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_circle_base.h"
#include "dt_sequencer.h"
#include "ofApp.h"
#include "dt_sequence_thread.h"

/*
 *
 *		data
 *
 */
ofFloatColor dt_circle_data::defaultColor = ofFloatColor( 0 );

dt_circle_data::dt_circle_data()
:
bStop( false ),
bMute( false ),
bFired( false ),
bCollide( true ),
bShowUI( false ),
bShow( true ),
phase_step( 0 ),
fired_ch( -1 ),
step_age( 0 ),
speed( 1 ),
rev_angle( 0.0 ),
rev_speed( 0.0 ),
rev_radius( 20.0 ),
collision_radius( 10.0 ),
input_connection_radius( 0.0 ),
output_connection_radius( 0.0 ),
fire_rate( 0.0 ),
position( ofVec2f(-1,-1) ),
name( "def" )
{
}

/*
 *
 *		circle
 *
 */
dt_circle_base * dt_circle_base::selected_circle = NULL;

dt_circle_base::dt_circle_base(){
	app = ofApp::getInstance();
}

void dt_circle_base::step(){
	
	if( wait_step > 0 ){
		wait_step--;
		return;
	}
	
	if( app->sequence_thread.master_step % data.speed == 0 ){
		if( data.bStop )
			return;
		
		check_sequencer();
	}
}

void dt_circle_base::check_sequencer(){
	seq->updateIndicator();	
	data.rev_speed = (float)360.0 / (float)seq->total_steps;
	data.rev_angle = seq->indicator * data.rev_speed;

	if ( !data.bMute ){
		bool is_on_Beat = seq->isOnBeat();
		
		if( is_on_Beat ){
			if( seq->getDataNow() ){
				data.bFired = true;
				fire();
			}else{
				data.bFired = false;
			}
		}
	}
}

ofVec2f dt_circle_base::calc_indi_position(){
	float deg = 360.0 * seq->indicator/seq->total_steps * DEG_TO_RAD;
	ofVec2f indi_pos = data.position + ofVec2f( cos(deg), sin(deg) ) * data.rev_radius;
	return indi_pos;
}

void dt_circle_base::change_beat( int beat ){
	int shape = seq->rhythm_shape_type;
	seq->setup( beat );
    seq->setRhythmShape( shape );
	data.rev_speed = (float)360.0 / (float)seq->total_steps;
	change_speed( data.speed );
    make_vbo();
}

void dt_circle_base::change_speed( int speed ){
    data.speed = speed;
   	data.rev_angle = seq->indicator * data.rev_speed;
}

void dt_circle_base::change_shape( int shape ){
    seq->setRhythmShape( shape );
    make_vbo();
}

void dt_circle_base::change_circle_color( float r, float g, float b, float a ){
    data.circle_color.set( r, g, b, a );
    make_vbo();
}

void dt_circle_base::setup_text( string initial ){
	
    if( data.rev_radius<15 ){
        font = &app->font_manager.font_S;
    }else{
        font = &app->font_manager.font_M;
    }
	
    ofRectangle bb = font->getStringBoundingBox( initial, 0,0 );
    float font_w = bb.width;
    float font_h = bb.height;
    float target_w = data.rev_radius;
    float scale = target_w/font_w;
    
    text_mesh = font->getStringMesh( initial, -font_w/2-1, font_h/2 );
}

void dt_circle_base::draw_initial(){
	font->getFontTexture().bind();
    text_mesh.draw();
    font->getFontTexture().unbind();
}
