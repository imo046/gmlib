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



#ifndef GM_PARAMETRICS_CURVES_PBUTTERFLY_H
#define GM_PARAMETRICS_CURVES_PBUTTERFLY_H


#include "../gmpcurve.h"


namespace GMlib {


  template <typename T>
  class PButterfly : public PCurve<T,3> {
    GM_SCENEOBJECT(PButterfly)
  public:
    PButterfly( T size = T(5) );
    PButterfly( const PButterfly<T>& copy );

    virtual ~PButterfly();

    //****************************************
    //****** Virtual public functions   ******
    //****************************************

    // from PCurve
    bool                isClosed() const override;

  protected:
    // Virtual function from PCurve that has to be implemented locally
    void                eval(T t, int d, bool l) override;
    T                   getStartP() const override;
    T                   getEndP()   const override;


    // Protected data for the curve
    T             _size;

  }; // END class PButterfly

} // END namepace GMlib

// Include PButterfly class function implementations
#include "gmpbutterfly.c"


#endif // GM_PARAMETRICS_CURVES_PBUTTERFLY_H

