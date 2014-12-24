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

	void takeBullet();
	void shootBullet();

	bool isShooting() { return bShootingBullet; }

	bool isFootDown();

	void applyForce(const ofVec3f& f);
	ofNode& getCamTarget() { return camTargetNode; }

	void setSpeed(float speed) { forwardSpeed = speed; }

	void update(float dt);
	void draw();


	void setupParams();
private:

	float targetX;

	float getNormalizedX();
	float getXForce();
	
	ofNode camTargetNode;

	ofVec3f acc;
	ofVec3f vel;

	bool bLeftFootDown;
	bool bRightFootDown;
	float forwardSpeed;


	void updateForces();

	// geometry
	void createCarpetGeometry();
	ofVbo carpetVbo;
	void createCarpetTexture();
	void renderCarpetTexture();
	ofFbo carpetFbo;

	
	// params
	void updateParams();
	float balanceSensitivity;
	ofVec3f targetNodePos;

	//
	int life;
	bool bHit;
	float bHitCounter;
	bool bExploding;

	bool bHasBullet;
	bool bShootingBullet;
	float bulletShotCounter;


	TactonicInput* tactonic;



};
#endif /* defined(__TTGame__Carpet__) */
