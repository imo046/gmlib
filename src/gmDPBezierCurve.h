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



/*! \file gmDPBezierCurve.h
 *
 *  Interface for the gmDPBezierCurve class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmDPBEZIERCURVE_H__
#define __gmDPBEZIERCURVE_H__


// GMlib includes+
#include "gmDCurve.h"
#include "gmPBezierCurve.h"
#include "gmSelectorGrid.h"


namespace GMlib {


  template <typename T>
  class DPBezierCurve : public DCurve<T> {
  public:
    DPBezierCurve( const DVector< Vector<T,3> >& cp );
    DPBezierCurve( const DVector< Vector<T,3> >& cp, T s, T t, T e );
    DPBezierCurve( const DPBezierCurve<T>& copy );
    DPBezierCurve( const PBezierCurve<T,3>& copy );
    DPBezierCurve( PBezierCurve<T,3>* copy );
    virtual ~DPBezierCurve();

    void                          edit( int selector );
    virtual PBezierCurve<T,3>*    getPBezierCurve();
    virtual void                  hideSelectors();
    void                          rotate( Angle a, const Vector<float,3>& rot_axel );
    void                          rotate( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d );
    void                          rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    void                          rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                  showSelectors( bool grid = false, const GLColor& _selector_color = GMcolor::DarkBlue, const GLColor& grid_color = GMcolor::LightGreen );
    void                          translate( const Vector<float,3>& trans_vector );
    void                          translateGlobal( const Vector<float,3>& trans_vector );

  protected:
    bool                          _selectors;
    SelectorGrid<T,3>*			      _sg;
    DVector< Selector<T,3>* >     _s;
    PBezierCurve<T,3>             *_l_ref;

    string                        getIdentity() const;
    virtual void                  init();
    void                          localDisplay();
  };




} // END namepace GMlib

// Include DPBezierCurve class function implementations
#include "gmDPBezierCurve.c"


#endif // __gmDPBEZIERCURVE_H__
