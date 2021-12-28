#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	int span = 200;
	for (int x = -span; x <= span; x += span) {

		for (int y = -span; y <= span; y += span) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int len = 50; len < 180; len += 30) {

				auto noise_seed = ofRandom(1000);
				for (int param = 100; param < 200; param += 1) {

					auto location = this->make_point(len, param);
					auto next_location = this->make_point(len, param + 1);

					auto noise_value = ofNoise(glm::vec4(noise_seed, this->make_point(120, param) * 0.0085, ofGetFrameNum() * 0.015));
					auto prev_noise_value = ofNoise(glm::vec4(noise_seed, this->make_point(120, param - 1) * 0.0085, ofGetFrameNum() * 0.015));
					auto next_noise_value = ofNoise(glm::vec4(noise_seed, this->make_point(120, param + 1) * 0.0085, ofGetFrameNum() * 0.015));

					if (noise_value > 0.5) {

						ofSetColor(255);
						ofDrawLine(location, next_location);

						if (prev_noise_value <= 0.5) {

							ofFill();
							ofDrawCircle(location, 4);
						}

						if (next_noise_value <= 0.5) {

							ofFill();
							ofSetColor(0);
							ofDrawCircle(next_location, 4);

							ofNoFill();
							ofSetColor(255);
							ofDrawCircle(next_location, 4);
						}
					}
				}
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}