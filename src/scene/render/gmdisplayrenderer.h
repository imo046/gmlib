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



/*! \file gmdisplayrender.h
 *  \brief Pending Documentation
 *
 *  Pending Documentation
 */

#ifndef __gmDISPLAYRENDERER_H__
#define __gmDISPLAYRENDERER_H__


#include "gmrenderer.h"

// local
#include "../camera/gmcamera.h"
#include "../visualizers/gmvisualizerstdrep.h"

// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmrenderbufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/bufferobjects/gmvertexbufferobject.h>


namespace GMlib {


  class DisplayRenderer : public MultiObjectRenderer {
  public:
    DisplayRenderer( Scene* scene );

    const GL::Texture&      getRenderTexture() const;
    const GL::Texture&      getSelectTexture() const;

    virtual void            render(Array<DisplayObject*>& objs, const Array<Camera*>& cameras ) const;

    /* virtual from Renderer */
    void                    resize(int w, int h);


  private:
    /* Rendering */
    GL::FramebufferObject   _fbo;
    GL::Texture             _rbo_color;
    GL::RenderbufferObject  _rbo_depth;

    /* Selection rendering */
    GL::FramebufferObject   _fbo_select;
    GL::Texture             _rbo_select;

    GL::FramebufferObject   _fbo_select_depth;
    GL::RenderbufferObject  _rbo_select_depth;

    void                    render(DisplayObject *obj, Camera *cam) const;
    void                    renderCoordSys( Camera *cam ) const;
    void                    renderSelection(DisplayObject *obj, Camera *cam) const;
    void                    renderSelectionDepth(DisplayObject *obj, Camera *cam) const;

  }; // END class DisplayRenderer










  inline
  const GL::Texture& DisplayRenderer::getRenderTexture() const {

    return _rbo_color;
  }

  inline
  const GL::Texture& DisplayRenderer::getSelectTexture() const {

    return _rbo_select;
  }

  inline
  void DisplayRenderer::render( DisplayObject* obj, Camera* cam ) const {

    if( obj != cam ) {

      const HqMatrix<float,3> &mvmat = obj->getModelViewMatrix(cam);
      const HqMatrix<float,3> &pmat = obj->getProjectionMatrix(cam);

      if(obj->isCollapsed()) {

        const GL::GLProgram &prog = VisualizerStdRep::getInstance()->getRenderProgram();
        prog.bind();
        prog.setUniform( "u_mvmat", mvmat, 1, true );
        prog.setUniform( "u_mvpmat", pmat * mvmat, 1, true );
        VisualizerStdRep::getInstance()->set(obj);
        VisualizerStdRep::getInstance()->display();
        prog.unbind();
      }
      else {

        const Array<Visualizer*>& visus = obj->getVisualizers();
        for( int i = 0; i < visus.getSize(); ++i ) {

          const GL::GLProgram &prog = visus(i)->getRenderProgram();
          prog.bind();
          prog.setUniform( "u_mvmat", mvmat, 1, true );
          prog.setUniform( "u_mvpmat", pmat * mvmat, 1, true );
          visus(i)->display();
          prog.unbind();
        }

        obj->localDisplay();
      }
    }
  }

  inline
  void DisplayRenderer::renderCoordSys(Camera *cam) const {

      // Get matrix of present camera and
      HqMatrix<float,3> base_mvmat;
      HqMatrix<float,3> mvmat = cam->SceneObject::getMatrix();
      mvmat[0][3] = 0.0f;
      mvmat[1][3] = 0.0f;
      mvmat[2][3] = 0.0f;
      const HqMatrix<float,3> &pmat = cam->getProjectionMatrix();

      // Compute the position of the of the "coordinate-system visualization"
      // Relevant to the camera position
      float hh = -1.5*cam->_near_plane*cam->_angle_tan;
      Point<float,3> cp(cam->_ratio*hh, hh, -cam->_near_plane-1.0);
      base_mvmat.translateGlobal(cp);
      mvmat.translateGlobal(cp);

      // Bind program
      const GL::GLProgram &prog = VisualizerStdRep::getInstance()->getRenderProgram();
      prog.bind();

      prog.setUniform( "u_mvmat", mvmat, 1, true );
      prog.setUniform( "u_mvpmat", pmat * mvmat, 1, true );

      // Render "coord-sys"
      VisualizerStdRep::getInstance()->set(cam);
      VisualizerStdRep::getInstance()->display();


      prog.unbind();
  }

  inline
  void DisplayRenderer::renderSelection(DisplayObject *obj, Camera *cam) const {

    if( obj != cam && obj->isSelected() ) {

      const GL::GLProgram render_select_prog("render_select");
      render_select_prog.bind();
      render_select_prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(cam), 1, true );

      if( obj->isCollapsed() ) {

        VisualizerStdRep::getInstance()->set(obj);
        VisualizerStdRep::getInstance()->select();
      }
      else {

        const Array<Visualizer*>& visus = obj->getVisualizers();
        for( int i = 0; i < visus.getSize(); ++i )
          visus(i)->select();

        obj->localSelect();
      }

      render_select_prog.unbind();
    }
  }

  inline
  void DisplayRenderer::renderSelectionDepth(DisplayObject *obj, Camera *cam) const {

    if(obj != cam) {

      const GL::GLProgram render_select_prog("render_select");
      render_select_prog.bind();
      render_select_prog.setUniform( "u_mvpmat", obj->getModelViewProjectionMatrix(cam), 1, true );

      if( obj->isCollapsed() ) {

        VisualizerStdRep::getInstance()->set(obj);
        VisualizerStdRep::getInstance()->select();
      }
      else {

        const Array<Visualizer*>& visus = obj->getVisualizers();
        for( int i = 0; i < visus.getSize(); ++i )
          visus(i)->select();

        obj->localSelect();
      }

      render_select_prog.unbind();
    }
  }

  inline
  void DisplayRenderer::render(Array<DisplayObject*>& objs, const Array<Camera *> &cameras) const {

    // Clear render buffers
    _fbo.clear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    _fbo_select.clearColorBuffer( GMcolor::Black );
    _fbo_select_depth.clear( GL_DEPTH_BUFFER_BIT );

    // Render
    for( int i = 0; i < cameras.getSize(); ++i ) {

      Camera *cam = cameras(i);
      cam->markAsActive();

      prepare( objs, cam );

      // Object rendering
      _fbo.bind(); {

        // Render coordinate-system visualization
        renderCoordSys( cam );

        // Render the scene objects
        for( int j = 0; j < objs.getSize(); ++j ) {
          render( objs[j], cam);
        }

      } _fbo.unbind();

      // Selection rendering - render to depth buffer
      _fbo_select_depth.bind(); {

        ::glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        for( int j = 0; j < objs.getSize(); ++j )
          renderSelectionDepth( objs[j], cam);

      } _fbo_select_depth.unbind();

      // Selection rendering - render
      _fbo_select.bind(); {

        GLint depth_mask, depth_func;
        ::glGetIntegerv( GL_DEPTH_WRITEMASK, &depth_mask );
        ::glGetIntegerv( GL_DEPTH_FUNC, &depth_func);

        ::glDepthFunc( GL_LEQUAL );
        ::glDepthMask( GL_FALSE );

        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        for( int j = 0; j < objs.getSize(); ++j )
          renderSelection( objs[j], cam );

        ::glDepthFunc( depth_func );
        ::glDepthMask( depth_mask );

      } _fbo_select.unbind();







      cam->markAsInactive();
    }
  }



} // END namespace GMlib

#endif // __gmDISPLAYRENDERER_H__
