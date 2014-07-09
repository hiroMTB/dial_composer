//
//  dt_font_manager.h
//  dial_t
//
//  Created by mtb on 5/5/14.
//
//

#pragma once

#include "ofMain.h"

class dt_font_manager{

public:

	dt_font_manager(){
		
		cout << "setting up Font Manager" << endl;
		
		ofTrueTypeFont::setGlobalDpi(72);
		
		string fontName = "fonts/Arial Unicode.ttf";
		
		bool antiAliased =		true;
		bool fullCharacterSet = true;
		bool makeContours =		true;
		//float _simplifyAmt = 0.3 // default
		//int _dpi = 0	// default
		
		font_SS.loadFont(fontName, 6, antiAliased, fullCharacterSet, makeContours);
		font_S.loadFont(fontName, 10, antiAliased, fullCharacterSet, makeContours);
		font_M.loadFont(fontName, 14, antiAliased, fullCharacterSet, makeContours);
		font_L.loadFont(fontName, 18, antiAliased, fullCharacterSet, makeContours);
	};

	ofTrueTypeFont font_SS;
	ofTrueTypeFont font_S;
	ofTrueTypeFont font_M;
	ofTrueTypeFont font_L;
	
//	ofVbo V;
//	ofVbo N;
//	ofVbo L;
//	ofVbo R;
//	ofVbo D;
//	
//	void make_vbo_font(){
//		// V
//		vector<ofVec2f> points;
//		vector<ofFloatColor> colors;
//	};
	
};



