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



/*! \file gmscene.h
 *  \brief Interface to the Scene Object
 *
 *  Interface to the Scene Object
 *
 *  \todo
 *  Rewrite the Scene class documentation, and translate it into english
 */


#ifndef __gmSCENE_H__
#define __gmSCENE_H__


// local
#include "gmfrustum.h"

// gmlib
#include <core/types/gmpoint.h>
#include <core/utils/gmtimer.h>
#include <core/containers/gmarray.h>
#include <core/utils/gmsortobject.h>


namespace GMlib{

  class EventManager;
  class SceneObject;
  class DisplayObject;
  class RenderManager;
  class Camera;
  class Light;



  /*! \class Scene gmscene.h <gmScene>
   *  \brief Pending Documentation cleanup, and general documentation
   *
   *    Inneholder: Scenen er startnoden i ojecttreet
   *
   *        privat;
   *                En array av pekere til førstenode objektene i ojecttreet
   *        public:
   *                Konstuktør med mulige default verdier og sletter
   *                En display funksjon for displaying av objektet.
   *                En select funksjon for plukking(select) av objektet med mus.
   *                En simulate funksjon for at objektet kan bevege seg eller subobjekter.
   *                En find funksjon for å finne en funksjon med et gitt navn.
   *                En insert funksjon for å legge inn et nytt førstenode objekt
   *                En remove funksjon for å fjerne et førstenode objekt
   *                En operator [] som returnerer et gitt føstenode-element.
   *                En funksjon size() som gir antallet føstenode-element.
   *                En funksjon getMatrix(obj,mat,type) som gir transformasjonsmatrisen
   *                   fra scenen til og med obj hvis type er 1 og til obj hvis type er 2.
   */
  class Scene {
  public:
    Scene();
    Scene( SceneObject* obj );
    Scene( const Scene&  s );
    virtual ~Scene();

    SceneObject*                find(unsigned int name);
    SceneObject*                getActiveObject();
    Array<Light*>&              getLights();
    int                         getSize();
    void                        prepare();
    void                        simulate();

    virtual void                insert(SceneObject* obj);
    void                        remove(SceneObject* obj);

    Sphere<float,3>             getSphere();
    Sphere<float,3>             getSphereClean() const;


    void                        updateSelection(SceneObject *obj );
    const Array<SceneObject*>&        getSelectedObjects();
    bool                        isSelected( SceneObject* obj ) const;
    void                        removeSelections();

    double                      getElapsedTime();
    double                      getTimeScale();
    void                        setTimeScale(double s);
    bool                        isRunning();
    void                        resetTime();
    void                        start();
    void                        stop();

    void                        setEventManager( EventManager* mgr );

    void                        enabledFixedDt();
    void                        disableFixedDt();
    void                        setFixedDt( double dt );

    virtual RenderManager*      getRenderManager() const;
    void                        getDisplayableObjects( Array<DisplayObject*>& disp_objs, const Camera* cam) const;


    SceneObject*                operator [] (int i);
    SceneObject*                operator () (int i);
    Scene&                      operator =  (const Scene& sc);

  protected:
    Array<SceneObject*>         _sel_objs;

    virtual void                updateMaxObjects( int no_objects );


  private:
    Array<SceneObject*>         _scene;

    Array<Light*>               _lights;
    Array<HqMatrix<float,3> >   _matrix_stack;

    GMTimer                     _timer;
    bool                        _timer_active;
    double                      _timer_time_elapsed;
    double                      _timer_time_scale;
    double                      _timer_fixed_dt;
    bool                        _timer_fixed_dt_enabled;

    EventManager*               _event_manager;

  }; // END class Scene










  /*! double Scene::getElapsedTime()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Scene::getElapsedTime() {

    return _timer_time_elapsed;
  }


  /*! Array<Light*>& Scene::getLights()
   *  \brief Returns the scene's light sources.
   *
   *  Returns a reference to the Array containing the light sources
   *  in the scene
   *
   *  \return A reference to the scene's light source.
   */
  inline
  Array<Light*>& Scene::getLights() {

    return _lights;
  }


  inline
  const Array<SceneObject*>& Scene::getSelectedObjects() {

    return _sel_objs;
  }


  /*! double Scene::getTimeScale()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Scene::getTimeScale() {

    return _timer_time_scale;
  }


  /*! bool Scene::isRunning()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Scene::isRunning() {

    return _timer_active;
  }


  /*! void Scene::resetTime()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::resetTime() {

    _timer_time_elapsed = 0;
  }


  /*! void Scene::setTimeScale( double s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::setTimeScale( double s ) {

    _timer_time_scale = s;
  }


  /*! void Scene::start()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::start() {

    _timer_active = true;
    _timer.update();
  }


  /*! void   Scene::stop()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void   Scene::stop() {

    _timer_active = false;
  }

} // END namespace GMlib

#endif // __gmSCENE_H__
