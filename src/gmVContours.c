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



/*! \file gmVContours.c
 *
 *  VContours class function implementations.
 *
 *  \date   2009-01-27
 */


namespace GMlib {

  template <typename T, int n>
  VContours<T,n>::VContours() {

    _init();
  }


  template <typename T, int n>
  inline
  VContours<T,n>::VContours( const VContours<T,n>& copy ) : VDefault<T,n>( copy ) {}


  template <typename T, int n>
  inline
  VContours<T,n>::~VContours() {}


  template <typename T, int n>
  inline
  Color VContours<T,n>::_getColor( T d ) {

    // Find Index
    int idx;
    idx = d * ( _colors.getSize()-1 );
    if( idx == _colors.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _colors.getSize()-1) ) idx = 0;


    double local_d = (double( _colors.getSize()-1 ) * d) - idx;
    Color ret = _colors[idx].getInterpolatedHSV( local_d, _colors[idx+1] );

    return ret;
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureCurve( DVector< Vector<T,3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfGauss( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return (e*g - f*f) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  T VContours<T,n>::_getCurvatureSurfMean( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
  }


  template <typename T, int n>
  inline
  Material VContours<T,n>::_getMaterial( T d ) {

    // Find Index
    int idx;
    idx = d * (_materials.getSize()-1);
    if( idx == _materials.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _materials.getSize()-1) ) idx = 0;


    double local_d = (double( _materials.getSize()-1 ) * d) - idx;
    Color amb = _materials[idx].getAmb().getInterpolatedHSV( local_d, _materials[idx+1].getAmb() );
    Color dif = _materials[idx].getDif().getInterpolatedHSV( local_d, _materials[idx+1].getDif() );
    Color spc= _materials[idx].getSpc().getInterpolatedHSV( local_d, _materials[idx+1].getSpc() );
    float shininess = ( _materials[idx].getShininess() + _materials[idx+1].getShininess() ) / 2.0f;

    Material ret( amb, dif, spc, shininess );
    return ret;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::_init() {

    _type = GM_VISUALIZER_CONTOURS_TYPE_COLOR;
    _mapping = GM_VISUALIZER_CONTOURS_MAP_X;

    // Set default colors
    _colors += GMcolor::Red;
    _colors += GMcolor::Blue;

    // Set default materials
    _materials += GMmaterial::Obsidian;
    _materials += GMmaterial::Gold;

  }


  template <typename T, int n>
  inline
  void VContours<T,n>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT );

    // Set Properties
    if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR )          glDisable( GL_LIGHTING );
    else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL )  glEnable( GL_LIGHTING );


    if( n == 1 ) {

      // Enable the Vertex Array
      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_COLOR_ARRAY );

      // Give Pointer to Vertex Data
      glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_c1[0] );
      glVertexPointer( 3, GL_FLOAT, 0, this->_n1(0).getPtr() );

      // Draw
      glDrawArrays( GL_LINE_STRIP, 0, this->_n1.getDim() );

      glDisableClientState( GL_VERTEX_ARRAY );
      glDisableClientState( GL_COLOR_ARRAY );
    }
    else if( n == 2 ) {

      // Enable Vertex and Normal Array
      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_COLOR_ARRAY );

      // Draw
      for( int i = 0; i < this->_n2.getDim1(); i++ ) {

        // Give Pointers to Vertex and Normal Data
        glColorPointer( 4, GL_UNSIGNED_BYTE, 0, &_c2[0][0] );
        glVertexPointer( 3, GL_FLOAT, 2*3*sizeof(float), this->_n2(i)(0).getPos().getPtr() );

        // Draw Strip
        glDrawArrays( GL_TRIANGLE_STRIP, 0, this->_n2(i).getDim() );
      }

      // Disable Client States
      glDisableClientState( GL_VERTEX_ARRAY );
      glDisableClientState( GL_COLOR_ARRAY );
    }

    // Pop GL Attribs
    glPopAttrib();
  }


  template <typename T, int n>
  inline
  const Array<Color>& VContours<T,n>::getColors() const {

    return _colors;
  }


  template <typename T, int n>
  inline
  std::string VContours<T,n>::getIdentity() const {

    return "VContours";
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_CONTOURS_MAP VContours<T,n>::getMapping() const {

    return _mapping;
  }


  template <typename T, int n>
  inline
  const Array<Material>& VContours<T,n>::getMaterials() const {

    return _materials;
  }


  template <typename T, int n>
  inline
  GM_VISUALIZER_CONTOURS_TYPE VContours<T,n>::getType() const {

    return _type;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {

    // Replot the default visualizer
    VDefault<T,n>::replot( p, m, d );

    // Color Countours
    DVector<Color> ccs;

    T min, max;
    T C; // Color Factor, (map to local)
    ccs.setDim( p.getDim() );
    switch( _mapping ) {

      case GM_VISUALIZER_CONTOURS_MAP_X:
      case GM_VISUALIZER_CONTOURS_MAP_Y:
      case GM_VISUALIZER_CONTOURS_MAP_Z:
      {

        int coord;
        switch( _mapping ) {
          case GM_VISUALIZER_CONTOURS_MAP_X:  coord = 0;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Y:  coord = 1;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Z:
          default:                            coord = 2;  break;
        }

        min = max = p[0][0][coord];

        // Extract all "height"-coords
        for( int i = 0; i < p.getDim(); i++ ) {

          const T value = p[i][0][coord];
          if( value < min )
            min = value;
          if( value > max )
            max = value;
        }

        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }


        // Compute colors
        for( int i = 0; i < p.getDim(); i++ ) {

          const T value = p[i][0][coord];
          ccs[i] = _getColor( ( C * value ) - min );
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_T:
      case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim(); i++ )
          ccs[i] = _getColor( double(i) / double(p.getDim()-1) );
      }
      break;


      case GM_VISUALIZER_CONTOURS_MAP_SPEED:
      {
        // Init min/max
        min = max = (p[0][1]).getLength();

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T speed = (p[i][1]).getLength();
          if( speed < min )
            min = speed;
          if( speed > max )
            max = speed;
        }

        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }

        // Compute interpolated color values
        for( int i = 0; i < p.getDim(); i++ ) {

          const T speed = (p[i][1]).getLength();
          ccs[i] = _getColor( ( C * speed ) - min );
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE:
      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_GAUSS:
      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_MEAN:
      {
        // Init min/max
        min = max = _getCurvatureCurve(p[0]);

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T curvature = _getCurvatureCurve(p[i]);
          if( curvature < min )
            min = curvature;
          if( curvature > max )
            max = curvature;
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim(); i++ )
            ccs[i] = _colors[0];
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated color values
          for( int i = 0; i < p.getDim(); i++ ) {

            const T curvature = _getCurvatureCurve(p[i]);
            ccs[i] = _getColor( ( C * curvature ) - min );
          }
        }
      }
      break;



      default:
      {
        // Compute colors
        for( int i = 0; i < p.getDim(); i++ )
          ccs[i] = _colors[0];
      }
      break;
    }


    // Create Vertex arrays ^^
//    if( this->_ref->isDynamic() ) {

      _c1 = ccs;
//    }
//    else {
//
//      if( _dlist )
//        glDeleteLists( _dlist, 1 );
//
//      _dlist = glGenLists(1);
//
//      // Create the Curve Display List
//      glNewList( _dlist, GL_COMPILE ); {
//        glBegin(GL_LINE_STRIP); {
//
//          for( int i = 0; i < p.getDim(); i++ ) {
//            glColor( ccs[i] );
//            glPoint( Point<float, 3>( p[i][0].toFloat() ) );
//          }
//
//        }glEnd();
//      } glEndList();
//    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    // Replot the default visualizer
    VDefault<T,n>::replot( p, normals, m1, m2, d1, d2 );

    // Color/Material Countours
    DMatrix<double> cmap;

    T min, max;
    T C;
    cmap.setDim( p.getDim1(), p.getDim2() );
    switch( _mapping ) {

      case GM_VISUALIZER_CONTOURS_MAP_T:
      case GM_VISUALIZER_CONTOURS_MAP_U:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(i) / double(p.getDim1()-1);
      }
      break;
      case GM_VISUALIZER_CONTOURS_MAP_V:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(j) / double(p.getDim2()-1);
      }
      break;


      case GM_VISUALIZER_CONTOURS_MAP_X:
      case GM_VISUALIZER_CONTOURS_MAP_Y:
      case GM_VISUALIZER_CONTOURS_MAP_Z:
      {

        int coord;
        switch( _mapping ) {
          case GM_VISUALIZER_CONTOURS_MAP_X:  coord = 0;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Y:  coord = 1;  break;
          case GM_VISUALIZER_CONTOURS_MAP_Z:
          default:                            coord = 2;  break;
        }

        min = max = p[0][0][0][0][coord];

        // Extract all "height"-coords
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T value = p[i][j][0][0][coord];
            if( value < min )
              min = value;
            if( value > max )
              max = value;
          }
        }


        // Correct interval
        if( max - min > 0 ) {
          C = 1.0f / (max - min);
          min /= (max - min);
        }
        else {
          C = min = T(0);
        }


        // Compute map values
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T value = p[i][j][0][0][coord];
            cmap[i][j] = ( C * value ) - min;
          }
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_GAUSS:
      {
        // Init min/max
        min = max = _getCurvatureSurfGauss(p[0][0]);

        // Extract all Gaussian Curvature data
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T curvature = _getCurvatureSurfGauss(p[i][j]);
            if( curvature < min )
              min = curvature;
            if( curvature > max )
              max = curvature;
          }
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ )
              cmap[i][j] = 0.0;
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated map values
          for( int i = 0; i < p.getDim1(); i++ ) {
            for( int j = 0; j < p.getDim2(); j++ ) {

              const T curvature = _getCurvatureSurfGauss(p[i][j]);
              cmap[i][j] = ( C * curvature ) - min;
            }
          }
        }
      }
      break;

      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE:
      case GM_VISUALIZER_CONTOURS_MAP_CURVATURE_MEAN:
      {
        // Init min/max
        min = max = _getCurvatureSurfGauss(p[0][0]);

        // Extract all Mean Curvature data
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T curvature = _getCurvatureSurfMean(p[i][j]);
            if( curvature < min )
              min = curvature;
            if( curvature > max )
              max = curvature;
          }
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ )
              cmap[i][j] = 0.0;
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated map values
          for( int i = 0; i < p.getDim1(); i++ ) {
            for( int j = 0; j < p.getDim2(); j++ ) {

              const T curvature = _getCurvatureSurfMean(p[i][j]);
              cmap[i][j] = ( C * curvature ) - min;
            }
          }
        }
      }
      break;


      case GM_VISUALIZER_CONTOURS_MAP_SPEED:
      default:
      {
        // Compute map values
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = 0.0;
//            ccs[i][j] = _colors[0];

      }
      break;
    }

    cout << "color map" << endl;
    for( int i = 0; i < cmap.getDim1(); i++ ) {

      for( int j = 0; j < cmap.getDim2(); j++ ) {

        cout << cmap[i][j] << " ";
      }
      cout << endl;

    }
    cout << endl;


    DMatrix<Color> ccs;
//    DMatrix<Material> mcs;
//    if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR ) {

      ccs.setDim( p.getDim1(), p.getDim2() );
      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ )
          ccs[i][j] = _getColor( cmap[i][j] );
//    }
//    else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL ) {
//
//      mcs.setDim( p.getDim1(), p.getDim2() );
//      for( int i = 0; i < p.getDim1(); i++ )
//        for( int j = 0; j < p.getDim2(); j++ )
//          mcs[i][j] = _getMaterial( cmap[i][j] );
//    }


    // Create Vertex arrays ^^
//    if( this->_ref->isDynamic() && _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR ) {

      _c2.setDim( p.getDim1()-1, p.getDim2()*2 );

      for( int i = 0; i < p.getDim1()-1; i++ ) {
        for( int j = 0; j < p.getDim2(); j++ ) {

          _c2[i][ 2*j   ] = ccs[ i   ][j];
          _c2[i][ 2*j+1 ] = ccs[ i+1 ][j];
        }
      }
//    }
//    else {
//
//      if( _dlist )
//        glDeleteLists( _dlist, 1 );
//
//      _dlist = glGenLists(1);
//
//      // Create the Curve Display List
//      glNewList( _dlist, GL_COMPILE ); {
//
//        for( int i = 0; i < p.getDim1() - 1; i++ ) {
//          glBegin(GL_TRIANGLE_STRIP); {
//            for( int j = 0; j < p.getDim2(); j++ ) {
//
//              if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR )          glColor( ccs[i][j] );
//              else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL )  mcs[i][j].glSet();
//
//              glVertex( Arrow<float, 3>(
//                Point3D<float>( ( p[i][j][0][0] ).toFloat() ),
//                ( normals[i][j] ).getNormalized().toFloat()
//              ) );
//
//              if( _type == GM_VISUALIZER_CONTOURS_TYPE_COLOR )          glColor( ccs[i+1][j] );
//              else if( _type == GM_VISUALIZER_CONTOURS_TYPE_MATERIAL )  mcs[i+1][j].glSet();
//
//              glVertex( Arrow<float, 3>(
//                Point3D<float>( ( p[i+1][j][0][0] ).toFloat() ),
//                ( normals[i+1][j] ).getNormalized().toFloat()
//              ) );
//            }
//          } glEnd();
//        }
//      } glEndList();
//    }
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setColors( const Array<Color>& c ) {

    _colors = c;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setMaterials( const Array<Material>& mat ) {

    _materials = mat;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setMapping( GM_VISUALIZER_CONTOURS_MAP mapping ) {

    _mapping = mapping;
  }


  template <typename T, int n>
  inline
  void VContours<T,n>::setType( GM_VISUALIZER_CONTOURS_TYPE type ) {

    _type = type;
  }
}
