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




#ifndef GM_PARAMETRICS_SURFACE_PHERMITESURF_H
#define GM_PARAMETRICS_SURFACE_PHERMITESURF_H


// local
#include "../gmpsurf.h"


namespace GMlib {


  /*! \class PHermiteSurf<T> gmPHermiteSurf.h <gmPHermiteSurf>
   *  \brief A 3th degree polynomial based tensor product surface
   *
   *	A template based surfase where the template in general might be float or double.
   *	The input must be information connected to the four corners of the surface,
   *	the position, the two partial derivatives and the mix dreivatives in each corner.
   *
   *	The resulting surface is interpolating the input information.
   *	This type of interpolation is called Hermite interpolation.
   */
  template <typename T>
  class PHermiteSurf : public PSurf<T,3> {
    GM_SCENEOBJECT(PHermiteSurf)
  public:
    PHermiteSurf( const DMatrix<Vector<T,3> >& m);
    PHermiteSurf( const DMatrix<Vector<T,3> >& c1, const DMatrix<Vector<T,3> >& c2,
                  const DMatrix<Vector<T,3> >& c3, const DMatrix<Vector<T,3> >& c4 );
    PHermiteSurf( const PHermiteSurf<T>& copy );

    virtual ~PHermiteSurf();

    //***************************************
    //****** Virtual public functions  ******
    //***************************************

    // from PSurf
    bool          isClosedU()  const override;
    bool          isClosedV()  const override;

  protected:
    // Virtual function from PSurf that has to be implemented locally
    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true ) override;
    T             getStartPU() const override;
    T             getEndPU()   const override;
    T             getStartPV() const override;
    T             getEndPV()   const override;


    // Help function to ensure consistent initialization
    virtual void      init();

    // Protected data for the surface
    DMatrix< Vector< T,3 > > _m;

  }; // END class PHermiteSurf


} // END namepace GMlib

// Include PHermiteSurf class function implementations
#include "gmphermitesurf.c"

#endif // GM_PARAMETRICS_SURFACE_PHERMITESURF_H


