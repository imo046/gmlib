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



/*! \file gmPBezierSurf.h
 *
 *  Interface for the gmPBezierSurf class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmPBEZIERSURF_H__
#define __gmPBEZIERSURF_H__


// GMlib includes+
#include "gmPSurf.h"
#include "gmSelector.h"
#include "gmSelectorGrid.h"


namespace GMlib {


  template <typename T>
  class PBezierSurf : public PSurf<T> {
  public:
    PBezierSurf( const DMatrix< Vector<T,3> >& cp );
    PBezierSurf( const DMatrix< Vector<T,3> >& cp, T u_s, T u, T u_e, T v_s, T v, T v_e  );
    PBezierSurf( const PBezierSurf<T>& dpbs );
    virtual ~PBezierSurf();

    virtual void                edit( int selector );
    DMatrix< Vector<T,3> >&     getControlPoints();
    int                         getDegreeU() const;
    int                         getDegreeV() const;
    string                      getIdentity() const;
    T                           getLocalMapping( T t, T ts, T tt, T te );
    virtual void                hideSelectors();
    bool                        isClosedU() const;
    bool                        isClosedV() const;
    bool                        isSelectorsVisible() const;
    void                        setClosed( bool closed_u, bool closed_v );
    void                        setControlPoints( const DMatrix< Vector<T,3> >& cp );
    void                        setResampleMode( GM_RESAMPLE_MODE mode );
    void                        setScale( T du, T dv );
    virtual void                showSelectors( bool grid = false, const GLColor& _selector_color = GMcolor::DarkBlue, const GLColor& grid_color = GMcolor::LightGreen );
    void                        updateCoeffs( const Vector<T,3>& d );


  protected:
    DMatrix< Vector<T,3> >      _c;
    T                           _su;
    T                           _sv;
    DMatrix< DMatrix< T > >     _u;
    DMatrix< DMatrix< T > >     _v;
    bool                        _cu;
    bool                        _cv;

    GM_RESAMPLE_MODE            _resamp_mode;
    bool                        _pre_eval;

    bool                        _selectors;
    SelectorGrid<T,3>*			    _sg;
    DMatrix< Selector<T,3>* >   _s;
    bool                        _c_moved;

    void	                      eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    T                           getEndPU();
    T                           getEndPV();
    T                           getStartPU();
    T                           getStartPV();
    virtual void                init();
    void                        resample( DMatrix<DMatrix <Vector<T,3> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    void                        resampleInline( DMatrix< DMatrix< Vector<T,3> > >& p, int m1, int m2, T du, T dv );
    void                        resamplePreEval( DMatrix< DMatrix< Vector<T,3> > >& p, int m1, int m2, T du, T dv );

  }; // END class PBezierSurf




} // END namepace GMlib

// Include PBezierSurf class function implementations
#include "gmPBezierSurf.c"


#endif // __gmPBEZIERSURF_H__


