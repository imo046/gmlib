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


#ifndef __gmINDEXBUFFEROBJECT_H__
#define __gmINDEXBUFFEROBJECT_H__


#include "gmbufferobject.h"


namespace GMlib {

  /*! class IndexBufferObject : public GLBufferObject
   *
   *
   * \todo Might be optimized for smaller groups of indices
   * \todo by changing the buffer representation
   * \todo to unisgned byte or unsigned short
   */
  class IndexBufferObject : public BufferObject {
  public:
    explicit IndexBufferObject();
    explicit IndexBufferObject( const std::string& name );

    void              createBufferData( unsigned int no_indices, const GLvoid* data, GLenum usage );

    virtual void      draw();
    const GLenum&     getMode() const;
    const GLenum&     getType() const;
    const GLsizei&    getTypeSize() const;

  private:
    GLenum      _mode;
    GLenum      _type;
    GLsizei     _type_size;

  }; // END class IndexBufferObject


  class TrianglesIBO : public IndexBufferObject {
  public:
    explicit TrianglesIBO();
    explicit TrianglesIBO( const std::string& name );

    virtual void      draw();

    int       _no_indices;

  private:

    void      init();

  }; // END class TrianglesIBO


  class TriangleStripIBO : public IndexBufferObject {
  public:
    explicit TriangleStripIBO();
    explicit TriangleStripIBO( const std::string& name );

    virtual void      draw();
    virtual void      fill(int m1, int m2);

  private:
    int       _no_strips;
    int       _no_indices_per_strip;
    GLsizei   _strip_size;

    void      init();

  }; // END class TriangleStripIBO


} // END namespace GMlib

#endif // __gmINDEXBUFFEROBJECT_H__