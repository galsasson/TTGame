//
//  Wall.h
//  TTGame
//
//  Created by Gal Sasson on 12/24/14.
//
//

#ifndef __TTGame__Wall__
#define __TTGame__Wall__

#include <stdio.h>
#include "ofMain.h"
#include "FlyingObjectPiece.h"

class Wall : public ofNode
{
public:

	void setup(float z);

	void explode();

	void update(float dt);
	void draw();

	bool didExplode() { return bExplode; }
	bool isDead() { return (bExplode && explosionCounter<0); }

private:
	ofColor color;

	vector<FlyingObjectPiece*> pieces;

	bool bExplode;
	float explosionCounter;
	
};
#endif /* defined(__TTGame__Wall__) */
