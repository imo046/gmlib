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



/*! \file gmpcurvevisualizer.c
 *
 *  Implementation of the PCurveVisualizer template class.
 */


// gmlib
#include <opengl/gmopengl.h>
#include <opengl/glsl/gmglprogram.h>
#include <opengl/glsl/gmglshadermanager.h>

namespace GMlib {

  template <typename T, int n>
  PCurveVisualizer<T,n>::PCurveVisualizer() {

    _curve = 0x0;
    setRenderProgram( GL::GLProgram("color") );
  }

  template <typename T, int n>
  PCurveVisualizer<T,n>::~PCurveVisualizer() {}

  template <typename T, int n>
  void PCurveVisualizer<T,n>::fillStandardVBO(
      GL::VertexBufferObject &vbo, unsigned int &no_vertices,
      DVector< DVector< Vector<T, n> > >& p, int d ) {

    no_vertices = p.getDim();

    vbo.bind();
    vbo.createBufferData( no_vertices * sizeof(GL::GLVertex), 0x0, GL_STATIC_DRAW );

    GL::GLVertex *ptr = vbo.mapBuffer<GL::GLVertex>();
    if( ptr ) {
      for( int i = 0; i < p.getDim(); i++ ) {

        ptr->x = p(i)(d)(0);
        ptr->y = p(i)(d)(1);
        ptr->z = p(i)(d)(2);
        ptr++;
      }
    }

    vbo.unmapBuffer();
    vbo.unbind();
  }

//  template <typename T, int n>
//  inline
//  void PCurveVisualizer<T,n>::populateLineStripVBO( GLuint _vbo_id, int& no_dp, DVector< DVector< Vector<T, 3> > >& p, int d ) {

//    no_dp = p.getDim();

//    glBindBuffer( GL_ARRAY_BUFFER, _vbo_id );
//    glBufferData( GL_ARRAY_BUFFER, no_dp * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

//    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
//    if( ptr ) {

//      for( int i = 0; i < p.getDim(); i++ )
//        for( int j = 0; j < 3; j++ )
//          *(ptr++) = p[i][d][j];
//    }

//    glUnmapBuffer( GL_ARRAY_BUFFER );
//    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
//  }

  template <typename T, int n>
  inline
  void PCurveVisualizer<T,n>::replot(
    DVector< DVector< Vector<T, n> > >& /*p*/,
    int /*m*/, int /*d*/, bool /*closed*/
  ) {}

  template <typename T, int n>
  void PCurveVisualizer<T,n>::set( DisplayObject* obj ) {

    Visualizer::set(obj);

    _curve = dynamic_cast<PCurve<T,n>*>( obj );
  }



} // END namespace GMlib
