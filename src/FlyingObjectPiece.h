//
//  FlyingObjectPiece.h
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#ifndef __TTGame__FlyingObjectPiece__
#define __TTGame__FlyingObjectPiece__

#include <stdio.h>
#include "ofMain.h"

class FlyingObjectPiece : public ofNode
{

public:

	void setup(float x, float y, float z, ofColor c);

	void update(float dt);
	void draw();

private:
	ofColor color;

	ofVec3f flyRotation;
	ofVec3f velocity;
};

#endif /* defined(__TTGame__FlyingObjectPiece__) */
