//
//  TheGame.h
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#ifndef __tacvis__TheGame__
#define __tacvis__TheGame__

#include <stdio.h>
#include "ofMain.h"

class TheGame
{
public:

	void setup();

	void update(float dt);
	void draw();

private:
	

	void renderToFbo();
	void allocateFbo();
	ofFbo fbo;
};
#endif /* defined(__tacvis__TheGame__) */
