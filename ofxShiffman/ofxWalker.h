#pragma once
#include "ofMain.h"

class ofxWalker{
public:
    
    ofVec3f pos;
    
    ofxWalker() {
        pos.set(ofGetWidth()/2,ofGetHeight()/2);
    }
    
    ofxWalker(ofVec3f pos_) {
        pos.set(pos_);
    }
    
    void step(int page) {
        if (page == 4) {
            int choice = int(ofRandom(4));
            if (choice == 0) {
                pos.x ++;
            } else if (choice == 1) {
                pos.x --;
            } else if (choice == 2) {
                pos.y ++;
            } else if (choice == 3) {
                pos.y --;
            }
        } else if (page == 5) {
            pos.x += int(ofRandom(0,3))-1;
            pos.y += int(ofRandom(0,3))-1;
        }
    }
    
    void display() {
        ofSetColor(255);
        ofCircle(pos.x,pos.y,1,1);
    }
};




