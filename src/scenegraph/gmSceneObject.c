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



/*! \file gmSceneObject.c
 *  \brief Inline ScenObject class implementations
 *
 *  Implementation of the SceneObject class.
 *
 *  \date   2008-08-03
 */

#include "gmVisualizer.h"


namespace GMlib {


  /*! void SceneObject::_display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::_display( Camera* cam ) {

    if(!_active) {

      if(_collapsed)
        _std_rep_visu->display( cam );
      else
        localDisplay( cam);
    }
  }

  /*! void SceneObject::_select( int what, Camera* cam )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::_select( int what, Camera* cam ) {

    if( !_active && ( what == 0 || what == _type_id || ( what < 0 && what + _type_id != 0 ) ) ) {

      if( _collapsed )
        _std_rep_visu->select( cam, getName() );
      else
        localSelect( cam, getName() );
    }
  }


  /*! void SceneObject::edit(int selector_id)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit( int /* selector_id */ ) {}


  /*! void SceneObject::edit(SceneObject* lp)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit( SceneObject* /* obj */ ) {}


  /*! void SceneObject::edit()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit() {}


  /*! void SceneObject::editPos(Vector<float,3> delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::editPos( Vector<float,3> /* delta*/  ) {}


  /*! void SceneObject::enableChildren( bool enable = true )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::enableChildren( bool enable ) {

    for(int i=0;i<_children.getSize();i++) _children[i]->setVisible(enable);
  }


  /*! bool SceneObject::flipSelected()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::flipSelected() {

    _selected = !_selected;

    if(_selected)
      edit();
    return _selected;
  }


  /*! Point<float,3> SceneObject::getCenterPos() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Point<float,3> SceneObject::getCenterPos() const	{

    return  getSurroundingSphere().getPos();
  }


  /*! Array<SceneObject*>& SceneObject::getChildren()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Array<SceneObject*>& SceneObject::getChildren(){

    return _children;
  }


  /*! const char* SceneObject::getIdentity() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  std::string SceneObject::getIdentity() const {

    return "Scene Object";
  }


  /*! const GL_Matrix& SceneObject::getMatrixGlobal() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const HqMatrix<float,3>& SceneObject::getMatrixGlobal() const {

    return _present;
  }


  /*! unsigned int SceneObject::getName() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned int SceneObject::getName() const {

    return _name;
  }


  inline
  SceneObject* SceneObject::getParent() {

    return _parent;
  }


  inline
  Scene* SceneObject::getScene() {

    return _scene;
  }


  /*! bool SceneObject::getSelected()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::getSelected() {

    return _selected;
  }


  /*! Sphere<float,3>	SceneObject::getSurroundingSphere() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere<float,3> SceneObject::getSurroundingSphere() const	{

    return  _global_total_sphere;
  }


  /*! int SceneObject::getTypeId()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  int SceneObject::getTypeId() {

    return _type_id;
  }


  /*! bool SceneObject::isCollapsed() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isCollapsed() const {

    return _collapsed;
  }


  inline
  bool SceneObject::isOpaque() const {

    return _opaque;
  }


  /*! bool SceneObject::isSelected() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isSelected() const {

    return _selected;
  }


  /*! bool SceneObject::isVisible() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isVisible() const {

    return _visible;
  }


  /*! void SceneObject::selectEvent(int selector_id)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::selectEvent( int /* selector_id */ ) {}



  /*! void SceneObject::setCollapsed(bool c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setCollapsed(bool c) {

    _collapsed = c;
  }


  inline
  void SceneObject::setOpaque( bool o ) {

    _opaque = o;
  }



  /*! void SceneObject::setParent( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setParent( SceneObject* obj ) {

    _parent = obj;
  }



  /*! void SceneObject::setSelected( bool s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setSelected( bool s ) {

    _selected = s;
  }



  /*! void SceneObject::setVisible(bool v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setVisible( bool v, int prop ) {

    _visible = v;

    // Propagate Children
    if( prop != 0 ) {

      if( prop > 0)
        prop -= 1;

      for( int i = 0; i < _children.getSize(); i++ )
        _children[i]->setVisible( v, prop );
    }
  }



  /*! void SceneObject::toggleCollapsed()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::toggleCollapsed() {

    return _collapsed = !_collapsed;
  }

  /*! void SceneObject::toggleVisible()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::toggleVisible() {

    return _visible =! _visible;
  }

}