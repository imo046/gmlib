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


#ifndef __GM_SCENE_RENDER_DEFAULTSELECTRENDERER_H__
#define __GM_SCENE_RENDER_DEFAULTSELECTRENDERER_H__



#include "gmrenderer.h"


// gmlib
#include <opengl/gmframebufferobject.h>
#include <opengl/gmtexture.h>
#include <opengl/gmprogram.h>

namespace GMlib {

  class DisplayObject;

  class DefaultSelectRenderer : public Renderer {
  public:
    explicit DefaultSelectRenderer();
    virtual ~DefaultSelectRenderer();

    const DisplayObject*            findObject(int x, int y) const;
    DisplayObject*                  findObject(int x, int y);
    Array<const DisplayObject*>     findObjects(int xmin, int ymin, int xmax, int ymax) const;
    Array<DisplayObject*>           findObjects(int xmin, int ymin, int xmax, int ymax);


    void                            select(int what);


    void                            setSelectRboName( const std::string& name ) { _rbo_color.setName(name); }

    /* Virtual from Renderer */
    void                            prepare();
    void                            reshape(const Vector<int,2> &size);

  protected:
    /* Virtual from Renderer */
    void                            render() {}
    void                            swap() {}


    mutable Array<DisplayObject*>   _objs;


  private:
    GL::Program                     _prog;

    GL::FramebufferObject           _fbo;
    GL::Texture                     _rbo_color;
    GL::Texture                     _rbo_depth;

    Vector<int,2>                   _size;

  }; // END class DefaultRendererWithSelect



} // END namespace GMlib





#endif // __GM_SCENE_RENDER_DEFAULTSELECTRENDERER_H__