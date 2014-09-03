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
	
	int resolution;
	ofVbo vbo;
	vector<ofVec2f> points;
	
	/*
	 *
	 *	Circle
	 *	radius=1.0, diameter=2.0
	 *
	 */
	dt_circle_drawer(){
		setup(60);
	}
	
	void setup(int _resolution){
		resolution = _resolution;
		points.clear();
		vbo.clear();
		
		double step_radian = TWO_PI / (double)resolution;
		double radian = 0;
		
		for(int i=0; i<resolution; i++){
			radian = (double)i * step_radian;
			float x = cos(radian);
			float y = sin(radian);
			points.push_back(ofVec2f(x, y));
		}
		
		vbo.setVertexData(&points[0], points.size(), GL_DYNAMIC_DRAW);
	};
	
	
	~dt_circle_drawer(){
		points.clear();
		vbo.clear();
	}

public:
	void draw(float radius, int draw_mode=GL_POINTS){
		glPushMatrix();
		glScalef(radius, radius, 1);
		vbo.bind();
		vbo.draw(draw_mode, 0, points.size());
		vbo.unbind();
		glPopMatrix();
	}

};