//
//  Wall.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/24/14.
//
//

#include "Wall.h"


void Wall::setup(float z)
{
	setPosition(0, 0, z);

	explosionCounter = 0;

	color = ofColor(100, 100, 255);

	for (int y=0; y<100; y+=20)
	{
		for (int x=-1000; x<1000; x+=40)
		{
			FlyingObjectPiece* fop = new FlyingObjectPiece();
			fop->setup(x, y, 0, color);
			fop->setVelocity(ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(10, 50)));
			fop->setSize(ofVec3f(40, 20, 1));
			pieces.push_back(fop);
		}
	}
}

void Wall::explode()
{
	bExplode = true;
	explosionCounter = 0.5f;
}

void Wall::update(float dt)
{
	if (bExplode) {
		explosionCounter -= dt;
		for (int i=0; i<pieces.size(); i++)
		{
			pieces[i]->update(dt);
		}
	}

}

void Wall::draw()
{
	ofPushMatrix();
	ofMultMatrix(getLocalTransformMatrix());


	if (bExplode) {
		for (int i=0; i<pieces.size(); i++)
		{
			pieces[i]->draw();
		}
	}
	else {
		ofFill();
		ofSetColor(color);
		ofDrawBox(0, 50, 0, 2000, 100, 30);
	}


	ofPopMatrix();
}