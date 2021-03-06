/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR (c) 1990 - 2016                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/**************************************************************************************
 * COORD_CONV.C: Routines to transform between coordinate systems
 */

#include <stdio.h>
#include <math.h>
#ifdef IRIX5
#define M_PI            3.14159265358979323846
#endif
  
/*#define EARTH_RAD 6380.12 */
/*#define EARTH_RAD 6371.0  */
 
#define EARTH_RAD 6378.16    /* @ equator- From Handbook of Chemistry & Physics */
#define DEGREES_PER_RADIAN (180.0/M_PI)
#define RADIANS_PER_DEGREE (M_PI/180.0)

/************************************************************************************
 * xy_to_latlong.c - convert from km to lat longs 
 *    From G. Wiener April 1990,  NCAR. 
 * Given the latitude and longitude of a point in degrees as well as the
 * x,y coordinates of another point in kilometers, determine the latitude
 * and longitude of the other point.
 */
xy_to_latlong(center_lat, center_long, x, y, lat, lon)
     double center_lat;
     double center_long;
     double x;
     double y;
     double *lat;    /* RETURN */
     double *lon;    /* RETURN */
     
{
  double diff_long, diff_lat;
  double theta;


  /* the length of a circular segment is r * theta */
  diff_lat = -y/EARTH_RAD;
  *lat = center_lat - diff_lat * DEGREES_PER_RADIAN;
  theta = *lat * RADIANS_PER_DEGREE;

  diff_long = x/(EARTH_RAD * cos(theta));
  *lon = center_long + diff_long * DEGREES_PER_RADIAN;
}
/************************************************************************************
 * latlong_to_xy - a routine to convert from lat-longs to cartesian Km based coords
 *    From G. Wiener April 1990,  NCAR. 
 * Given the latitude and longitude of a center point in degrees as well
 * as the latitude and longitude of a specified point in degrees
 * calculate the x, y kilometer coordinates of the specified point.
 *
 * center point: center_lat, center_long
 * specified point: other_lat, other_long
 * specified point in km: px, py
 */
latlong_to_xy(center_lat, center_long, other_lat, other_long, px, py)
     double center_lat;
     double center_long;
     double other_lat;
     double other_long;
     double *px;        /* RETURN */
     double *py;        /* RETURN */
     
{
  double cos_other_lat, diff_long, diff_lat;
  double theta;
  
  /*
   * In this case we use the latitude of the specified point in
   * calculating its km coordinates from a center point.
   * Another algorithm can be constructed using the latitude of the
   * center point instead.
   */
  theta = other_lat;
  
  /* convert to radians */
  theta = theta * RADIANS_PER_DEGREE;
  
  /* find the difference of the longitudes */
  diff_long = (center_long - other_long) * RADIANS_PER_DEGREE;
  
  /* find the difference of the latitudes */
  diff_lat = (center_lat - other_lat) * RADIANS_PER_DEGREE;
  
  /* the length of the circular segment is r * theta */
  *py = EARTH_RAD * (-diff_lat); /* y direction */
  
  /* the radius at center_lat latitude is EARTH_RAD * cos_center_lat */
  cos_other_lat = cos((double)theta);
  *px = -(EARTH_RAD * diff_long * cos_other_lat); /* x direction */
}

#ifndef LINT
static char RCS_id[] = "$Id: coord_conv.c,v 1.4 2016/03/07 18:28:26 dixon Exp $";
#endif /* not LINT */
