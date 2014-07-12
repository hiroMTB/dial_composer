//
//  dt_config.cpp
//  dt_osx
//
//  Created by mtb on 2014/07/12.
//
//

#include "dt_config.h"

// Rhythm
int dt_config::DT_RHYTHM_SHAPE_MIN_SLOT =	  3;
int dt_config::DT_RHYTHM_SHAPE_MAX_SLOT =	 24;
int dt_config::DT_QUANTIZE_RESOLUTION =		 64;
int dt_config::DT_BEAT_RESOLUTION =			 64;

// Circle
int dt_config::DT_MAX_CIRCLE_NUM =		  50000;
int dt_config::DT_CONNECTION_NUM_INPUT_MAX = 16;
int dt_config::DT_CONNECTION_NUM_OUTPUT_MAX = 3;

// OSC
int dt_config::DT_MAX_OSC_CH =				 32;
std::string dt_config::DT_OSC_OUT_ADDRESS_PREFIX = "/dt/";
std::string dt_config::DT_OSC_OUT_ADDRESS = "localhost";
int dt_config::DT_OSC_OUT_PORT =		   9999;

bool dt_config::DT_MOVE_CIRCLE = true;

bool dt_config::DT_MASSIVE_MODE = false;