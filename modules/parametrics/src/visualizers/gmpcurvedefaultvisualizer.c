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



/*! \file gmpcurvedefaultvisualizer.c
 *
 *  Implementation of the PCurveDefaultVisualizer template class.
 */


#include "gmpcurvedefaultvisualizer.h"

namespace GMlib {

  template <typename T, int n>
  PCurveDefaultVisualizer<T,n>::PCurveDefaultVisualizer()
    : _no_vertices(0), _line_width(3.0f) {

    _prog.acquire("color");
    _vbo.create();
  }

  template <typename T, int n>
  PCurveDefaultVisualizer<T,n>::PCurveDefaultVisualizer(const PCurveDefaultVisualizer<T,n>& copy)
    : PCurveVisualizer<T,n>(copy),
      _no_vertices(0), _line_width(3.0f) {

    _prog.acquire("color");
    _vbo.create();
  }

  template <typename T, int n>
  inline
  void PCurveDefaultVisualizer<T,n>::render(const SceneObject* obj, const Camera *cam) const {

    const HqMatrix<float,3> &mvpmat = obj->getModelViewProjectionMatrix(cam);

    // GL States
    glLineWidth( _line_width );

    _prog.bind(); {

      // Model view and projection matrices
      _prog.setUniform( "u_mvpmat", mvpmat );
      _prog.setUniform( "u_color", obj->getColor() );

      // Vertex attribute location
      GL::AttributeLocation vert_loc = _prog.getAttributeLocation( "in_vertex" );

      // Bind and draw
      _vbo.bind();
      _vbo.enable( vert_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertex), reinterpret_cast<const GLvoid*>(0x0) );
      glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );
      _vbo.disable( vert_loc );
      _vbo.unbind();

    } _prog.unbind();
  }

  template <typename T, int n>
  inline
  void PCurveDefaultVisualizer<T,n>::replot( const DVector< DVector< Vector<T, n> > >& p,
                                             int /*m*/, int /*d*/, bool /*closed*/ ) {

    PCurveVisualizer<T,n>::fillStandardVBO( _vbo, p, _no_vertices );
  }

  template <typename T, int n>
  inline
  void PCurveDefaultVisualizer<T,n>::renderGeometry( const GL::Program &prog, const SceneObject* obj, const Camera* cam ) const {

    prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(cam) );
    GL::AttributeLocation vertice_loc = prog.getAttributeLocation( "in_vertex" );

    _vbo.bind();
    _vbo.enable( vertice_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GL::GLVertex), reinterpret_cast<const GLvoid*>(0x0) );
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );
    _vbo.disable( vertice_loc );
    _vbo.unbind();
  }


} // END namespace GMlib
