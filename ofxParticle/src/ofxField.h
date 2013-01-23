#pragma once
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>


class ofxField{
public:
    
    int res;
    float mass;
    vector <ofVec3f> points;
    vector <ofVec3f> velocities;
    vector <ofVec3f> forces;
    vector <ofVec3f> randoms;
    vector <ofVec3f> pos;
    
    ofxField() {
        
    }

    ofxField(int res_, ofVec3f minBounds, ofVec3f maxBounds) {
        points.clear();
        velocities.clear();
        forces.clear();
        res = res_;
        mass = 5;
        for (int i=minBounds.x;i<maxBounds.x;i++) {
            for (int j = minBounds.x;j < maxBounds.y; j++) {
                for(int k=minBounds.z;k<maxBounds.z;k++) {
                    if (i % res == 0) {
                        if (j % res == 0) {
                            if (k % res == 0) {
                                pos.push_back( ofVec3f(i, j, k));
                                points.push_back( ofVec3f(i, j, k));
                                forces.push_back(ofVec3f(0,0,0));
                                velocities.push_back(ofVec3f(0,0,0));
                                randoms.push_back(ofVec3f(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10)));
                            }
                        }
                    }
                }
            }
        }
    }
    
    void update(vector <ofxBody> attractors, vector <ofxBody> repulsors) {
        
        for (int i = 0;i<points.size();i++) {
            for (int j=0;j<attractors.size();j++) {
                ofVec3f act;
                act.set(attractors[j].pos);
                forces[i] = act - points[i];
//                float dist = force.length();
//                float inverseSquare = (mass * attractors[j].mass) / (dist * dist);
//                forces[i] *= inverseSquare;
                velocities[i] += forces[i];
                velocities[i].normalize();
                velocities[i] *= mass;
                points[i] += velocities[i];

            }
        }
        for (int i = 0;i<points.size();i++) {
            for (int j=0;j<repulsors.size();j++) {
                ofVec3f act;
                act.set(repulsors[j].pos);
                forces[i] = act - points[i];
//                float dist = force.length();
//                float inverseSquare = (mass * repulsors[j].mass) / (dist * dist);
//                forces[i] *= inverseSquare;
                velocities[i] += -forces[i];
                velocities[i].normalize();
                velocities[i] *= mass;
                points[i] += velocities[i];

            }
        }
    }
    
    void draw() {
        ofPushMatrix();
//        for (int i=0;i<points.size();i++) {
//            ofTranslate(points[i].x,points[i].y,points[i].z);
//            ofLine(0,0,0,randoms[i].x,randoms[i].y,randoms[i].z);
//        }
        ofPopMatrix();
        for (int i=0;i<points.size();i++) {
            ofSetColor(255,0,0);
//            ofSphere(pos[i].x,pos[i].y,pos[i].z,1);
            ofSetColor(0,0,255);
//            ofSphere(points[i].x,points[i].y,points[i].z,5);
            ofSetColor(255);
            ofLine(pos[i].x,pos[i].y,pos[i].z,points[i].x,points[i].y,points[i].z);
            points[i].set(pos[i].x,pos[i].y,pos[i].z);
        }
   
    }
    
    
    
    
};




