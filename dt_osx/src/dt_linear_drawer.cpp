//
//  dt_linear_drawer.cpp
//  dialt_osx
//
//  Created by mtb on 2014/06/28.
//
//

#include "dt_linear_drawer.h"
#include "def.h"
#include "ofApp.h"
#include "dt_circle_all_containers.h"
#include "dt_circle_container.h"
#include "dt_circle_note_on.h"
#include "dt_sequencer.h"

dt_linear_drawer::dt_linear_drawer(){

	app = ofApp::getInstance();
	
	for(int i=0; i<10000; i++){

		// for indicators
		points.push_back(ofVec2f(-1,-1));
		colors_p.push_back(ofFloatColor(0,0,0));

		// for onset beat
		for(int j=0; j<DT_RHYTHM_SHAPE_MAX_SLOT; j++){
			points.push_back(ofVec2f(-1,-1));
			colors_p.push_back(ofFloatColor(0,0,0));
		}
		
		// for timeline
		lines.push_back(ofVec2f(-1,-1));
		lines.push_back(ofVec2f(-1,-1));
		colors_l.push_back(ofFloatColor(0,0,0));
   		colors_l.push_back(ofFloatColor(0,0,0));
	}
	
	point_vbo.setColorData(&colors_p[0], colors_p.size(), GL_DYNAMIC_DRAW);
	point_vbo.setVertexData(&points[0], points.size(), GL_DYNAMIC_DRAW);
	
	line_vbo.setColorData(&colors_l[0], colors_l.size(), GL_DYNAMIC_DRAW);
	line_vbo.setVertexData(&lines[0], lines.size(), GL_DYNAMIC_DRAW);
}

/*
 *	default
 *	1 beat = 10 pixel
 *
 */
void dt_linear_drawer::draw(int x, int y, int w, int h, float scale){
	
    ofEnableAlphaBlending();
	ofSetColor(30, 30, 40, 70);
	ofRect(x-10, y-10, w+20, h+20);
    ofDisableAlphaBlending();
	
	// clear
	points.clear();
	colors_p.clear();
	lines.clear();
	colors_l.clear();

	ofFloatColor line_color(0.6);
	ofFloatColor onset_color(0.9);
	
	float pix_per_beat = 8;
	float pix_per_step = pix_per_beat / DT_BEAT_RESOLUTION;
	float line_height = 10;
	
	// update data
	vector<dt_circle_note_on*> &ns = ofApp::getInstance()->all_containers.note_on_container->circles;
	for(int i=0; i<ns.size(); i++){

		int speed = ns[i]->data.speed;
		float y_max = h;
		float width = pix_per_beat * (DT_RHYTHM_SHAPE_MAX_SLOT+1);
		
		float x = 0;
		float y = i * line_height;
		int col = y / y_max;
		y -= (y_max * col);
		
		dt_sequencer * seq = ns[i]->seq;
		int total_beats = seq->total_beats;
		
		// add on beat
		{
			for(int j=0; j<total_beats; j++){
				x = pix_per_beat * j;
				x += col * width;
				
				if(seq->getDataFromBeat(j)){
					points.push_back(ofVec2f(x, y));
					colors_p.push_back(onset_color);
				};
			}
		}
		
		// add line
		{
			// start
			x = col * width;
			lines.push_back(ofVec2f(x, y));
			colors_l.push_back(line_color);

			// end
			x = pix_per_beat * total_beats;
			x += col * width;
			lines.push_back(ofVec2f(x, y));
			colors_l.push_back(line_color);
		}
		
		// add indicator
		{
			x = seq->indicator * pix_per_step;
			x += col * width;

			points.push_back(ofVec2f(x, y));
			colors_p.push_back(ofFloatColor(1,0,0));
		}
	}
		
	glLineWidth(1);
	glPointSize(2);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(scale, scale, 1);

	line_vbo.bind();
	line_vbo.updateColorData(&colors_l[0], colors_l.size());
	line_vbo.updateVertexData(&lines[0], lines.size());
	line_vbo.draw(GL_LINES, 0, lines.size());
	line_vbo.unbind();
	
	point_vbo.bind();
	point_vbo.updateColorData(&colors_p[0], colors_p.size());
	point_vbo.updateVertexData(&points[0], points.size());
	point_vbo.draw(GL_POINTS, 0, points.size());
	point_vbo.unbind();
	glPopMatrix();

}