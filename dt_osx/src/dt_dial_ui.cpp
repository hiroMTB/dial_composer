//
//  dt_dial_ui.cpp
//  dialt
//
//  Created by mtb on 5/7/14.
//
//

#include "dt_dial_ui.h"
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_base.h"
#include "dt_font_manager.h"

bool dt_dial_ui::bInitialized	= false;
bool dt_dial_ui::bUseSvg		= false;
const float dt_dial_ui::ui_template_radius = 60.0;

ofxSVG dt_dial_ui::speed_ui_svg;
ofxSVG dt_dial_ui::shape_ui_svg;
ofxSVG dt_dial_ui::mute_ui_svg;

/*
 *
 *	VBO stuff
 *
 */

// speed
vector<ofVec2f> dt_dial_ui::speed_vbo_points;
vector<ofFloatColor> dt_dial_ui::speed_vbo_colors;
ofVbo dt_dial_ui::speed_vbo;

// Shape
vector<ofVec2f> dt_dial_ui::shape_vbo_points;
vector<ofFloatColor> dt_dial_ui::shape_vbo_colors;
ofVbo dt_dial_ui::shape_vbo;

// Param
vector<ofVec2f> dt_dial_ui::param_vbo_points;
vector<ofFloatColor> dt_dial_ui::param_vbo_colors;
ofVbo dt_dial_ui::param_vbo;

// LR
vector<ofVec2f> dt_dial_ui::param_LR_vbo_points;
vector<ofFloatColor> dt_dial_ui::param_LR_vbo_colors;
ofVbo dt_dial_ui::param_LR_vbo;

dt_dial_ui::dt_dial_ui( dt_circle_base * _parent )
:
ui_base_radius( 0 ),
ui_ind_radius( 0 ),
button_radius( 13 ),
parent( _parent ),
mode( DT_DIAL_UI_HOME )
{
	
	bNeedParam = parent->data.circle_type != DT_CIRCLE_NOTE_ON;

	if(bNeedParam){
		num_home_button = 5;
	}else{
		num_home_button = 4;
	}
	
	// static init 
	if(!bInitialized){
		init();
	}
	
	setup();

}

void dt_dial_ui::init(){
	
//	if(bUseSvg){
		speed_ui_svg.load( "ui/speed_ui.svg" );
		shape_ui_svg.load( "ui/shape_ui.svg" );
		mute_ui_svg.load( "ui/mute_ui.svg" );
//	}else{
		// normaly we prefer this
		make_vbo_param();
		make_vbo_param_LR();
		make_vbo_shape();
		make_vbo_speed();
//	}
	
	bInitialized = true;
}

void dt_dial_ui::setup(){}

void dt_dial_ui::make_vbo_speed(){
}

void dt_dial_ui::make_vbo_shape(){
	float start_angle = 0;
	float range_angle = 360;
	float step_angle = range_angle / shape_step_num;
	float angle = 0;
	float rad = 0;
	float disc_width = 15;
	
	for( int i=0; i<=shape_step_num; i++ ){
		angle = start_angle + step_angle*i;
		if( angle>=360 ) angle -= 360;
		
		rad = angle * DEG_TO_RAD;
		
		float w = disc_width;
		shape_vbo_points.push_back( ofVec2f((float)ui_template_radius*cosf(rad),(float)ui_template_radius*sinf(rad)) );
		if( i!=shape_step_num)
			shape_vbo_points.push_back( ofVec2f(((float)ui_template_radius+w)*cosf(rad),((float)ui_template_radius+w)*sinf(rad)) );
		
		ofFloatColor color;
		float gray = 0.8;
		color.set( gray );
		shape_vbo_colors.push_back( color );
		if( i!=shape_step_num )
			shape_vbo_colors.push_back( color );
	}
	
	shape_vbo.setVertexData( &shape_vbo_points[0], shape_vbo_points.size(), GL_DYNAMIC_DRAW );
	shape_vbo.setColorData( &shape_vbo_colors[0], shape_vbo_colors.size(), GL_DYNAMIC_DRAW );
}

void dt_dial_ui::make_vbo_param(){

	float start_angle = 135; //+35;	// 7:30 PM
	float range_angle = 270;
	float step_angle = range_angle / param_step_num;
	float angle = 0;
	float rad = 0;
	
	float disc_width = 15;
	
	for( int i=0; i<=param_step_num; i++ ){
		angle = start_angle + step_angle*i;
		if( angle>=360 ) angle -= 360;
		
		rad = angle * DEG_TO_RAD;
		
		float w = disc_width;
		param_vbo_points.push_back( ofVec2f((float)ui_template_radius*cosf(rad),(float)ui_template_radius*sinf(rad)) );
		if( i != param_step_num )
			param_vbo_points.push_back( ofVec2f(((float)ui_template_radius+w)*cosf(rad),((float)ui_template_radius+w)*sinf(rad)) );

		ofFloatColor color;
		float gray = 0.8;
		color.set( gray );
		param_vbo_colors.push_back( color );
		if(i!=param_step_num)param_vbo_colors.push_back( color );
	}
	
	param_vbo.setVertexData( &param_vbo_points[0], param_vbo_points.size(), GL_DYNAMIC_DRAW );
	param_vbo.setColorData( &param_vbo_colors[0], param_vbo_colors.size(), GL_DYNAMIC_DRAW );
}

void dt_dial_ui::make_vbo_param_LR(){
}

void dt_dial_ui::draw(){
	ui_elem_pos.clear();
	
	float p_radius = parent->data.rev_radius;
	ui_base_radius =  p_radius + 20;
	ui_ind_radius =   p_radius + 25;

	if( ui_base_radius<60 ){
		ui_base_radius = 60;
		ui_ind_radius =  65;
	}

	switch( mode ){
		case DT_DIAL_UI_NONE:	break;
		case DT_DIAL_UI_HOME:	draw_HOME(); break;
		case DT_DIAL_UI_SPEED:	draw_SPEED(); break;
		case DT_DIAL_UI_SHAPE:	draw_SHAPE(); break;
		case DT_DIAL_UI_ROT:	draw_ROT(); break;
		case DT_DIAL_UI_MUTE:	draw_MUTE(); break;
		case DT_DIAL_UI_PRAM:	if( bNeedParam )draw_PARAM(); break;
		default: break;
	}
}

void dt_dial_ui::draw_HOME(){
	
	float p_radius = parent->data.rev_radius;
	float angle = 0;
	float step_angle = 50;
	float start_angle = 195;
	string icon = "0";
//	ofNoFill();
//    glLineWidth( 1 );
//	parent->app->circle_drawer.draw( ui_base_radius, GL_LINES );

	for( int i=0; i<num_home_button; i++ ){
		angle = i*step_angle + start_angle;
		ofPushMatrix();{
			ofRotate( angle, 0, 0, 1 );
			
			ofNoFill();
			ofSetLineWidth( 1 );
			ofSetColor( 100 );
			ofLine( ui_base_radius, 0, ui_ind_radius-2, 0 );
						
			switch( i+1 ){
				case 1: icon = "Speed"; break;
				case 2: icon = "Shape"; break;
				case 3: icon = "Rot"; break;
				case 4: icon = "Mute"; break;
				case 5: if( bNeedParam ){ icon = "Prm"; } break;
				default: icon = "none"; break;
			}
			
			ofPushMatrix();{
				ofTranslate( ui_ind_radius+3, 0 );
				
				GLfloat model[16];
				glGetFloatv( GL_MODELVIEW_MATRIX, model );
				ui_elem_pos.push_back( ofVec2f(model[12], model[13]) );
									  
				ofRotate( 90, 0, 0, 1 );
#ifndef NOT_USE_OF_DRAW_TEXT
				ofTrueTypeFont &font = ofApp::app->font_manager.font_S;
				ofRectangle r = font.getStringBoundingBox( icon, 0, 0 );
				ofSetColor( 50 );
				ofFill();
				font.drawStringAsShapes( icon, -r.width/2, 0 );
#endif
			}ofPopMatrix();
		}ofPopMatrix();
	}
}

void dt_dial_ui::debug_draw_touch_area(){
	ofFill();
	ofSetColor( 200, 0, 0 );
	for( int i=0; i< ui_elem_pos.size(); i++ ){
		ofCircle( ui_elem_pos[i], button_radius );
	}
}

void dt_dial_ui::draw_SPEED(){
	float scale = ui_base_radius / ui_template_radius;
	glPushMatrix();
	glScalef( scale,scale,1 );
	speed_ui_svg.draw();
	glPopMatrix();
}

void dt_dial_ui::draw_SHAPE(){
	
	if(bUseSvg){
		shape_ui_svg.draw();
	}else{
		float scale = ui_base_radius / ui_template_radius;
		
		glLineWidth( 1 );
		glPushMatrix();
		glScalef( scale,scale,1 );
		shape_vbo.bind();
		shape_vbo.draw( GL_LINES, 0, shape_vbo_points.size() );
		shape_vbo.unbind();
		glPopMatrix();
	}
}

void dt_dial_ui::draw_ROT(){
}

void dt_dial_ui::draw_MUTE(){
	float scale = ui_base_radius / ui_template_radius;
	glPushMatrix();
	glScalef( scale,scale,1 );
	
	mute_ui_svg.draw();
	glPopMatrix();
}

void dt_dial_ui::draw_PARAM(){
	float scale = ui_base_radius / ui_template_radius;

	glLineWidth( 1 );
	glPushMatrix();
	glScalef( scale,scale,1 );
	param_vbo.bind();
	param_vbo.draw( GL_LINES, 0, param_vbo_points.size() );
	param_vbo.unbind();
	glPopMatrix();
}

dt_dial_ui_mode dt_dial_ui::touch_test( ofVec2f &t ){

	// Hit ?
	if( parent && parent->data.bShowUI ){
		for( int i=0; i< ui_elem_pos.size(); i++ ){
			float dist = t.distance( ui_elem_pos[i] );
			if( dist <= button_radius ){
				// hit!!
				mode = (dt_dial_ui_mode)i;
				return mode;
				break;
			}
		}
	}

	return DT_DIAL_UI_NONE;
}

void dt_dial_ui::turn_on(){
	// tweemn
}

void dt_dial_ui::turn_off(){
	// tween
}

void dt_dial_ui::change_mode( dt_dial_ui_mode _mode ){
	mode = _mode;
	if( mode == DT_DIAL_UI_NONE )
		parent->data.bShowUI = false;
	else
		parent->data.bShowUI = true;
}