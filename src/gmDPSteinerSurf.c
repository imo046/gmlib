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



/*! \file gmDPSteinerSurf.c
 *
 *  Implementation of the gmDPSteinerSurf template class.
 *
 *  \date   2008-09-07
 */


namespace GMlib {


//  template <typename T>
//  inline
//  DPSteinerSurf<T>::DPSteinerSurf( T radius ) : DSurf<T>( new PSteinerSurf<T,3>( radius ) ) {
//
//    init();
//  }


  template <typename T>
  inline
  DPSteinerSurf<T>::DPSteinerSurf( T radius ) {

    init();

    _r = radius;
  }


  template <typename T>
  inline
  DPSteinerSurf<T>::DPSteinerSurf( const DPSteinerSurf<T>& copy ) : DSurf<T>( copy ) {

    init();

    _r = copy._r;
  }


//  template <typename T>
//  inline
//  DPSteinerSurf<T>::DPSteinerSurf( const PSteinerSurf<T,3>& copy ) : DSurf<T>( copy ) {
//
//    init();
//  }


  template <typename T>
  DPSteinerSurf<T>::~DPSteinerSurf() {}


  template <typename T>
  inline
  std::string DPSteinerSurf<T>::getIdentity() const {

    return "DPSteinerSurf";
  }


//  template <typename T>
//  inline
//  PSteinerSurf<T,3>* DPSteinerSurf<T>::getPSteinerSurf() {
//
//    return _l_ref;
//  }


  template <typename T>
  void DPSteinerSurf<T>::init() {

//    _l_ref = dynamic_cast<PSteinerSurf<T,3>*>( this->_p_ref );
  }




  //////////////////////// PSteinerSurf !!!!!!!!!!!!!! PSteinerSurf ////////////////////////
  //////////////////////// PSteinerSurf !!!!!!!!!!!!!! PSteinerSurf ////////////////////////
  //////////////////////// PSteinerSurf !!!!!!!!!!!!!! PSteinerSurf ////////////////////////
  //////////////////////// PSteinerSurf !!!!!!!!!!!!!! PSteinerSurf ////////////////////////




  template <typename T>
  inline
  T DPSteinerSurf<T>::getEndPU() {

    return T(M_PI);
  }


  template <typename T>
  inline
  T DPSteinerSurf<T>::getEndPV() {

    return T(M_PI);
  }


  template <typename T>
  void DPSteinerSurf<T>::eval(T u, T v, int d1, int d2, bool lu, bool lv ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	T(.5)*_r*_r*sin(T(2)*u)*cos(v)*cos(v);
    this->_p[0][0][1] =	T(.5)*_r*_r*sin(u)*sin(T(2)*v);
    this->_p[0][0][2] =	T(.5)*_r*_r*cos(u)*sin(T(2)*v);

//    if( this->_dm == GM_DERIVATION_EXPLICIT ) {
//
//      if(d1) //u
//      {
//        this->_p[1][0][0] =	_r*_r*cos(T(2)*u)*cos(v)*cos(v);
//        this->_p[1][0][1] =	T(.5)*_r*_r*cos(u)*sin(T(2)*v);
//        this->_p[1][0][2] =	-T(.5)*_r*_r*sin(u)*sin(T(2)*v);
//      }
//      if(d1>1)//uu
//      {
//        this->_p[2][0][0] =	-T(2)*_r*_r*sin(T(2)*u)*pow(cos(v),T(2));
//        this->_p[2][0][1] =	-_r*_r*sin(u)*sin(T(2)*v)/T(2);
//        this->_p[2][0][2] =	-_r*_r*cos(u)*sin(T(2)*v)/T(2);
//      }
//      if(d2) //v
//      {
//        this->_p[0][1][0] =	-_r*_r*sin(T(2)*u)*cos(v)*sin(v);
//        this->_p[0][1][1] =	_r*_r*sin(u)*cos(T(2)*v);
//        this->_p[0][1][2] =	_r*_r*cos(u)*cos(T(2)*v);
//      }
//      if(d2>1) //vv
//      {
//        this->_p[0][2][0] =	_r*_r*sin(T(2)*u)*pow(sin(v),T(2))-_r*_r*sin(T(2)*u)*pow(cos(v),T(2));
//        this->_p[0][2][1] =	-T(2)*_r*_r*sin(u)*sin(T(2)*v);
//        this->_p[0][2][2] =	-T(2)*_r*_r*cos(u)*sin(T(2)*v);
//      }
//      if(d1 && d2) //uv
//      {
//        this->_p[1][1][0] =	-T(2)*_r*_r*cos(T(2)*u)*cos(v)*sin(v);
//        this->_p[1][1][1] =	_r*_r*cos(u)*cos(T(2)*v);
//        this->_p[1][1][2] =	_r*_r*sin(u)*cos(T(2)*v);
//      }
//      if(d1>1 && d2)//uuv
//      {
//        this->_p[2][1][0] =	T(4)*_r*_r*sin(T(2)*u)*cos(v)*sin(v);
//        this->_p[2][1][1] =	-_r*_r*sin(u)*cos(T(2)*v);
//        this->_p[2][1][2] =	-_r*_r*cos(u)*cos(T(2)*v);
//      }
//      if(d1 && d2>1) //uvv
//      {
//        this->_p[1][2][0] =	T(2)*_r*_r*cos(T(2)*u)*pow(sin(v),T(2))-T(2)*_r*_r*cos(T(2)*u)*pow(cos(v),T(2));
//        this->_p[1][2][1] =	-T(2)*_r*_r*cos(u)*sin(T(2)*v);
//        this->_p[1][2][2] =	T(2)*_r*_r*sin(u)*sin(T(2)*v);
//      }
//      if(d1>1 && d2>1) //uuvv
//      {
//        this->_p[2][2][0] =	-T(4)*_r*_r*sin(T(2)*u)*pow(sin(v),T(2))+T(4)*_r*_r*sin(T(2)*u)*pow(cos(v),T(2));
//        this->_p[2][2][1] =	T(2)*_r*_r*sin(u)*sin(T(2)*v);
//        this->_p[2][2][2] =	T(2)*_r*_r*cos(u)*sin(T(2)*v);
//      }
//    }
  }


  template <typename T>
  inline
  T DPSteinerSurf<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T DPSteinerSurf<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  inline
  bool DPSteinerSurf<T>::isClosedU() const {

    return true;
  }


  template <typename T>
  inline
  bool DPSteinerSurf<T>::isClosedV() const {

    return true;
  }
}
