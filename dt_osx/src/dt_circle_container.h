//
//  dt_circle_container.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "def.h"
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_note_on.h"
#include "dt_circle_base.h"
#include "dt_circle_output_base.h"
#include "dt_circle_all_containers.h"

/*
 *
 *		Container template class for ...
 *
 *		dt_circle_note_on*
 *		dt_circle_param_velocity*
 *		dt_circle_param_noteNum*
 *		dt_circle_param_duration*
 *		dt_circle_param_pan*
 *
 */

template<typename T>
class dt_circle_container{

public:
		
	vector<T> circles;
		
	ofApp * app;
	
	dt_circle_container(){
		//circles.reserve(max_circle_num);
	}
	
	bool addCircle( T c ){
		circles.push_back( c );
		return true;
	}
	
	bool removeCircle( T  c ){
		typename vector<T>::iterator itr = std::find( circles.begin(), circles.end(), c );
		bool find = itr != circles.end();
		if( find ){
			circles.erase( itr );
			return true;
		}else{
			return false;
		}
	}
	
	T getTouchedCircle( const ofVec2f &t ){
		for( int i=0; i<circles.size(); i++ ){
			T c = circles[ i ];
			ofVec2f& pos = c->data.position;
			float dis = pos.distance( t );
			if( dis <= c->data.rev_radius ){
				return c;
			}
		}
		return NULL;
	}
	
	void update(){
		for( int i=0; i<circles.size(); i++ ){
			circles[ i ]->update();
			ofApp::getInstance()->all_containers.add_point_to_all_points( circles[i]->data.world_position, circles[i]->data.circle_color );
		}
	}
	
	void draw(){
		for( int i=0; i<circles.size(); i++ ){
			circles[ i ]->draw();
		}
	}
	
	void step(){
		for( int i=0; i<circles.size(); i++ ){
			circles[ i ]->step();
		}
	};

	void check_connection( dt_circle_note_on * c1, bool bInput ){
		
		int connection_num_input = 0;
		int connection_num_output = 0;

		if( bInput )
			c1->p_state.reset();
		
		for( int i=0; i<circles.size(); i++ ){
			
			if(  bInput && connection_num_input > dt_config::DT_CONNECTION_NUM_INPUT_MAX ) break;
			if( !bInput && connection_num_output > dt_config::DT_CONNECTION_NUM_OUTPUT_MAX ) break;

			T c2 = circles[ i ];
			ofVec2f &p1 = c1->data.position;
			ofVec2f &p2 = c2->data.position;
			float dist = p2.distance( p1 );
			float connection_radius = bInput ? c1->data.input_connection_radius : c1->data.output_connection_radius;
			
			if( dist<connection_radius ){
				if( bInput ){
					connection_num_input++;
					switch( c2->data.circle_type ){
                        case DT_CIRCLE_NOTE_NUM:    c1->p_state.bNote = true; break;
                        case DT_CIRCLE_VELOCITY:    c1->p_state.bVel = true; break;
						case DT_CIRCLE_DURATION:    c1->p_state.bDur = true; break;
						case DT_CIRCLE_PAN:         c1->p_state.bPan = true; break;
						case DT_CIRCLE_CC1:         c1->p_state.bCc1 = true; break;
						case DT_CIRCLE_CC2:         c1->p_state.bCc2 = true; break;
						case DT_CIRCLE_CC3:         c1->p_state.bCc3 = true; break;
						case DT_CIRCLE_CC4:         c1->p_state.bCc4 = true; break;
						default: break;
					}
				}
				
				if( !bInput ) connection_num_output++;
				
				ofVec2f dir = ( p2-p1 ).normalize();	// p1 -> p2
				float r1 = c1->data.collision_radius-5;
				float r2 = c2->data.collision_radius-5;

				ofVec2f connect_p1 = p1 + dir*r1;
				ofVec2f connect_p2 = p2 - dir*r2;
				
				if( bInput )c1->input_circles.push_back( c2 );
				else c1->output_circles.push_back( c2 );
				ofFloatColor line_color = c2->data.line_color;
				line_color.a = 0.4;
				ofApp::getInstance()->all_containers.add_line_to_all_lines( connect_p1, connect_p2, line_color, line_color );
			}
		}
	}

	void process_collision(){
		for( int i=0; i<circles.size(); i++ ){
			T c1 = circles[ i ];
			if( c1->data.bCollide ){
			
				ofVec2f &p1 = c1->data.position;
				float r1 = c1->data.collision_radius;
				
				float quickness = 0.03f;
				float rad_range = 1.0;
				
				for( int j=i+1; j<circles.size(); j++ ){
					T c2 = circles[ j ];
					if( c2->data.bCollide ){
						
						ofVec2f &p2 = c2->data.position;
						float r2 = c2->data.collision_radius;
						
						float dist_x = p2.x - p1.x;
						float dist_y = p2.y - p1.y;
						
						float dist2 = pow( dist_x,2 ) + pow( dist_y, 2 );
						float rad_sum = pow( r1+r2, 2 ) * rad_range;
						bool collide = dist2<rad_sum;
						if( collide ){
							c1->data.position.x -= ( dist_x*quickness );
							c1->data.position.y -= ( dist_y*quickness );
							
							c2->data.position.x += ( dist_x*quickness );
							c2->data.position.y += ( dist_y*quickness );
						}
					}
				}
			}
			
			/*
			 *	against wall
			 */
//			dt_circle_data &d = c1->data;
//			ofRectangle& canvas = ofApp::getInstance()->canvas;
//			float x = d.position.x;
//			float y = d.position.y;
//			float r = d.collision_radius;
//			if( x-r < canvas.x ){
//				d.position.x = r + canvas.x;
//				d.move_speed.x = -d.move_speed.x;
//			}else if( canvas.width + canvas.x < x+r ){
//				d.position.x = canvas.width + canvas.x-r;
//				d.move_speed.x = -d.move_speed.x;
//			}else if( y-r < canvas.y ){
//				d.position.y = r + canvas.y;
//				d.move_speed.y = -d.move_speed.y;
//			}else if( canvas.height + canvas.y < y+r ){
//				d.position.y = canvas.height + canvas.y-r;
//				d.move_speed.y = -d.move_speed.y;
//			}
		}
	}
};


