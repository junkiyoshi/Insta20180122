#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
	for (ofxBulletBox* tmp : this->boxes) {
		delete tmp;
	}
	this->boxes.clear();
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofEnableDepthTest();
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->world.setup();
	this->world.setGravity(ofVec3f(0.0, 64.0, 0));

	this->light.setPosition(ofVec3f(0, 0, 512));
	ofEnableLighting();
	this->light.enable();

	this->img.loadImage("he.jpg");
	this->pixels = this->img.getPixelsRef();
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = 0; i < 10; i++) {
		ofxBulletBox* box = new ofxBulletBox();
		float size = ofRandom(5, 15);
		box->create(this->world.world, ofVec3f(ofRandom(-256, 256), -300, 0), 1.0, size, size, size);
		box->setRestitution(0.5);
		box->add();

		this->boxes.push_back(box);
	}

	this->world.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();
	ofRotateX(180);
	
	
	this->light.setPosition(this->cam.getPosition());

	for (int i = this->boxes.size() - 1; i >= 0; i--) {
		
		if (this->boxes[i]->getPosition().y > ofGetHeight() / 2) {
			delete this->boxes[i];
			this->boxes.erase(this->boxes.begin() + i);
			continue;
		}

		int x = this->boxes[i]->getPosition().x + 256;
		int y = this->boxes[i]->getPosition().y + 256;

		if (x >= 0 && x < 512 && y >= 0 && y < 512) {
			ofSetColor(this->pixels.getColor(x, y));
			this->boxes[i]->draw();
		}

	}

	this->cam.end();
}

//========================================================================
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}