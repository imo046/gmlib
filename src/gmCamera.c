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



/*! \file gmCamera.c
 *  \brief Inline Camera class implementations
 *
 *  Inline implementations of the Camera class.
 *  This file is included in the header file
 *
 *  \date   2008-08-03
 */


#include <iostream>
using std::cout;
using std::endl;




namespace GMlib {



  /*! void Camera::basisChange(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::basisChange(
    const Vector<float,3>& x,
    const Vector<float,3>& y,
    const Vector<float,3>& z,
    const Vector<float,3>& p
  ) {
    _matrix.basisChangeCam(x,y,z,p);
  }


  /*! void Camera::decreaseEyeDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::decreaseEyeDist(double delta) {

    _eye_dist-=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::decreaseFocalDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::decreaseFocalDist(double delta) {

    increaseFocalDist(-delta);
  }


  /*! void Camera::display()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::display() {

    //cout << "Rendering camera View of camera with ID: " << getTypeId() << endl;
    setPerspective();
    glViewport(_x,_y,_w,_h);
    glPushMatrix();
      _matrix.mult();
      _matrix_scene_inv.mult();
      if(_coord_sys_visible) drawActiveCam();
      _scene->_culling( _frustum, _culling );
      _scene->_lighting();
      _scene->_display();

    glPopMatrix();
  }


  /*! void Camera::enableCulling( bool enable )
   *	\brief Enable or disable culling
   *
   *	Enable or disable Culling for this camera
   */
  inline
  void Camera::enableCulling( bool enable ) {

    _culling = enable;
  }


  /*! SceneObject* Camera::find(unsigned int name
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  SceneObject* Camera::find(unsigned int name) {

    return _scene->find(name);
  }


  /*! float Camera::getFarPlane() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getFarPlane() const	{

    return _far_plane;
  }


  /*! float Camera::getFocalLength() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getFocalLength() const {

    return _focal_length;
  }


  /*! std::string Camera::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string Camera::getIdentity() const {

    return "Camera";
  }


  /*! float Camera::getNearPlane() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getNearPlane() const {

    return _near_plane;
  }


  /*! float Camera::getRatio() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getRatio() const {

    return _ratio;
  }


  /*!
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::getViewport(int& w1, int& w2, int& h1, int& h2) const {

    w1 = _x;
    h1 = _y;
    w2 = _x+_w;
    h2 = _y+_h;
  }


  /*! int Camera::getViewPortW() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int Camera::getViewportW() const {

    return _w;
  }


  /*! int Camera::getViewPortH() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int Camera::getViewportH() const {

    return _h;
  }


  /*! void Camera::increaseEyeDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::increaseEyeDist(double delta) {

    _eye_dist+=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::increaseFocalDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::increaseFocalDist(double delta) {

    setFocalDist(_focal_length+delta);
  }


  /*! bool Camera::isCoordSysVisible() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isCoordSysVisible() const {

    return _coord_sys_visible;
  }


  /*! bool Camera::isCulling() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isCulling() const {

    return _culling;
  }

  /*! bool Camera::isFrustumVisible() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isFrustumVisible() const {

    return _frustum_visible;
  }


  /*! void Camera::reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	To be used when changing Camera.
   */
  inline
  void Camera::reset() {

    int	wp[4];
    glGetIntegerv(GL_VIEWPORT,wp);
    reshape(wp[0],wp[1],wp[2],wp[3]);
  }


  /*! void Camera::setCuttingPlanes(float near_plane, float far_plane)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setCuttingPlanes(float near_plane, float far_plane) {

    _near_plane = near_plane;
    _far_plane	= far_plane;
    _angle_tan	= 13.0f*_near_plane/_focal_length;
  }


  /*! void Camera::setCoordSysVisible(bool visible)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setCoordSysVisible(bool visible) {

    _coord_sys_visible=visible;
  }


  /*! void Camera::setEyeDist(double eye_dist)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setEyeDist(double eye_dist) {

    _eye_dist=eye_dist;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::setFocalDist(double focal)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setFocalDist(double focal)	{

    _focal_length   = focal;
    _ed_fd			= _eye_dist/_focal_length;
    _angle_tan		= 13.0f*_near_plane/_focal_length;
  }


  /*! void Camera::setFrustumVisible(bool visible=true)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setFrustumVisible(bool visible) {

    _frustum_visible=visible;
  }


  /*! void Camera::setScene(Scene& s)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setScene(Scene& s) {

    _scene = &s;
  }


  /*! void Camera::setScene(Scene *s)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setScene(Scene *s) {

    _scene = s;
  }

}