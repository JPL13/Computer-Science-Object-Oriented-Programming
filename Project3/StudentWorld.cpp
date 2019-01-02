#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

int StudentWorld::init()
{
    m_ticks=0;
    m_alien_destroyed=0;
  
    //add a Nachenblaster
    m_Blaster = new NachenBlaster(this);
   
    //adding Stars
    for (int i = 0; i < 30; i++)
    {
        int r=randInt(0, 255);
        int c=randInt(0, 255);
        
        m_field.push_back( new Star(c, r, this));
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}



int StudentWorld::move()
{
    updateTickCount();
    setDisplayText();
    
    //Do something for each actor
    m_Blaster->doSomething();
    

    for(list<Actor*>::iterator it = m_field.begin(); it != m_field.end(); it++)
    {
        //if no object, then continue
        if((*it) == nullptr) continue;
        
        //if the object is alive, do something
        if((*it)->isAlive())
            (*it)->doSomething();
        
    }
        //if the object is dead
        if (!m_Blaster->isAlive())
        {
            decLives();
            
            return GWSTATUS_PLAYER_DIED;
        }
        
        if (m_alien_destroyed==6+(4*getLevel()))
        {
             return GWSTATUS_FINISHED_LEVEL;
        }
    

 
    //Remove dead actors
    

    for(list<Actor*>::iterator it = m_field.begin(); it != m_field.end(); )
    {
        if((*it) == nullptr) continue;
        
        if(!(*it)->isAlive())
        {
            delete *it;
            it=m_field.erase(it);
        }
        
        else
            it++;
    }

 
    //adding stars
    
    if(randInt(1,15)==1)
    {
        int r=randInt(0, 255);
        int c=VIEW_WIDTH-1;
        m_field.push_back(new Star(c, r, this));
    }

 //*******   add aliens ************************************
    int Tobe_killed=6+(4*getLevel());
    int R=Tobe_killed-m_alien_destroyed;
    int M=4+(0.5*getLevel());
    if(countCurrentAlien()<min(M, R))
    {
        int S1=60;
        int S2=20+getLevel()*5;
        int S3=5+getLevel()*10;
        int S=S1+S2+S3;
       
        int r=randInt(0, 255);
        int c=VIEW_WIDTH-1;
        
        if(randInt(1,S)<=S1)
          addObject(new Smallgon(c, r, this));
        if(randInt(1,S)<=S2)
            addObject(new Smoregon(c, r, this));
        if(randInt(1,S)<=S3)
            addObject(new Snagglegon(c, r, this));
    }
 
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for(list<Actor*>::iterator it = m_field.begin(); it != m_field.end(); )
    {
        delete *it;
        it=m_field.erase(it);
        
    }

    delete m_Blaster;
    m_Blaster=nullptr;
    
}

//Lives: 3 Health: 100% Score: 24530 Level: 3 Cabbages: 80% Torpedoes: 4
void StudentWorld::setDisplayText()
{
    int lives = getLives();
    int health = m_Blaster->getHitPoints()/.5;
    int score = getScore();
    int level = getLevel();
    double cabbages = m_Blaster->getCabbage()/0.3;
    int Torpedoes = m_Blaster->getTorpedoes();
    
    ostringstream oss;
    
    oss.setf(ios::fixed);
    oss.precision(2);
    oss << "Lives: ";                //1 digit
    oss << setw(1) << lives;
    
    oss.fill(' ');
    oss << "  Health: ";                //3 digits in percentage w/ leading spaces followed by percentage sign (_##%) is 3 digits
    oss << setw(3) << health;
    oss <<'%';
    
    oss.fill(' ');
    oss << "  Score: ";                //6 digit
    oss << setw(6) << score;
    
    oss.fill(' ');
    oss << "  Level: ";                    //2 digits w/ leading spaces
    oss << setw(2) << level;
    
    oss.fill(' ');
    oss << "  Cabbages: ";                //3 digits in percentage w/ leading spaces followed by percentage sign (_##%) is 3 digits
    oss << setw(3) << cabbages;
    oss <<'%';
    
    oss.fill(' ');
    oss << "  Torpedoes: ";                //2 digit
    oss << setw(2) << Torpedoes;
    
    string s = oss.str();
    setGameStatText(s);
}



bool StudentWorld::isNearNachen(Actor* obj)
{
    int x = obj->getX();
    int y = obj->getY();
    int r = obj->getRadius();
    
    int xNachen = m_Blaster->getX();
    int yNachen = m_Blaster->getY();
    int rNachen = m_Blaster->getRadius();
    return (euclidian_dist(x, y, xNachen, yNachen) <= .75 * (rNachen + r));
}

bool StudentWorld::isNearAliens(Actor* obj)
{
    int x = obj->getX();
    int y = obj->getY();
    int r = obj->getRadius();
    int id =obj->getID();
    
    list<Actor*>::iterator it;
    it = m_field.begin();
    while (it != m_field.end())
    {
        if((*it)->getID()==IID_SMALLGON||(*it)->getID()==IID_SMOREGON||(*it)->getID()==IID_SNAGGLEGON)
        {
            int xAlien = (*it)->getX();
            int yAlien = (*it)->getY();
            int rAlien = (*it)->getRadius();
            
            if (euclidian_dist(x, y, xAlien, yAlien) <= .75 * (rAlien + r))
            {
                (*it)->getAttacked(id);
                (*it)->setAttacked(true);
                return true;
            }
        }
        
        it++;
    }
    return false;
}


int StudentWorld::euclidian_dist(double x1, double y1, double x2, double y2)
{
    double x = x1 - x2; //calculating number to square in next step
    double y = y1 - y2;
    double dist;
    
    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);
    
    return dist;
}

void StudentWorld::addObject(Actor* obj)
{
    m_field.push_back(obj);
}

int StudentWorld::countCurrentAlien()
{
    int count=0;
    for(list<Actor*>::iterator it = m_field.begin(); it != m_field.end(); it++)
    {
        if((*it)->getID()==IID_SMALLGON||(*it)->getID()==IID_SMOREGON||(*it)->getID()==IID_SNAGGLEGON)
             count++;
    }
    
    return count;
}

