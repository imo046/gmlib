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



/*! \file gmsceneobject.cpp
 *
 *  Implementation of the SceneObject class.
 */


#include "gmsceneobject.h"

#include "gmdisplayobject.h"
#include "light/gmlight.h"

// gmlib
#include <core/types/gmpoint.h>

// stl
#include <string>


namespace GMlib {




  unsigned int SceneObject::_free_name = 1;


  /*! SceneObject( const Vector<float,3>& trans  = Vector<float,3>(0,0,0), const Point<float,3>&  scale   = Point<float,3>(1,1,1), const Vector<float,3>& rotate = Vector<float,3>(1,0,0), Angle a=0 )
   *  \brief default and standard constructor
   *
   *  Default and standard constructor.
   *  First rotates, then scales and finaly translates the object.
   */
  SceneObject::SceneObject (
    const Vector<float,3>& trans_vector,
    const Point<float,3>&  scale,
    const Vector<float,3>& rot_axel,
    Angle a
  ) :_scale(scale),_select_prog("select") {

    _parent = 0;
    _matrix.translate(trans_vector);

    Vector<float,3> ra = rot_axel;
    Vector<float,3> lu = ra.getLinIndVec();
    Vector<float,3> u  = lu ^ ra;
    Vector<float,3> v  = ra ^ u;

    _matrix.rotateGlobal(a, u, v);

    _name	            = _free_name++;
    _active	          = false;
    _local_cs         = true;
    _type_id          = GM_SO_TYPE_SCENEOBJECT;
    _is_part          = false;
    _visible          = true;
    _selected         = false;

    _children.clear();
  }


  /*! SceneObject::SceneObject( const SceneObject& d )
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  SceneObject::SceneObject( const SceneObject& copy ) :
    _select_prog( copy._select_prog ) {

    _copy_of          = &copy;

    _parent           = 0;
    _matrix	          = copy._matrix;
    _sphere	          = copy._sphere;
    _scale            = copy._scale;
    _name	            = _free_name++;
    _active	          = false;
    _local_cs         = copy._local_cs;
    _type_id          = copy._type_id;
    _is_part          = false;
    _visible          = copy._visible;
    _selected         = copy._selected;


    // update children
    for( int i = 0; i < copy._children.getSize(); ++i ) {

      SceneObject *child_copy = copy._children(i)->makeCopy();
      if( child_copy )
        _children += child_copy;
    }
  }


  /*! SceneObject::~SceneObject()
   *  \brief Default Destructor
   *
   *  Default Destructor
   */
  SceneObject::~SceneObject() {
    for(int i=0; i < _children.getSize(); i++) {
      if( _children[i] ) {

        _children[i]->setParent(0);
        remove( _children[i] );
        delete _children[i];
      }
    }

    for(int i=0; i < _scene_object_attributes.getSize(); i++)
      delete _scene_object_attributes[i];
  }

  ArrayT<SceneObjectAttribute*>&
  SceneObject::accessSceneObjectAttributes() {
    return _scene_object_attributes;
  }


  /*! void SceneObject::_fillObj( Array<SceneObject*>& )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::fillObj( Array<DisplayObject*>& disp_objs ) {

    if(_sphere.isValid()) {

      DisplayObject *disp_obj = dynamic_cast<DisplayObject*>(this);
      if( disp_obj )
        disp_objs += disp_obj;
    }
    for(int i=0; i< _children.getSize(); i++)
      _children[i]->fillObj(disp_objs);
  }


  /*! int SceneObject::prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* mother=0)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  int SceneObject::prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* parent) {

    int nr = 1;
    _scene  = s;

    _parent=parent;

    Light * pl  = dynamic_cast<Light *>(this);
    if(pl) obj += pl;

    mat.push();

    prepareDisplay(mat.back());
    mat.back() = mat.back() * getMatrix();

    _present = mat.back();
    _global_total_sphere = _global_sphere = _present*_sphere;


    if(_scale.isActive()) {

      _global_sphere *= _scale.getMax();
      _global_sphere %= _scale.getScale();
      _global_total_sphere *= _scale.getMax();
      _global_total_sphere %= _scale.getScale();
    }
    for( int i = 0; i < _children.getSize(); i++ ) {

      nr += _children[i]->prepare(obj,mat,s,this);
      _global_total_sphere += _children[i]->getSurroundingSphere();
    }

    mat.pop();
    return nr;
  }


  /*! void SceneObject::prepareDisplay( const HqMatrix<float,3>& mat )
   *  \brief Pending Documentation
   *
   *  Made specially for DisplayObject's
   */
  void SceneObject::prepareDisplay( const HqMatrix<float,3>& /*mat*/ ) {}


  /*! void culling( Array<SceneObject*>&, const Frustum& );
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::culling( Array<DisplayObject*>& disp_objs, const Frustum& f ) {

    //if(!_visible) return;
    if(!_sphere.isValid())
      return;

    int k = f.isInterfering(getSurroundingSphere());

    if( k < 0 )
      return;	// Outside

    // Inside
    if( k > 0 ) {

      if(_visible) {
        DisplayObject *disp_obj = dynamic_cast<DisplayObject*>(this);
        if(disp_obj)
          disp_objs += disp_obj; // added check for visible, children don't automatic follow anymore
      }

      for( int i = 0; i < _children.getSize(); i++ )
//        _children[i]->culling( disp_objs, f );
        _children[i]->fillObj( disp_objs );
    }
    else { // if(k == 0)     Intersecting

      if( _visible && f.isInterfering( _global_sphere ) >= 0 ) {
        DisplayObject *disp_obj = dynamic_cast<DisplayObject*>(this);
        if(disp_obj)
          disp_objs += disp_obj; // added check for visible, children don't automatic follow anymore
      }
      for( int i = 0; i < _children.getSize(); i++ )
        _children[i]->culling( disp_objs, f );
    }


  }


  /*! SceneObject* SceneObject::find(unsigned int name)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  SceneObject* SceneObject::find(unsigned int name) {

    SceneObject* d;

    if(name == _name)	return this;
    for(int i=0; i < _children.getSize(); i++)
      if( (d = _children(i)->find(name)) ) return d;
    return 0;
  }

  /*! HqMatrix<flaot,3>& SceneObject::getMatrix()
   *  \brief Pending Documentation
   *
   *  Made specially for Cameras
   */
  const HqMatrix<float,3>& SceneObject::getMatrix() const	{

    return _matrix;
  }

  HqMatrix<float,3>& SceneObject::getMatrix()	{

    return _matrix;
  }


  /*! const	GL_Matrix& SceneObject::getMatrixParentGlobal() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  const	HqMatrix<float,3>& SceneObject::getMatrixParentGlobal() const {

    if(_parent)
      return _parent->getMatrixGlobal();

    static HqMatrix<float,3> id;
    return id;
  }




  /*! Sphere<float,3>	SceneObject::getSurroundingSphereClean() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3> SceneObject::getSurroundingSphereClean() const {

    Sphere<float,3> sp;

    for(int i=0; i< _children.getSize(); i++)
      sp += _children(i)->getSurroundingSphereClean();

    if(_type_id!=GM_SO_TYPE_CAMERA && _type_id!=GM_SO_TYPE_LIGHT)
      sp += _global_sphere;

    return sp;
  }



  /*! void SceneObject::insert(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::insert(SceneObject* obj) {

    if(obj)
    {
      _children.insert(obj);
      obj->_parent=this;
    }
  }



  /*! void localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localDisplay() {}

  /*! void localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localSelect()  {}


  /*! void localSimulate(double dt)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::localSimulate( double /*dt*/ ) {}


  /*! void SceneObject::remove(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::remove(SceneObject* obj) {

    if(obj)
      if(!_children.remove(obj))
        for(int i=0; i< _children.getSize(); i++)
          _children[i]->remove(obj);
  }


  /*! void SceneObject::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::reset() {

    _matrix.reset();
  }


  /*! void SceneObject::rotate(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::rotate(Angle a, const Vector<float,3>& rot_axel) {

    _matrix.rotate(a, rot_axel);
  }


  /*! void SceneObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& rot_axel) {

    _matrix.rotate(a, rot_axel, p);
  }


  /*! void SceneObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::rotateGlobal( Angle a, const Vector<float,3>& rot_axel ) {

    _matrix.rotateGlobal(a, rot_axel);
  }


  /*! void SceneObject::rotateGlobal(Angle a, const Point<float,3>& p, const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::rotateGlobal(Angle a, const Point<float,3>& p, const UnitVector<float,3>& rot_axel) {

    _matrix.rotateGlobal(a, rot_axel, p);
  }

  void SceneObject::rotate(const UnitQuaternion<float>& q) {

    _matrix.rotate(q);
  }

  void SceneObject::rotateGlobal(const UnitQuaternion<float>& q) {

    _matrix.rotateGlobal(q);
  }


  /*! void SceneObject::scale(const Point<float,3>& scale_factor)
   *  \brief Pending Documentation
   *
   *  ( Only geometry )
   */
  void SceneObject::scale(const Point<float,3>& scale_factor) {
    for(int i=0; i<_children.getSize(); i++)
    {
      Point<float,3> tr = -(_children[i]->_matrix*Point<float,3>(0.0f));
      _children[i]->translate(scale_factor%tr);
      _children[i]->scale(scale_factor);
    }
    _scale.scale(scale_factor);
    _sphere = _scale.scaleSphere(_sphere);
  }


  void SceneObject::setIsPart( bool is_part ) {

    _is_part = is_part;
  }

  void SceneObject::setMatrix( const HqMatrix<float,3>& mat ) {

    _matrix = mat;
  }

  void SceneObject::setSelectProgram(const GL::GLProgram &prog) {

    _select_prog = prog;
  }

  /*! void SceneObject::setSurroundingSphere(const Sphere<float,3>& b)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::setSurroundingSphere(const Sphere<float,3>& b) {

    _sphere = b;
  }


  /*! void SceneObject::_simulate( double dt )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::simulate( double dt ) {

    localSimulate(dt);

    for(int i=0; i< _children.size(); i++)
      _children[i]->simulate(dt);
  }

  /*! void SceneObject::translate(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In local coordinates.**
   */
  void SceneObject::translate(const Vector<float,3>& trans_vector) {

    _matrix.translate(trans_vector);
  }


  /*! void SceneObject::translateGlobal(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In Scene Coordinates **
   */
  void SceneObject::translateGlobal(const Vector<float,3>& trans_vector) {

    _matrix.translateGlobal(trans_vector);
  }


  /*! void SceneObject::updateSurroundingSphere(const Point<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void SceneObject::updateSurroundingSphere(const Point<float,3>& p) {

    _sphere += p;
  }

}
