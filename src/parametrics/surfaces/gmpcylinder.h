/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmpcylinder.h
 *
 *  Interface for the PCylinder class.
 */

#ifndef __gmPCYLINDER_H__
#define __gmPCYLINDER_H__


#include "../gmpsurf.h"



namespace GMlib {

  template <typename T>
  class PCylinder : public PSurf<T,3> {
    GM_SCENEOBJECT(PCylinder)
  public:
    PCylinder( T rx = 4, T ry = 4, T h = 2 );
    PCylinder( const PCylinder<T>& copy );
    virtual ~PCylinder();

    T             getHeight() const;
    T             getRadiusX() const;
    T             getRadiusY() const;
    bool          isClosedU() const;
    bool          isClosedV() const;
    void          setConstants( T rx, T ry, T h );

  protected:
    T             _rx;
    T             _ry;
    T             _h;

    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T             getEndPV();
    T             getEndPU();
    T             getStartPU();
    T             getStartPV();

  }; // END class PCylinder


} // END namespace GMlib

// Include PCylinder class function implementations
#include "gmpcylinder.c"



#endif // __gmPCYLINDER_H__


