/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <gwolf@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:16:15 by gwolf             #+#    #+#             */
/*   Updated: 2023/02/12 23:55:05 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define DTOR 0.01745329252
#define EPSILON 0.001
#define PERSPECTIVE 0
#define ORTHOGRAPHIC 1
#define ABS(x) ((x) < 0 ? -(x) : (x))

/* Point in screen "window" space */
typedef struct {
   int h;
   int v;
} t_point;

/* Point in 3 space */
typedef struct {
   double x;
   double y;
   double z;
} t_vec;

/* Camera definition */
typedef struct {
   t_vec from;
   t_vec to;
   t_vec up;
   double angleh;
   double anglev;
   double zoom;
   double front;
   double back;
   short projection;
} t_camera;

/* Screen definition */
typedef struct {
   t_point center;
   t_point size;
} t_screen;


/* Prototypes */
int  Trans_Initialise(t_camera,t_screen);
void Trans_World2Eye(t_vec,t_vec *,t_camera);
int  Trans_ClipEye(t_vec *,t_vec *,t_camera);
void Trans_Eye2Norm(t_vec,t_vec *,t_camera);
int  Trans_ClipNorm(t_vec *,t_vec *);
void Trans_Norm2Screen(t_vec,t_point *,t_screen);
int  Trans_Point(t_vec,t_point *,t_screen,t_camera);
int  Trans_Line(t_vec,t_vec,t_point *,t_point *,t_screen,t_camera);
void Normalise(t_vec *);
void CrossProduct(t_vec,t_vec,t_vec *);
int  EqualVertex(t_vec,t_vec);

/* Static globals */
double tanthetah,tanthetav;
t_vec right,foward,up;

/*
   Trans_Init() initialises various variables and performs checks
   on some of the camera and screen parameters. It is left up to a
   particular implementation to handle the different error conditions.
   It should be called whenever the screen or camera variables change.
*/
int Trans_Initialise(t_camera camera, t_screen screen)
{
   const t_vec origin = {0.0, 0.0, 0.0};

   /* Is the camera position and view vector coincident ? */
   if (EqualVertex(camera.to, camera.from)) {
      return(false);
   }

   /* Is there a legal camera up vector ? */
   if (EqualVertex(camera.up, origin)) {
      return(false);
   }
   
   foward.x = camera.to.x - camera.from.x;
   foward.y = camera.to.y - camera.from.y;
   foward.z = camera.to.z - camera.from.z;
   Normalise(&foward);
   
   CrossProduct(camera.up, foward, &right);
   Normalise(&right);

   /* Are the up vector and view direction colinear */
   if (EqualVertex(right, origin)) {
      return(false);
   }
   
   CrossProduct(foward, right, &up);
   
   /* Do we have legal camera apertures ? */
   if (camera.angleh < EPSILON || camera.anglev < EPSILON) {
      return(false);
   }
   
   /* Calculate camera aperture statics, note: angles in degrees */
   tanthetah = tan(camera.angleh * DTOR / 2);
   tanthetav = tan(camera.anglev * DTOR / 2);
   
   /* Do we have a legal camera zoom ? */
   if (camera.zoom < EPSILON) {
      return(false);
   }
   
   /* Are the clipping planes legal ? */
   if (camera.front < 0 || camera.back < 0 || camera.back <= camera.front) {
      return(false);
   }
   
   return(true);
}

/*
   Take a point in world coordinates and transform it to
   a point in the eye coordinate system.
*/
void Trans_World2Eye(t_vec w, t_vec *e, t_camera camera)
{
   /* Translate world so that the camera is at the origin */
   w.x -= camera.from.x;
   w.y -= camera.from.y;
   w.z -= camera.from.z;

   /* Convert to eye coordinates using basis vectors */
   e->x = w.x * right.x + w.y * right.y + w.z * right.z;
   e->y = w.x * foward.x + w.y * foward.y + w.z * foward.z;
   e->z = w.x * up.x + w.y * up.y + w.z * up.z;
}

/*
   Clip a line segment in eye coordinates to the camera front
   and back clipping planes. Return FALSE if the line segment
   is entirely before or after the clipping planes.
*/
int Trans_ClipEye(t_vec *e1, t_vec *e2, t_camera camera)
{
   double mu;

   /* Is the vector totally in front of the front cutting plane ? */
   if (e1->y <= camera.front && e2->y <= camera.front)
      return(false);
   
   /* Is the vector totally behind the back cutting plane ? */
   if (e1->y >= camera.back && e2->y >= camera.back)
      return(false);
   
   /* Is the vector partly in front of the front cutting plane ? */
   if ((e1->y < camera.front && e2->y > camera.front) || 
      (e1->y > camera.front && e2->y < camera.front)) {
      mu = (camera.front - e1->y) / (e2->y - e1->y);
      if (e1->y < camera.front) {
         e1->x = e1->x + mu * (e2->x - e1->x);
         e1->z = e1->z + mu * (e2->z - e1->z);
         e1->y = camera.front;
      } else {
         e2->x = e1->x + mu * (e2->x - e1->x);
         e2->z = e1->z + mu * (e2->z - e1->z);
         e2->y = camera.front;
      }
   }

   /* Is the vector partly behind the back cutting plane ? */
   if ((e1->y < camera.back && e2->y > camera.back) || 
      (e1->y > camera.back && e2->y < camera.back)) {
      mu = (camera.back - e1->y) / (e2->y - e1->y);
      if (e1->y < camera.back) {
         e2->x = e1->x + mu * (e2->x - e1->x);
         e2->z = e1->z + mu * (e2->z - e1->z);
         e2->y = camera.back;
      } else {
         e1->x = e1->x + mu * (e2->x - e1->x);
         e1->z = e1->z + mu * (e2->z - e1->z);
         e1->y = camera.back;
      }
   }
   
   return(true);
}

/*
   Take a vector in eye coordinates and transform it into
   normalised coordinates for a perspective view. No normalisation
   is performed for an orthographic projection. Note that although
   the y component of the normalised vector is copied from the eye
   coordinate system, it is generally no longer needed. It can
   however still be used externally for vector sorting.
*/
void Trans_Eye2Norm(t_vec e, t_vec *n, t_camera camera)
{
	double d;
	
   if (camera.projection == PERSPECTIVE) {
   	d = camera.zoom / e.y;
      n->x = d * e.x / tanthetah;
      n->y = e.y;
      n->z = d * e.z / tanthetav;
   } else {
      n->x = camera.zoom * e.x / tanthetah;
      n->y = e.y;
      n->z = camera.zoom * e.z / tanthetav;
   }
}

/* 
   Clip a line segment to the normalised coordinate +- square.
   The y component is not touched.
*/
int Trans_ClipNorm(t_vec *n1, t_vec *n2)
{
   double mu;

   /* Is the line segment totally right of x = 1 ? */
   if (n1->x >= 1 && n2->x >= 1)
      return(false);

   /* Is the line segment totally left of x = -1 ? */
   if (n1->x <= -1 && n2->x <= -1)
      return(false);
      
   /* Does the vector cross x = 1 ? */
   if ((n1->x > 1 && n2->x < 1) || (n1->x < 1 && n2->x > 1)) {
      mu = (1 - n1->x) / (n2->x - n1->x);
      if (n1->x < 1) {
         n2->z = n1->z + mu * (n2->z - n1->z);
         n2->x = 1;
      } else {
         n1->z = n1->z + mu * (n2->z - n1->z);
         n1->x = 1;
      }
   }
      
   /* Does the vector cross x = -1 ? */
   if ((n1->x < -1 && n2->x > -1) || (n1->x > -1 && n2->x < -1)) {
      mu = (-1 - n1->x) / (n2->x - n1->x);
      if (n1->x > -1) {
         n2->z = n1->z + mu * (n2->z - n1->z);
         n2->x = -1;
      } else {
         n1->z = n1->z + mu * (n2->z - n1->z);
         n1->x = -1;
      }
   }

   /* Is the line segment totally above z = 1 ? */
   if (n1->z >= 1 && n2->z >= 1)
      return(false);

   /* Is the line segment totally below z = -1 ? */
   if (n1->z <= -1 && n2->z <= -1)
      return(false);
      
   /* Does the vector cross z = 1 ? */
   if ((n1->z > 1 && n2->z < 1) || (n1->z < 1 && n2->z > 1)) {
      mu = (1 - n1->z) / (n2->z - n1->z);
      if (n1->z < 1) {
         n2->x = n1->x + mu * (n2->x - n1->x);
         n2->z = 1;
      } else {
         n1->x = n1->x + mu * (n2->x - n1->x);
         n1->z = 1;
      }
   }
      
   /* Does the vector cross z = -1 ? */
   if ((n1->z < -1 && n2->z > -1) || (n1->z > -1 && n2->z < -1)) {
      mu = (-1 - n1->z) / (n2->z - n1->z);
      if (n1->z > -1) {
         n2->x = n1->x + mu * (n2->x - n1->x);
         n2->z = -1;
      } else {
         n1->x = n1->x + mu * (n2->x - n1->x);
         n1->z = -1;
      }
   }
   
   return(true);
}

/*
   Take a vector in normalised Coordinates and transform it into
   screen coordinates.
*/
void Trans_Norm2Screen(t_vec norm, t_point *projected, t_screen screen)
{
   projected->h = screen.center.h - screen.size.h * norm.x / 2;
   projected->v = screen.center.v - screen.size.v * norm.z / 2;
}

/* 
   Transform a point from world to screen coordinates. Return TRUE
   if the point is visible, the point in screen coordinates is p.
   Assumes Trans_Initialise() has been called
*/
int Trans_Point(t_vec w, t_point *p, t_screen screen, t_camera camera)
{
   t_vec e;
   t_vec n;
   
   Trans_World2Eye(w, &e, camera);
   if (e.y >= camera.front && e.y <= camera.back) {
      Trans_Eye2Norm(e, &n, camera);
      if (n.x >= -1 && n.x <= 1 && n.z >= -1 && n.z <= 1) {
         Trans_Norm2Screen(n,p,screen);
         return(true);
      }
   }
   return(false);
}

/* 
   Transform and appropriately clip a line segment from
   world to screen coordinates. Return TRUE if something
   is visible and needs to be drawn, namely a line between
   screen coordinates p1 and p2.
   Assumes Trans_Initialise() has been called
*/
int Trans_Line(t_vec w1, t_vec w2,t_point *p1,t_point *p2,t_screen screen, t_camera camera)
{
   t_vec e1;
   t_vec e2;
   t_vec n1;
   t_vec n2;
   
   Trans_World2Eye(w1,&e1,camera);
   Trans_World2Eye(w2,&e2,camera);
   if (Trans_ClipEye(&e1,&e2,camera)) {
      Trans_Eye2Norm(e1,&n1,camera);
      Trans_Eye2Norm(e2,&n2,camera);
      if (Trans_ClipNorm(&n1,&n2)) {
         Trans_Norm2Screen(n1,p1,screen);
         Trans_Norm2Screen(n2,p2,screen);
         return(true);
      }
   }
   return(false);
}

/*
   Normalise a vector
*/
void Normalise(t_vec *v)
{
   double length;
	
   length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
   v->x /= length;
   v->y /= length;
   v->z /= length;
}

/*
   Cross product of two vectors, p3 = p1 x p2
*/
void CrossProduct(t_vec p1, t_vec p2, t_vec *p3)
{
   p3->x = p1.y * p2.z - p1.z * p2.y;
   p3->y = p1.z * p2.x - p1.x * p2.z;
   p3->z = p1.x * p2.y - p1.y * p2.x;
}

/*
   Test for coincidence of two vectors, TRUE if coincident
*/
int EqualVertex(t_vec p1, t_vec p2)
{
   if (fabs(p1.x - p2.x) > EPSILON)
      return(false);
   if (fabs(p1.y - p2.y) > EPSILON)
      return(false);
   if (fabs(p1.z - p2.z) > EPSILON)
      return(false);
   return(true);
}

