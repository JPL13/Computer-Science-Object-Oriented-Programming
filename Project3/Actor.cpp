#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
#include <cmath>
#include <iostream>
using namespace std;




///////////////////////////////////////////////
// Star
///////////////////////////////////////////////

void Star::doSomething()
{
    GraphObject::moveTo(GraphObject::getX()-1, GraphObject::getY());
    
    if(GraphObject::getX()<=-1)
        Actor::setDead();
    
}


///////////////////////////////////////////////
// NachenBlaster
///////////////////////////////////////////////

NachenBlaster::NachenBlaster(StudentWorld* world)
:Actor(IID_NACHENBLASTER, 0, 128, world)
{
    m_cabbage = 30;
    m_TorpedoGoodie = 0;
    m_HitPoints=50;
}

NachenBlaster::~NachenBlaster()
{//
}

void NachenBlaster::doSomething()
{
    if (!isAlive())
        return;
    
    
    int ch;
    
    if(getWorld()->getKey(ch))
    {
        switch (ch)
        {
            case KEY_PRESS_SPACE:    //fire a cabbage
              
                if (m_cabbage >= 5)
                {
                    m_cabbage-=5;
                    //a new cabbage object must be added exactly 12 pixels to the right of the NachenBlaster ship, with a starting direction of zero degrees.
                    int x=getX();
                    int y=getY();
                    getWorld()->addObject(new Cabbages(x+12, y,getWorld()));
                    
                    getWorld()->playSound(SOUND_PLAYER_SHOOT);
                }
                    
                break;
          
            //any movement may cause a collision with an alien ship or projectile, so you must check for this.
                
            case KEY_PRESS_LEFT:        //move
                    if(getX()>=6)  //able to move
                     moveTo(getX() - 6, getY());
                        
                break;
            case KEY_PRESS_RIGHT:
                  if(getX()<=VIEW_WIDTH-6)  //able to move
                    moveTo(getX() + 6, getY());
                break;
            case KEY_PRESS_UP:
                if(getY()<=VIEW_HEIGHT-6)  //able to move
                    moveTo(getX(), getY() + 6);
                break;
            case KEY_PRESS_DOWN:
                if(getY()>=6)  //able to move
                    moveTo(getX(), getY() - 6);
                break;
            
            case KEY_PRESS_TAB:        //fire a tropedo
                if (m_TorpedoGoodie> 0)
                {
                    m_TorpedoGoodie--;
                    // a new torpedo object must be added exactly 12 pixels to the right of the NachenBlaster ship, with a starting direction of zero degrees.
                    int x=getX();
                    int y=getY();
                    getWorld()->addObject(new FTorpedo(x+12,y,getWorld(),0));
                    getWorld()->playSound(SOUND_TORPEDO);
                }
        }//end of switch
    }//end of if
    
    
    //NachenBlaster will receive one cabbage energy point, max 30
    if(m_cabbage<30)
        m_cabbage++;
    if(m_HitPoints<=0)
        Actor::setDead();
    
    if(getAttacked())
    { getWorld()->playSound(SOUND_BLAST);
        setAttacked(false);}
}

void NachenBlaster::addToInventory(int ID, int num)
{
    if (ID == IID_TORPEDO_GOODIE)
        m_TorpedoGoodie+=num;
}

///////////////////////////////////////////////
// Explosion
///////////////////////////////////////////////

Explosion::Explosion(int startX, int startY, StudentWorld *sw) : Actor(IID_EXPLOSION, startX, startY, sw, 0, 1, 0){
    
    StartingTick= getWorld()->getCurrentTicks();
};
void Explosion::doSomething()
{
    if(getWorld()->getCurrentTicks()-StartingTick==4){
      Actor::setDead();
    }
    
    setSize(1.5*getSize());

}


///////////////////////////////////////////////
// Projectile
///////////////////////////////////////////////

bool Projectile::checkFlownOff()
{
    if(getX()>=VIEW_WIDTH||getX()<0)
        {   Actor::setDead();
            return true;     }
 
    return false;
}


void Projectile::Rotate()
{//Right is 0, up is 90, left is 180, and down is 270.
    int current= getDirection();
    setDirection(current+20);
}

void Projectile::doSomething()
{
    if (!isAlive())
        return;
    if(checkFlownOff())
        return;
    if(Collided())
        return;
    MakeMove();
    Rotate();
    if(Collided())
        return;
}



///////////////////////////////////////////////
// Cabbages
///////////////////////////////////////////////
bool Cabbages::Collided()
{
    if(getWorld()->isNearAliens(this))
    {
       //Damageing the victim ship is handled by StudentWorld::isNearAliens()
       
        Actor::setDead();
        return true;
    }
    
    return false;
}

///////////////////////////////////////////////
// Turnips
///////////////////////////////////////////////
bool Turnips::Collided()
{
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->getNachenBlaster()->updateHitPoints(-2);
        getWorld()->getNachenBlaster()->setAttacked(true);
        
        Actor::setDead();
        return true;
    }
    
    return false;
}

///////////////////////////////////////////////
// FTorpedo
///////////////////////////////////////////////
bool FTorpedo::Collided()
{
    if(getWorld()->isNearNachen(this))
    {
        //Damage the victim ship appropriately
        getWorld()->getNachenBlaster()->updateHitPoints(-8);
        getWorld()->getNachenBlaster()->setAttacked(true);
        
        Actor::setDead();
        return true;
    }
    
    if(getWorld()->isNearAliens(this))
    {
        //Damageing the victim ship is handled by StudentWorld::isNearAliens()
        
        Actor::setDead();
        return true;
    }
    
    return false;
}

void FTorpedo::doSomething()
{
    if (!isAlive())
        return;
    if(checkFlownOff())
        return;
    if(Collided())
        return;
    MakeMove();
    
    if(Collided())
        return;
}
void FTorpedo::MakeMove()
{
    if(getDirection()==0)
    moveTo(getX()+8, getY());
    
    if(getDirection()==180)
    moveTo(getX()-8, getY());
}

///////////////////////////////////////////////
// Goodies
///////////////////////////////////////////////
void Goodies::doSomething()
{
    if (!isAlive())
        return;
    if(Collided())
        return;

    moveTo(getX()-0.75, getY()-0.75);
    
    if(Collided())
        return;
}

///////////////////////////////////////////////
// Extra Life
///////////////////////////////////////////////
bool ExtraLife::Collided()
{
     if(getWorld()->isNearNachen(this))
     {   getWorld()->increaseScore(100);
    
       Actor::setDead();
    
       getWorld()->playSound(SOUND_GOODIE);
       getWorld()->incLives();
         return true;
         
     }
    return false;
}

///////////////////////////////////////////////
// RepairGoodie
///////////////////////////////////////////////
bool RepairGoodie::Collided()
{
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->increaseScore(100);
        
        Actor::setDead();
        
        getWorld()->playSound(SOUND_GOODIE);
        getWorld()->getNachenBlaster()->updateHitPoints(10);
        int exceed=getWorld()->getNachenBlaster()->getHitPoints()-50;
        if(exceed>0)
           getWorld()->getNachenBlaster()->updateHitPoints(-exceed);
        
        return true;
    }
    return false;
}

///////////////////////////////////////////////
// FTGoodie
///////////////////////////////////////////////
bool FTGoodie::Collided()
{
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->increaseScore(100);
        
        Actor::setDead();
        
        getWorld()->playSound(SOUND_GOODIE);
        getWorld()->getNachenBlaster()->addToInventory(IID_TORPEDO_GOODIE, 5);
        return true;
        
    }
    return false;
}

///////////////////////////////////////////////
// AlienShip
///////////////////////////////////////////////
void AlienShip::getAttacked(int damageType)
{
    if(damageType==IID_CABBAGE)
        updateHitPoints(-2);
    if(damageType==IID_TORPEDO)
        updateHitPoints(-8);
    
}

void AlienShip::move()
{
    moveTo(getX()+m_deltaX, getY()+m_deltaY);
}


///////////////////////////////////////////////
// Smallgon
///////////////////////////////////////////////
Smallgon::Smallgon(int startX, int startY,StudentWorld* world):AlienShip(startX, startY, world, IID_SMALLGON, 5 * (1), 2.0, 0, 0,0)
{
    setHitPoints(5 * (1 + (getWorld()->getLevel() -1) * .1));
    setAttacked(false);
}

void Smallgon::doSomething()
{
    if (!isAlive())
        return;
    if(getX()<0)
    { Actor::setDead();
        return;}
    
      Collided();
//********************************
//check if needs a new flight plan
    if(getY()>=VIEW_HEIGHT-1)
    {   setDeltaX(-getSpeed());//Down and Left
        setDeltaY(-getSpeed()); }
    if(getY()<=0)
    {   setDeltaX(-getSpeed());//Up and Left
        setDeltaY(getSpeed());   }
    
    if(getFlightPlan()==0)
    {
        int random=randInt(1,3);
        if(random==1)//left
        {   setDeltaX(-getSpeed());//
            setDeltaY(0);}
        if(random==2)//Up left
        {   setDeltaX(-getSpeed());
            setDeltaY(getSpeed());}
        if(random==3)//Down left
        {   setDeltaX(-getSpeed());
            setDeltaY(-getSpeed());}
    }
    
   // The Smallgon will pick a random new flight plan length in the range [1, 32].
    setFlightPlan(randInt(1, 32));
    
    //5.If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate, then:
   if(getWorld()->getNachenBlaster()->getX()<getX()&&(getWorld()->getNachenBlaster()->getY()-getY()>=-4 && getWorld()->getNachenBlaster()->getY()-getY()<=4))
   {
       if(randInt(1,(20/getWorld()->getLevel())+5)==1)
       {     
           int x=getX();
           int y=getY();
           getWorld()->addObject(new Turnips(x-14,y, getWorld()));
           
           getWorld()->playSound(SOUND_ALIEN_SHOOT);
          
           return;
       }
       
   }
//6.The Smallgon will try to move in its current travel direction (as determined by the last flight plan) and then reduce its flight plan length by 1. If its travel direction is:
    move();
    setFlightPlan(getFlightPlan()-1);
 
        Collided();
}

void Smallgon::Collided()
{
   if(Actor::getAttacked())
   {
       setAttacked(false);
      
     if(getHitPoints()<=0)
     {
        getWorld()->increaseScore(250);
        getWorld()->updateAliensDestroyed();
        Actor::setDead();
   
        getWorld()->playSound(SOUND_DEATH);
  
        int x=getX();
        int y=getY();

        getWorld()->addObject(new Explosion(x,y, getWorld()));
      }//end of if
    
     getWorld()->playSound(SOUND_BLAST);
   }
    
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->getNachenBlaster()->updateHitPoints(-5);
        getWorld()->getNachenBlaster()->setAttacked(true);
        getWorld()->updateAliensDestroyed();
         Actor::setDead();
       
        getWorld()->increaseScore(250);
       
        getWorld()->playSound(SOUND_DEATH);
       
        int x=getX();
        int y=getY();
        
        getWorld()->addObject(new Explosion(x,y, getWorld()));

    }
        
}



///////////////////////////////////////////////
// Smoregon
///////////////////////////////////////////////
Smoregon::Smoregon(int startX, int startY,StudentWorld* world):AlienShip(startX, startY, world, IID_SMOREGON, 5 * (1), 2.0, 0, 0, 0)
{
    if(getWorld()->getLevel()>2)
    setHitPoints(5 * (1 + (getWorld()->getLevel() -1) * .1));
    
    setAttacked(false);
}

void Smoregon::doSomething()
{
    if (!isAlive())
        return;
    if(getX()<0)
    { Actor::setDead();
        return;}
    
    Collided();
    //********************************
    //check if needs a new flight plan
    if(getY()>=VIEW_HEIGHT-1)
    {   setDeltaX(-getSpeed());//Down and Left
        setDeltaY(-getSpeed()); }
    if(getY()<=0)
    {   setDeltaX(-getSpeed());//Up and Left
        setDeltaY(getSpeed());   }
    
    if(getFlightPlan()==0)
    {
        int random=randInt(1,3);
        if(random==1)//left
        {   setDeltaX(-getSpeed());//
            setDeltaY(0);}
        if(random==2)//Up left
        {   setDeltaX(-getSpeed());
            setDeltaY(getSpeed());}
        if(random==3)//Down left
        {   setDeltaX(-getSpeed());
            setDeltaY(-getSpeed());}
    }
    
    
    // The Smallgon will pick a random new flight plan length in the range [1, 32].
    setFlightPlan(randInt(1, 32));
    
    //5.If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate, then:
    if(getWorld()->getNachenBlaster()->getX()<getX()&&(getWorld()->getNachenBlaster()->getY()-getY()>=-4 && getWorld()->getNachenBlaster()->getY()-getY()<=4))
    {
        if(randInt(1,(20/getWorld()->getLevel())+5)==1)
        {
            int x=getX();
            int y=getY();
            getWorld()->addObject(new Turnips(x-14,y, getWorld()));
            
            getWorld()->playSound(SOUND_ALIEN_SHOOT);
            
            return;
        }
        
         if(randInt(1,(20/getWorld()->getLevel())+5)==1)
         {
             setDeltaX(-getSpeed());
             setDeltaY(0);
             //It will set the length of its flight plan to VIEW_WIDTH steps.
             setFlightPlan(VIEW_WIDTH) ;
             setSpeed(5);
         }
        
    }
    //6.The Smallgon will try to move in its current travel direction (as determined by the last flight plan) and then reduce its flight plan length by 1. If its travel direction is:
    move();
    setFlightPlan(getFlightPlan()-1);
   
    Collided();
}

void Smoregon::Collided()
{
    if(Actor::getAttacked())
    {
        setAttacked(false);
        
        if(getHitPoints()<=0)
        {
            getWorld()->increaseScore(250);
            getWorld()->updateAliensDestroyed();
            Actor::setDead();
            
            getWorld()->playSound(SOUND_DEATH);
            
            int x=getX();
            int y=getY();
            
            getWorld()->addObject(new Explosion(x,y, getWorld()));
            
            if(randInt(1,3)==1)
            {
                if(randInt(1,2)==1)
                    getWorld()->addObject(new RepairGoodie(x,y, getWorld()));
                else
                    getWorld()->addObject(new FTGoodie(x,y, getWorld()));
            }
        }//end of if
        
        getWorld()->playSound(SOUND_BLAST);
       
    }
    
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->getNachenBlaster()->updateHitPoints(-5);
        getWorld()->getNachenBlaster()->setAttacked(true);
        getWorld()->updateAliensDestroyed();
        Actor::setDead();
        
        getWorld()->increaseScore(250);
        
        getWorld()->playSound(SOUND_DEATH);
        
        int x=getX();
        int y=getY();
        
        getWorld()->addObject(new Explosion(x,y, getWorld()));
        
        if(randInt(1,3)==1)
        {
            if(randInt(1,2)==1)
             getWorld()->addObject(new RepairGoodie(x,y, getWorld()));
            else
             getWorld()->addObject(new FTGoodie(x,y, getWorld()));
        }
        
    }
}
///////////////////////////////////////////////
// Snagglegon
///////////////////////////////////////////////
Snagglegon::Snagglegon(int startX, int startY,StudentWorld* world):AlienShip(startX, startY, world, IID_SNAGGLEGON, 10 * (1), 1.75, 0, -1.75, -1.75)
{
    //flight plan?
    if(getWorld()->getLevel()>2)
      setHitPoints(10 * (1 + (getWorld()->getLevel() -1) * .1));
    
    setAttacked(false);
}

void Snagglegon::doSomething()
{
    if (!isAlive())
        return;
    if(getX()<0)
    { Actor::setDead();
        return;}
    
    Collided();
    
    //********************************
    //check if needs a new flight plan
    if(getY()>=VIEW_HEIGHT-1)
    {   setDeltaX(-getSpeed());//Down and Left
        setDeltaY(-getSpeed()); }
    if(getY()<=0)
    {   setDeltaX(-getSpeed());//Up and Left
        setDeltaY(getSpeed());   }
  
    //5.If the NachenBlaster is to the left of the Smallgon AND the Smallgon has a y coordinate that is within [-4,4] pixels of the NachenBlaster’s y coordinate, then:
    if(getWorld()->getNachenBlaster()->getX()<getX()&&(getWorld()->getNachenBlaster()->getY()-getY()>=-4 && getWorld()->getNachenBlaster()->getY()-getY()<=4))
    {
        if(randInt(1,(15/getWorld()->getLevel())+10)==1)
        {
            int x=getX();
            int y=getY();
            getWorld()->addObject(new FTorpedo(x-14,y, getWorld(),180));
            
            getWorld()->playSound(SOUND_TORPEDO);
            
            return;
        }
    }
    //6.The Snagglegon will try to move in its current travel direction.
    move();
       
    Collided();
}

void Snagglegon::Collided()
{
    if(Actor::getAttacked())
    {
        setAttacked(false);
        
        if(getHitPoints()<=0)
        {
            getWorld()->increaseScore(1000);
            getWorld()->updateAliensDestroyed();
            Actor::setDead();
            
            getWorld()->playSound(SOUND_DEATH);
            
            int x=getX();
            int y=getY();
            
            getWorld()->addObject(new Explosion(x,y, getWorld()));
            
            if(randInt(1,6)==1)
           
            getWorld()->addObject(new ExtraLife(x,y, getWorld()));
              
        }//end of if
        
        getWorld()->playSound(SOUND_BLAST);
        
    }
    
    if(getWorld()->isNearNachen(this))
    {
        getWorld()->getNachenBlaster()->updateHitPoints(-15);
        getWorld()->getNachenBlaster()->setAttacked(true);
        getWorld()->updateAliensDestroyed();
        Actor::setDead();
        
        getWorld()->increaseScore(1000);
        
        getWorld()->playSound(SOUND_DEATH);
        
        int x=getX();
        int y=getY();
        
        getWorld()->addObject(new Explosion(x,y, getWorld()));
        
        if(randInt(1,6)==1)
            
            getWorld()->addObject(new ExtraLife(x,y, getWorld()));
        
    }
    
}


