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

/*! \file gmrendermanager.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */


#include "gmrenderer.h"

// local
#include "../gmfrustum.h"
#include "../camera/gmcamera.h"

// stl
#include <cassert>


namespace GMlib {

  Renderer::Renderer(Scene *scene) {

    _scene = scene;
    _initialized = false;
  }

  Renderer::~Renderer() {}

  bool Renderer::isStereoEnabled() const {

    return _stereo;
  }

  void Renderer::enableStereo(bool enable) {

    _stereo = enable;
  }

  int Renderer::getBufferHeight() const {

    return _buffer_height;
  }

  int Renderer::getBufferWidth() const {
  }

  bool Renderer::isInitialized() const {

    return _initialized;
  }

  void Renderer::markAsInitialized() {

    _initialized = true;
  }

  void Renderer::setBufferSize(int w, int h) {

    _buffer_width = w;
    _buffer_height = h;
  }






  SingleObjectRenderer::SingleObjectRenderer(Scene *scene) : Renderer(scene) {

  }

  MultiObjectRenderer::MultiObjectRenderer(Scene *scene) : Renderer(scene) {
  }








  DisplayRenderer::DisplayRenderer(Scene *scene) : MultiObjectRenderer(scene), _fbo("DefaultRenderBufferObject"), _rbo_color(GL_TEXTURE_2D), _rbo_select(GL_TEXTURE_2D), _rbo_depth() {


    // Color rbo texture parameters
    _rbo_color.setParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_color.setParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_color.setParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_color.setParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Select rbo texture parameters
    _rbo_select.setParameteri( GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    _rbo_select.setParameteri( GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    _rbo_select.setParameterf( GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    _rbo_select.setParameterf( GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Bind renderbuffers to framebuffer.
    _fbo.attachRenderbuffer( _rbo_depth, GL_DEPTH_ATTACHMENT );
    _fbo.attachTexture2D( _rbo_color,  GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );
    _fbo.attachTexture2D( _rbo_select, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1 );

    // Bind color renderbuffer to color framebuffer
    _fbo_color.attachTexture2D( _rbo_color, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

    // Bind select renderbuffer to select framebuffer
    _fbo_select.attachTexture2D( _rbo_select, GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 );

  }

  void DisplayRenderer::prepare(Array<SceneObject*>& objs, Camera *cam) {

    // Compute frustum/frustum-matrix, set glViewport
    cam->setupDisplay();


    const Frustum &frustum = cam->getFrustum();
    const bool is_culling = cam->isCulling();

    objs.resetSize();

    assert( _scene );

    if(is_culling)
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->culling( objs, frustum );
    else
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->fillObj( objs );
  }

  void DisplayRenderer::render(Array<SceneObject*>& objs, const Array<Camera *> &cameras) {

    // Clear render buffers
    _fbo.clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    _fbo_select.clear( GMcolor::Black, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    // Tell renderer that rendering is begining
    {
      _fbo.bind();

      GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
      glDrawBuffers( 2, buffers );

    }

    // Rendering
    {

      for( int i = 0; i < cameras.getSize(); ++i ) {


        Camera *cam = cameras(i);
        cam->markAsActive();

        prepare( objs, cam );

        for( int i = 0; i < objs.getSize(); i++ )
          objs[i]->display( cam );

        cam->markAsInactive();
      }
    }

    // Tell renderer that rendering is ending
    {
      _fbo.unbind();
    }
  }

  void DisplayRenderer::renderSelect(Array<SceneObject*>& objs, const Array<Camera *> &cameras) {

    // Prepare renderer for rendering
    GL::OGL::clearRenderBuffer();

    // Tell renderer that rendering is begining
    GL::OGL::bindRenderBuffer();
    {

      for( int i = 0; i < cameras.getSize(); ++i ) {

        Camera *cam = cameras(i);
        cam->markAsActive();

        prepare( objs, cam);

        for( int i = 0; i < objs.getSize(); ++i )
          objs[i]->displaySelection( cam );

        cam->markAsInactive();
      }

    // Tell renderer that rendering is ending
    }
    GL::OGL::unbindRenderBuffer();
  }

  void DisplayRenderer::resize(int w, int h) {

    setBufferSize( w, h );

    _rbo_depth.createStorage( GL_DEPTH_COMPONENT, w, h );
    _rbo_color.texImate2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
    _rbo_select.texImate2D( 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0x0 );
  }








  SelectRenderer::SelectRenderer(Scene *scene) : MultiObjectRenderer( scene ) {

    GL::OGL::createSelectBuffer();
  }

  SceneObject *SelectRenderer::findObject(int x, int y) {

    Color c;
    GL::OGL::bindSelectBuffer();
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte*)(&c));
    GL::OGL::unbindSelectBuffer();

    SceneObject *obj = _scene->find(c.get());
    if( obj )
      obj->setSelected(true);

    return obj;
  }

  Array<SceneObject*> SelectRenderer::findObjects(int xmin, int ymin, int xmax, int ymax) {

    Array<SceneObject* > sel;
    int dx=(xmax-xmin)+1;
    int dy=(ymax-ymin)+1;


    Color* pixels = new Color[dx*dy];
    GL::OGL::bindSelectBuffer();
    glReadPixels(xmin,ymin,dx-1,dy-1,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)pixels);
    GL::OGL::unbindSelectBuffer();


    int ct = 0;
    Color c;
    for(int i = ymin; i < ymax; ++i) {
      for(int j = xmin; j < xmax; ++j) {
        c = pixels[ct++];
        SceneObject *tmp = _scene->find(c.get());
        if(tmp)
          if(!tmp->getSelected()) { sel.insertAlways(tmp); tmp->setSelected(true); }
      }
    }
    delete [] pixels;

    return sel;
  }

  void SelectRenderer::prepare(Array<SceneObject *> &objs, Camera *cam){


    const Frustum &frustum = cam->getFrustum();
    const bool is_culling = cam->isCulling();

    objs.resetSize();

    assert( _scene );

    if(is_culling)
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->culling( objs, frustum );
    else
      for( int i = 0; i < _scene->getSize(); ++i )
        (*_scene)[i]->fillObj( objs );

  }

  void SelectRenderer::select(Array<SceneObject*>& objs, Camera *cam, int type_id) {


    prepare( objs, cam );




    GL::OGL::clearSelectBuffer();




    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    GL::OGL::bindSelectBuffer();

//    GLboolean depth_test_state;
//    glGetBooleanv( GL_DEPTH_TEST, &depth_test_state );
    glEnable( GL_DEPTH_TEST );
    {

      // Compute frustum/frustum-matrix, set glViewport
      cam->setupDisplay();

      const GL::GLProgram select_prog("select");

      select_prog.bind();

      for( int i=0; i < objs.getSize(); i++ )
        objs[i]->select( type_id, cam );

      select_prog.unbind();


    }
//    if( !depth_test_state )
      glDisable( GL_DEPTH_TEST );

    GL::OGL::unbindSelectBuffer();

  }

  void SelectRenderer::resize(int w, int h) {

    GL::OGL::setSelectBufferSize( w, h );
  }


} // END namespace GMlib
