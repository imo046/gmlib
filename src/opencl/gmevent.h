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

//! \file gmevent.h


#ifndef __GM_OPENCL_GMEVENT_H__
#define __GM_OPENCL_GMEVENT_H__


// local
#include "gmopencl.h"

// stl
#include <string>

namespace GMlib {

namespace CL {


  class Event : public CLObject<cl::Event> {
  public:
    Event();
    Event( const std::string& name );

  }; // END class Event



} // END namespace CL

} // END namespace GMlib


#endif // __GM_OPENCL_GMEVENT_H__
