//
//  dt_preset.hpp
//  dt_osx
//
//  Created by mtb on 2014/07/12.
//
//

#pragma once

#include <string>

class dt_config{

public:
	
	// Rhythm
	static int DT_RHYTHM_SHAPE_MIN_SLOT;
	static int DT_RHYTHM_SHAPE_MAX_SLOT;
	static int DT_QUANTIZE_RESOLUTION;
	static int DT_BEAT_RESOLUTION;		// hwo many steps per 1 beat

	// Circle
	static int DT_MAX_CIRCLE_NUM;
	static int DT_CONNECTION_NUM_INPUT_MAX;
	static int DT_CONNECTION_NUM_OUTPUT_MAX;

	// OSC
	static int DT_MAX_OSC_CH;
	static std::string DT_OSC_OUT_ADDRESS_PREFIX;
	static std::string DT_OSC_OUT_ADDRESS;
	static int DT_OSC_OUT_PORT;

	static bool DT_MOVE_CIRCLE;

	static bool DT_MASSIVE_MODE;
};