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


namespace GMlib {


  template <typename T>
  PLine<T>::PLine( const Point<T,3>& p, const Vector<T,3>& v ) : _pt(p), _v(v) {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }

  template <typename T>
  PLine<T>::PLine( const Point<T,3>& p1, const Point<T,3>& p2 ) : _pt(p1), _v(p2-p1) {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  PLine<T>::PLine( const PLine<T>& copy ) : PCurve<T,3>(copy) {}


  template <typename T>
  PLine<T>::~PLine() {}


  template <typename T>
  inline
  void PLine<T>::eval( T t, int d, bool /*l*/ ) {

    this->_p.setDim( d + 1 );

    this->_p[0] = _pt + t * _v;

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if( d )     this->_p[1] = _v;
      if( d > 1 ) this->_p[2] = Vector<T,3>(T(0));
      if( d > 2 ) this->_p[3] = Vector<T,3>(T(0));
      if( d > 3 ) this->_p[4] = Vector<T,3>(T(0));
      if( d > 4 ) this->_p[5] = Vector<T,3>(T(0));
      if( d > 5 ) this->_p[6] = Vector<T,3>(T(0));
      if( d > 6 ) this->_p[7] = Vector<T,3>(T(0));
    }
  }


  template <typename T>
  inline
  T PLine<T>::getEndP() {

    return T(1);
  }


  template <typename T>
  inline
  T PLine<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool PLine<T>::isClosed() const {

    return false;
  }

} // END namespace GMlib