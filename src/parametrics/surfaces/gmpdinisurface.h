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



/*! \file gmpdinisurface.h
 *
 *  Interface for the PDiniSurface class.
 */

#ifndef __gmPDINISURFACE_H__
#define __gmPDINISURFACE_H__

#include "../gmpsurf.h"


namespace GMlib {

  template <typename T>
  class PDiniSurface : public PSurf<T> {
  public:
    PDiniSurface( T radius = T(1), T dist_turns = T(0.1) );
    PDiniSurface( const PDiniSurface<T>& copy );
    virtual ~PDiniSurface();


  protected:
    T                 _r1; // Radius
    T                 _r2; // Distance between turns

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    std::string       getIdentity() const;
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PDiniSurface


} // END namespace GMlib

// Include PDiniSurface class function implementations
#include "gmpdinisurface.c"



#endif // __gmPDINISURFACE_H__
