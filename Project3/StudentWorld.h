#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Actor;
class NachenBlaster;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    void addObject(Actor* obj);
    bool isNearNachen(Actor* obj);
    bool isNearAliens(Actor* obj);
    void updateAliensDestroyed(){m_alien_destroyed++;}
    
    //getter
    int getCurrentTicks()const{return m_ticks;};
    NachenBlaster* getNachenBlaster()const{return m_Blaster;}
    
    
    

private:
    int getAliensDestroyed()const{return m_alien_destroyed;}
    int countCurrentAlien();
    int updateTickCount(){return m_ticks++;};
    void setDisplayText();
    int euclidian_dist(double x1, double y1, double x2, double y2);
    
    int m_alien_destroyed;
    int m_ticks;
    
    std::list<Actor*> m_field;
    NachenBlaster* m_Blaster;
    
};

#endif // STUDENTWORLD_H_

