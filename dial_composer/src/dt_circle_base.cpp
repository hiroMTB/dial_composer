//
//  dt_circle_base.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_sequencer.h"
#include "dt_sequence_thread.h"
#include "dt_config.h"
/*
 *
 *		data
 *
 */
ofFloatColor dt_circle_data::defaultColor = ofFloatColor( 0 );
ofColor dt_circle_base::noteOn_color =		ofColor( 200 );
ofColor dt_circle_base::noteNum_color =	ofColor( 184,  88,  32 );
ofColor dt_circle_base::velocity_color =	ofColor( 247, 106, 129 );
ofColor dt_circle_base::duration_color =	ofColor(  52,  78, 168 );
ofColor dt_circle_base::pan_color =		ofColor(  30, 141,  25 );
ofColor dt_circle_base::cc1_color =		ofColor( 133, 135,  65 );
ofColor dt_circle_base::cc2_color =		ofColor( 160, 163,  79 );
ofColor dt_circle_base::cc3_color =		ofColor( 201, 204,  98 );
ofColor dt_circle_base::cc4_color =		ofColor( 241, 244,  138 );

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
midi_ch( 1 ),
midi_cc_num( 0 ),
rev_speed( 0.0 ),
rev_radius( 20.0 ),
collision_radius( 10.0 ),
input_connection_radius( 0.0 ),
output_connection_radius( 0.0 ),
fire_rate( 0.0 ),
note( 0 ),
vel( 0 ),
dur( 0 ),
pan( 0 ),
position( ofVec2f(-1,-1) ),
name( "default" ),
address( "/1" ),
output_value( (int)ofRandom(0, 127) )
{
}

/*
 *
 *		circle
 *
 */
weak_ptr<dt_circle_base> dt_circle_base::selected_circle;

dt_circle_base::dt_circle_base()
:
wait_step( 0 )
{
    parent.reset();
    app = ofApp::app;
}

dt_circle_base::~dt_circle_base(){
//    for( int i=0; i<input_circles.size(); i++ ){
//        if( input_circles[i] )
//            delete input_circles[i];
//    }
    input_circles.clear();
    
    cout << " base" << endl;
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
	seq->updateIndicator( 1 );
	data.rev_speed = (float)360.0 / (float)seq->total_steps;

	if ( !data.bMute ){
		bool is_on_Beat = seq->isOnBeat();
		
		if( is_on_Beat ){
			if( seq->getDataNow() ){
				data.bFired = true;
				on_process();
			}else{
				data.bFired = false;
			}
		}
	}
}

ofVec2f dt_circle_base::calc_indi_position(){
    int pos = seq->indicator-data.phase_step;
	float deg = 360.0 * (float)pos/seq->total_steps * DEG_TO_RAD;
	ofVec2f indi_pos = data.position + ofVec2f( cos(deg), sin(deg) ) * data.rev_radius;
	return indi_pos;
}

bool dt_circle_base::change_beat( int beat ){

    if( dt_config::DT_RHYTHM_SHAPE_SLOT_MIN<=beat && beat<< dt_config::DT_RHYTHM_SHAPE_SLOT_MAX){
        int shape = seq->rhythm_shape_type;
        seq->setup( beat );
        seq->setRhythmShape( shape );
        data.rev_speed = (float)360.0 / (float)seq->total_steps;
        change_speed( data.speed );
        make_vbo();
        
        circle_drawer.initialize( seq->total_steps / 4 );
        return true;
    }else{
        return false;
    }
}

bool dt_circle_base::change_speed( int speed ){
    data.speed = speed;
}

bool dt_circle_base::change_shape( int shape ){
    seq->setRhythmShape( shape );
    make_vbo();
}

bool dt_circle_base::change_type( dt_circle_type type ){
	data.circle_type = type;
    
    switch ( data.circle_type ) {
		case DT_CIRCLE_NOTE_ON:
        {
            ofFloatColor c;
            c.setHsb( ofRandom( 0.0, 1.0 ), ofRandom(0.6, 0.8), 0.8 );
			change_circle_color( c );
            initial = "T";
			data.address = "/trg";
        }
            break;
        case DT_CIRCLE_NOTE_NUM:
            change_circle_color( noteNum_color );
            initial = "N";
			data.address = "/note";
            data.midi_cc_num = -1;
            break;
        case DT_CIRCLE_VELOCITY:
            change_circle_color( velocity_color );
            initial = "V";
			data.address = "/vel";
            data.midi_cc_num = -1;
            break;
        case DT_CIRCLE_DURATION:
            change_circle_color( duration_color );
            initial = "D";
			data.address = "/dur";
            data.midi_cc_num = -1;
            break;
        case DT_CIRCLE_PAN:
            change_circle_color( pan_color );
            initial = "P";
			data.address = "/pan";
            data.midi_cc_num = 9;
            break;
        case DT_CIRCLE_CC1:
            change_circle_color( cc1_color );
            initial = "CC1";
			data.address = "/cc1";
            data.midi_cc_num = 12;
            break;
        case DT_CIRCLE_CC2:
            change_circle_color( cc2_color );
            initial = "CC2";
			data.address = "/cc2";
            data.midi_cc_num = 13;
            break;
        case DT_CIRCLE_CC3:
            change_circle_color( cc3_color );
            initial = "CC3";
			data.address = "/cc3";
            data.midi_cc_num = 14;
            break;
        case DT_CIRCLE_CC4:
            change_circle_color( cc4_color );
            initial = "CC4";
			data.address = "/cc4";
            data.midi_cc_num = 15;
            break;
            
        default:
            break;
    }
    
    setup_text( initial );
}

bool dt_circle_base::change_circle_color( ofColor & c ){
    change_circle_color( c.r/255.0, c.g/255.0, c.b/255.0, c.a/255.0 );
}

bool dt_circle_base::change_circle_color( ofFloatColor &c ){
    change_circle_color( c.r, c.g, c.b, c.a );
}

bool dt_circle_base::change_circle_color( float r, float g, float b, float a ){
    data.circle_color.set( r, g, b, a );
    make_vbo();
}

bool dt_circle_base::change_rotation( int p_step ){
    int ds = p_step - data.phase_step;
    data.phase_step = p_step;
    seq->indicator += ds;
}

void dt_circle_base::setup_text( string initial ){
	
    font = &app->font_manager.font_M;
    ofRectangle bb = font->getStringBoundingBox( initial, 0,0 );
    float font_w = bb.width;
    float font_h = bb.height;
    float target_w = data.rev_radius;
    float scale = target_w/font_w;
    text_pos.set( -font_w/2-1, font_h/2 );
    text_mesh = font->getStringMesh( initial, -font_w/2-1, font_h/2 );  // this seems just the quad
}

void dt_circle_base::draw_initial(){
/*
 
    // bad text drawing quality
    //
	float scale = 1.0 / app->font_manager.dpi_rate;
    font->getFontTexture().bind();
    ofPushMatrix();
    ofScale( scale, scale );
    text_mesh.draw();
    ofPopMatrix();
    font->getFontTexture().unbind();
 */

    float scale = 1.0 / app->font_manager.dpi_rate;
    ofPushMatrix();
    ofScale( scale, scale );
    ofFill();
    font->drawStringAsShapes( initial, text_pos.x, text_pos.y );
    ofPopMatrix();
}

void dt_circle_base::make_vbo(){
    
    rguid.clear();
    rshape.clear();
    
	int beat_num = seq->total_beats;
	float start_angle = 0;
    float h = data.circle_color.getHue();
    float s = data.circle_color.getSaturation();
    float b = data.circle_color.getBrightness();
    
    int vertIndex = 0;
    
	for( int i=0; i<beat_num; i++ ){
        bool on = seq->getDataFromBeat( i );
        float angle = start_angle + ( i * data.rev_speed * dt_config::DT_BEAT_RESOLUTION );
        float cos = cosf( angle*DEG_TO_RAD );
        float sin = sinf( angle*DEG_TO_RAD );
        float r = 100.0;
        float x = r * cos;
        float y = r * sin;
		if( on ){
            ofFloatColor c = data.circle_color;
            c.setHsb( h + i*0.005, s+ofRandom(-0.01, 0.01), b, c.a);
            rshape.addVertex( ofVec2f(x, y) );
            rshape.addIndex( vertIndex++ );
            rshape.addColor( c );
		}
        
        // guide shape
        rguid.addVertex( ofVec2f(x, y) );
        rguid.addIndex( i );
        if( on ){
            ofFloatColor c = data.circle_color;
            c.a = 1;
            rguid.addColor( c );
        }else{
            rguid.addColor( ofFloatColor(0.7, 0.75) );
        }
	}
    
    // setup Mode and Usage
    if( vertIndex <=2 ){
        rshape.setMode(OF_PRIMITIVE_LINES );
    }else{
        rshape.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
    }
    rguid.setMode( OF_PRIMITIVE_POINTS);
    
    rshape.setUsage( GL_DYNAMIC_DRAW );
    rguid.setUsage( GL_DYNAMIC_DRAW );    
}


#include <cereal/types/polymorphic.hpp>
#include "dt_circle_param.h"

CEREAL_REGISTER_TYPE(dt_circle_note_on);
CEREAL_REGISTER_TYPE(dt_circle_param);
CEREAL_REGISTER_POLYMORPHIC_RELATION(dt_circle_base, dt_circle_param)
CEREAL_REGISTER_POLYMORPHIC_RELATION(dt_circle_base, dt_circle_note_on)
