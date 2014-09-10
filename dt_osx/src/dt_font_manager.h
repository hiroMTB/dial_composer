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

    ofTrueTypeFont font_SS;
	ofTrueTypeFont font_S;
	ofTrueTypeFont font_M;
	ofTrueTypeFont font_L;
    
	dt_font_manager(){
		string fontName = "fonts/Arial Unicode.ttf";
		ofLogNotice( "dt_font_manager", "setup " + fontName );
		
		ofTrueTypeFont::setGlobalDpi( 72 );
		bool antiAliased =		true;
		bool fullCharacterSet = true;
		bool makeContours =		true;
		font_SS.loadFont( fontName, 6, antiAliased, fullCharacterSet, makeContours );
		font_S.loadFont( fontName, 10, antiAliased, fullCharacterSet, makeContours );
		font_M.loadFont( fontName, 14, antiAliased, fullCharacterSet, makeContours );
		font_L.loadFont( fontName, 18, antiAliased, fullCharacterSet, makeContours );
    }
};



