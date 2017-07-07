//
//  dt_circle_container.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once
#include "ofMain.h"
#include "dt_circle_base.h"
#include "dt_circle_note_on.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

class ofApp;

class dt_circle_container{

public:
		
    ofApp * app;
    vector<shared_ptr<dt_circle_base>> circles;
	
    dt_circle_container();
    bool addCircle( shared_ptr<dt_circle_base> c );
    bool removeCircle( shared_ptr<dt_circle_base> c );
    shared_ptr<dt_circle_base> getTouchedCircle( const ofVec2f &t );
    void update();
    void draw();
    void step();
    void check_connection( dt_circle_note_on * c1, bool bInput );
    void process_collision();

public:
    template<class Archive>
    void serialize( Archive & ar){
        ar(CEREAL_NVP(circles));
    }

};
