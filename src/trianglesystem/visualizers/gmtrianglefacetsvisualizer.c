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



/*! \file gmtrianglefacetsvisualizer.h
 *
 *  TriangleFacetsVisualizer implementations
 */

namespace GMlib {

  template <typename T>
  TriangleFacetsVisualizer<T>::TriangleFacetsVisualizer() {

    _tf = 0x0;
  }

  template <typename T>
  TriangleFacetsVisualizer<T>::~TriangleFacetsVisualizer() {}

  template <typename T>
  void GMlib::TriangleFacetsVisualizer<T>::fillStandardVBO(
      GLVertexBufferObject<GMlib::GLVertexNormal> &vbo,
      unsigned int &no_vertices, const GMlib::TriangleFacets<T> *tf) {

    no_vertices = tf->getSize();
    GLVertexNormal vertices[no_vertices];

    for( int i = 0; i < no_vertices; i++ ) {

      TSVertex<float> *v = tf->getVertex(i);
      const Point<float,3> &pos = v->getPos();
      const Vector<float,3> &nor = v->getDir();

      vertices[i].x = pos(0);
      vertices[i].y = pos(1);
      vertices[i].z = pos(2);

      vertices[i].nx = nor(0);
      vertices[i].ny = nor(1);
      vertices[i].nz = nor(2);
    }

    vbo.bind();
    vbo.createBufferData( no_vertices * sizeof(GLVertexNormal), vertices, GL_STATIC_DRAW );
    vbo.unbind();
  }

  template <typename T>
  std::string TriangleFacetsVisualizer<T>::getIdentity() const {

    return "TriangleFacets Visualizer";
  }

  template <typename T>
  inline
  void TriangleFacetsVisualizer<T>::replot() {}

  template <typename T>
  void TriangleFacetsVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _tf = dynamic_cast<TriangleFacets<T>*>( obj );
  }



} // END namespace GMlib
