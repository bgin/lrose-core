// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
/**
 * @file CloudGaps.cc
 */
#include "CloudGaps.hh"
#include "CloudGap.hh"
#include "CloudEdge.hh"
#include "ClumpAssociate.hh"

using std::vector;
using std::string;

/*----------------------------------------------------------------*/
// x0,x1 = run bounds,
// y = beam
// v0 = value of clump
// depth = param
//
static void _add_edges(const Grid2d &clumps, const int x0, const int x1,
		       const int y, const int nx, const double v0,
		       const int depth, vector<CloudEdge> &edges)
{
  int length = x1 - x0 + 1;
  
  int x00 = -1;
  int x01 = -1;

  // create 'outside' points below, from just before x0 to a maximum depth
  for (int x=x0-1; x>=x0-depth && x >= 0; --x)
  {
    double v;
    if (clumps.getValue(x, y, v))
      // part of another clump, meaning back 'in' after being 'out'
      break;

    // still 'out', adjust range by one
    x00 = x;
    if (x01 == -1)
      x01 = x;
  }

  // create 'outside' points above, from just after x1 to a maximum depth
  int x10 = -1;
  int x11 = -1;
  for (int x=x1+1; x<x1+depth && x < nx; ++x)
  {
    double v;
    if (clumps.getValue(x, y, v))
      // part of another clump, meaning back 'in' .. done
      break;
    // adjust range by 1
    x11 = x;
    if (x10 == -1)
      x10 = x;
  }

  // now build the two CloudEdge objects and save
  int w;
  if (length > depth)
    w = depth;
  else
    w = length;

  if (x00 != -1)
  {
    CloudEdge p(y, x0, x0+w-1, x00, x01, v0, true);
    p.log("Adding");
    edges.push_back(p);
  }
  else
    LOG(DEBUG_VERBOSE) << "Skipping";
  if (x10 != -1)
  {
    CloudEdge p(y, x1-w+1, x1, x10, x11, v0, false);
    p.log("Adding");
    edges.push_back(p);
  }
  else
    LOG(DEBUG_VERBOSE) << "Skipping";
}

/*----------------------------------------------------------------*/
CloudGaps::CloudGaps(void)
{
}

/*----------------------------------------------------------------*/
CloudGaps::~CloudGaps()
{
}

/*----------------------------------------------------------------*/
void CloudGaps::print(void) const
{
  vector<CloudGap>::const_iterator i;
  for (i=_gap.begin(); i!=_gap.end(); ++i)
  {
    i->print();
  }
}

/*----------------------------------------------------------------*/
Grid2d CloudGaps::edge(const int nx, const int ny) const
{
  Grid2d ret("edge", nx, ny, 0);
  vector<CloudGap>::const_iterator i;
  for (i=_gap.begin(); i!=_gap.end(); ++i)
    i->to_grid(ret);
  return ret;
}

/*----------------------------------------------------------------*/
Grid2d CloudGaps::outside(const int nx, const int ny) const
{
  Grid2d ret("outside", nx, ny, 0);
  vector<CloudGap>::const_iterator i;
  for (i=_gap.begin(); i!=_gap.end(); ++i)
    i->to_outside_grid(ret);
  return ret;
}

/*----------------------------------------------------------------*/
void CloudGaps::filter(int const min_gridpt)
{
  vector<CloudGap>::iterator i;
  for (i=_gap.begin(); i!=_gap.end(); )
  {
    if (i->npt_between() >= min_gridpt)
      ++i;
    else
      i = _gap.erase(i);
  }
}

/*----------------------------------------------------------------*/
void CloudGaps::filter(const Grid2d &pid_clumps, ClumpAssociate &ca,
		       const int max_gridpt)
{
  vector<CloudGap>::iterator i;
  for (i=_gap.begin(); i!=_gap.end(); )
  {
    int npt0, npt1;
    ca.penetration(*i, pid_clumps, npt0, npt1);
    if (npt0 > max_gridpt || npt1 > max_gridpt)
    {
      vector<string> debug = ca.get_penetration_report();
      if (npt0 > max_gridpt)
	LOG(DEBUG_VERBOSE) << "FILTER penetration in npt=" << npt0 << " "
			   << debug[0];
      if (npt1 > max_gridpt)
	LOG(DEBUG_VERBOSE) << "FILTER penetration out npt=" << npt1 << " "
			   << debug[1];
      i = _gap.erase(i);
    }
    else
      ++i;
  }
}

/*----------------------------------------------------------------*/
void CloudGaps::add_gaps(const int y, const int nx, const Grid2d &clumps,
			 const int depth)
{
  // start outside
  bool inside = false;
  int in0 = 0, in1 = 0;
  vector<CloudEdge> edges;
  double v0 = 0.0;
  for (int x=0; x<nx; ++x)
  {
    double v = 0.0;
    if (clumps.getValue(x,  y, v))
    {
      if (!inside)
      {
	// start a 'cloud' run at x with value
	inside = true;
	in0 = in1 = x;
	v0 = v;
      }
      else
      {
	// continue the run
	if (v0 != v)
	  LOG(WARNING) << "clumping not right";
	in1 = x;
      }
    }
    else
    {
      if (inside)
      {
	// finish the cloud run, adding to edge state
	inside = false;
	_add_edges(clumps, in0, in1, y, nx, v0, depth, edges);
      }
    }
  }
  if (edges.size() == 0)
    return;

  // the 0th gap is assumed going back to the radar
  CloudGap e(edges[0]);
  _gap.push_back(e);

  // now build up all the gaps (pairs) and add
  for (int i=2; i<(int)edges.size(); i+=2)
  {
    CloudGap e(edges[i-1], edges[i]);
    _gap.push_back(e);
  }
}

