#pragma once
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>
#include "ofxBody.h"
#include "ofxField.h"


enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_HOVER,
	PARTICLE_MODE_NOISE,
    PARTICLE_MODE_ATTRACT_AND_REPEL
};

class ofxParticle{
    public:
    
    ofVec3f vel, force, pos;
    string printString;
    float mass, radius;
    float attractionRadius = 300;
    float tooCloseAttractionRadius = 10;
    float repulsionRadius = 100;
    float uniqueVal, scale, drag = 0.99, visualField = 1000, personalSpace = 20, max_force = 0.2, max_vel = 1;
    particleMode mode;
    vector<ofVec3f*> vectors;
    bool isDead = false;
    bool cont = false;
    int age, decay, ID;
    bool particleAttraction = false, particleRepulsion = false, bodyRepulsion = false, bodyAttraction = false;
    bool posSet = false;
    ofVec3f minBounds, maxBounds;
    
    ofxParticle() {

    }
    
    ofxParticle(int ID_, ofVec3f loc_, float mass_, ofVec3f minBounds_, ofVec3f maxBounds_) {
        ID = ID_;
        pos.set(loc_);
        mass = mass_;
        posSet = true;
        minBounds = minBounds_;
        maxBounds = maxBounds_;
    }
    
    void update(){
        if (isDead  == false) {
            vectors.push_back(new ofVec3f(pos.x,pos.y,pos.z));
            vel *= drag;
            pos += vel;
            age++;
        }
    }
    
    void draw() {
        if (isDead == false) {
            ofSetColor(255, 63, 180);
            ofSphere(pos.x, pos.y, pos.z, radius);
//            glBegin(GL_LINES);
//            for (int i=1;i<vectors.size();i++) {
//                glVertex3f(vectors[i]->x,vectors[i]->y,vectors[i]->z);
//                glVertex3f(vectors[i-1]->x,vectors[i-1]->y,vectors[i-1]->z);
//            }
//            glEnd();
            drawInfo();
        } else {
            ofSetColor(255);
        }
        if (decay < 1000) {

        }
    }
    
    void setMode(particleMode newMode) {
        mode = newMode;
    }
    void setForces(bool bodyAttraction_, bool bodyRepulsion_, bool particleAttraction_, bool particleRepulsion_) {
        bodyAttraction = bodyAttraction_;
        bodyRepulsion = bodyRepulsion_;
        particleAttraction = particleAttraction_;
        particleRepulsion = particleRepulsion_;
    }
    
    void interact(vector <ofxParticle> particles, vector <ofxBody> bodies) {
        for (int i=0;i<bodies.size();i++) {
            if (bodyAttraction && bodies[i].charge == 0) {             // be attracted to global attractors
                ofVec3f att;
                att.set(bodies[i].pos);
                force = att - pos;
                float dist = force.length();
                float inverseSquare = (mass * bodies[i].mass) / (dist * dist);
                float minDist = (radius + bodies[i].mass);
                if (dist > minDist) {
                    force *= inverseSquare;
                    vel += force;
                } else if (dist < minDist) {
                    force *= inverseSquare;
                    force += -force;
                }
            }
            if (bodyRepulsion && bodies[i].charge > 0) {
                ofVec3f rep;
                rep.set(bodies[i].pos);
                force = rep - pos;
                float dist = force.length();
                float inverseSquare = (mass * bodies[i].mass) / (dist * dist);
                //                    force.normalize();
                if (dist < mass * 300) {
                    force *= inverseSquare;
                    vel += -force;
                }
            }
        }
        for (int i=0;i<particles.size();i++) {
            if (ID != particles[i].ID){
                if (particleAttraction) {
                    ofVec3f att;
                    att.set(particles[i].pos);
                    force = att - pos;
                    float dist = force.length();
                    float inverseSquare = (mass * particles[i].mass) / (dist * dist);
                    float minDist = (radius + particles[i].mass);
                    if (dist > minDist) {
                        force *= inverseSquare;
                        vel += force;
                    } else if (dist < minDist) {
                        force *= inverseSquare;
                        force += -force;
                    }
                }
                if (particleRepulsion) {
                    ofVec3f otherPos;
                    otherPos.set(particles[i].pos);
                    force = otherPos - pos;
                    float dist = force.length();
                    float inverseSquare = (mass * particles[i].mass) / (dist * dist);
                    force *= inverseSquare;
                    vel += -force;
                }
            }
        }
    }
    
        
//    void seek(ofVec3f target_) {
//        ofVec3f target;
//        target.set(target_);
//        ofVec3f desired;
//        desired = target - pos;
//        
//        desired.normalize();
//        desired *= max_vel;
//        
//        ofVec3f steer;
//        steer = desired - vel;
//        steer *= drag;
//        vel += steer;
//
//
////        float dist = force.length();
////        ofVec3f desired = PVector.sub(target,location);
////        desired.normalize();
////        desired.mult(maxspeed);
////        PVector steer = PVector.sub(desired,velocity);
////        steer.limit(maxforce);
////        addForce(steer);
//    }

    
//    void interact(vector <ofxParticle> particles, vector <ofxBody> attractors, vector <ofxBody> repulsors) {
//            if (attraction) {
//                // be attracted to global attractors
//                for (int i=0;i<attractors.size();i++) {
//                    ofVec3f att;
//                    att.set(attractors[i].pos);
//                    force = att - pos;
//                    float dist = force.length();
//                    float inverseSquare = (mass * attractors[i].mass) / (dist * dist);
//                    vel *= drag;
//                    if (dist > radius + attractors[i].mass) {
//                        force *= inverseSquare;
//                    } 
//                    vel += force;
//                }
//            }
//            if (pAttraction) {
//                // be attracted to other particles
//            }
//            if (repulsion) {
//                // be repelled by global repulsors
//                for (int i=0;i<repulsors.size();i++) {
//                    ofVec3f rep;
//                    rep.set(repulsors[i].pos);
//                    force = rep - pos;
//                    float dist = force.length();
//                    float inverseSquare = (mass * repulsors[i].mass) / (dist * dist);
////                    force.normalize();
//                    vel *= drag;
//                    if (dist > radius * 2) {
//                        force *= inverseSquare;
//                    } else {
//                        force /= mass;
//                    }
//                    vel += -force;
//                }
//            }
//            if (pRepulsion) {
//                // be repelled by other particles
//            }
////        } else if ( mode == PARTICLE_MODE_HOVER ) {
//            // not sure what i'll put in here
////        }
//    }

//    void attract(vector <ofxParticle> particles, vector <ofVec3f> attractors) {
//        if( mode == PARTICLE_MODE_ATTRACT ){
//        }
//    }

//    void repel(vector <ofxParticle> particles, vector <ofVec3f> repulsors) {
//        if( mode == PARTICLE_MODE_REPEL ){
//        }
//    }
    
//    void interact(vector <ofxParticle> particles) {
//        if( mode == PARTICLE_MODE_HOVER ){
//            if( attractors ){
            
//                ofPoint closestPt;
//                int closest = -1;
//                float closestDist = 9999999;
//                
//                for(int i = 0; i < attractPoints->size(); i++){
//                    float lenSq = ( attractPoints->at(i)-pos ).lengthSquared();
//                    if( lenSq < closestDist ){
//                        closestDist = lenSq;
//                        closest = i;
//                    }
//                }
//                if( closest != -1 ){

//                    float lensq = (attractPoints[0]-pos).lengthSquare();
//                    closestPt = attractPoints->at(0);
//                    float dist = sqrt(lensq);
//                    
//                    //in this case we don't normalize as we want to have the force proportional to distance
//                    frc = closestPt - pos;
//                    
//                    vel *= drag;
//                    
//                    //lets also limit our attraction to a certain distance and don't apply if 'f' key is pressed
//                    if( dist < attractionRadius && dist > tooCloseAttractionRadius && !ofGetKeyPressed('f') ){
//                        vel += frc * 0.003;
//                        vel *= 0.99;
//                    } else if (dist < 40) {
//                        vel *= -0.01;
//                    } else if (dist > attractionRadius) {
//                        vel += frc * 0.003;
//                    } else {
//                        //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
//                        frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
//                        frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
//                        frc.z = ofSignedNoise(uniqueVal, pos.z * 0.01, ofGetElapsedTimef()*0.2);
//                        vel += frc * 0.4;
//                    }
            
//                }
//                ofPoint repelPoint(ofGetWidth()/2 , ofGetHeight()/2, 0);
//                ofPoint repelForce = repelPoint-pos;
//                //let get the distance and only repel points close to the mouse
//                float distance = repelForce.length();
//                repelForce.normalize();
//                vel *= drag;
//                if( distance < 200 ){
//                    vel += -repelForce * 0.6;
//                }
//            }
            
//        }
//    }
    
    void reset(ofVec3f min, ofVec3f max) {
        
        uniqueVal = ofRandom(-10000, 10000);
        minBounds.set(min);
        maxBounds.set(max);
        
        if (posSet == false) {
            pos.set(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0);
            mass = ofRandom(1,10);
        }
        
        vel.set(0,0,0);
        radius = mass;
        force = ofPoint(0,0,0);
    }
//
//    
//    void flock(vector <ofxParticle> particles) {
//        cont = true;
//        int insight_count = 0;
//        ofVec3f average_vel, average_pos;
//        for(int i = 0; i < particles.size(); i++){
//            average_vel.set(0,0,0);
//            average_pos.set(0,0,0);
//            insight_count = 0;
//
//            for (int j = 0; j < particles.size(); ++j) {
//                if (particles[i].isDead) {
//                    cont = false;
//                }
//                if (particles[j].isDead) {
//                    cont = false;
//                }
//                if (i == j) {
//                    cont = false;
//                }
//                if (cont == true) {
//                    float dist = (particles[i].pos - particles[j].pos).length();
//                    if (dist <= visualField) {
//                        average_vel += particles[j].vel;
//                        average_pos += particles[j].pos;
//                        insight_count++;
//                        if (dist <= personalSpace) {
//                            particles[i].flee(particles, particles[j].pos);
//                        }
//                    }
//                }
//            }
//            if (insight_count > 0) {
//                average_pos /= insight_count;
//                average_vel /= insight_count;
//                particles[i].seek(average_pos);
//                particles[i].addForce(average_vel - particles[i].vel);
//            }
//        }
//    }
    
    
//    void flee(vector <ofxParticle> particles, ofVec3f oTarget) {
//        for (int i = 0; i < particles.size(); ++i) {
//            particles[i].flee(particles, oTarget);
//        }
//    }
//    
//    void seek(ofVec3f oTarget) {
//        ofVec3f desired_vel = oTarget - pos;
//        desired_vel.scale(max_vel);
//        desired_vel -= vel;
//        addForce(desired_vel);
//    }
//
//    void addForce(ofVec3f oForce) {
//        force += oForce;
//    }
    
    void drawInfo() {
        string a;
//        a += " mass: " + ofToString(mass,2) + " \n";
//        a += " vel: " + ofToString(vel,2) + " \n";
//        a += " pos: " + ofToString(pos,2) + " \n";
//        a += " age: " + ofToString(age,5) + " \n";
        a += printString;
        ofDrawBitmapString(a, pos.x+10, pos.y+10, pos.z);
        printString = "";
    }
    
};




