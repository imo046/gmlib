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



/*! \file gmVDefault.h
 *
 *  Interface for the VDefault class.
 *  Default Visualizer for Displayable Curves, Surfaces, etc.
 *
 *  \date   2009-01-27
 */

#ifndef __gmVDEFAULT_H__
#define __gmVDEFAULT_H__


// STL includes
#include <string>

// GMlib includes
#include "gmVisualizer.h"


namespace GMlib {

  template <typename T, int n>
  class VDefault : public Visualizer<T,n> {
  public:
    VDefault();
    VDefault( const VDefault<T,n>& copy );

    void          display();

    std::string   getIdentity() const;


  }; // END class VDefault

} // END namespace GMlib

// Include VDefault class function implementations
#include "gmVDefault.c"


#endif // __gmVDEFAULT_H__