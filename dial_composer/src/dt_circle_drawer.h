//
//  dt_circle_drawer.h
//  dialt_osx
//
//  Created by mtb on 2014/06/20.
//
//

#pragma once

#include "ofMain.h"

class dt_circle_drawer{
	
public:
	
	/*
	 *
	 *	Circle
	 *	radius=1.0, diameter=2.0
	 *
	 */
	dt_circle_drawer(){
        clear();
    }

	~dt_circle_drawer(){
		clear();
	}

    void clear(){
        circle_p.clear();
        circle_l.clear();
        circle_f.clear();
        
        circle_p.setMode( OF_PRIMITIVE_POINTS );
        circle_l.setMode( OF_PRIMITIVE_LINE_LOOP );
        circle_f.setMode( OF_PRIMITIVE_TRIANGLE_FAN );
    }
    
	void initialize( int _resolution ){
		resolution = _resolution;
		clear();
		
		double step_radian = TWO_PI / (double)resolution;
		double radian = 0;
		
		for( int i=0; i<resolution; i++ ){
			radian = (double)i * step_radian;
			float x = cos( radian );
			float y = sin( radian );
            circle_p.addVertex( glm::vec3(x, y, 0) );
            circle_p.addIndex( i );
            
            circle_l.addVertex( glm::vec3(x, y, 0) );
            circle_l.addIndex( i );
            
            circle_f.addVertex( glm::vec3(x, y, 0) );
            circle_f.addIndex( i );
		}
        
        bInitialized = true;
	};
	
	void draw( float radius, ofPolyRenderMode renderMode=OF_MESH_POINTS ){
		glPushMatrix();
		glScalef( radius, radius, 1 );
        switch( renderMode ){
            case OF_MESH_POINTS:
                circle_p.draw( renderMode );
                break;
            case OF_MESH_WIREFRAME:
                circle_l.draw( renderMode );
                break;
            case OF_MESH_FILL:
                circle_f.draw( renderMode );
                break;
            default:
                break;
        }
		glPopMatrix();
	}
	
    bool bInitialized;
	int resolution;
	ofVboMesh circle_p;
	ofVboMesh circle_l;
	ofVboMesh circle_f;
};