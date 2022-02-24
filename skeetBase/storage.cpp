//
//  storage.cpp
//  Lab03
//
//  Created by Journey Curtis on 2/24/22.
//

#include "storage.h"

#define FRAMES_PER_SECOND 30

/******************************
 * STORAGETIME :: RESET
 * INPUTS  :: NONE
 * OUTPUTS :: NONE
 * resets the data within time.
 *****************************/
void StorageTime::reset()
{
    // first level is 30 seconds in length, the first 5 are the status time
    levelLength = { 0, 30, 30, 45, 45 };
    levelNumber = 1;
    framesLeft = FRAMES_PER_SECOND * levelLength[levelNumber];
}

/*********************************
 * STORAGE :: RESET
 * INPUTS  :: NONE
 * OUTPUTS :: NONE
 * resets the data within storage.
 * This includes time and gun.
 ********************************/
void Storage :: reset() {
   elements.clear();
   numBirds = 0; points = 0;
   numKilled = 0;
   time.reset();
   gun.setAngle(.78);
}

/*******************************
 * STORAGE :: ITERATORBIRD
 * iterator for storage elements
 * that are birds.
 ******************************/
class Storage :: IteratorBird {
private:
   StorageElement * p; // Pointer to the data
   
public:
   // Constructors
   IteratorBird() : p(NULL) { }
   IteratorBird(StorageElement * p) : p(p) { }
   IteratorBird(const IteratorBird & rhs) { *this = rhs; }

   // Set operator
   IteratorBird & operator = (const IteratorBird & rhs) {
      this->p = rhs.p;
      return *this;
   }
   
   // Equivalence operators
   bool operator != (const IteratorBird & rhs) const { return rhs.p != this->p; }
   bool operator == (const IteratorBird & rhs) const { return rhs.p == this->p; }
   
   // postfix subtract operator
   IteratorBird & operator -- () {
      p--; // Start off one down
      while (p != NULL) { // Find the next one that is bird or the beginning
         if (p->getStorageType() == BIRD)
            return *this; // return if it is a bird
         else
            p--;
      }
      
      return *this; // This returns null
   }
   
   // prefix subtract operator
   IteratorBird operator -- (int postfix) {
      IteratorBird tmp(*this);
      p--;
      return tmp;
   }
   
   // postfix addition operator
   IteratorBird & operator ++ () {
      p++; // Add first
      while (p != NULL) { // Go till you find it or to the end of the container
         if (p->getStorageType() == BIRD)
            return *this;
         else
            p++;
      }
      
      return *this; // Return null
   }
   
   // prefix addition operator
   IteratorBird operator ++ (int postfix) {
      IteratorBird tmp(*this);
      p++;
      return tmp;
   }
};

/*********************************
 * STORAGE :: BEGINBIRD
 * INPUTS  :: NONE
 * OUTPUTS :: iteratorBird
 * Returns iterator for beginning
 * of birdElements
 ********************************/
Storage::IteratorBird Storage::beginBird() {
   IteratorBird it = IteratorBird((*elements.begin()));
   return ++it;
}

/*****************************
 * STORAGE :: ENDBIRD
 * INPUTS  :: NONE
 * OUTPUTS :: iteratorBird
 * Returns iterator for end of
 * BirdElements
 ****************************/
Storage::IteratorBird Storage::endBird() {
   IteratorBird it = IteratorBird((*elements.end()));
   return --it;
}

/*****************************
 * STORAGE :: IteratorBullet
 * Iterator for bullets in
 * StorageElements
 ****************************/
class Storage :: IteratorBullet {
private:
   StorageElement * p;
   
public:
   // Constructors
   IteratorBullet() : p(NULL) { }
   IteratorBullet(StorageElement * p) : p(p) { }
   IteratorBullet(const IteratorBird & rhs) { *this = rhs; }

   // Assignment operator
   IteratorBullet & operator = (const IteratorBullet & rhs) {
      this->p = rhs.p;
      return *this;
   }
   
   // Equivalence operators
   bool operator != (const IteratorBullet & rhs) const { return rhs.p != this->p; }
   bool operator == (const IteratorBullet & rhs) const { return rhs.p == this->p; }
   
   // Postix Subtract
   IteratorBullet & operator -- () {
      p--;
      while (p != NULL) {
         if (p->getStorageType() == BULLETS)
            return *this;
         else
            p--;
      }
      
      return *this;
   }
   
   // Prefix subtract
   IteratorBullet operator -- (int postfix) {
      IteratorBullet tmp(*this);
      p--;
      return tmp;
   }
   
   // postfix addition
   IteratorBullet & operator ++ () {
      p++;
      while (p != NULL) {
         if (p->getStorageType() == BULLETS)
            return *this;
         else
            p++;
      }
      
      return *this;
   }
   
   // prefix addition
   IteratorBullet operator ++ (int postfix) {
      IteratorBullet tmp(*this);
      p++;
      return tmp;
   }
};

/********************************
 * STORAGE :: BEGINBULLET
 * INPUTS  :: NONE
 * OUTPUTS :: iteratorBullet
 * Returns iterator for beginning
 * of BulletElements
 *******************************/
Storage::IteratorBullet Storage::beginBullet() {
   IteratorBullet it = IteratorBullet((*elements.begin()));
   return ++it;
}

/*****************************
 * STORAGE :: ENDBULLET
 * INPUTS  :: NONE
 * OUTPUTS :: iteratorBullet
 * Returns iterator for end of
 * BulletElements
 ****************************/
Storage::IteratorBullet Storage::endBullet() {
   IteratorBullet it = IteratorBullet((*elements.end()));
   return --it;
}
