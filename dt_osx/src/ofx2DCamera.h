//
//  ofx2DCamera.h
//  dial
//
//  Created by hiroshi matoba on 9/9/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTween.h"

class ofx2DCamera{
    
public:
    ofx2DCamera();
    
    void reset();
    void update();
    void begin();
    void end();
    void move( ofVec2f _trans, int time_ms, int delay_ms=0 );
    void zoom( float _zoomRate, int time_ms, int delay_ms=0 );
    void moveZoom( ofVec2f _trans, float _zoomRate, int time_ms, int delay_ms=0);
    
    void startPivot( ofVec2f pivotXY );
    
    void debugDraw();
        
    ofVec2f worldToScreen( ofVec2f worldXY ) const;
	ofVec2f screenToWorld( ofVec2f ccreenXY) const;
    
    float zoomRate;
    float angle;
    ofVec2f pivot;
    ofVec2f trans;
    ofVec2f dragStartPos;
    
    ofxTween transX_tw, transY_tw, zoomRate_tw;
    ofxEasingSine easingsine;
    
    bool bZooming;
};