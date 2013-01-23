#ifndef PARTICLE_H
#define PARTICLE_H
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>
#define GLOBAL_MASS_MAGNIFIER 10

enum particleMode{
	PARTICLE_MODE_ATTRACT = 0,
	PARTICLE_MODE_REPEL,
	PARTICLE_MODE_NEAREST_POINTS,
	PARTICLE_MODE_NOISE
};


class ofParticle {
public:
    
    ofColor c;
    float max_force, max_vel, mass, radius, dragF, distance, arrive_dist, largestMass;
    int ID, age;
    string type, state, printString;
    ofVec3f pos, origin, acc, vel, vec, force, dispForce;
    bool isDead, calculateForces, printMe = false;
    float phi,theta,vPhi,vTheta, orbitRadius;
    ofVec3f loc, sLoc,  minBounds, maxBounds, rand2D, rand3D, loci, randomLoc, randomVel;
    int dim;
    vector<ofVec3f*> vectors;
    
    int particleCount, mostMassiveParticleID;
    float personalSpace, visualField, totalMass, minBoundsX, maxBoundsX, minBoundsY, maxBoundsY, minBoundsZ, maxBoundsZ, randomMass, background;

    vector<ofParticle*> particles;
    float posArray[1000000 * 2 * 2];
	float colArray[1000000 * 3 * 2];
    ofVec3f zeroForce;


    
    //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ INIT
    ofParticle(int ID_, string type_, ofVec3f loc_, float mass_, ofVec3f vel_) {
        ID = ID_;
        type = type_;
        mass = mass_;
        vel.set(vel_.x,vel_.y,vel_.z);
        pos.set(loc_.x,loc_.y,loc_.z);
        initParticles();
    }
    
    ofParticle(int ID_, string type_, float mass_, ofVec3f vel_, ofVec3f sLoc_, float sRadius_){
        ID = ID_;
        type = type_;
        mass = mass_;
        vel.set(vel_.x,vel_.y,vel_.z);
        sLoc.set(sLoc_);
        loc.set(sLoc);
        theta = ofRandom(0,TWO_PI);
        phi = ofRandom(-1,1);
        orbitRadius = sRadius_;

        float x = orbitRadius*cos(theta)*sqrt(1-(phi*phi));
        float y = orbitRadius*sin(theta)*sqrt(1-(phi*phi));
        float z = orbitRadius*phi;

        loc += (x,y,z);
        pos.set(loc);
        initParticles();
    }
    
    

    
    //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Main Functions
    void update(bool printMe_) {
        printMe = printMe_;
        if (isDead == false) {
            age++;
            vectors.push_back(new ofVec3f(pos.x,pos.y,pos.z));
            if (mass < 1) {
                radius = mass * 10;
            } else {
                radius = mass;
            }
            if (calculateForces == true) {
                if (dim == 2) {
                    pos.set(pos.x,pos.y,0);
                }
                vel += force;
                pos += vel;
                //        dragF = ((0.9*0.5) * (vel.lengthSquared()) * 0.47 * (2*radius));
                //        vel /= dragF;
                dispForce.set(force);
                force.set(0,0,0);

//                ofVec3f rotater;
//                rotater.set(mass*2,cos(ofGetElapsedTimef()*1.4) * 30.f,sin(ofGetElapsedTimef()*1.4) * 30.f);
//                vec = pos+rotater;
            }
        }
    }
    
    void draw(string drawingType) {
        if (isDead == false) {
            if (dim == 3) {
                draw3D();
            } else if (dim == 2) {
                draw2D(drawingType);
            }
        }
    }
    
    //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Drawing Functions (2D/3D)
    void draw3D() {
        ofPushMatrix();
        ofTranslate(pos.x, pos.y, pos.z);
        if (type == "repulsive") {
            ofSetColor(255,0,0);
            ofSphere(0,0,0, radius);
        } else if (type == "attractive") {
            if (ID == 0) {
                ofSetColor(255);
            } else {
                ofSetColor(0,0,255);
            }
            ofSphere(0,0,0, radius);
        } else if (type == "neutral") {
            ofSetColor(255);
            ofSphere(0,0,0, radius);
        }
        ofPopMatrix();
    }
    
    void draw2D(string drawingType) {
        ofSetColor(c,50);
        if (drawingType == "vectors") {
            if (type == "boid") {
                glBegin(GL_LINES);
                for (int i=0;i<vectors.size();i++) {
                    if (i > 0) {
                        glVertex3f(vectors[i]->x,vectors[i]->y,vectors[i]->z);
                        glVertex3f(vectors[i-1]->x,vectors[i-1]->y,vectors[i-1]->z);
                    }
                }
                glEnd();
            }
        } else if (drawingType == "objects") {
            ofEnableSmoothing();
            ofCircle(pos.x,pos.y,pos.z,radius);
            printStatus();
            ofDisableSmoothing();
        }
    }
    
    
    //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Utilities
    void initParticles(){
        isDead = false;
        age = 0;
        arrive_dist = 140;
        vec.set(0,0,0);
        if (type == "boid") {
            c.set(0,200,100);
        } else if (type == "attractor"){
            c.set(255,0,0);
        } else if (type == "repulsor") {
            c.set(255,0,255);
        } else if (type == "particle") {
            c.set(255,10,10);
        } 

        origin.set(pos.x,pos.y,pos.z);
        calculateForces = true;
        printMe = false;
    }
    
    void printStatus() {
        if (printMe == true) {
            string a;
            a += " mass: " + ofToString(mass,2) + " \n";
            a += " vel: " + ofToString(vel,2) + " \n";
            a += " pos: " + ofToString(pos,2) + " \n";
            a += " force: " + ofToString(dispForce,5) + " \n";
            a += " age: " + ofToString(age,5) + " \n";
            a += printString;
            ofDrawBitmapString(a, 10, 10);
        }
    }
    
    void setDimensions(int dim_) {
        dim = dim_;
    }

    void addForce(ofVec3f oForce) {
        force += oForce;
    }
    
    void subtractForce(ofVec3f oForce) {
        force -= oForce;
    }
    
    ofVec3f getPosition() {
        return pos;
    }
    
    ofVec3f getVelocity() {
        return vel;
    }
    
    void setPosition(ofVec3f oPos) {
        pos = oPos;
    }
    
    void setMaxVelocity(float fMax) {
        max_vel = fMax;
    }
    
    void setMass(float fMass) {
        mass = fMass;
    }
    
    float getMaxVelocity() {
        return max_vel;
    }
    
    void setMaxForce(float fMaxForce){
        max_force = fMaxForce;
    }
    
    void setVelocity(ofVec3f oVel) {
        vel = oVel;
    }
    
    void setArrive(float fThresh) {
        arrive_dist = fThresh;
    }
    
    void collide(){
        isDead = true;
    }
    
    void addMass(float addMass) {
        mass += addMass;
    }

    
    //  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Particle Interaction
    void seek(ofVec3f oTarget) {
        ofVec3f desired_vel = oTarget - pos;
        desired_vel.scale(max_vel);
        desired_vel -= vel;
        addForce(desired_vel);
    }
    
    void flee(ofVec3f oTarget) {
        ofVec3f desired_vel = oTarget - pos;
        desired_vel.scale(max_vel);
        desired_vel -= vel;
        subtractForce(desired_vel);
    }
    
    void arrive(ofVec3f oTarget) {
        ofVec3f desired_vel = oTarget - pos;
        float dist = desired_vel.length();
        desired_vel.normalize();
        
        if (dist <= arrive_dist) {
            desired_vel *= ((max_vel * dist / arrive_dist));
            ofSetColor(0);
        }
        else {
            desired_vel *= max_vel;
        }
        if (dist > 10) {
            desired_vel -= vel;
            addForce(desired_vel);
        }
        else{
            force.set(0,0,0);
            vel.set(0,0,0);
        }
    }
    
    void pursue(ofParticle* pParticle) {
        float dist = (pParticle->getPosition() - getPosition()).length();
        float ahead_time = dist / max_vel;
        ofVec3f predicted_target = pParticle->getPosition() + pParticle->getVelocity()*ahead_time;
        seek(predicted_target);
    }
    
    void moveOnSurf() {
        calculateForces = false;
        vTheta += ofRandom(0,0.0001);
        theta += vTheta;
        
        if (theta<0||theta>TWO_PI) {
            vTheta*=-0.1;
        }
        
        vPhi += ofRandom(-0.001,0.001);
        phi += vPhi;
        
        if (phi<-1||phi>1) vPhi*=-1;
        
        vPhi *= 0.95;
        vTheta *= 0.95;
        
        float x = sLoc.x + (orbitRadius*cos(theta)*sqrt(1-(phi*phi)));
        float y = sLoc.y + (orbitRadius*sin(theta)*sqrt(1-(phi*phi)));
        float z = sLoc.z + (orbitRadius*phi);
        ofVec3f newPos;
        newPos.set(x,y,z);
        pos += newPos;
//        pos.set(x,y,z);
    }
    
    
    
    
private:
    ofImage img;
    
    
};

#endif
