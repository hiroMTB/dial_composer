#include "dt_circle_container.h"

#include "dt_circle_note_on.h"
#include "dt_circle_output_base.h"
#include "def.h"
#include "ofMain.h"
#include "ofApp.h"
#include "dt_circle_all_containers.h"
#include "dt_mode_manager.h"

dt_circle_container::dt_circle_container(){
    //circles.reserve(max_circle_num);
}

bool  dt_circle_container::addCircle( shared_ptr<dt_circle_base> c ){
    circles.push_back( c );
    return true;
}


bool dt_circle_container::removeCircle( shared_ptr<dt_circle_base> c ){
    typename vector<shared_ptr<dt_circle_base>>::iterator itr = std::find( circles.begin(), circles.end(), c );
    bool find = itr != circles.end();
    if( find ){
        circles.erase( itr );
        return true;
    }else{
        return false;
    }
}

shared_ptr<dt_circle_base> dt_circle_container::getTouchedCircle( const ofVec2f &t ){
    for( int i=0; i<circles.size(); i++ ){
        shared_ptr<dt_circle_base> c = circles[ i ];
        ofVec2f pos = c->data.position;
        
        if( ofApp::app->mode_manager.mode == DT_MODE_HOME ){
            // only pick note_on
            if( c->data.circle_type != DT_CIRCLE_NOTE_ON )
                continue;
            
        }else if(ofApp::app->mode_manager.mode == DT_MODE_ZOOM ){
            shared_ptr<dt_circle_base> target = ofApp::app->mode_manager.zoom_mode_target.lock();
            shared_ptr<dt_circle_base> parent = c->parent.lock();
            if( c != target && parent != target){
                continue;
            }
            
            if( parent ){
                pos += parent->data.position;
            }
        }
        float dis = pos.distance( t );
        if( dis <= c->data.rev_radius ){
            return c;
        }
    }
    return NULL;
}

void dt_circle_container::update(){
    for( int i=0; i<circles.size(); i++ ){
        circles[ i ]->update();
    }
}

void dt_circle_container::draw(){
    for( int i=0; i<circles.size(); i++ ){
        circles[ i ]->draw();
    }
}

void dt_circle_container::step(){
    for( int i=0; i<circles.size(); i++ ){
        circles[ i ]->step();
    }
}

void dt_circle_container::check_connection( dt_circle_note_on * c1, bool bInput ){
    
    int connection_num_input = 0;
    int connection_num_output = 0;
    
    for( int i=0; i<circles.size(); i++ ){
        
        shared_ptr<dt_circle_base> c2 = circles[ i ];
        ofVec2f &p1 = c1->data.position;
        ofVec2f &p2 = c2->data.position;
        float dist = p2.distance( p1 );
        float connection_radius = bInput ? c1->data.input_connection_radius : c1->data.output_connection_radius;
        
        if( dist<connection_radius ){
            
            if( !bInput ) connection_num_output++;
            
            ofVec2f dir = ( p2-p1 ).normalize();	// p1 -> p2
            float r1 = c1->data.collision_radius-5;
            float r2 = c2->data.collision_radius-5;
            
            ofVec2f connect_p1 = p1 + dir*r1;
            ofVec2f connect_p2 = p2 - dir*r2;
            
            if( bInput )c1->input_circles.push_back( c2 );
            else c1->output_circles.push_back( c2 );
            ofFloatColor line_color = c2->data.circle_color;
            line_color.a = 0.4;
            ofApp::app->all_containers.add_connection_line( connect_p1, connect_p2, line_color, line_color );
        }
    }
}

void dt_circle_container::process_collision(){
    for( int i=0; i<circles.size(); i++ ){
        shared_ptr<dt_circle_base> c1 = circles[ i ];
        if( c1->data.bCollide ){
            
            ofVec2f &p1 = c1->data.position;
            float r1 = c1->data.collision_radius;
            
            float quickness = 0.03f;
            float rad_range = 1.0;
            
            for( int j=i+1; j<circles.size(); j++ ){
                shared_ptr<dt_circle_base> c2 = circles[ j ];
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
        //			ofRectangle& canvas = ofApp::app->canvas;
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

