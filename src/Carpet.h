//
//  Carpet.h
//  TTGame
//
//  Created by Gal Sasson on 12/17/14.
//
//

#ifndef __TTGame__Carpet__
#define __TTGame__Carpet__

#include <stdio.h>
#include "ofMain.h"
#include "TactonicInput.h"

class Carpet : public ofNode
{
public:
	enum State {
		WAITING_FOR_USER,
		FLYING
	} state;

	void setup(TactonicInput* tt);

	void hit();
	void explode();
	bool didExplode() { return bExploding; }

	void applyForce(const ofVec3f& f);
	ofNode& getCamTarget() { return camTargetNode; }

	void setSpeed(float speed) { forwardSpeed = speed; }

	void update(float dt);
	void draw();


	void setupParams();
private:
	TactonicInput* tactonic;

	float prevX;

	float getNormalizedX();
	float getXForce();
	
	ofNode camTargetNode;

	ofVec3f acc;
	ofVec3f vel;

	float forwardSpeed;



	// geometry
	void createCarpetGeometry();
	ofVbo carpetVbo;
	void createCarpetTexture();
	void renderCarpetTexture();
	ofFbo carpetFbo;

	
	// params
	void updateParams();
//	ofVec2f points[4];
	ofVec3f targetNodePos;

	//
	int life;
	bool bHit;
	float bHitCounter;
	bool bExploding;

};
#endif /* defined(__TTGame__Carpet__) */
