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



/*! \file gmPCurveDefaultVisualizer.h
 *
 *  Interface for the PCurveDefaultVisualizer class.
 *
 *  \date   2011-01-17
 */


#ifndef __gmPCURVEDEFAULTVISUALIZER_H__
#define __gmPCURVEDEFAULTVISUALIZER_H__

#include "gmPCurveVisualizer.h"


namespace GMlib {

  template <typename T>
  class PCurveDefaultVisualizer : public PCurveVisualizer<T> {
  public:
    PCurveDefaultVisualizer();
    ~PCurveDefaultVisualizer();

    void          display( Camera* cam );
    std::string   getIdentity() const;
    virtual void  replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void          select( Camera* cam, const Color& name = Color() );

  protected:
    GLuint        _vbo_v;
    int           _no_vertices;

    GLProgram     _display;
    GLProgram     _select;

  }; // END class PCurveDefaultVisualizer

} // END namespace GMlib

// Include PCurveDefaultVisualizer class function implementations
#include "gmPCurveDefaultVisualizer.c"

#endif // __gmPCURVEDEFAULTVISUALIZER_H__