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

class Cannon : public ofNode
{
public:

	void setup();


	void update(float dt);
	void draw();

private:
	ofVec2f pos;
	float length;
	float angle;
};


#endif /* defined(__tacvis__Cannon__) */
