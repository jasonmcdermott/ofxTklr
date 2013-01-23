#pragma once
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>


class ofxBody{
public:
    
    ofVec3f pos;
    float mass, radius;
    int charge;
    
    ofxBody(ofVec3f loc_, float mass_, int charge_) {
        pos.set(loc_);
        mass = mass_;
        charge = charge_;
        radius = mass/2;
    }
    
    void update() {
        radius = mass/2;
    }
    
    void addMass(float m) {
        mass = mass + m;
    }
    
    void draw() {
//        if (charge < 0) {
//            ofSetColor(10,10,10);
//        } else {
//            ofSetColor(200,200,215);
//        }
        ofSetColor(mass);
        ofSphere(pos.x,pos.y,pos.z,radius);
    }
};




