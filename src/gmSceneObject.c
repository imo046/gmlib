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


namespace GMlib {



  /*! void SceneObject::edit(int selector_id)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit(int selector_id) {}


  /*! void SceneObject::edit(SceneObject* lp)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit(SceneObject* lp) {}


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
  void SceneObject::editPos(Vector<float,3> delta) {}


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
  const GLMatrix& SceneObject::getMatrixGlobal() const {

    return  _present;
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
  Sphere<float,3>	SceneObject::getSurroundingSphere() const	{

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
  void SceneObject::selectEvent(int selector_id) {}



  /*! void SceneObject::setCollapsed(bool c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setCollapsed(bool c) {

    _collapsed = c;
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
  void SceneObject::setVisible(bool v) {

    _visible = v;
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


  /*! void SceneObject::setMaterial(const Material& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setMaterial(const Material& m) {}


  /*! void SceneObject::_display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::_display() {
    if(!_active) {
    /*		if(_type_id != GM_SO_TYPE_SELECTOR_GRID)
      {
        glPushMatrix();
        Sphere3D sp(_global_sphere,10,10);
        sp.display();
        glPopMatrix();
      }
    */
      glPushMatrix();
        if(_local_cs) _present.mult();
        _scale.glScaling();


        if(_collapsed) {

          glPushAttrib( GL_LIGHTING_BIT );
            glDisable( GL_LIGHTING );

            if(_selected)
              _marked.glSet();
            else
              _default.glSet();

            displayCollapsed();

          glPopAttrib();
        }
        else localDisplay();
      glPopMatrix();
    }
  }


  /*! void SceneObject::_select( int what )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::_select( int what ) {

//    cout << "Evaluationg select request" << endl;
//    cout << "\t_active:  " << _active << endl;
//    cout << "\twhat:     " << what << endl;
//    cout << "\t_type_id: " << _type_id << endl;


    if( !_active && ( what == 0 || what == _type_id || ( what < 0 && what + _type_id != 0 ) ) ) {
//      cout << "\t\tPaint Select" << endl;

      glPushMatrix(); {

        if( _local_cs )
          _present.mult();

        _scale.glScaling();
        GLColor name(getName());
        name.glSet();

        if( _collapsed )
          displayCollapsed();
        else
          localSelect();

      } glPopMatrix();
    }
  }

}