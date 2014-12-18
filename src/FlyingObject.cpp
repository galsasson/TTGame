//
//  FlyingObject.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "FlyingObject.h"

#define BOX_SIZE 70

void FlyingObject::setup(float x, float y, float z,FlyingObject::Type t)
{
	setPosition(x, y, z);
	type = t;
	bAlive = true;
	bExploding = false;

	// create pieces
	for (float z=-BOX_SIZE/2; z<BOX_SIZE/2; z+=BOX_SIZE/8)
	{
		for (float y=-BOX_SIZE/2; y<BOX_SIZE/2; y+=BOX_SIZE/8)
		{
			for (float x=-BOX_SIZE/2; x<BOX_SIZE/2; x+=BOX_SIZE/8)
			{
				FlyingObjectPiece* fop = new FlyingObjectPiece();
				fop->setup(x, y, z, ofColor(0, 200, 0));
				pieces.push_back(fop);
			}
		}
	}
}

void FlyingObject::explode()
{
	bExploding = true;
	explodeCounter = 3;
}

void FlyingObject::update(float dt)
{
	rotate(90*dt, ofVec3f(0, 1, 0));

	if (bExploding) {
		for (int i=0; i<pieces.size(); i++) {
			pieces[i]->update(dt);
		}

		explodeCounter -= dt;
		if (explodeCounter < 0) {
			bAlive = false;
		}
	}
}

void FlyingObject::draw()
{
	ofPushMatrix();
	ofMultMatrix(getLocalTransformMatrix());

	ofFill();

	switch (type) {
		case BARRIER:
			ofSetColor(200, 0, 0);
			break;
		case POINT:
			ofSetColor(0, 200, 0);
			break;
	}

	if (bExploding) {
		for (int i=0; i<pieces.size(); i++)
		{
			pieces[i]->draw();
		}
	}
	else {
		ofDrawBox(0, 0, 0, BOX_SIZE, BOX_SIZE, BOX_SIZE);
	}

	ofPopMatrix();
}



