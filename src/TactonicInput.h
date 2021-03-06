//
//  TactonicInput.h
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#ifndef __tacvis__TactonicInput__
#define __tacvis__TactonicInput__

#include <stdio.h>
#include "ofMain.h"
#include "ofxTactonic.h"

class TactonicInput
{

public:

	bool setup();

	void update();
	void draw();

	vector<ofVec3f> getForcePoints();
	float getMaxForce() { return maxForce; }
	ofVec2f getCenterOfMass() { return centerOfMass; }

	int getNRows() { return nRows; }
	int getNCols() { return nCols; }

	ofEvent<void> eventNewFrame;
	
private:
	bool bHasDevice;
	int nRows;
	int nCols;
	ofxTactonic device;
	TactonicFrame *frame;

	void onTactonicFrame(TactonicFrameEvent& evt);

	float maxForce;
	ofVec2f centerOfMass;

	ofMutex mutex;
	
	void renderFbo(TactonicFrame* frame);
	void allocateFbo();
	ofFbo forceFbo;

};
#endif /* defined(__tacvis__TactonicInput__) */
