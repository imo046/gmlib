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



/*! \file gmcblasmatmult.c
 *
 *  Implementation of generic CBLAS matrix multiplication operators.
 */

#include "cblas_netlib_reference.h"

namespace GMlib
{

inline
const DMatrix<float>&  operator*(const DMatrix<float>& m, const DMatrix<float>& b)
{
	static DMatrix<float> r;
	static Array<float> cA;
	static Array<float> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(float));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(float));
	}

	static Array<float> work;
	work.setSize(m.getDim1() * b.getDim2());

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), 1.0f, cA.getPtr(), m.getDim2(), cB.getPtr(), b.getDim2(), 0.0f, work.getPtr(), m.getDim2());

	for(int i=0; i<r.getDim1(); i++)
		memcpy(&r[i][0], &work[i*r.getDim2()], r.getDim2()*sizeof(float));

	return r;
}

inline
const DMatrix<double>&  operator*(const DMatrix<double>& m, const DMatrix<double>& b)
{
	static DMatrix<double> r;
	static Array<double> cA;
	static Array<double> cB;
	r.setDim(m.getDim1(), b.getDim2());
	cA.setSize(m.getDim1() * m.getDim2());
	cB.setSize(b.getDim1() * b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(double));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(double));
	}

	static Array<double> work;
	work.setSize(m.getDim1() * b.getDim2());

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m.getDim1(), b.getDim2(), m.getDim2(), 1.0, cA.getPtr(), m.getDim2(), cB.getPtr(), b.getDim2(), 0.0, work.getPtr(), m.getDim2());
	
	for(int i=0; i<r.getDim1(); i++)
		memcpy(&r[i][0], &work[i*r.getDim2()], r.getDim2()*sizeof(double));

	return r;
}

inline
const DVector<float>&  operator*(const DMatrix<float>& m, const DVector<float>& b) {
	static DVector<float> r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int i;
	const float* vec = &b(0);
	for(i=0;i<m.getDim1();i++)
	{
		r[i] = cblas_sdot(m.getDim2(), &m(i)(0), 1, vec, 1);
	}
	return r;
}

inline
const DVector<double>&  operator*(const DMatrix<double>& m, const DVector<double>& b) {
	static DVector<double> r;

	if(m.getDim2() != b.getDim()) return r;

	r.setDim(m.getDim1());
	int i;
	const double* vec = &b(0);
	for(i=0;i<m.getDim1();i++)
	{
		r[i] = cblas_ddot(m.getDim2(), &m(i)(0), 1, vec, 1);
	}
	return r;
}

inline
const DMatrix<std::complex<float> >&  operator*(const DMatrix<std::complex<float> >& m, const DMatrix<std::complex<float> >& b)
{
	static DMatrix<std::complex<float> > r;
	std::complex<float>* cA = new std::complex<float>[m.getDim1() * m.getDim2()];
	std::complex<float>* cB = new std::complex<float>[b.getDim1() * b.getDim2()];
	r.setDim(m.getDim1(), b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(std::complex<float>));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(std::complex<float>));
	}

	std::complex<float>* work = new std::complex<float>[m.getDim1() * b.getDim2()];
	float alpha[2] = {1.0f, 0.0f};
	float beta[2] = {0.0f, 0.0f};
	const int m_ = m.getDim1();
	const int n_ = b.getDim2();
	const int k_ = m.getDim2();

	cblas_cgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m_, n_, k_, &alpha, cA, m_, cB, k_, &beta, work, m_);
	
	for(int i=0; i<r.getDim1(); i++)
		memcpy(&r[i][0], &work[i*r.getDim2()], r.getDim2()*sizeof(std::complex<float>));

	delete[] cA;
	delete[] cB;
	delete[] work;
	return r;
}

inline
const DMatrix<std::complex<double> >&  operator*(const DMatrix<std::complex<double> >& m, const DMatrix<std::complex<double> >& b)
{
	static DMatrix<std::complex<double> > r;
	std::complex<double>* cA = new std::complex<double>[m.getDim1() * m.getDim2()];
	std::complex<double>* cB = new std::complex<double>[b.getDim1() * b.getDim2()];
	r.setDim(m.getDim1(), b.getDim2());

	for(int i=0; i<m.getDim1(); i++)
	{
		memcpy(&cA[i*m.getDim2()], &m(i)(0), m.getDim2()*sizeof(std::complex<double>));
	}
	for(int i=0; i<b.getDim1(); i++)
	{
		memcpy(&cB[i*b.getDim2()], &b(i)(0), b.getDim2()*sizeof(std::complex<double>));
	}

	std::complex<double>* work = new std::complex<double>[m.getDim1() * b.getDim2()];
	double alpha[2] = {1.0, 0.0};
	double beta[2] = {0.0, 0.0};
	const int m_ = m.getDim1();
	const int n_ = b.getDim2();
	const int k_ = m.getDim2();

	cblas_zgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m_, n_, k_, &alpha, cA, m_, cB, k_, &beta, work, m_);
	
	for(int i=0; i<r.getDim1(); i++)
		memcpy(&r[i][0], &work[i*r.getDim2()], r.getDim2()*sizeof(std::complex<double>));

	delete[] cA;
	delete[] cB;
	delete[] work;
	return r;
}

} // namespace GMlib
