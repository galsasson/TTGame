//
//  TactonicInput.cpp
//  tacvis
//
//  Created by Gal Sasson on 11/19/14.
//
//

#include "TactonicInput.h"

bool TactonicInput::setup()
{
	device = new ofxTactonic();

	device->init();
	if (device->getWidth() <= 0) {
		bHasDevice = false;
		nRows = -1;
		nCols = -1;
		return false;
	}

	device->createFrame(&frame);
	ofAddListener(ofxTactonic::eventNewFrame, this, &TactonicInput::onTactonicFrame);

	nCols = device->getWidth();
	nRows = device->getHeight();

	cout<<"Tactonic Input: "<<nCols<<"x"<<nRows<<endl;

//	allocateFbo();

	maxForce = 0;
	centerOfMass = ofVec2f();
	bHasDevice = true;

	device->start();

	return true;
}

void TactonicInput::stop()
{
	ofRemoveListener(ofxTactonic::eventNewFrame, this, &TactonicInput::onTactonicFrame);
	device->stop();
}

vector<ofVec3f> TactonicInput::getForcePoints()
{
	vector<ofVec3f> forces;

	for (int y=0; y<frame->rows; y++) {
		for (int x=0; x<frame->cols; x++) {
			float force = frame->forces[y*frame->cols + x];

			if (force > 0) {
				forces.push_back(ofVec3f(x, y, force));
			}
		}
	}

	return forces;
}

void TactonicInput::update()
{
	if (!bHasDevice) {
		return;
	}

//	renderFbo(frame);
}

void TactonicInput::draw()
{
	if (!bHasDevice) {
		return;
	}

//	forceFbo.draw(0, 0);
}

void TactonicInput::onTactonicFrame(TactonicFrameEvent &evt)
{
	mutex.lock();
	device->copyFrame(evt.frame, frame);
	mutex.unlock();

	userLock.lock();
	float max = 0;
	totalForce = 0;
	centerOfMass.set(0, 0);

	for (int y=0; y<frame->rows; y++) {
		for (int x=0; x<frame->cols; x++) {
			float force = frame->forces[y*frame->cols + x];

			// max
			if (force > max) {
				max = force;
			}

			// center of mass
			totalForce += force;
			centerOfMass += ofVec2f(x, y)*force;
		}
	}

	maxForce = max;
	centerOfMass /= totalForce;
	
	userLock.unlock();

	ofNotifyEvent(eventNewFrame);
}

#if 0
void TactonicInput::renderFbo(TactonicFrame* frame)
{
	mutex.lock();

	ofFloatPixels pixels;
	pixels.allocate(frame->cols, frame->rows, 1);

	for (int y=0; y<frame->rows; y++) {
		for (int x=0; x<frame->cols; x++) {
			pixels.setColor(x, y, (float)frame->forces[y*frame->cols + x] / 3900);
		}
	}

	forceFbo.getTextureReference().loadData(pixels);

	mutex.unlock();
}


void TactonicInput::allocateFbo()
{
	forceFbo.allocate(device->getWidth(), device->getHeight());
}
#endif