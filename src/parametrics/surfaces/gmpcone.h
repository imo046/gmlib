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



/*! \file gmpcone.h
 *
 *  Interface for the PCone class.
 */

#ifndef __gmPCONE_H__
#define __gmPCONE_H__

#include "../gmpsurf.h"



namespace GMlib {

  template <typename T>
  class PCone : public PSurf<T,3> {
    GM_SCENEOBJECT(PCone)
  public:
    PCone( T radius = T(3), T height = T(5) );
    PCone( const PCone<T>& copy );
    virtual ~PCone();


  protected:
    T                 _r;
    T                 _h;

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PCone


} // END namespace GMlib

// Include PCone class function implementations
#include "gmpcone.c"



#endif // __gmPCONE_H__

