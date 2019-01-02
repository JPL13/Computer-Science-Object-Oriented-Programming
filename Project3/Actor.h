#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

//Actor class: The base class for all game objects

class Actor : public GraphObject {
    
public:
    Actor(int imageID, double startX, double startY, StudentWorld *sw, int dir = 0, double size = 1.0, int depth = 0) : GraphObject(imageID, startX, startY, dir, size, depth), m_sw(sw)
    {
        m_isAlive = true;
        m_ID=imageID;
        m_Attacked=false;
    };
    
    virtual ~Actor(){};
    
    //Called every tick
    virtual void doSomething() = 0;
    
    //Called when actor is got attackted
    virtual void getAttacked(int damageType){};
    //setter
    bool setAttacked(bool status){m_Attacked=status; return m_Attacked;}

    
   //getter
    bool getAttacked()const{return m_Attacked;}
    bool isAlive() const {return m_isAlive;};
    StudentWorld* getWorld()const{return m_sw;};
    int getID()const {return m_ID;}
   
    
protected:
    virtual void setDead(){m_isAlive = false;}
    
private:

    bool m_isAlive;
    StudentWorld *m_sw;
    int m_ID;
    bool m_Attacked;
};


//Star class
class Star : public Actor {
    
public:
    Star(int startX, int startY, StudentWorld *sw) : Actor(IID_STAR, startX, startY, sw, 0, randInt(5,50)/100.0, 3){};
    virtual ~Star(){};
    virtual void doSomething();
    

};

class NachenBlaster: public Actor
{
public:
    NachenBlaster(StudentWorld* world);
    virtual ~NachenBlaster();
    virtual void doSomething();

    
    //setter
    void addToInventory(int ID, int num);
    void updateHitPoints(int hp){m_HitPoints+=hp;}
    
    //getter
    int getCabbage()const{return m_cabbage;};
    int getTorpedoes()const{return m_TorpedoGoodie;};
    int getHitPoints()const{return m_HitPoints;}
    
  
private:
    int m_cabbage;
    int m_TorpedoGoodie;
    int m_HitPoints;
};

class Explosion: public Actor
{
public:
    Explosion(int startX, int startY, StudentWorld *sw);
    ~Explosion(){};
    virtual void doSomething();
    
private:
    int StartingTick;
    
};

class Projectile: public Actor  //serve as Base class for cabbages, Turnips and Flatulence Torpedo
{
public:
    Projectile(int imageID, int startX, int startY, StudentWorld *sw, int dir = 0, double size = 1.0, int depth = 0) : Actor(imageID, startX, startY, sw, dir, size, depth){};
    virtual ~Projectile(){};
    
    virtual void doSomething();
    bool checkFlownOff();
    
private:
    void Rotate();
   virtual bool Collided()=0;
   virtual void MakeMove()=0;
};


class Cabbages: public Projectile  //serve as Base class for cabbages, Turnips and Flatulence Torpedo
{
public:
    Cabbages(int startX, int startY, StudentWorld *sw) : Projectile(IID_CABBAGE, startX, startY, sw, 0, 0.5,1){};
    virtual ~Cabbages(){};
  
private:
    virtual bool Collided();
    virtual void MakeMove() {moveTo(getX()+8, getY());}
};

class Turnips: public Projectile  //serve as Base class for cabbages, Turnips and Flatulence Torpedo
{
public:
    Turnips(int startX, int startY, StudentWorld *sw) : Projectile(IID_TURNIP, startX, startY, sw, 0, 0.5,1){};
    virtual ~Turnips(){};
    

private:
    virtual bool Collided();
    virtual void MakeMove() {moveTo(getX()-6, getY());}
};

class FTorpedo: public Projectile  //serve as Base class for cabbages, Turnips and Flatulence Torpedo
{
public:
    FTorpedo(int startX, int startY, StudentWorld *sw, int dir) : Projectile(IID_TORPEDO, startX, startY, sw, dir, 0.5,1){};
    virtual ~FTorpedo(){};
    virtual void doSomething();
    

private:
    virtual bool Collided();
    virtual void MakeMove();
};


//Goodies Base class
class Goodies: public Actor  //serve as Base class
{
public:
    Goodies(int imageID, int startX, int startY, StudentWorld *sw, int dir = 0, double size = 1.0, int depth = 0) : Actor(imageID, startX, startY, sw, dir, size, depth){};
    virtual ~Goodies(){};
    void doSomething();
  

private:
    virtual bool Collided()=0;
    
};


class ExtraLife : public Goodies{
    
public:
    ExtraLife(int startX, int startY, StudentWorld *sw) : Goodies(IID_LIFE_GOODIE, startX, startY, sw, 0, 0.5, 1){};
    virtual ~ExtraLife(){};
    
private:
    virtual bool Collided();
    
};

//Goodies
class RepairGoodie : public Goodies {
    
public:
    RepairGoodie(int startX, int startY, StudentWorld *sw) : Goodies(IID_REPAIR_GOODIE, startX, startY, sw, 0, 0.5, 1){};
    virtual ~RepairGoodie(){};
    
    
private:
    virtual bool Collided();
    
};

//Goodies
class FTGoodie : public Goodies {
    
public:
    FTGoodie(int startX, int startY, StudentWorld *sw) : Goodies(IID_TORPEDO_GOODIE, startX, startY, sw, 0, 0.5, 1){};
    virtual ~FTGoodie(){};
    
private:
    virtual bool Collided();
   
};


class AlienShip: public Actor
{
public:
    AlienShip(int startX, int startY, StudentWorld* sw,int imageID,
              double hitPoints, double speed, int flight_plan_len, double deltaX, double deltaY):Actor(imageID, startX, startY, sw, 0,1.5,1), m_HitPoints(hitPoints), m_speed(speed), m_flight_plan_len(flight_plan_len),m_deltaX(deltaX),m_deltaY(deltaY){};
    virtual ~AlienShip(){};
    virtual void doSomething()=0;
    virtual void Collided()=0;
    
    // Move the player by the current speed in the direction indicated
    // by the x and y deltas.
    void move();
    
    // Setter
    void setDeltaY(double dy){m_deltaY=dy;}
    void setDeltaX(double dx){m_deltaX=dx;}
    void getAttacked(int damageType);
    void updateHitPoints(int hp){m_HitPoints+=hp;}
    void setHitPoints(double hp){m_HitPoints=hp;}
    void setFlightPlan(int i){m_flight_plan_len=i;}
    void setSpeed(int s){m_speed=s;}
    
    //getter
    double getHitPoints()const{return m_HitPoints;}
    double getSpeed()const{return m_speed;}
    int getFlightPlan()const{return m_flight_plan_len;}
    double getDeltaX()const{return m_deltaX;}
    double getDeltaY()const{return m_deltaY;}

    
private:
    
    int m_flight_plan_len;
    double m_HitPoints;
    double m_speed;
    double m_deltaX;
    double m_deltaY;
    
};


class Smallgon: public AlienShip
{
public:
    Smallgon(int startX, int startY,StudentWorld* world);
    virtual ~Smallgon(){};
    void doSomething();
    void Collided();
    
};

class Smoregon: public AlienShip
{
public:
    Smoregon(int startX, int startY,StudentWorld* world);
    virtual ~Smoregon(){};
    void doSomething();
    void Collided();
    
};

class Snagglegon : public AlienShip
{
public:
    Snagglegon (int startX, int startY,StudentWorld* world);
    virtual ~Snagglegon (){};
    void doSomething();
    void Collided();
    
};


#endif // ACTOR_H_
