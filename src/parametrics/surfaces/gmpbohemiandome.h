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



/*! \file gmpbohemiandome.h
 *
 *  Interface for the PBohemianDome class.
 */

#ifndef __gmPBOHEMIANDOME_H__
#define __gmPBOHEMIANDOME_H__


#include "../gmpsurf.h"

namespace GMlib {

  template <typename T>
  class PBohemianDome : public PSurf<T> {
  public:
    PBohemianDome( T radius = T(5), T domewidth=T(2), T height=T(2) );
    PBohemianDome( const PBohemianDome<T>& copy );
    virtual ~PBohemianDome();


  protected:
    T                 _r; // radius
    T                 _w; // domewidth
    T                 _h; // height

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    std::string       getIdentity() const;
    T                 getStartPU();
    T                 getStartPV();
    virtual void      init();
    bool              isClosedU() const;
    bool              isClosedV() const;

  }; // END class PBohemianDome


} // END namespace GMlib

// Include PBohemianDome class function implementations
#include "gmpbohemiandome.c"



#endif // __gmPBOHEMIANDOME_H__
