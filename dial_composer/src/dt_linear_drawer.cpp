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

	app = ofApp::app;
}

/*
 *	default
 *	1 beat = 10 pixel
 *
 */
void dt_linear_drawer::draw( int x, int y, int w, int h, float scale ){

    // settomgs
    static float pix_per_beat = 20;
	static float line_height = 30;
    
    static ofFloatColor line_color( 0.6 );
	static ofFloatColor onset_color( 0.9 );
	float pix_per_step = pix_per_beat / dt_config::DT_BEAT_RESOLUTION;
	
	/*
     *      update
     */
	points.clear();
	lines.clear();
	
	vector<shared_ptr<dt_circle_base>> &ns = ofApp::app->all_containers.note_on_container.circles;
	for( int i=0; i<ns.size(); i++ ){

		int speed = ns[i]->data.speed;
		float y_max = h;
		float width = pix_per_beat * (dt_config::DT_RHYTHM_SHAPE_SLOT_MAX+1);
		
		float x = 0;
		float y = i * line_height;
		int col = y / y_max;
		y -= ( y_max * col );
		
		shared_ptr<dt_sequencer> seq = ns[i]->seq;
		int total_beats = seq->total_beats;
		
		// add on beat
		{
			for( int j=0; j<total_beats; j++ ){
				x = pix_per_beat * j;
				x += col * width;
				
				if( seq->getDataFromBeat(j) ){
                    points.addVertex( glm::vec3(x, y, 0) );
					points.addColor( onset_color );
				};
			}
		}
		
		// add line
		{
			// start
			x = col * width;
			lines.addVertex( glm::vec3(x, y, 0) );
			lines.addColor( line_color );

			// end
			x = pix_per_beat * total_beats;
			x += col * width;
			lines.addVertex( glm::vec3(x, y, 0) );
			lines.addColor( line_color );
		}
		
		// add indicator
		{
			x = seq->indicator * pix_per_step;
			x += col * width;
			points.addVertex( glm::vec3(x, y, 0) );
			points.addColor( ofFloatColor(1,0,0) );
		}
	}
    
    points.setUsage( GL_DYNAMIC_DRAW );
    lines.setUsage( GL_DYNAMIC_DRAW );
    points.setMode( OF_PRIMITIVE_POINTS );
    lines.setMode( OF_PRIMITIVE_LINES );
    
    /*
     *      draw
     */
    glPushMatrix();{
        ofSetColor( 30, 30, 40, 70 );
        ofRect( x-10, y-10, w+20, h+20 );

        glTranslatef( x, y, 0 );
        glScalef( scale, scale, 1 );
        glLineWidth( 2 );
        glPointSize( 4 );

        lines.draw( OF_MESH_WIREFRAME );
        points.draw( OF_MESH_WIREFRAME );
    }glPopMatrix();
}
