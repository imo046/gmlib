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



/*! \file gmcamera.cpp
 *
 *  Implementation of the Camera class.
 */


#include "gmcamera.h"

// local
#include "../utils/gmmaterial.h"
//#include "../render/gmrendermanager.h"
#include "../render/gmdefaultrenderer.h"
#include "../light/gmspotlight.h"
#include "../light/gmpointlight.h"
#include "../light/gmsun.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/containers/gmdvector.h>
#include <opengl/gmprogram.h>

//stl
#include <iostream>
#include <cassert>

namespace GMlib {


  Scene  Camera::_default_scene;
  unsigned int  Camera::_display_list = 0;




  /*! Camera::Camera( Scene& s = _default_scene )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Camera::Camera( Scene& s ) : SceneObject(),_scene(&s) {

    resetC();
  }


  /*! Camera::Camera( Scene* s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Camera::Camera( Scene* s ) : SceneObject(),_scene(s) {

    resetC();
  }


  /*! Camera::Camera( const Point<float,3>& pos, const Point<float,3>& look_at_pos )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Camera::Camera(
    const Point<float,3>&  pos,
    const Point<float,3>&  look_pos
  ) : SceneObject(look_pos,pos), _scene(&_default_scene) {

    resetC();
  }

  /*! Camera::Camera( const Point<float,3>&  pos,  const Vector<float,3>& dir,  const Vector<float,3>& up, float zoom )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Camera::Camera(
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up,
    float zoom
  ) : SceneObject(pos,dir,up),_scene(&_default_scene) {

    resetC(zoom);
  }


  /*! Camera::~Camera()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Camera::~Camera() {}


  /*! double Camera::deltaTranslate(SceneObject *)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  double Camera::deltaTranslate(SceneObject* obj) {

    if(obj)
      return 26*(getDir()*(obj->getPos()-getPos()))*getNearPlane()/(getFocalLength()*getViewportH());
    else
      return 0.0;
  }

  /*! double Camera::getDistanceToObject(int x, int y)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  double Camera::getDistanceToObject(int x, int y) {

    assert(false);
//    SceneObject*   obj = getScene()->getRenderManager()->findObject(x,y);
//    return getDistanceToObject(obj);
  }


  /*! double Camera::getDistanceToObject(SceneObject*)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  double Camera::getDistanceToObject(SceneObject* obj) {

    if(obj) {

      const HqMatrix<float,3> mat = _matrix*_matrix_scene_inv;
      const Vector<float,3> dv = mat*Point<float,3>(obj->getCenterPos());
      return dv.getLength();
    }
    else
      return 0.0;
  }


  /*! HqMatrix<float,3>& Camera::getMatrix()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  HqMatrix<float,3>& Camera::getMatrix() {

    /*! \todo fix how the matrix is returned */
    static HqMatrix<float,3> retmat;
    retmat = _matrix;
    retmat.invertOrthoNormal();
    return retmat;
  }


  const HqMatrix<float,3>& Camera::getMatrix() const {

    /*! \todo fix how the matrix is returned */
    static HqMatrix<float,3> retmat;
    retmat = _matrix;
    retmat.invertOrthoNormal();
    return retmat;
  }


//  /*! void Camera::go(bool stereo)
//   *  \brief Pending Documentation
//   *
//   *  Pending Documentation
//   *  Running the Camera.
//   */
//  void Camera::go(bool stereo) {



//    _active = true;
////    if (stereo)
////    {
////      Point3D<float>    tmp_pos  = _pos  - _eye_dist*_side;
////      UnitVector3D<float>  tmp_dir  = _dir  + _ed_fd*_side; //tmp_dir  = _pos + _focus_dist*_dir - tmp_pos;
////      UnitVector3D<float>  tmp_side = _side - _ed_fd*_dir;  //tmp_side = _up^tmp_dir;
////      basisChange(tmp_side, _up, tmp_dir, tmp_pos);      // Change to right eye
////      display();
////      basisChange(_side, _up, _dir, _pos);            // Back to left eye
////    }
////    else
//    {
//      Point<float,3>    tmp_pos  = _pos  - _eye_dist*_side;
//      UnitVector<float,3>  tmp_dir  = _dir  + _ed_fd*_side; //tmp_dir  = _pos + _focus_dist*_dir - tmp_pos;
//      UnitVector<float,3>  tmp_side = _side - _ed_fd*_dir;  //tmp_side = _up^tmp_dir;
//      basisChange(tmp_side, _up, tmp_dir, tmp_pos);      // Change to right eye
//      display();
//    }

//    _active = false;
//  }


  /*! void Camera::localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Camera::localDisplay() {

//    static Material lins(
//      Color( 0.19125f,  0.0735f,  0.0225f,    1.0f ),
//      Color( 0.5038f,   0.27048f,  0.0828f,   1.0f ),
//      Color( 0.256777f, 0.137622f, 0.086014f, 1.0f ),
//      12.8f
//    );

//    static Material rubb(
//      Color( 0.105882f, 0.058824f, 0.103725f, 1.0f ),
//      Color( 0.427451f, 0.470588f, 0.501176f, 1.0f ),
//      Color( 0.333333f, 0.333333f, 0.501569f, 1.0f ),
//      9.84615f
//    );

//    //PolishedSilver.glSet();
//    glCallList(_display_list);
//    glCallList(_display_list+2);
//    rubb.glSet();
//  //  GMmaterial::PolishedBronze.glSet();
//    glCallList(_display_list+1);
//    glCallList(_display_list+3);
//  //  GMmaterial::PolishedRed.glSet();
//    lins.glSet();
//    glCallList(_display_list+4);
//    if(_frustum_visible) {

//      Color    col( 1.0f, 1.0f, 1.0f, 1.0f ); // hvit
//      Point<float,3> p1(0,0,-_near_plane);
//      Point<float,3> p2(0,0,-_far_plane);
//      Vector<float,3> v1(0,_angle_tan*_near_plane,0);
//      Vector<float,3> v2(-_ratio*_angle_tan*_near_plane,0,0);
//      Vector<float,3> v3(0,_angle_tan*_far_plane,0);
//      Vector<float,3> v4(-_ratio*_angle_tan*_far_plane,0,0);
//      Point<float,3> p1m(p1-v1);
//      Point<float,3> p2m(p2-v3);
//      p1 += v1;
//      p2 += v3;
//      GLboolean lg;
//      glGetBooleanv(GL_LIGHTING,&lg);
//      if(lg) glDisable(GL_LIGHTING);
//      glColor(col);
//      glBegin(GL_LINE_LOOP);
//        glPoint(p1+v2);  glPoint(p1-v2);  glPoint(p1m-v2);  glPoint(p1m+v2);
//      glEnd();
//      glBegin(GL_LINE_LOOP);
//        glPoint(p2+v4);  glPoint(p2-v4);  glPoint(p2m-v4);  glPoint(p2m+v4);
//      glEnd();
//      glBegin(GL_LINES);
//        glPoint(p1 +v2);  glPoint(p2 +v4);  glPoint(p1 -v2);  glPoint(p2 -v4);
//        glPoint(p1m-v2);  glPoint(p2m-v4);  glPoint(p1m+v2);  glPoint(p2m+v4);
//      glEnd();
//      if(lg) glEnable(GL_LIGHTING);
//    }
//    if(_locked && !_lock_object) {

//      GLboolean lg;
//      glGetBooleanv(GL_LIGHTING,&lg);
//      if(lg) glDisable(GL_LIGHTING);
//      glPushMatrix();
//      HqMatrix<float,3> invmat = _present; invmat.invertOrthoNormal();
//      glTranslate(invmat*_lock_pos);
//      glColor(GMcolor::Green);
//      glCallList(_display_list+8);
//      glPopMatrix();
//      if(lg) glEnable(GL_LIGHTING);
  }



  /*! void Camera::localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Camera::localSelect() {

//    if(!_active) {
//      glCallList(_display_list+9);
    //    }
  }

  /*! SceneObject* Camera::lockTargetAtPixel(int x, int y)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* Camera::lockTargetAtPixel(int x, int y) {

    assert(false);
//    SceneObject*   obj = getScene()->getRenderManager()->findObject(x,y);
//    if(obj)
//    {
//      lock(obj);
//      return obj;
//    }
//    return 0;
  }


  /*! void Camera::reshape(int w1, inth1, int w2, int h2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  To be used when changing size of window
   */
  void Camera::reshape(int x1, int y1, int x2, int y2) {

    _x = x1;
    _y = y1;
    _w = x2-x1;
    _h = y2-y1;
    _ratio = float(_w)/float(_h);
  }


  /*! void Camera::zoom(float z)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Camera::zoom(float z) {

    setFocalDist(z*_focal_length);
  }


  /*! void Camera::makeGraphics()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Camera::makeGraphics() {

//    int i;
//    Point<float,3>    p[18];
//    UnitVector<float,3>  v[18];

//    p[0] = Point<float,3>(0.07,0.1,0.3);    p[4] = Point<float,3>(-0.07,0.1,0.3);
//    p[1] = Point<float,3>(0.07,0.1,-0.3);    p[5] = Point<float,3>(-0.07,0.1,-0.3);
//    p[2] = Point<float,3>(0.07,-0.1,-0.3);  p[6] = Point<float,3>(-0.07,-0.1,-0.3);
//    p[3] = Point<float,3>(0.07,-0.1,0.3);    p[7] = Point<float,3>(-0.07,-0.1,0.3);

//    v[0] = Vector<float,3>(1,0,0);
//    v[1] = Vector<float,3>(0,1,0);
//    v[2] = Vector<float,3>(-1,0,0);
//    v[3] = Vector<float,3>(0,-1,0);
//    v[4] = Vector<float,3>(0,0,1);
//    v[5] = Vector<float,3>(0,0,-1);

//    _display_list = glGenLists(10);

//    // Lager displayliste for display
//    glNewList(_display_list, GL_COMPILE);
//      glBegin(GL_QUADS);
//        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
//        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
//        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();
//    glEndList();

//    glNewList(_display_list+9, GL_COMPILE);
//      glBegin(GL_QUADS);
//        glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
//        glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
//        glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();
//    glEndList();

//    p[0] = Point<float,3>(0.1,0.1,0.1);  p[4] = Point<float,3>(-0.1,0.1,0.1);
//    p[1] = Point<float,3>(0.1,0.1,-0.1);  p[5] = Point<float,3>(-0.1,0.1,-0.1);
//    p[2] = Point<float,3>(0.1,-0.1,-0.1);  p[6] = Point<float,3>(-0.1,-0.1,-0.1);
//    p[3] = Point<float,3>(0.1,-0.1,0.1);  p[7] = Point<float,3>(-0.1,-0.1,0.1);

//    glNewList(_display_list+8, GL_COMPILE);  //  For lock at Point.
//      glBegin(GL_QUADS);
//        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
//        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
//        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();
//    glEndList();

//    p[0] = Point<float,3>(0.02,-0.1,-0.02);  p[4] = Point<float,3>(-0.02,-0.1,-0.02);
//    p[1] = Point<float,3>(0.02,-0.1,-0.08);  p[5] = Point<float,3>(-0.02,-0.1,-0.08);
//    p[2] = Point<float,3>(0.02,-0.25,-0.06);  p[6] = Point<float,3>(-0.02,-0.25,-0.06);
//    p[3] = Point<float,3>(0.02,-0.25,0.0);  p[7] = Point<float,3>(-0.02,-0.25,0.0);

//    glNewList(_display_list+1, GL_COMPILE);  //  For handtak.
//      glBegin(GL_QUADS);
//        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
//        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
//        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();
//    glEndList();

//    p[0] = Point<float,3>(-0.016,0.12,0.09);  p[4] = Point<float,3>(-0.054,0.12,0.09);
//    p[1] = Point<float,3>(-0.016,0.12,0.05);  p[5] = Point<float,3>(-0.054,0.12,0.05);
//    p[2] = Point<float,3>(-0.016,0.1,0.05);  p[6] = Point<float,3>(-0.054,0.1,0.05);
//    p[3] = Point<float,3>(-0.016,0.1,0.09);  p[7] = Point<float,3>(-0.054,0.1,0.09);

//    glNewList(_display_list+2, GL_COMPILE);
//      glBegin(GL_QUADS);            //  For søker del 1
//        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();

//      p[0] = Point<float,3>(-0.015,0.16,0.35);
//      p[1] = Point<float,3>(-0.015,0.16,0.0);
//      p[2] = Point<float,3>(-0.015,0.12,0.0);
//      p[3] = Point<float,3>(-0.015,0.12,0.35);
//      p[4] = Point<float,3>(-0.055,0.16,0.35);
//      p[5] = Point<float,3>(-0.055,0.16,0.0);
//      p[6] = Point<float,3>(-0.055,0.12,0.0);
//      p[7] = Point<float,3>(-0.055,0.12,0.35);

//      glBegin(GL_QUADS);    //  For søker del 2
//        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);  // right
//        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
//        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
//        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
//        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
//        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
//      glEnd();
//    glEndList();

//    GLMatrix mat(Angle(M_PI_4),Point<float,3>(-0.035,0.14,0.0),UnitVector<float,3>(0,0,-1));
//    p[1]  = Point<float,3>(-0.055,0.16,0.35);    v[1]  = Vector<float,3>(-1,1,0);
//    p[5]  = Point<float,3>(-0.015,0.16,0.35);    v[5]  = Vector<float,3>(1,1,0);
//    p[9]  = Point<float,3>(-0.015,0.12,0.35);    v[9]  = Vector<float,3>(1,-1,0);
//    p[13] = Point<float,3>(-0.055,0.12,0.35);    v[13] = Vector<float,3>(-1,-1,0);
//    p[17] = Point<float,3>(-0.055,0.16,0.35);    v[17] = Vector<float,3>(-1,1,0);

//    p[3]  = Point<float,3>(-0.035,0.16,0.35);    v[3]  = Vector<float,3>(0,1,0);
//    p[7]  = Point<float,3>(-0.015,0.14,0.35);    v[7]  = Vector<float,3>(1,0,0);
//    p[11] = Point<float,3>(-0.035,0.12,0.35);    v[11] = Vector<float,3>(0,-1,0);
//    p[15] = Point<float,3>(-0.055,0.14,0.35);    v[15] = Vector<float,3>(-1,0,0);

//    p[0] = p[1] + Vector<float,3>(-0.01,0.01,0.05); v[0] = v[1] + Vector<float,3>(0.0,0.0,0.02);

//    for(i=2; i<18;i+=2)
//    {
//      p[i] = mat*p[i-2];
//      v[i] = mat*v[i-2];
//    }

//    glNewList(_display_list+3, GL_COMPILE);
//      glBegin(GL_TRIANGLE_STRIP);    //  For søker del 3
//        for(i=0; i<18;i++)
//        {
//          glNormal(v[i]); glPoint(p[i]);
//        }
//      glEnd();
//    glEndList();

//    // The lence
//    GLMatrix mat2(Angle(M_PI_4),UnitVector<float,3>(0,0,1));
//    Point<float,3> cp(0,0,-0.3);
//    p[0] = cp + Vector<float,3>(0.0,0.05,0.0);
//    p[1] = cp + Vector<float,3>(0.0,0.08,-0.2);
//    v[0] = Vector<float,3>(0.0,1.0,0.15);

//    for(i=2; i<18;i+=2)
//    {
//      p[i]   = mat2*p[i-2];
//      p[i+1] = mat2*p[i-1];
//      v[i]   = mat2*v[i-2];
//    }

//    glNewList(_display_list+4, GL_COMPILE);
//      glBegin(GL_TRIANGLE_STRIP);    //  For Linse
//        for(i=0; i<18;i+=2)
//        {
//          glNormal(v[i]); glPoint(p[i]); glPoint(p[i+1]);
//        }
//      glEnd();
//    glEndList();

  }


  /*! void Camera::resetC(float z)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  NB!!! Only for the constructors.
   */
  void Camera::resetC(float z) {

    basisChange(_side, _up, _dir, _pos);  // Must repete because the virtual functions do not work proper jet.
    _ratio    = 1.0;
    _near_plane = 1.0;
    _far_plane  = 1000.0;
    _eye_dist  = 0.08;
    setFocalDist(z*50);
    setSurroundingSphere(Sphere<float,3>(Point<float,3>(0,0,0),1.0));
    if (!_display_list) makeGraphics();
    setCoordSysVisible();
    setFrustumVisible();
    _type_id  = GM_SO_TYPE_CAMERA;
    _culling = true;


//    _renderer = new DefaultRenderer;
//    _select_renderer = new SelectRenderer;
  }


//  /*! void Camera::select(int type_id)
//   *  \brief Pending Documentation
//   *
//   *  Pending Documentation
//   */
//  void Camera::select(int type_id) {


//    std::cout << "Camera::select()" << std::endl;
//    GL::OGL::clearSelectBuffer();
//    GL::OGL::bindSelectBuffer();

//    GLboolean depth_test_state;
//    glGetBooleanv( GL_DEPTH_TEST, &depth_test_state );
//    glEnable( GL_DEPTH_TEST );

//    glViewport(_x,_y,_w,_h);

//    const GL::GLProgram &select_prog = getSelectProgram();
//    select_prog.bind();
//    _scene->select(type_id, this);
//    select_prog.unbind();

//    if( !depth_test_state )
//      glDisable( GL_DEPTH_TEST );

//    GL::OGL::unbindSelectBuffer();
//  }



  /*! void Camera::setPerspective()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Camera::setPerspective() {

    _frustum = PerspectiveFrustum( _matrix_scene,
                                   _pos, _dir,_up,_side,
                                   _near_plane, _far_plane, _ratio, _angle_tan );
  }















































} // END namespace GMlib
