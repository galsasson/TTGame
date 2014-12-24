//
//  FlyingObject.h
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#ifndef __TTGame__FlyingObject__
#define __TTGame__FlyingObject__

#include <stdio.h>
#include "ofMain.h"
#include "FlyingObjectPiece.h"

class FlyingObject : public ofNode
{
public:

	enum Type {
		BARRIER,
		POINT,
		BULLET
	} type;

	void setup(float x, float y, float z, Type t);

	void explode();

	void update(float dt);
	void draw();

	bool isAlive() { return bAlive; }
	bool isExploding() { return bExploding; }

private:

	ofColor color;
	ofColor getColor();
	
	bool bAlive;

	bool bExploding;
	float explodeCounter;

	vector<FlyingObjectPiece*> pieces;

};

#endif /* defined(__TTGame__FlyingObject__) */
