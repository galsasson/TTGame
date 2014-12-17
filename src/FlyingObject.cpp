//
//  FlyingObject.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "FlyingObject.h"

#define BOX_SIZE 40

void FlyingObject::setup(float x, float y, float z,FlyingObject::Type t)
{
	setPosition(x, y, z);
	type = t;
}

void FlyingObject::update(float dt)
{
	rotate(90*dt, ofVec3f(0, 1, 0));
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

	ofDrawBox(0, 0, 0, BOX_SIZE, BOX_SIZE, BOX_SIZE);

	ofPopMatrix();
}



