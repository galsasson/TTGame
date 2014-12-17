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

class FlyingObject : public ofNode
{
public:

	enum Type {
		BARRIER,
		POINT
	} type;

	void setup(float x, float y, float z, Type t);

	void update(float dt);
	void draw();


private:



};

#endif /* defined(__TTGame__FlyingObject__) */
