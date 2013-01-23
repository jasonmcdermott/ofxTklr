#ifndef BOIDS_H
#define BOIDS_H





class ofParticleSystem {
	public:

    
    
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++                                           Main                                                        +++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


    
    ofParticleSystem(int dim_) {
        dim = dim_;
    }
    
    ofParticleSystem(int dim_, int num_, string type_) {
        dim = dim_;
        for (int i=0;i<num_;i++) {
            addParticles("boid");
        }
        setDefaults();
    }

    ofParticleSystem(int dim_, int num_, string type_, float mass_) {
        dim = dim_;
        for (int i=0;i<num_;i++) {
            addParticles("boid", mass_);
        }
        setDefaults();
    }

    
    void update() {
        for(int i = 0; i < particles.size(); ++i) {
            particles[i]->update(printMe);
        }
    }
    
    void draw(string drawingType){
        for(int i = 0; i < particles.size(); ++i) {
            particles[i]->draw(drawingType);
        }
        printStatus(20,20);
    }

    
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++                                           New Particles                                               +++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    
    
//    void addParticles(string type_) {
//        genRandomMassLocVel(1,1,1);
//        addParticles(type_,randomLoc,randomMass,randomVel);
//    }
//    
//    void addParticles(string type_, float mass_) {
//        genRandomMassLocVel(mass_,1,1);
//        addParticles(type_,randomLoc,mass_,randomVel);
//    }
//    
//    void addParticles(string type_, int num_) {
//        for (int i=0;i<num_;i++) {
//            genRandomMassLocVel(1,1,1);
//            addParticles(type_,randomLoc,randomMass,randomVel);
//        }
//    }
//    
//    void addParticles(string type_, float mass_, ofVec3f loc_, ofVec3f vel_) {
//        addParticles(type_,loc_,mass_,vel_);
//    }
//    
//    void addParticles(string type_, int num_, float mass_){
//        for (int i=0;i<num_;i++) {
//            genRandomMassLocVel(mass_,1,1);
//            addParticles(type_,randomLoc,mass_,randomVel);
//        }
//    }
//
//    void addParticles(string type_, int num_, ofVec3f loc_){
//        for (int i = 0; i < num_; ++i) {
//            genRandomMassLocVel(1,1,1);
//            addParticles(type_,loc_,randomMass,randomVel);
//        }
//    }
//
//    void addParticles(string type_, int num_, float mass_, ofVec3f vel_){
//        for (int i=0;i<num_;i++) {
//            genRandomMassLocVel(1,1,1);
//            addParticles(type_,randomLoc,mass_,vel_);
//        }
//    }
//    
//    void addParticles(string type_, int num_, float mass_, float vel_){
//        for (int i=0;i<num_;i++) {
//            genRandomMassLocVel(1,1,vel_);
//            addParticles(type_,randomLoc,mass_,randomVel);
//        }
//    }
//    
//    void addParticles(string type_, int num_, ofVec3f loc_, float mass_, ofVec3f vel_){
//        for (int i=0;i<num_;i++) {
//            addParticles(type_,loc_,mass_,vel_);
//        }
//    }
//
//    void addParticles(string type_, float mass_, ofVec3f vel_, ofVec3f orbitLoc_, float orbitRadius_){
//        particles.push_back(new ofParticle(particleCount,type_,mass_,vel_, orbitLoc_, orbitRadius_));
//        particleCount++;
//    }
//    
//    void addParticles(string type_, ofVec3f loc_, float mass_, ofVec3f vel_){
//        particles.push_back(new ofParticle(particleCount,type_,loc_,mass_,vel_));
//        particleCount++;
//        setDefaults();
//    }
    
    
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++                                               Bounds                                                  +++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    
    void bounce() {
        for(int i = 0; i < particles.size(); ++i) {
            if (particles[i]->pos.x > maxBounds.x) {
                particles[i]->pos.x = maxBounds.x;
                particles[i]->vel.x *= -1.0;
            }
            if (particles[i]->pos.x < minBounds.x) {
                particles[i]->pos.x = minBounds.x;
                particles[i]->vel.x *= -1.0;
            }
            if (particles[i]->pos.y > maxBounds.y) {
                particles[i]->pos.y = maxBounds.y;
                particles[i]->vel.y *= -1.0;
            }
            if (particles[i]->pos.y < minBounds.y) {
                particles[i]->pos.y = minBounds.y;
                particles[i]->vel.y *= -1.0;
            }
            if (particles[i]->pos.z > maxBounds.z) {
                particles[i]->pos.z = maxBounds.z;
                particles[i]->vel.z *= -1.0;
            }
            if (particles[i]->pos.z < minBounds.z) {
                particles[i]->pos.z = minBounds.z;
                particles[i]->vel.z *= -1.0;
            }
        }
    }

    void fleeBounds(){
        ofVec3f fleePos;
        for(int i = 0; i < particles.size(); ++i) {
            ofVec3f tempPos = particles[i]->getPosition();
            
            if (tempPos.x < minBounds.x + visualField) {
                fleePos.set(minBounds.x,tempPos.y,tempPos.z);
                particles[i]->flee(fleePos);
            }
            if (tempPos.x > maxBounds.x-visualField) {
                fleePos.set(maxBounds.x,tempPos.y,tempPos.z);
                particles[i]->flee(fleePos);
            }
            if (tempPos.y < minBounds.y+visualField) {
                fleePos.set(tempPos.x,minBounds.y,tempPos.z);
                particles[i]->flee(fleePos);
            }
            if (tempPos.y > maxBounds.y-visualField){
                fleePos.set(tempPos.x,maxBounds.y,tempPos.z);
                particles[i]->flee(fleePos);
            }
            if (tempPos.z > minBounds.z+visualField){
                fleePos.set(tempPos.x,tempPos.y,minBounds.z);
                particles[i]->flee(fleePos);
            }
            if (tempPos.z > maxBounds.z-visualField){
                fleePos.set(tempPos.x,tempPos.y,maxBounds.z);
                particles[i]->flee(fleePos);
            }
        }
    }
    
    void transportBounds() {
        for(int i = 0; i < particles.size(); ++i) {
            if (particles[i]->pos.x > maxBounds.x) {
                particles[i]->pos.x = minBounds.x;
            }
            if (particles[i]->pos.x < minBounds.x) {
                particles[i]->pos.x = maxBounds.x;
            }
            if (particles[i]->pos.y > maxBounds.y) {
                particles[i]->pos.y = minBounds.y;
            }
            if (particles[i]->pos.y < minBounds.y) {
                particles[i]->pos.y = maxBounds.y;
            }
            if (particles[i]->pos.z > maxBounds.z) {
                particles[i]->pos.z = minBounds.z;
            }
            if (particles[i]->pos.z < -minBounds.z) {
                particles[i]->pos.z = maxBounds.z;
            }
        }
    }
    
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++                                           Utilities                                                   +++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    void ageAndDie() {
        for(int i = 0; i < particles.size(); ++i) {
            if (particles[i]->age > 1000) {
                particles[i]->isDead = true;
            }
        }
    }
    
    int countLiveParticles() {
        int count = 0;
        for(int i = 0; i < particles.size(); ++i) {
            if (particles[i]->isDead == false) {
                count++;
            }
        }
        return count;
    }
    
    void setDefaults() {
        randomLoc.set(0,0,0);
        randomVel.set(0,0,0);
        randomMass = 0;
        mostMassiveParticleID = 0;
        minBounds.set(0,0,0);
        if (dim > 2) {
            maxBounds.set(ofGetWidth(),ofGetHeight(),400);
        } else {
            maxBounds.set(ofGetWidth(),ofGetHeight(),-400);
        }
        setMaxVelocity(0.2f);
        setMaxForce(0.2f);
        personalSpace = 25;
        visualField = 100;
        setArriveThreshold(140.0);
        setDimensions();
        zeroForce.set(0,0,0);
    }

    void setDimensions(){
        for (int i=0;i<particles.size();i++) {
            particles[i]->setDimensions(dim);
        }
    }

    bool checkParticles(int i, int j) {
        bool cont = true;
        if (j == i) cont = false;
        if (particles[i]->isDead) cont = false;
        if (particles[j]->isDead) cont = false;
        if (particles[i]->type == "neutral") cont = false;
        if (particles[j]->type == "neutral") cont = false;
        return cont;
    }
    

    void genRandomMassLocVel(float mass, float loc, float vel){
        randomLoc.set(ofRandom(minBounds.x,maxBounds.x) * loc, ofRandom(minBounds.y, maxBounds.y) * loc, ofRandom(minBounds.z,maxBounds.z) * loc);
        randomVel.set(ofRandom(-1,1) * vel, ofRandom(-1,1) * vel, ofRandom(-1,1) * vel);
        randomMass = ofRandom(0.2,5) * mass;
    }

    
    ofVec3f getLargestBodyPosition() {
        float bigger = 0;
        for (int i = 0; i < particles.size(); ++i) {
            if (particles[i]->isDead == true) continue;
            if (particles[i]->mass > bigger) {
                bigger = particles[i]->mass;
                mostMassiveParticleID = i;
            }
        }
        
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->largestMass = bigger;
        }
        ofVec3f loc;
        loc.set(particles[mostMassiveParticleID]->pos);
        return loc;
    }

    ofVec3f getLargestParticleVector() {
        ofVec3f loc;
        loc.set(particles[mostMassiveParticleID]->vec);
        return loc;
        
    }
    
    void tallyMass() {
        for(int i = 0; i < particles.size(); ++i) {
            totalMass += particles[i]->mass;
        }
    }
    
    vector<ofParticle*> getParticles() {
        return particles;
    }
    
    void setMaxVelocity(float fMax) {
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->setMaxVelocity(fMax);
        }
    }
    
    void setMaxForce(float fMax) {
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->setMaxForce(fMax);
        }
    }
    
    void setMass(float fMass) {
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->setMass(fMass);
        }
    }
    
    void setMass(string type_, float fMass) {
        for (int i = 0; i < particles.size(); ++i) {
            if (particles[i]->type == type_) {
                particles[i]->setMass(fMass);
            }
        }
    }
    
    void setArriveThreshold(float fThresh){
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->setArrive(fThresh);
        }
    }
    
    void returnToOrigin() {
        setDefaults();
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->isDead = false;
            particles[i]->pos.set(particles[i]->origin.x,particles[i]->origin.y,particles[i]->origin.z);
        }
    }
    
    void startWithRandomVelocity() {
        ofVec3f randVel;
        randVel.set(ofRandom(minBounds.x,maxBounds.x),ofRandom(minBounds.y, maxBounds.y),ofRandom(minBounds.z,maxBounds.z));
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->addForce(randVel);
        }
    }
    
    void printStatus(int x_, int y_) {
        ofSetColor(255-background);
        string  info  = "FPS: "+ofToString(ofGetFrameRate(),0)+"\n";
        info += "particles: "+ofToString(particleCount,0)+"\n";
        ofDrawBitmapString(info, x_, y_);
    }

    
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++                                           Forces                                                    +++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    ofVec3f measureForce(int i, int j, string mode) {
        if (particles[j]->type == "attractor") {
            return zeroForce;
        }
        else if (particles[j]->type == "repulsor") {
            return zeroForce;
        } else {
            if (mode == "attract") {
                ofVec3f dir = particles[j]->pos-particles[i]->pos;
                float dist = dir.length();
                dir.normalize();
                if (dist < 1000) {
                    dir /= particles[j]->mass;
                    dir *= 0.95;
                    return dir;
                }
            } else if (mode == "repel") {
                ofVec3f dir = particles[j]->pos-particles[i]->pos;
                float dist = dir.length();
                dir.normalize();
                if (dist < 1000) {
                    if( dist < 150 ){
                        dir /= particles[j]->mass;
                        dir *= 0.95;
                        dir.set(-dir.x,-dir.y,-dir.z);
                        return dir;
                    }
                }
            }
        }
    }

    
    void flock() {
        int insight_count = 0;
        ofVec3f average_vel, average_pos;
        for (int i = 0; i < particles.size(); ++i) {
            average_vel.set(0,0,0);
            average_pos.set(0,0,0);
            insight_count = 0;
            
            //for(int j = i + 1; j < particles.size(); ++j) {
            for(int j = 0; j < particles.size(); ++j) {
                
                checkParticles(i,j);
                float dist = (particles[i]->getPosition() - particles[j]->getPosition()).length();
                
                // separate
                if (dist <= visualField ) {
                    average_vel += particles[j]->getVelocity();
                    average_pos += particles[j]->getPosition();
                    insight_count++;
                    if (dist <= personalSpace) {
                        particles[i]->flee(particles[j]->getPosition());
                        /*
                         ofxVec3f heading = particles[i]->getVelocity().normalize();
                         ofxVec3f diff = boids[j]->getPosition()-particles[i]->getPosition();
                         float dot_prod = diff.dot(heading);
                         if (dot_prod > 0) {
                         particles[i]->flee(boids[j]->getPosition());
                         }
                         */
                    }
                }
            }
            if (insight_count > 0) {
                average_pos /= insight_count;
                average_vel /= insight_count;
                particles[i]->seek(average_pos);
                particles[i]->addForce(average_vel - particles[i]->getVelocity());
            }
        }
    }
    
    void arrive(ofVec3f oTarget) {
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->arrive(oTarget);
        }
    }
    
    void flee(ofVec3f oTarget) {
        for (int i = 0; i < particles.size(); ++i) {
            particles[i]->flee(oTarget);
        }
    }
    
//    void explode() {
//        float max_vel = particles[0]->getMaxVelocity();
//        for (int i = 0; i < particles.size(); ++i) {
//            particles[i]->setVelocity(ofVec3f(ofRandom(-max_vel,max_vel),ofRandom(-max_vel,max_vel),ofRandom(0,-max_vel)));
//        }
//    }

    void attract() {
        for (int i = 0; i < particles.size(); ++i) {
            for(int j = 0; j < particles.size(); ++j) {
                bool doAttract = checkParticles(i,j);
                if (doAttract) {
                    if (particles[i]->type == "boid" && particles[j]->type == "boid") continue;
                    particles[j]->subtractForce(measureForce(i,j,"attract"));
                }
            }
        }
    }
    
    void repulse() {
        for (int i = 0; i < particles.size(); ++i) {
            for(int j = 0; j < particles.size(); ++j) {
                bool doAttract = checkParticles(i,j);
                if (doAttract) {
                    if (particles[i]->type == "boid" && particles[j]->type == "boid") continue;
                    
//                    ofVec3f attractPoint;
//                    attractPoint.set(particles[i]->pos);
//                    
//                    ofVec3f force;
//                    force = attractPoint - particles[j]->pos;
//                    float dist = force.length();
//                    force.normalize();
//                    particles[j]->vel *= 0.9;
//                    if (dist < 1000) {
//                        particles[j]->vel += force;
//                    }
                    
                    
//                    ofVec3f dir = particles[j]->pos-particles[i]->pos;
//                    float dist = dir.length();
//                    dir.normalize();
//                    if (dist < 1000) {
//                        if( dist < 150 ){
//                            dir /= particles[j]->mass;
//                            dir *= 0.95;
//                            //                        dir.set(-dir.x,-dir.y,-dir.z);
//                            return dir;
//                        }
//                    }
                    
                    
//                    ofPoint attractPt(ofGetMouseX(), ofGetMouseY(),0);
//                    frc = attractPt-pos;
                    //let get the distance and only repel points close to the mouse
//                    float dist = frc.length();
//                    frc.normalize();
//                    vel *= drag;
//                    if( dist < 150 ){
//                        vel += -frc * 0.6;
//                    }
                    
//                    particles[j]->vel += -(measureForce(i,j, "repel"));
                    particles[j]->subtractForce(measureForce(i,j, "repel"));
                }
            }
        }
    }
    
    void gravitate() {
        for (int i = 0; i < particles.size(); ++i) {
            for(int j = 0; j < particles.size(); ++j) {
                bool doAttract = checkParticles(i,j);
                if (doAttract) {
                    if (particles[j]-> type == "attractor") continue;
                    if (particles[j]-> type == "repulsor") continue;
                        ofVec3f dir = particles[j]->pos-particles[i]->pos;
                        float dist = particles[j]->pos.distance(particles[i]->pos);
                        float massProduct = particles[i]->mass * particles[j]->mass;
                        float distanceSquared = dist * dist;
                        float G = 6.6;
                        
                        dir.normalize();
                        
                        dir += massProduct / distanceSquared;
//                        dir *= 0.09; // drag
                    
                        ofVec3f forceJ;
//                        ofVec3f forceI;
                    
                        forceJ += dir;
                        forceJ /= particles[j]->mass;
                    
//                        forceI += dir;
//                        forceI /= particles[i]->mass;
                    
                        particles[j]->addForce(forceJ);
//                        particles[i]->addForce(forceI);
                    
                        //                        float dist = aPos.distance(bPos);
                        //                        float F = 0;
                        //                        float iMass = particles[i]->mass*GLOBAL_MASS_MAGNIFIER;
                        //                        float jMass = particles[j]->mass*GLOBAL_MASS_MAGNIFIER;
                        //                        if (dist > particles[i]->radius + particles[j]->radius ) {
                        //                            dir.normalize();
                        //                            F = 1.0f / dist;
                        //                            ofVec3f forceJ = dir*(F/jMass);
                        //                            ofVec3f forceI = dir*(F/iMass);
                        //                            particles[j]->addForce(forceJ);
                        ////                            particles[i]->addForce(-forceI);
                        //                        }
                }
            }
        }
    }
    
    
    


    
//    if( mode == PARTICLE_MODE_ATTRACT ){
//		ofPoint attractPt(ofGetMouseX(), ofGetMouseY(),0);
//		frc = attractPt-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
//		frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point
//		
//		vel *= drag; //apply drag
//		vel += frc * 0.6; //apply force
//	}

    
//    void seekParent(ofVec3f oMainTarget) {
//        particles[0]->seek(oMainTarget);
//        for(int i = 1; i < particles.size(); ++i) {
//            particles[i]->seek(particles[i-1]->getPosition());
//        }
//    }

    
    

    
    
//    void repulse() {
//        for (int i = 0; i < particles.size(); ++i) {
//            for(int j = 0; j < particles.size(); ++j) {
//                bool proceed = checkParticles(i,j,"repulsor");
//                if (proceed) {
//                    ofVec3f aPos = particles[i]->pos;
//                    ofVec3f bPos = particles[j]->pos;
//                    ofVec3f dir = aPos-bPos;
//                    float dist = aPos.distance(bPos);
//                    float F = 0;
//                    float iMass = particles[i]->mass*GLOBAL_MASS_MAGNIFIER;
//                    float jMass = particles[j]->mass*GLOBAL_MASS_MAGNIFIER;
//                    if (dist > 0.0) {
//                        dir.normalize();
//                        F = 1.0f / dist;
//                        ofVec3f forceI = dir*(F/jMass);
//                        ofVec3f forceJ = dir*(F/iMass);
//                        particles[j]->addForce(-forceI);
//                        particles[i]->addForce(forceJ);
//                    }
//                }
//            }
//        }
//    }
    
//    void collide(string collisionType_) {
//        for (int i = 0; i < particles.size(); ++i) {
//            for(int j = 0; j < particles.size(); ++j) {
//                if (j == i) continue;
//                if (particles[i]->isDead == false && particles[j]->isDead == false) {
//                    
//                    
//                    ofVec3f aPos;
//                    ofVec3f bPos;
//                    ofVec3f cPos;
//                    aPos.set(particles[j]->pos.x,particles[j]->pos.y,particles[j]->pos.z);
//                    bPos.set(particles[i]->pos.x,particles[i]->pos.y,particles[i]->pos.z);
//                    cPos.set(aPos.x,aPos.y,aPos.z);
//                    cPos -= bPos;
//                    float distance = cPos.length();
//                    
//                    //                // hacky way to get the particles to print.
//                    //                string bland = ofToString(aPos) + " ---- " + ofToString(bPos) + " ---- " + ofToString(cPos);
//                    //                particles[i]->printMe = bland;
//                    
//                    if (distance < particles[i]->radius + particles[j]->radius) {
//                        if (collisionType_=="elastic") {
//                            elasticCollision(i,j);
//                        } else if (collisionType_ == "inelastic") {
//                            inelasticCollision(i,j);
//                        } else if (collisionType_ == "cluster") {
//                            cluster(i,j);
//                        }
//                        
//                    }
//                    
//                    //                string a = " ";
//                    //                a += "Dist: " + ofToString(dist,0) + " \n";
//                    //                a += "C: " + ofToString(c,0) + " \n";
//                    //
//                    //                ofSetColor(255);
//                    //                ofDrawBitmapString(a,100,100);
//                    
//                    
//                    
//                    
//                    
//                    
//                    
//                    
//                    
//                    
//                    //                if (particles[j]->mass > particles[i]->mass) {
//                    //                    particles[j]->addMass(particles[i]->mass);
//                    //                    particles[j]->addForce(particles[i]->vel);
//                    //                    particles[i]->collide();
//                    //                } else if (particles[j]->mass > particles[i]->mass) {
//                    //                    particles[i]->addMass(particles[j]->mass);
//                    //                    particles[j]->collide();
//                    //                    particles[i]->addForce(particles[j]->vel);
//                    //                } else if (particles[j]->mass == particles[i]->mass) {
//                    //                    particles[i]->addMass(particles[j]->mass);
//                    //                    particles[j]->addMass(particles[i]->mass);
//                    //                    particles[j]->addForce(particles[i]->vel);
//                    //                    particles[i]->addForce(particles[j]->vel);
//                    //                    particles[j]->collide();
//                    //                    particles[i]->collide();
//                    //                }
//                    //            }
//                    
//                    
//                    
//                    //            if (dist < (particles[i]->radius/2 + particles[j]->radius/2)) {
//                    //
//                    //                if (particles[i]->mass > particles[j]->mass) {
//                    //                    particles[i]->mass += particles[j]->mass/particles[i]->mass;
//                    //                    particles[j]->collide();
//                    //                } else {
//                    //                    particles[j]->mass += particles[i]->mass/particles[j]->mass;
//                    //                    particles[i]->collide();
//                    //                }
//                    //            }
//                }
//            }
//        }
//    }

    
//    void inelasticCollision(int i, int j) {
//        // nothing yet
//    }
    
//    void elasticCollision(int i, int j) {
//        
//        //    p = m * v;
//        
//        float massA = particles[i]->mass;
//        float massB = particles[j]->mass;
//        ofVec3f oldVelA = particles[i]->vel;
//        ofVec3f oldVelB = particles[j]->vel;
//        
//        //    vi = (ui(mi-mii)+(2*(mii*uii))) / (mi + mii);
//        //    vii = (uii(mii-mi)+(2*(mi*ui))) / (mi + mii);
//        
//        
//        
//        ofVec3f newVelA = (oldVelA*(massA-massB)+(2*(massB*oldVelB))) / (massA + massB);
//        ofVec3f newVelB = (oldVelB*(massB-massA)+(2*(massA*oldVelA))) / (massA + massB);
//        
//        particles[i]->addForce(newVelA);
//        particles[j]->addForce(newVelB);
//        
//    }
    
//    void cluster(int i, int j) {
//        // nothing yet
//    }
//    
//    void moveOnSurface() {
//        
//        for (int i=0;i<particles.size();i++) {
//            particles[i]->moveOnSurf();
//        }
//    }
//    
//    void constrainToSurface(int particleID) {
//        for (int i = 0; i < particles.size(); ++i) {
//            bool proceed = checkParticles(i,particleID,"attractive");
//            if (proceed) {
//                
//                ofVec3f aPos = particles[i]->pos;
//                ofVec3f bPos = particles[particleID]->pos;
//                ofVec3f dir = aPos-bPos;
//                float dist = aPos.distance(bPos);
//                float constrainRadius = particles[particleID]->radius;
//                
//                float theta = 0;
//                float phi = 0;
//                float posXsqr = dir.x * dir.x;
//                float posYsqr = dir.y * dir.y;
//                float posZsqr = dir.z * dir.z;
//                
//                float rad = sqrt(posXsqr + posYsqr + posZsqr);
//                float weirdS = 0;
//                
//                if (rad < constrainRadius) {
//                    
//                    //            if (dist <= constrainRadius) {
//                    
//                    
//                    //                float vTheta = 0;
//                    //                float vPhi = 0;
//                    
//                    //                vTheta += ofRandom(0,0.0001);
//                    //                theta += vTheta;
//                    
//                    //        if (theta<0||theta>TWO_PI) {
//                    //            vTheta*=-1;
//                    //        }
//                    
//                    //        vPhi += ofRandom(-0.001,0.001);
//                    //        phi += vPhi;
//                    
//                    //        if (phi<-1||phi>1) vPhi*=-1;
//                    
//                    //                vPhi *= 0.95;
//                    //                vTheta *= 0.95;
//                    
//                    
//                    
//                    //                theta = acosf(particles[i]->pos.y/constrainRadius);
//                    //                weirdS = sqrt(posXsqr + posYsqr);
//                    
//                    
//                    //                if (dir.x < 0) {
//                    //                    phi = asinf(dir.y/weirdS);
//                    //                } else if (dir.x >= 0) {
//                    //                    phi = PI - asinf(dir.y/weirdS);
//                    //                }
//                    
//                    theta = acosf(dir.y/rad);
//                    phi = atan2f(dir.y, dir.x);
//                    
//                    float x = rad * sin(theta) * cos(phi);
//                    float y = rad * sin(theta) * sin(phi);
//                    float z = rad * cos(theta);
//                    
//                    
//                    //                float x = constrainRadius * cos(theta) * sqrt(1-(phi*phi));
//                    //                float y = constrainRadius * sin(theta) * sqrt(1-(phi*phi));
//                    //                float z = constrainRadius * phi;
//                    particles[i]->pos.set(x,y,z);
//                    //                particles[i]->vel.set(0,0,0);
//                    
//                }
//                
//                
//            }
//        }
//    }
    
    


    
private:
		int num_Particles;
		

};

#endif
