//
//  Mattress.h
//  TTGame
//
//  Created by Gal Sasson on 12/10/14.
//
//

#ifndef __TTGame__Matress__
#define __TTGame__Matress__

#include <stdio.h>
#include "TactonicInput.h"

class Mattress
{
public:

	void setup(TactonicInput *input);

	vector<ofVec3f> getWorldForcePoints();


	void update(float dt);
	void draw();
	void drawDebug();

	void mouseDown(const ofVec2f& p);
	void mouseDragged(const ofVec2f& p);
	void mouseUp(const ofVec2f& p);

private:

	TactonicInput* ttInput;
//	ofRectangle rect;

	void calcMatToWorldMatrix();
	ofMatrix4x4 matToWorld;

	// calibration
	ofVec2f points[4];	// tl, bl, tr, br
	int activePoint;

	
};

#endif /* defined(__TTGame__Mattress__) */
