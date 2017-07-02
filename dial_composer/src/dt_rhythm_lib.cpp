//
//  dt_rhythm_lib.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "dt_rhythm_lib.h"
#include "dt_config.h"


dt_rhythm_lib::dt_rhythm_lib(){
	shapes.resize( dt_config::DT_RHYTHM_SHAPE_SLOT_MAX+1 );
}

dt_rhythm_lib::~dt_rhythm_lib(){
    shapes.clear();
}

int dt_rhythm_lib::getRhythmSize( int slotNum ){
    if( 0<= slotNum && slotNum < shapes.size() )
        return shapes[slotNum].size();
    else
        return -1;
}

const RHYTHM_SHAPE& dt_rhythm_lib::getRhythm( int slotNum, int type ){
    return shapes[slotNum][type];
}

void dt_rhythm_lib::setup( int start_slot, int end_slot ){

	/*
	 *		parallel laod :	 10 /   30 msec	(release/debug)
	 *		serial laod :	620 / 3400 msec	(release/debug)
	 */

	double start = ofGetElapsedTimeMillis();
#define PRALELL_LOAD 1
#ifdef PRALELL_LOAD
	setup_parallel( start_slot, end_slot );
#else
	setup_serial( start_slot, end_slot );
#endif
	
	cout << "loading time: " << ofGetElapsedTimeMillis() - start << endl;
}

void dt_rhythm_lib::setup_serial( int start_slot, int end_slot ){
	for(int i=start_slot; i<=end_slot; i++ ){
		load_rhythm( i );
	}
}

void dt_rhythm_lib::setup_parallel( int start_slot, int end_slot ){
    vector<std::thread> ths;
    for(int i=start_slot; i<=end_slot; i++ ){
        ths.push_back( std::thread(&dt_rhythm_lib::load_rhythm, this, i) );
	}
    
    for(std::thread&t : ths){
        t.join();
    }
}

void dt_rhythm_lib::load_rhythm( int slot ){
	char c[255];
	sprintf(c, "%03d", slot );
	string fileName = string( c ) + ".rhythmShape";
	string path = "rhythmShape/" + fileName;
	ifstream file( ofToDataPath(path).c_str() );
//	ofLogNotice( "loading " + ofToDataPath(path) );
	
	SLOT_SHAPE ss;
		
	int line_num = 0;
	while( file.good() ){
			
		string binst;
		getline( file, binst, '\n' );
			
		//if( line_num++<=1 )
		//	continue;	// avoid to load 0000 or 1000
		
		if( binst!="" ){
			RHYTHM_SHAPE s;
			for( int b=0; b<binst.size(); b++ ){
				bool bin = 0;
				char c = binst[ b ];
				if( c == '1' ){
					bin = 1;
				}
				
				s.push_back( bin );
			}
			
			ss.push_back( s );
		}
	}
	shapes[slot] = ( ss );
}

void dt_rhythm_lib::check_data(){
	for( int i=0; i<shapes.size(); i++ ){
		SLOT_SHAPE ss = shapes[i];
		for( int j=0; j<ss.size(); j++ ){
			cout << ofToString( ss[j] ) << endl;
		}
	}
}
