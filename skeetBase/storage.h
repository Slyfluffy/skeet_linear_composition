//
//  storage.h
//  Skeet
//
//  Created by Journey Curtis on 2/24/22.
//

#ifndef storage_h
#define storage_h

#include "element.h"

#include <iterator>
#include <array>
#include <vector>

/**********************************
 * SKEET :: STORAGETIME
 * Storage container for everything
 * about time.
 *********************************/
class StorageTime {
protected:
   // number of frames left in this level
   int framesLeft;
   
   // the level number we are currently in
   int levelNumber;
   
   // length in seconds of each level
   std::array<int, 5> levelLength;
   
public:
   StorageTime() { reset(); }
   
   // Getters
   int getFramesLeft()  const { return framesLeft;  }
   int level() const { return levelNumber; }
   std::array<int, 5> getArray() { return levelLength; }
      
   // Setters
   void setFramesLeft(int frames) { framesLeft = frames; }
   void setLevel(int level) { levelNumber = level;       }
   void setArray(std::array<int, 5> rhs) { levelLength = rhs; }
   void reset();
};

/**********************************
 * SKEET :: STORAGEGUN
 * Storage container for everything
 * about the gun.
 *********************************/
class StorageGun {
private:
   double angle;
   Point pt;
   
public:
   StorageGun(const Point & pt) : angle(0.78 /* 45 degrees */), pt(pt) {}
   
   // Getters
   double getAngle() const { return angle; }
   Point  getPoint() const { return pt;    }
   
   // Setters
   void setAngle(double rhs) { angle = rhs; }
   void setPoint(Point rhs)  { pt = rhs;    }
};

/*************************************
 * SKEET :: STORAGE
 * Storage Class. Contains the various
 * StorageElements, time, and gun.
 ************************************/
class Storage {
private:
   std::vector<StorageElement*> elements;
   int numBirds;
   int points;
   int numKilled;
   StorageTime time;
   StorageGun gun;
   
public:
   // Constructor
   Storage() : numBirds(0), points(0), numKilled(0), gun(Point(800.0, 0)), time() {}
   
   // Getters.
   int getPoints()    { return points;               }
   int getNumKilled() { return numKilled;            }
   int getNumMissed() { return numBirds - numKilled; }
   
   // Normal iterator to go through entire list
   std::vector<StorageElement*> :: iterator begin() { return elements.begin(); }
   std::vector<StorageElement*> :: iterator end()   { return elements.end();   }
   
   // Iterator to go through birds
   class IteratorBird;
   IteratorBird beginBird();
   IteratorBird endBird();
   
   // Iterator to go through bullets
   class IteratorBullet;
   IteratorBullet beginBullet();
   IteratorBullet endBullet();
   
   // Setters/ adders
   void add(StorageElement * element) { elements.push_back(element); }
   void reset();
};

#endif /* storage_h */
