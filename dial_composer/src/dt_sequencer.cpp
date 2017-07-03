//
//  dt_sequencer.cpp
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#include "ofApp.h"
#include "dt_sequencer.h"
#include "dt_sequence_thread.h"
#include "dt_rhythm_lib.h"
#include "dt_config.h"

dt_sequencer::dt_sequencer()
:
indicator( 0 ),
bCounter_clockwise( true ),
total_beats( -1 ),
rhythm_shape_type( 0 )
{
	app = ofApp::app;
	beat_resolution = dt_config::DT_BEAT_RESOLUTION;
}

void dt_sequencer::setup( float _total_beats ){
	total_beats = _total_beats;
	total_steps = total_beats * beat_resolution;
    indicator = 0;
}

void dt_sequencer::updateIndicator( int steps ){
	int new_ind = indicator + steps;
	indicator = loop_map( new_ind );
}

void dt_sequencer::setRhythmShape( int type ){
	int rsize = app->rhythm_lib.getRhythmSize( total_beats );
	
	if( 0 <= type ){
		rhythm_shape_type = type % rsize;
	}else{
		if( type%rsize == 0 ){
			rhythm_shape_type = 0;
		}else{
			rhythm_shape_type = rsize + type%rsize;
		}
	}
}

void dt_sequencer::incRhythmShape( int n ){
	setRhythmShape( rhythm_shape_type + n );
}

int dt_sequencer::getCurrentBeat(){
	return ( indicator / beat_resolution );
}

bool dt_sequencer::isOnBeat(){
    return indicator%beat_resolution == 0;
}

bool dt_sequencer::getDataFromBeat( int beat ){
	return app->rhythm_lib.getRhythm( (int)total_beats, rhythm_shape_type )[beat];
}

bool dt_sequencer::getDataFromStep( int step ){
    int beat = step % beat_resolution;
    if( beat == 0 )
        return getDataFromBeat( beat );
	
    return false;
}

bool dt_sequencer::getDataNow(){
	if( isOnBeat() )
		return app->rhythm_lib.getRhythm( (int)total_beats, rhythm_shape_type )[((int)indicator/beat_resolution)];

	return false;
}

unsigned int dt_sequencer::loop_map( int i ){
	/*
	 *		mapping int value to 0 ~ total_step range
	 */
	if( i >= total_steps ){
		return i % total_steps;
	}else if( i < 0 ){
		return total_steps + (i%total_steps);
	}else{
		return i;
	}
}