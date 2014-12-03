//
//  TheGame.cpp
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#include "TheGame.h"

void TheGame::setup()
{

}


void TheGame::renderToFbo()
{
	fbo.begin();
	ofClear(0);

	

	fbo.end();
}

void TheGame::allocateFbo()
{
	fbo.allocate(ofGetWindowWidth(), ofGetWindowHeight());
}