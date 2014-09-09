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
#include "dt_circle_trig.h"
#include "dt_circle_base.h"
#include "dt_circle_output_base.h"
#include "dt_circle_all_containers.h"

/*
 *
 *		Container template class for ...
 *
 *		dt_circle_trig*
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
			dt_circle_data &d = c1->data;
			ofRectangle& canvas = ofApp::getInstance()->canvas;
			float x = d.position.x;
			float y = d.position.y;
			float r = d.collision_radius;
			if( x-r < canvas.x ){
				d.position.x = r + canvas.x;
				d.move_speed.x = -d.move_speed.x;
			}else if( canvas.width + canvas.x < x+r ){
				d.position.x = canvas.width + canvas.x-r;
				d.move_speed.x = -d.move_speed.x;
			}else if( y-r < canvas.y ){
				d.position.y = r + canvas.y;
				d.move_speed.y = -d.move_speed.y;
			}else if( canvas.height + canvas.y < y+r ){
				d.position.y = canvas.height + canvas.y-r;
				d.move_speed.y = -d.move_speed.y;
			}
		}
	}
};


