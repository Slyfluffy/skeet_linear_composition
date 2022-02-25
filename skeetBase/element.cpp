//
//  element.cpp
//  Lab03
//
//  Created by Journey Curtis on 2/24/22.
//

#include "element.h"
#include <cassert>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Point& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point& begin, const Point& end,
              double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
void drawDot(const Point& point, double radius,
             double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;

   // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 ****************************************************************/
int random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}

void InterfacePellet::draw(StorageElement * p) {
   if (!p->isDead())
      drawDot(p->getPosition(), 3.0, 1.0, 1.0, 0.0);
}

void InterfaceMissile::draw(StorageElement * p) {
   if (!p->isDead()) {
      Point ptNext(p->getPosition());
      ptNext.add(p->getVelocity());
      drawLine(p->getPosition(), ptNext, 1.0, 1.0, 0.0);
      drawDot(p->getPosition(), 3.0, 1.0, 1.0, 1.0);
   }
}

void InterfaceBomb::draw(StorageElement * p) {
   if (!p->isDead())
   {
       // Bomb actually has a gradient to cut out the harsh edges
       drawDot(p->getPosition(), p->getRadius() + 2.0, 0.50, 0.50, 0.00);
       drawDot(p->getPosition(), p->getRadius() + 1.0, 0.75, 0.75, 0.00);
       drawDot(p->getPosition(), p->getRadius() + 0.0, 0.87, 0.87, 0.00);
       drawDot(p->getPosition(), p->getRadius() - 1.0, 1.00, 1.00, 0.00);
   }
}

void InterfaceShrapnel::draw(StorageElement * p) {
   if (!p->isDead())
      drawDot(p->getPosition(), p->getRadius(), 1.0, 1.0, 0.0);
}

void InterfaceFragment::draw(StorageElement * p) {
   // Do nothing if we are already dead
   if (p->isDead())
       return;
   
   p->setAge(random(0.4, 1.0));
   double size = random(1.0, 2.5);
   
   // Draw this sucker
   glBegin(GL_TRIANGLE_FAN);
   
   // the color is a function of age - fading to black
   glColor3f((GLfloat)p->getAge(), (GLfloat)p->getAge(), (GLfloat)p->getAge());
   
   // draw the fragment
   glVertex2f((GLfloat)(p->getPosition().getX() - size), (GLfloat)(p->getPosition().getY() - size));
   glVertex2f((GLfloat)(p->getPosition().getX() + size), (GLfloat)(p->getPosition().getY() - size));
   glVertex2f((GLfloat)(p->getPosition().getX() + size), (GLfloat)(p->getPosition().getY() + size));
   glVertex2f((GLfloat)(p->getPosition().getX() - size), (GLfloat)(p->getPosition().getY() + size));
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void InterfaceExhaust::draw(StorageElement * p) {
   // Do nothing if we are already dead
   if (p->isDead())
       return;
   
   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)p->getAge(), (GLfloat)p->getAge(), (GLfloat)p->getAge());

   // Draw the actual line
   glVertex2f((GLfloat)p->getPosition().getX(), (GLfloat)p->getPosition().getY());
   glVertex2f((GLfloat)p->getEndPoint().getX(), (GLfloat)p->getEndPoint().getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void InterfaceStreek::draw(StorageElement * p) {
   // Do nothing if we are already dead
   if (p->isDead())
       return;
   
   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)p->getAge(), (GLfloat)p->getAge(), (GLfloat)p->getAge());

   // Draw the actual line
   glVertex2f((GLfloat)p->getPosition().getX(), (GLfloat)p->getPosition().getY());
   glVertex2f((GLfloat)p->getEndPoint().getX(), (GLfloat)p->getEndPoint().getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void drawDisk(const Point& center, double radius,
              double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Point pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Point pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}

void InterfaceStandard::draw(StorageElement * p) {
   if (!p->isDead())
   {
      drawDisk(p->getPosition(), p->getRadius() - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(p->getPosition(), p->getRadius() - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

void InterfaceFloater::draw(StorageElement * p) {
   if (!p->isDead())
   {
      drawDisk(p->getPosition(), p->getRadius() - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(p->getPosition(), p->getRadius() - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

void InterfaceSinker::draw(StorageElement * p) {
   if (!p->isDead())
   {
      drawDisk(p->getPosition(), p->getRadius() - 0.0, 0.0, 0.0, 0.8);
      drawDisk(p->getPosition(), p->getRadius() - 4.0, 0.0, 0.0, 0.0);
   }
}

void InterfaceCrazy::draw(StorageElement * p) {
   if (!p->isDead())
   {
      drawDisk(p->getPosition(), p->getRadius() * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(p->getPosition(), p->getRadius() * 0.8, 0.2, 0.2, 1.0);
      drawDisk(p->getPosition(), p->getRadius() * 0.6, 0.4, 0.4, 1.0);
      drawDisk(p->getPosition(), p->getRadius() * 0.4, 0.6, 0.6, 1.0);
      drawDisk(p->getPosition(), p->getRadius() * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

/*
 * LOGICELEMENTS
 */

void LogicPellet::advance(StorageElement * p) {
   // inertia
   Point newP = p->getPosition();
   newP.add(p->getVelocity());
   p->setPosition(newP);

   // out of bounds checker
   if (p->isOutOfBounds())
      p->kill();
}

void LogicMissile::advance(StorageElement * p) {
   // kill if it has been around too long
   StorageEffect s;
   s.setAge(.5);
   s.setPosition(p->getPosition());
   
   Velocity v = p->getVelocity() * -1.0;
   
   Point endP = p->getPosition();
   endP += v;
   s.setEndPoint(endP);

   // inertia
   Point newP = p->getPosition();
   newP.add(p->getVelocity());
   p->setPosition(newP);

   // out of bounds checker
   if (p->isOutOfBounds())
      p->kill();
}

void LogicMissile::turn(StorageElement * p) {
   
}

void LogicBomb::advance(StorageElement * p) {
   
}

void LogicShrapnel::advance(StorageElement * p) {
   
}

void LogicFragment::advance(StorageElement * p) {
   
}

void LogicExhaust::advance(StorageElement * p) {
   p->setAge(p->getAge() - .025);
}

void LogicStreek::advance(StorageElement * p) {
   
}

void LogicStandard::advance(StorageElement * p) {
   
}

void LogicFloater::advance(StorageElement * p) {
   
}

void LogicSinker::advance(StorageElement * p) {
   
}

void LogicCrazy::advance(StorageElement * p) {
   
}
