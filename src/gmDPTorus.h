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



/*! \file gmDPTorus.h
 *
 *  Interface for the gmDPTorus class.
 *
 *  \date   2008-11-26
 */

#ifndef __gmDPTORUS_H__
#define __gmDPTORUS_H__

// STL
#include <string>

// GMlib
#include "gmDSurf.h"
#include "gmPTorus.h"


namespace GMlib {

  template <typename T>
  class DPTorus : public DSurf<T> {
  public:
    DPTorus( T wheelrad=T(3), T tuberad1=T(1), T tuberad2=T(1) );
    DPTorus( const DPTorus<T>& pshere );
//    DPTorus( const PTorus<T,3>& pshere );
//    DPTorus( PTorus<T,3>* copy );
    virtual ~DPTorus();

//    virtual PTorus<T,3>*    getPTorus();

  protected:
//    PTorus<T,3>             *_l_ref;

    std::string             getIdentity() const;
    virtual void            init();



  //////////////////////// PTorus !!!!!!!!!!!!!! PTorus ////////////////////////
  //////////////////////// PTorus !!!!!!!!!!!!!! PTorus ////////////////////////
  //////////////////////// PTorus !!!!!!!!!!!!!! PTorus ////////////////////////
  //////////////////////// PTorus !!!!!!!!!!!!!! PTorus ////////////////////////


  public:
		bool          isClosedU() const;
		bool          isClosedV() const;


	protected:
		T             _a;		//Wheelradius
		T             _b;		//Tuberadius1
		T             _c;		//Tuberadius2

		void          eval(T u, T v, int d1, int d2, bool lu, bool lv );
		T             getEndPU();
		T             getEndPV();
		T             getStartPU();
		T             getStartPV();
  };


} // END namespace GMlib


// Include DPTorus class function implementations
#include "gmDPTorus.c"


#endif // __gmDPTORUS_H__


