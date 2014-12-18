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

	void stop();

	void update();
	void draw();

	vector<ofVec3f> getForcePoints();
	float getMaxForce() { userLock.lock(); float val = maxForce; userLock.unlock(); return val;}
	float getTotalForce() { userLock.lock(); float val = totalForce; userLock.unlock(); return val;}
	ofVec2f getCenterOfMass() { userLock.lock(); ofVec2f c = centerOfMass; userLock.unlock(); return c;}

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
	float totalForce;
	ofVec2f centerOfMass;

	ofMutex mutex;
	ofMutex userLock;
	
	void renderFbo(TactonicFrame* frame);
	void allocateFbo();
	ofFbo forceFbo;

};
#endif /* defined(__tacvis__TactonicInput__) */
