/**********************************************************************************
**
** Copyright (C) 2013 Narvik University College
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



/*! \file gmmklmatmult.h
 *
 *  Interface for MKL-specific matrix multiplication operators.
 */

#ifndef __gmMATMULT_H__
#define __gmMATMULT_H__

#include "../../containers/gmdmatrix.h"
#include "../../containers/gmarray.h"

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b);
inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b);

} // namespace GMlib

#include "gmmklmatmult.c"

#endif // __gmMATMULT_H__