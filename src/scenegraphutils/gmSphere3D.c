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



/*! \file gmSphere3D.c
 *  \brief Inline Shpere3D class implementations
 *
 *  Inline implementation of the Sphere3D class.
 *
 *  \date   2008-08-03
 */


// GMlib includes
#include "gmPoint3D.h"


namespace GMlib {



  /*! Sphere3D::Sphere3D(float r, int m1, int m2) : Sphere<float,3>(Point<float,3>(float(0)),r), _display( "default" )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere3D::Sphere3D(float r, int m1, int m2) : Sphere<float,3>(Point<float,3>(float(0)),r),
  _prog_light("default"), _prog_color("color"), _prog_select("select") {

    glGenBuffers( 1, &_vbo_v );
    glGenBuffers( 1, &_vbo_n );
    replot(m1,m2);
  }


  /*! Sphere3D::Sphere3D(const Sphere<float,3>& s, int m1, int m2) : Sphere<float,3>(s), _display( "default" )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere3D::Sphere3D(const Sphere<float,3>& s, int m1, int m2) : Sphere<float,3>(s),
  _prog_light("default"), _prog_color("color"), _prog_select("select")  {

    glGenBuffers( 1, &_vbo_v );
    glGenBuffers( 1, &_vbo_n );
    replot(m1,m2);
  }

  inline
  Sphere3D::Sphere3D( const Sphere3D& copy ): Sphere<float,3>( copy ),
  _prog_light("default"), _prog_color("color"), _prog_select("select")  {

    glGenBuffers( 1, &_vbo_v );
    glGenBuffers( 1, &_vbo_n );
    replot(copy._m1,copy._m2);
  }

  inline
  Sphere3D::~Sphere3D() {

    glDeleteBuffers( 1, &_vbo_v );
    glDeleteBuffers( 1, &_vbo_n );
  }

  /*! void Sphere3D::display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::display( const HqMatrix<float,3>& mvpmat, bool selected ) {

    _prog_color.bind();

    _prog_color.setUniform( "u_mvpmat", mvpmat, 1, true );
    _prog_color.setUniform( "u_selected", selected );
    _prog_color.setUniform( "u_color", GMlib::GMcolor::Blue );

    GLuint vert_loc = _prog_color.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    // Draw top and bottom caps
    for( int i = 0; i < 2; i++ )
      glDrawArrays( GL_TRIANGLE_FAN, i * _top_bot_verts, _top_bot_verts );

    // Draw body strips
    for( int i = 0; i < _mid_strips; i++ )
      glDrawArrays( GL_TRIANGLE_STRIP, _top_bot_verts*2 + i*_mid_strips_verts, _mid_strips_verts );

    glDisableVertexAttribArray( vert_loc );

    _prog_color.unbind();
  }

  /*! void Sphere3D::display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::display( const HqMatrix<float,3>& mvmat, const HqMatrix<float,3>& mvpmat, bool selected ) {

    _prog_light.bind();

    _prog_light.setUniform( "u_mvmat", mvmat, 1, true );
    _prog_light.setUniform( "u_mvpmat", mvpmat, 1, true );
    _prog_light.setUniform( "u_selected", selected );
    _prog_light.setUniform( "u_color", GMlib::GMcolor::Blue );

    GLuint vert_loc = _prog_light.getAttributeLocation( "in_vertex" );
    GLuint normal_loc = _prog_light.getAttributeLocation( "in_normal" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_n );
    glVertexAttribPointer( normal_loc, 3, GL_FLOAT, GL_TRUE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( normal_loc );

    // Draw top and bottom caps
    for( int i = 0; i < 2; i++ )
      glDrawArrays( GL_TRIANGLE_FAN, i * _top_bot_verts, _top_bot_verts );

    // Draw body strips
    for( int i = 0; i < _mid_strips; i++ )
      glDrawArrays( GL_TRIANGLE_STRIP, _top_bot_verts*2 + i*_mid_strips_verts, _mid_strips_verts );

    glDisableVertexAttribArray( normal_loc );
    glDisableVertexAttribArray( vert_loc );

    _prog_light.unbind();
  }

  /*! void Sphere3D::display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::select( const HqMatrix<float,3>& mvpmat, const Color& sel_color ) {

    _prog_select.bind();


    _prog_select.setUniform( "u_mvpmat", mvpmat, 1, true );
    _prog_color.setUniform( "u_color", sel_color );

    GLuint vert_loc = _prog_select.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    // Draw top and bottom caps
    for( int i = 0; i < 2; i++ )
      glDrawArrays( GL_TRIANGLE_FAN, i * _top_bot_verts, _top_bot_verts );

    // Draw body strips
    for( int i = 0; i < _mid_strips; i++ )
      glDrawArrays( GL_TRIANGLE_STRIP, _top_bot_verts*2 + i*_mid_strips_verts, _mid_strips_verts );

    glDisableVertexAttribArray( vert_loc );

    _prog_select.unbind();
  }

  /*! void Sphere3D::replot(int m1, int m2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::replot(int m1, int m2) {

    // Check lower replot boundaries
    if( m1 > 1 )
      _m1 = m1;

    if( m2 > 1 )
      _m2 = m2;


    // Set some vars
    const float x = _pos[0];
    const float y = _pos[1];
    const float z = _pos[2];
    const float r = _value;
    _top_bot_verts = _m2+2;
    _mid_strips = (_m1-2);
    _mid_strips_verts = (_m2+1) * 2;


    // Map buffers and allocate data on the GPU
    const unsigned int verts = _top_bot_verts * 2 + _mid_strips * _mid_strips_verts;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glBufferData( GL_ARRAY_BUFFER, verts * 3 * sizeof(float), 0x0, GL_STATIC_DRAW );
    float *ptr_v = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_n );
    glBufferData( GL_ARRAY_BUFFER, verts * 3 * sizeof(float), 0x0, GL_STATIC_DRAW );
    float *ptr_n = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );


    // Compute stride in the spheres u and v parametric direction.
    const float du = M_PI / _m1;
    const float dv = M_2PI / _m2;

    // Compute top and bottom triangle fans for the sphere
    {
      float u;
      float su, cu, ru;

      const Arrow<float,3> top = Arrow<float,3>(_pos+Point3D<float>(0,0,r), Vector3D<float>(0,0,1));
      *ptr_v++ = top.getPos()(0);
      *ptr_v++ = top.getPos()(1);
      *ptr_v++ = top.getPos()(2);
      *ptr_n++ = top.getDir()(0);
      *ptr_n++ = top.getDir()(1);
      *ptr_n++ = top.getDir()(2);

      u = M_PI_2 - du;

      su = sin(u);
      cu = cos(u);
      ru = r * cu;

      float v = 0;
      for( int i = 0; i < _m2+1; i++, v += dv ) {

        const float sv = sin(v);
        const float cv = cos(v);

        *ptr_v++ = x + ru*cv;
        *ptr_v++ = y + ru*sv;
        *ptr_v++ = z + r*su;
        *ptr_n++ = cu*cv;
        *ptr_n++ = cu*sv;
        *ptr_n++ = su;
      }


      const Arrow<float,3> bottom = Arrow<float,3>(_pos+Point3D<float>(0,0,-r),Vector3D<float>(0,0,-1));
      *ptr_v++ = bottom.getPos()(0);
      *ptr_v++ = bottom.getPos()(1);
      *ptr_v++ = bottom.getPos()(2);
      *ptr_n++ = bottom.getDir()(0);
      *ptr_n++ = bottom.getDir()(1);
      *ptr_n++ = bottom.getDir()(2);

      u = M_PI_2 - du * (_m1-1);
      su = sin(u);
      cu = cos(u);
      ru = r * cu;

      v = 0;
      for( int i = _m2; i >= 0; i--, v += dv ) {

        const float sv = sin(v);
        const float cv = cos(v);

        *ptr_v++ = x + ru*cv;
        *ptr_v++ = y + ru*sv;
        *ptr_v++ = z + r*su;
        *ptr_n++ = cu*cv;
        *ptr_n++ = cu*sv;
        *ptr_n++ = su;
      }
    }


    // Compute body triangle strips on the sphere
    for( int i = 0; i < _m1-2; i++ ) {

      const float u1 = M_PI_2 - du * (i+1);
      const float u2 = M_PI_2 - du * (i+2);

      const float su1 = sin(u1);
      const float cu1 = cos(u1);
      const float ru1 = r * cu1;

      const float su2 = sin(u2);
      const float cu2 = cos(u2);
      const float ru2 = r * cu2;

      for( int j = 0; j < _m2+1; j++ ) {

        const float v = j * dv;
        const float sv = sin(v);
        const float cv = cos(v);

        *ptr_v++ = x + ru1*cv;
        *ptr_v++ = y + ru1*sv;
        *ptr_v++ = z + r*su1;
        *ptr_n++ = cu1*cv;
        *ptr_n++ = cu1*sv;
        *ptr_n++ = su1;

        *ptr_v++ = x + ru2*cv;
        *ptr_v++ = y + ru2*sv;
        *ptr_v++ = z + r*su2;
        *ptr_n++ = cu2*cv;
        *ptr_n++ = cu2*sv;
        *ptr_n++ = su2;
      }
    }


    // Unmap GPU buffers
    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glUnmapBuffer( GL_ARRAY_BUFFER );
  }

} // END namespace GMlib
