//
//  element.h
//  Skeet
//
//  Created by Journey Curtis on 2/24/22.
//

#ifndef element_h
#define element_h

#include "point.h"

class StorageElement;

/*
 * INTERFACEELEMENTS
 */


class InterfaceElement {
public:
   virtual void draw(StorageElement *) = 0;
};

class InterfacePellet : public InterfaceElement {
   
public:
   void draw(StorageElement *);
};

class InterfaceFragment : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceMissile : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceBomb : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceShrapnel : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceExhaust : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceStreek : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceStandard : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceSinker : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceFloater : public InterfaceElement {
public:
   void draw(StorageElement *);
};

class InterfaceCrazy : public InterfaceElement {
public:
   void draw(StorageElement *);
};

/*
 * LOGICELEMENTS
 */

class LogicElement {
public:
   virtual void advance(StorageElement *) { }
   virtual void turn(StorageElement *) { }
};

class LogicPellet : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicMissile : public LogicElement {
public:
   void advance(StorageElement *);
   void turn(StorageElement *);
};

class LogicBomb : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicShrapnel : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicFragment : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicExhaust : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicStreek : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicStandard : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicSinker : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicFloater : public LogicElement {
public:
   void advance(StorageElement *);
};

class LogicCrazy : public LogicElement {
public:
   void advance(StorageElement *);
};

/*
 * STORAGEEELEMENTS
 */

enum StorageType { BIRD, BULLETS, EFFECTS };

class StorageElement {
protected:
   StorageType type;
   
   Point pt;
   Velocity v;
   
   double radius;
   int points;
   bool dead;
   
   LogicElement * pLogic;
   InterfaceElement * pInterface;
   
public:
   // getters
   StorageType getStorageType()  { return type;   }
   bool isDead()           const { return dead;   }
   Point getPosition()     const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   
   // Virtual methods for effects
   virtual double getAge();
   virtual void setAge(double rhs);
   virtual Point getEndPoint();
   virtual void  setEndPoint(Point rhs);
   
   LogicElement * getLogicElement()         { return pLogic;     }
   InterfaceElement * getInterfaceElement() { return pInterface; }
   
   // Setters
   void kill() { dead = true; }
   void setRadius(double rhs)           { radius = rhs; }
   void setPoints(int rhs)              { points = rhs; }
   void setStorageType(StorageType rhs) { type = rhs;   }
   
   // Position
   void setPosition(double x, double y) { pt.setX(x); pt.setY(y);   }
   void setPosition(Point rhs)          { pt = rhs;                 }
   
   // Velocity
   void setVelocity(double dx, double dy) { v.setDx(dx); v.setDy(dy); }
   void setVelocity(Velocity rhs)         { v = rhs;                  }
   
   // Set current logic and interface element we're working with
   void setLogicElement(LogicElement * p)         { pLogic = p;     }
   void setInterfaceElement(InterfaceElement * p) { pInterface = p; }
};

class StorageBird : public StorageElement {
protected:
   static Point dimensions;
   
public:
   // Setters
   void operator=(const Point    & rhs) { pt = rhs;    }
   void operator=(const Velocity & rhs) { v = rhs;     }
   
   // Getters
   int getPoints() { return points; }
   bool isOutOfBounds() const {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
};

class StorageBullet : public StorageElement {
protected:
   static Point dimensions;
   
public:
   int getValue() { return points; }
   bool isOutOfBounds() const {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
};

class StorageEffects : public StorageElement {
protected:
   double age;
   Point ptEnd;
   
public:
   double getAge() { return age; }
   void setAge(double rhs) { age = rhs; }
   
   Point getEndPoint()          { return ptEnd; }
   void  setEndPoint(Point rhs) { ptEnd = rhs;  }
};


#endif /* element_h */
