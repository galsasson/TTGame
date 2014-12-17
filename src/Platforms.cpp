//
//  Platforms.cpp
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#include "Platforms.h"

void Platforms::setup()
{
	for (int i=0; i<100; i++)
	{
		float x = ofRandom(0, 0.8);
		float y = ofRandom(0, -100);
		float w = 0.2f;
		float h = ofRandom(0.3, 1);
		platforms.push_back(ofRectangle(x, y, w, h));
	}
}

bool Platforms::isOneForceOffPlatforms(const vector<ofVec3f> &forces)
{
	for (int f=0; f<forces.size(); f++)
	{
		bool onPlatform = false;
		for (int p=0; p<platforms.size(); p++)
		{
			if (platforms[p].inside(forces[f])) {
				onPlatform = true;
				break;
			}
		}

		if (!onPlatform) {
			return true;
		}
	}

	return false;
}


void Platforms::update(float dt)
{
	float speed = 1;
	for (int i=0; i<platforms.size(); i++)
	{
		platforms[i].translateY(speed*dt);
	}
}


void Platforms::draw()
{
	ofSetColor(255);
	ofFill();
	for (int i=0; i<platforms.size(); i++)
	{
		ofRect(platforms[i]);
	}
}

