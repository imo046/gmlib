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



/*! \file gmtrianglefacetsdefaultvisualizer.h
 *
 *  Interface for the TriangleFacetsDefaultVisualizer class.
 */

#ifndef __gmTRIANGLEFACETSDEFAULTVISUALIZER_H__
#define __gmTRIANGLEFACETSDEFAULTVISUALIZER_H__


#include "gmtrianglefacetsvisualizer.h"


namespace GMlib {

  template <typename T>
  class TriangleFacetsDefaultVisualizer : public TriangleFacetsVisualizer<T> {
  public:
    TriangleFacetsDefaultVisualizer();
    ~TriangleFacetsDefaultVisualizer();
    void          display( Camera * cam );
    std::string   getIdentity() const;
    virtual void  replot();
    void          select( Camera * cam, const Color& name );

  protected:
    GLuint        _vbo;
    GLuint        _ibo;

    GLProgram     _dprog;
    GLProgram     _sprog;


  }; // END class TriangleFacetsDefaultVisualizer

} // END namespace GMlib

// Include TriangleFacetsDefaultVisualizer class function implementations
#include "gmtrianglefacetsdefaultvisualizer.c"

#endif // __gmTRIANGLEFACETSDEFAULTVISUALIZER_H__