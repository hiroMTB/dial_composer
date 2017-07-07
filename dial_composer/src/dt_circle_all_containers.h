//
//  dt_circle_all_containers.h
//  dialt
//
//  Created by mtb on 30/05/14.
//
//

#pragma once

#include "ofMain.h"

#include "dt_circle_container.h"

class ofApp;

class dt_circle_all_containers{

public:
	dt_circle_all_containers();
	~dt_circle_all_containers(){};
	
	void setup();
	void update();
	void draw();
	void step();
	void add_indicator( const  ofVec2f& p, const ofFloatColor &c );
	void add_connection_line( const ofVec2f &p1, const ofVec2f &p2, const ofFloatColor &c1, const ofFloatColor &c2 );
	ofApp * app;
	dt_circle_container circle_base_container;
	dt_circle_container note_on_container;
	dt_circle_container param_container;
	ofVboMesh indicators;
	ofVboMesh connection_lines;
    
public:
    template<class Archive>
    void serialize( Archive & ar){
        ar( CEREAL_NVP(note_on_container)
//            CEREAL_NVP(param_container)
        );
    }

};
