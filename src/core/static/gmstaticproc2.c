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



/*! \file gmstaticproc2.c
 *
 *  File Description
 */


namespace GMlib {



  ///////////////////////////////
  // template <typename T, int n, int m>
  // class GM_Static_P_<T,n,m>


  /*! void GM_Static_P_ <T,n,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c)
   *  \brief vec = mat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c) {

    (*a)=(*b)*c; GM_Static_P_<T,n-1,m>::mv_x(a+1,b+1,c);
  }


  /*! void GM_Static_P_ <T,n,m>::mv_xq(T *a, T* b, const Point<T,m>& c)
   *  \brief vec = HqMat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_xq(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr()); GM_Static_P_<T,n-1,m>::mv_xq(a+1,b+m+1,c);
  }


  /*! void GM_Static_P_ <T,n,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d)
   *  \brief vec = HqMat x vec + h(homogen col)
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr())+(*d); GM_Static_P_<T,n-1,m>::mv_xqP(a+1,b+m+1,c,d+m+1);
  }


  /*! void GM_Static_P_ <T,n,m>::eq_t(Point<T,m> *a, T *b)
   *  \brief a = b^T	matrix transposing
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::eq_t(Point<T,m> *a, T *b) {

    GM_Static_P2_<T,n,m,n>::eq_t(a,b);
  }


  /*! void GM_Static_P_<T,n,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c)
   *  \brief a = b x c tensor (outer) product
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c) {

    GM_Static_<T,m>::sc_r(a->getPtr(),b->getPtr(),double(*c)); GM_Static_P_<T,n-1,m>::vv_ox(a+1,b,c+1);
  }


  /*! void GM_Static_P_<T,n,m>::cm_x(T *a, T* b, T* c)
   *  \brief vec = col x mat
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::cm_x(T *a, T* b, T* c) {

    (*a) = GM_Static2_<T,m,m>::dpc(b,c); GM_Static_P_<T,n-1,m>::cm_x(a+1,b,c+1);
  }


  /*! void GM_Static_P_<T,n,m>::mc_x(T *a, T *b, T *c)
   *  \brief a = b(col)*c	matrix multiplication, but b is transposed
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mc_x(T *a, T *b, T *c) {

    GM_Static_P_<T,m,m>::cm_x(a,b,c); GM_Static_P_<T,n-1,m>::mc_x(a+m,b+1,c);
  }


  /*! void GM_Static_P_<T,n,m>::sc(Point<T,m>* a, T *b)
   *  \brief scaling of matrix (row by row)
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::sc(Point<T,m>* a, T *b) {

    GM_Static_<T,m>::sc(a->getPtr(),(double)*b); return GM_Static_P_<T,n-1,m>::sc(a+1,b+1);
  }

  /*! void GM_Static_P_<T,n,m>::hq_2x(T *a, T* b, const Point<T,m>& c)
   *  \brief vec = HqMat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::hq_2x(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr()); GM_Static_P_<T,n-1,m>::hq_2x(a+1,b+m+1,c);
  }


  /*! void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief col = vec - vec x HqMat
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p) {

    (*a) = (*p) - GM_Static3_<T,m,m>::dpr(r.getPtr(),b); GM_Static_P_<T,n-1,m>::hq_3x(a+m+1,b+1,r,p+1);
  }




  ///////////////////////////////
  //  template <class T,int m>
  //  class GM_Static_P_<T,1,m>


  /*! void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c) {

     (*a)=(*b)*c;
  }


  /*! void GM_Static_P_<T,1,m>::mv_xq(T *a, T* b, const Point<T,m>& c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_xq(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr());
  }


  /*! void GM_Static_P_<T,1,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr())+(*d);
  }


  /*! void GM_Static_P_<T,1,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c) {

    GM_Static_<T,m>::sc_r(a->getPtr(),b->getPtr(),double(*c));
  }

  /*! void GM_Static_P_<T,1,m>::cm_x(T *a, T* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::cm_x(T *a, T* b, T* c) {

    (*a) = GM_Static2_<T,m,m>::dpc(b,c);
  }

  /*! void GM_Static_P_<T,1,m>::mc_x(T *a, T *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mc_x(T *a, T *b, T *c) {

    GM_Static_P_<T,m,m>::cm_x(a,b,c);
  }

  /*! void GM_Static_P_<T,1,m>::sc(Point<T,m>* a, T *b)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::sc(Point<T,m>* a, T *b) {

    GM_Static_<T,m>::sc(a->getPtr(),(double)*b);
  }

  /*! void GM_Static_P_<T,1,m>::hq_2x(T *a, T* b, const Point<T,m>& c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::hq_2x(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr());
  }

  /*! void GM_Static_P_<T,1,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p) {

    (*a) = (*p) - GM_Static3_<T,m,m>::dpr(r.getPtr(),b);
  }


  ///////////////////////////////////////////
  //template <typename T, int n, int m, int k>
  //class GM_Static_P2_<T,n,m,k>


  /*! void GM_Static_P2_<T,n,m,k>::vm_x(T *a, Point<T,m>* b, T* c)
   *  \brief vec = vec x mat
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::vm_x(T *a, Point<T,m>* b, T* c) {
    (*a) = GM_Static2_<T,m,k>::dpr(b->getPtr(),c); GM_Static_P2_<T,n-1,m,k>::vm_x(a+1,b,c+1);
  }


  /*! void GM_Static_P2_<T,n,m,k>::mm_x(Point<T,k> *a, Point<T,m> *b, T *c)
   *  \brief a = b*c	matrix multiplication
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::mm_x(Point<T,k> *a, Point<T,m> *b, T *c)	{

    GM_Static_P2_<T,k,m,k>::vm_x(a->getPtr(),b,c); GM_Static_P2_<T,n-1,m,k>::mm_x(a+1,b+1,c);
  }


  /*! void GM_Static_P2_<T,n,m,k>::vm_xT(T *a, Point<T,m>* b, T* c)
   *  \brief vec =  mat x vec (a = c x b)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::vm_xT(T *a, Point<T,m>* b, T* c)	{
    (*a) = GM_Static_<T,m>::dpr(b->getPtr(),c); GM_Static_P2_<T,n-1,m,k>::vm_xT(a+1,b,c+m);
  }


  /*! void GM_Static_P2_<T,n,m,k>::mm_xT(Point<T,k> *a, Point<T,m> *b, T *c)
   *  \brief a = b*c	matrix multiplication (c transposed)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::mm_xT(Point<T,k> *a, Point<T,m> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xT(a->getPtr(),b,c); GM_Static_P2_<T,n-1,m,k>::mm_xT(a+1,b+1,c);
  }


  /*! void GM_Static_P2_<T,n,m,k>::vm_xTT(T *a, T* b, T* c)
   *  \brief a(vec) = b(col) x mat
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::vm_xTT(T *a, T* b, T* c)	{
    (*a) = GM_Static2_<T,m,k>::dpc(b,c); GM_Static_P2_<T,n-1,m,k>::vm_xTT(a+1,b,c+1);
  }


  /*! vec(a) = vec(c) x mat(b) (b homogen)
   *  \brief a = b*c	matrix multiplication (b transposed)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::mm_xTT(Point<T,k> *a, T *b, T *c)	{
    GM_Static_P2_<T,k,m,k>::vm_xTT(a->getPtr(),b,c); GM_Static_P2_<T,n-1,m,k>::mm_xTT(a+1,b+1,c);
  }


  /*! void GM_Static_P2_<T,n,m,k>::vm_xH(T *a, Point<T,m+1>* b, T* c)
   *  \brief vec(a) = vec(c) x mat(b) (b homogen)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::vm_xH(T *a, Point<T,m+1>* b, T* c)	{
    (*a) = GM_Static2_<T,m,k>::dpr(b->getPtr(),c); GM_Static_P2_<T,n-1,m,k>::vm_xH(a+1,b,c+1);
  }


  /*! void GM_Static_P2_<T,n,m,k>::mm_xH(Point<T,k> *a, Point<T,m+1> *b, T *c)
   *  \brief a = Hb * c	matrix multiplication (b homogen)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::mm_xH(Point<T,k> *a, Point<T,m+1> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xH(a->getPtr(),b,c); GM_Static_P2_<T,n-1,m,k>::mm_xH(a+1,b+1,c);
  }


  /*! void GM_Static_P2_<T,n,m,k>::vm_xHT(T *a, Point<T,m+1>* b, T* c)
   *  \brief vec =  mat x vec (a = c x b)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::vm_xHT(T *a, Point<T,m+1>* b, T* c) {
    (*a) = GM_Static_<T,m>::dpr(b->getPtr(),c); GM_Static_P2_<T,n-1,m,k>::vm_xHT(a+m,b,c+m);
  }


  /*! void GM_Static_P2_<T,n,m,k>::mm_xHT(T *a, Point<T,m+1> *b, T *c)
   *  \brief a = b*c	matrix multiplication (c transposed)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::mm_xHT(T *a, Point<T,m+1> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xHT(a,b,c); GM_Static_P2_<T,n-1,m,k>::mm_xHT(a+1,b+1,c);
  }


  /*! void GM_Static_P2_<T,n,m,k>::eq_t(Point<T,m> *a, T *b)
   *  \brief a = b^T	matrix transposeing (a = n x m)
   *  Pending Documentation
   */
  template <typename T, int n, int m, int k>
  inline
  void GM_Static_P2_<T,n,m,k>::eq_t(Point<T,m> *a, T *b) {
    GM_Static2_<T,m,n>::eq1(a->getPtr(),b); GM_Static_P2_<T,n,m,k-1>::eq_t(a+1,b+1);
  }






  ///////////////////////////////
  //  template <class T, int m, int k>
  //  class GM_Static_P2_<T,1,m,k>


  /*! void GM_Static_P2_<T,1,m,k>::vm_x(T *a, Point<T,m>* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::vm_x(T *a, Point<T,m>* b, T* c) {
    (*a) = GM_Static2_<T,m,k>::dpr(b->getPtr(),c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::mm_x(Point<T,k> *a, Point<T,m> *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::mm_x(Point<T,k> *a, Point<T,m> *b, T *c)	{

    GM_Static_P2_<T,k,m,k>::vm_x( a->getPtr(), b, c );
  }


  /*! void GM_Static_P2_<T,1,m,k>::vm_xT(T *a, Point<T,m>* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::vm_xT(T *a, Point<T,m>* b, T* c)	{

    (*a) = GM_Static_<T,m>::dpr(b->getPtr(),c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::mm_xT(Point<T,k> *a, Point<T,m> *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::mm_xT(Point<T,k> *a, Point<T,m> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xT(a->getPtr(),b,c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::vm_xTT(T *a, T* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::vm_xTT(T *a, T* b, T* c)	{
    (*a) = GM_Static2_<T,m,k>::dpc(b,c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::mm_xTT(Point<T,k> *a, T *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::mm_xTT(Point<T,k> *a, T *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xTT(a->getPtr(),b,c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::vm_xH(T *a, Point<T,m+1>* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::vm_xH(T *a, Point<T,m+1>* b, T* c) {
    (*a) = GM_Static2_<T,m,k>::dpr(b->getPtr(),c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::vm_xHT(T *a, Point<T,m+1>* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::mm_xH(Point<T,k> *a, Point<T,m+1> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xH(a->getPtr(),b,c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::vm_xHT(T *a, Point<T,m+1>* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::vm_xHT(T *a, Point<T,m+1>* b, T* c) {
    (*a) = GM_Static_<T,m>::dpr(b->getPtr(),c);
  }


  /*! void GM_Static_P2_<T,1,m,k>::mm_xHT(T *a, Point<T,m+1> *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T, int m, int k>
  inline
  void GM_Static_P2_<T,1,m,k>::mm_xHT(T *a, Point<T,m+1> *b, T *c) {
    GM_Static_P2_<T,k,m,k>::vm_xHT(a,b,c);
  }






  ///////////////////////////////
  //template <class T, int n, int m>
  //class GM_Static_P2_<T,n,m,1>


  /*! void GM_Static_P2_<T,1,m,k>::vm_x(T *a, Point<T,m>* b, T* c)
   *  \brief a = b^T	matrix transposeing

   *  Pending Documentation
   */
  template <typename T, int n, int m>
  void GM_Static_P2_<T,n,m,1>::eq_t(Point<T,m> *a, T *b) {
    GM_Static2_<T,m,n>::eq1(a->getPtr(),b);
  }


} // END namespace GMlib