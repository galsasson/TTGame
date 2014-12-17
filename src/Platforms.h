//
//  Platforms.h
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#ifndef __TTGame__Platforms__
#define __TTGame__Platforms__

#include <stdio.h>
#include "ofMain.h"

class Platforms
{
public:

	void setup();

	bool isOneForceOffPlatforms(const vector<ofVec3f>& forces);

	void update(float dt);
	void draw();


private:

	vector<ofRectangle> platforms;


};
#endif /* defined(__TTGame__Platforms__) */
