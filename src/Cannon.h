//
//  Cannon.h
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#ifndef __tacvis__Cannon__
#define __tacvis__Cannon__

#include <stdio.h>
#include "ofMain.h"

class Cannon
{
public:
	void setup();
//	void setup(float x, float y);


	void update(float dt);
	void draw();

private:
	float length;

	vector<ofVec2f> circles;
};


#endif /* defined(__tacvis__Cannon__) */
