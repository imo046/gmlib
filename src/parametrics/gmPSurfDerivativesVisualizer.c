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



/*! \file gmPSurfDerivativesVisualizer.c
 *
 *  Implementation of the PSurfDerivativesVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PSurfDerivativesVisualizer<T>::PSurfDerivativesVisualizer() : _display( "color" ) {

    _color = GMcolor::Green;
    _u = 1;
    _v = 0;
    _mode = GM_SURF_DERIVATIVESVISUALIZER_RELATIVE;
    _size = 1.0;

    _no_elements = 0;

    glGenBuffers( 1, &_vbo_v );
  }

  template <typename T>
  PSurfDerivativesVisualizer<T>::~PSurfDerivativesVisualizer() {

    glDeleteBuffers( 1, &_vbo_v );
  }

  template <typename T>
  inline
  void PSurfDerivativesVisualizer<T>::display( Camera* cam ) {

    _display.bind();

    _display.setUniform( "u_mvpmat", cam->getProjectionMatrix() * this->_obj->getModelViewMatrix(cam), 1, true );
    _display.setUniform( "u_color", _color );

    GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    // Draw
    glDrawArrays( GL_LINES, 0, _no_elements );

    glDisableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    _display.unbind();
  }

  template <typename T>
  const Color& PSurfDerivativesVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  int PSurfDerivativesVisualizer<T>::getDerivativeU() const {

    return _u;
  }

  template <typename T>
  int PSurfDerivativesVisualizer<T>::getDerivativeV() const {

    return _v;
  }

  template <typename T>
  std::string PSurfDerivativesVisualizer<T>::getIdentity() const {

    return "PSurf Derivatives Visualizer";
  }

  template <typename T>
  GM_SURF_DERIVATIVESVISUALIZER_SIZE PSurfDerivativesVisualizer<T>::getMode() const {

    return _mode;
  }

  template <typename T>
  double PSurfDerivativesVisualizer<T>::getSize() const {

    return _size;
  }

  template <typename T>
  inline
  void PSurfDerivativesVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    int der_u = 0;
    int der_v = 0;

    if( (_u >= 0) || (_u <= p[0][0].getDim1()-1) )
      der_u = _u;

    if( (_v >= 0) || (_v <= p[0][0].getDim2()-1) )
      der_v = _v;


    int no_derivatives = p.getDim1() * p.getDim2();
    _no_elements = no_derivatives * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v);
    glBufferData( GL_ARRAY_BUFFER, no_derivatives * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );


    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      switch( _mode ) {
      case GM_SURF_DERIVATIVESVISUALIZER_RELATIVE: {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ ) {

              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k];

              const GMlib::Vector<T,3> v = p[i][j][der_u][der_v] * _size;
              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k] + v(k);
            }
        }
        break;

      case GM_SURF_DERIVATIVESVISUALIZER_ABSOLUTE: {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ ) {

              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k];

              const GMlib::Vector<T,3> v = p[i][j][der_u][der_v].getNormalized() * _size;
              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k] + v(k);
            }
        }
        break;

      case GM_SURF_DERIVATIVESVISUALIZER_NORMALIZED: {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ ) {

              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k];

              const GMlib::UnitVector<T,3> uv = p[i][j][der_u][der_v];
              for( int k = 0; k < 3; k++ )
                *(ptr++) = p[i][j][0][0][k] + uv(k);
            }
        }
        break;
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PSurfDerivativesVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T>
  void PSurfDerivativesVisualizer<T>::setDerivatives( int u, int v ) {

    if( u < 1 && v < 1 )
      return;

    if( u < 0 || v < 0 )
      return;

    _u = u;
    _v = v;
  }

  template <typename T>
  void PSurfDerivativesVisualizer<T>::setMode( GM_SURF_DERIVATIVESVISUALIZER_SIZE mode ) {

    _mode = mode;
  }

  template <typename T>
  void PSurfDerivativesVisualizer<T>::setSize( double size ) {

    _size = size;
  }


} // END namespace GMlib