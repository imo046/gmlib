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



/*! \file gmwindow.h
 *
 *  Interface for the Window and "Camera" View classes.
 */


#ifndef __gmWINDOW_H__
#define __gmWINDOW_H__


// gmlib::scenegraph
#include <scenegraph/camera/gmcamera.h>

// gmlib::scenegraph - might be removed as light and is implemented with different mechanisms...
#include <scenegraph/light/gmlight.h>
#include <scenegraph/light/gmsun.h>

// stl
#include <iostream>

namespace GMlib {

  class View;
  class ViewBorder;
  class ViewSet;
  class GMWindow;


  /*! \class View gmwindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class View {
	public:
		View( Camera* cam = 0x0 );
		View( ViewBorder* border );
		View( const View& view );

	private:
		friend class ViewSet;
		friend class ViewBorder;

		Camera*				_camera;
		ViewBorder*		_border;


    void 					corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow);
    void 					find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders);
    int  					getSize(bool split_vertically = true);
    bool 					isCamera(Camera* cam);
    void 					prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders);
    void 					removeCamera(Camera* cam);
    void 					split(Camera* new_cam, bool split_vertically, double d);
    void 					splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d);

	}; // END class View










  /*! \class ViewBorder gmwindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class ViewBorder {
	public:
		ViewBorder(Camera* cam_to_split, Camera* new_cam, bool v, double r);
		ViewBorder(const ViewBorder& w);

	private:
		friend class ViewSet;
		friend class View;

		bool			_vertical;		/// True if border is vertical
		double		_displacement;
		int				_x1, _x2, _y1, _y2;	/// Pixel-index of the border
		View			_child_lt;
		View			_child_rb;

    void 			corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow);
    void 			display();
    void 			find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders);
    int  			getSize(bool vertical=true);
    View* 		hasCamera(Camera* cam);
    bool 			isVertical();
    void 			move(int x, int y);
    void 			prepare( int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders );
    void 			removeCamera(Camera* cam);
    void 			splitCamera(Camera* cam_to_split, Camera* new_cam, bool vertical, double d);


	}; // END class ViewBorder










  /*! \class ViewSet gmwindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class ViewSet {
	public:
		ViewSet(Camera* cam=0);
		ViewSet(const ViewSet& viewset);
		~ViewSet();

		int  								getSize();
		Point2D<int> 				getViewPortSize();
		void 								prepare(int w, int h);
		void 								removeCamera(Camera*);

		ViewSet& 						operator=(const ViewSet& viewset);
		bool 								operator<(const ViewSet& viewset)const;


	private:
		friend class GMWindow;

		int									_vp_w; // ViewPort size ( Width )
		int 								_vp_h;	// Viewport size ( height )
		Array<Camera*>			_cameras;
		Array<ViewBorder*>	_borders;
		View								_root;
    Color							_border_color;

		Array<ViewBorder*>	_selected_borders;


    void 								drawBorder();

  public:
    void 								drawCamera(bool stereo=false);

  private:
    bool 								find(int x, int y, Camera*& cam);
    bool 								insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically=true, double d=0.5);
    void 								moveBorder(int x, int y);
    void 								removeCamera(int i);
    void 								reset();
    void 								setBorderColor(const Color& bc);

		Camera* 						operator[](int i);

	}; // END class ViewSet










  /* \class GMWindow gmWindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class GMWindow : public Scene {
  public:
    GMWindow( bool init_default_cam = true );
    GMWindow(const GMWindow&);

    virtual ~GMWindow();


    void                    addToViewSet( int cam_idx, int split_cam_idx, bool split_vertically=true, double d=0.5 );
    void                    addViewSet( int cam_idx );
    virtual void            clearScene();
    Camera*                 findCamera( int x, int y );
    Camera*                 findCamera( const Vector<int,2>& pos );
    int                     getCameraIndex( Camera* cam ) const;
    const Color&            getSelectColor() const;
    int                     getViewportHeight() const;
    int                     getViewportWidth() const;
    int                     getViewSetStackSize() const;
    void                    insertCamera(Camera* cam, bool insert_in_scene = false);

    void                    insertLight(Light* light, bool insert_in_scene = false);
    void                    insertSun();
    bool                    isRunning() const;
    bool                    isStereoEnabled() const;
    void                    popView(int cam_idx);
    void                    popViewSet();
    void                    prepareViewSets();

    bool                    removeCamera(Camera * cam);
    bool                    removeLight(Light* light);
    void                    removeSun();
    void                    reset();

    void                    scaleDayLight(double d);
    void                    setSelectColor( const Color& color );
    void                    setSunDirection(Angle d);


    virtual bool            toggleRun();
    bool                    toggleStereo();


    GMWindow&               operator=(const GMWindow& gw);



  protected:

    // Cameras light and sun
    Array<Camera*>	        _cameras;
    Array<Light*>	          _lights;
    Sun*			              _sun;

    // Viewport size
    int				              _w;
    int                     _h;					// GMWindow size in viewport coordinates.


    Array<ViewSet>          _view_set_stack;  /// Active camera set

    // index of active camera, old/previous x and y mouse positions
    int				              _active_cam;

    double					        _move;


    bool                    find(int x, int y, int& index);
    virtual void            message( const std::string& str);
    virtual void            message( SceneObject* d);
    virtual void            message( Point<float,3>& p);
    void                    moveBorder(int x, int y);

    void                    display();

  public:
    virtual void            init();
  protected:
    void                    reshape(int w, int h);
    virtual void            swapBuffers();


  private:
    bool			              _stereo;

    SceneObject*	          _target;		/// NB!!!! take a look at this variable not used proper today.....
    bool			              _running;		/// Used to stor the state of simulation while mouse/keboard temporary turn off simulation
    bool			              _isbig;			/// State of one window functionality have been used (see _mouseDoubleClick on right knob)

    Color                   _select_color;

    GLuint          _vbo_quad;
    GLuint          _vbo_quad_tex;


  }; // END class GMWindow

















  /*! View::View(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(Camera* cam) {

    _camera = cam;
    _border = 0;
  }


  /*! View::View(ViewBorder* border)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(ViewBorder* border) {

    _camera = 0;
    _border = border;
  }


  /*! View::View(const View& view)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View::View(const View& view) {

    _camera = view._camera;
    _border = view._border;
  }


  /*! void View::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void View::corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow) {

    if( _border )
      _border = nw[ow.index(_border)];
  }


  /*! int View::_getSize( bool split_vertically )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int View::getSize( bool split_vertically ) {

    if( _border )
      return _border->getSize( split_vertically );
    else {

      int w1, w2, h1, h2;
      _camera->getViewport( w1, w2, h1, h2 );
      if( split_vertically )
        return w2 - w1;
      else
        return h2 - h1;
    }
  }


  /*! bool View::_isCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool View::isCamera(Camera* cam)	{

    return _camera == cam;
  }


  /*! void View::_split(Camera* new_cam, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Splitting this in two
   */
  inline
  void View::split(Camera* new_cam, bool split_vertically, double d) {

    if(_camera) {

      _border = new ViewBorder( _camera, new_cam, split_vertically, d );
      _camera = 0;
    }
    else {

      _border = 0;
      _camera = new_cam;
    }
  }

  /*! ViewBorder::ViewBorder( Camera* cam_to_split, Camera* new_cam, bool v, double r )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  ViewBorder::ViewBorder( Camera* cam_to_split, Camera* new_cam, bool v, double r )
    : _vertical(v), _displacement(r), _child_lt(cam_to_split), _child_rb(new_cam)
  {}


  /*! ViewBorder::ViewBorder(const ViewBorder& w)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  ViewBorder::ViewBorder(const ViewBorder& w)
    : _vertical(w._vertical), _displacement(w._displacement), _child_lt(w._child_lt), _child_rb(w._child_rb)
  {}


  /*! void ViewBorder::_corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::corr(Array<ViewBorder*>& nw, const Array<ViewBorder*>& ow) {

    _child_lt.corr( nw, ow );
    _child_rb.corr( nw, ow );
  }


  /*! void ViewBorder::_display()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::display() {

    glRecti( _x1, _y1, _x2, _y2 );
  }


  /*! void ViewBorder::_find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::find(int x, int y, Camera*& cam, Array<ViewBorder*>& borders) {

    if(x>(_x1-5) && x<(_x2+5) && y>(_y1-5) && y<(_y2+5)) borders += this;

    _child_lt.find(x,y,cam,borders);
    _child_rb.find(x,y,cam,borders);
  }


  /*! int  ViewBorder::_getSize(bool vertical)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int  ViewBorder::getSize(bool vertical) {

    if(vertical == _vertical)
      return _child_lt.getSize(vertical) + _child_rb.getSize(vertical);
    else
      return std::min<int>( _child_lt.getSize(vertical), _child_rb.getSize(vertical) );
  }


  /*! View* ViewBorder::_hasCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  View* ViewBorder::hasCamera(Camera* cam) {

    if(_child_lt.isCamera(cam))
      return &_child_rb;
    else if(_child_rb.isCamera(cam))
      return &_child_lt;
    else
      return 0;
  }


  /*! bool ViewBorder::_isVertical()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool ViewBorder::isVertical() {

    return _vertical;
  }


  /*! void ViewBorder::_move(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::move(int x, int y) {

    int l_size = _child_lt.getSize(_vertical);
    int r_size = _child_rb.getSize(_vertical);

    if(_vertical) {

      l_size = _x1-l_size;
      r_size += _x2;
      if((x > l_size && x < _x1)||(x > _x2 && x < r_size))
        _displacement = (double)(x-l_size)/(r_size-l_size);
    }
    else
    {
      l_size = _y1-l_size;
      r_size += _y2;
      if((y > l_size && y < _y1)||(y > _y2 && y < r_size))
        _displacement = (double)(y-l_size)/(r_size-l_size);
    }
  }


  /*! void ViewBorder::_prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::prepare(int x1, int y1, int x2, int y2, Array<ViewBorder*>& borders) {

    borders.insert(this);
    if(_vertical) {

      _x1 = x1 + int(_displacement*(x2-x1)) - 1;
      _x2 = _x1 + 2;
      _y1 = y1-2;
      _y2 = y2+2;
      _child_lt.prepare( x1, y1, _x1, y2, borders );
      _child_rb.prepare( _x2, y1, x2, y2, borders );
    }
    else {

      _y1 = y1 + int( _displacement * (y2-y1) ) - 1;
      _y2 = _y1 + 2;
      _x1 = x1-2;
      _x2 = x2+2;
      _child_lt.prepare( x1, y1, x2, _y1, borders );
      _child_rb.prepare( x1, _y2, x2, y2, borders );
    }
  }


  /*! void ViewBorder::_removeCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::removeCamera(Camera* cam) {

    _child_lt.removeCamera(cam);
    _child_rb.removeCamera(cam);
  }


  /*! void ViewBorder::_splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewBorder::splitCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d) {

    _child_lt.splitCamera( cam_to_split, new_cam, split_vertically, d );
    _child_rb.splitCamera( cam_to_split, new_cam, split_vertically, d );
  }

  /*! Point2D<int> ViewSet::getViewPortSize()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  Point2D<int> ViewSet::getViewPortSize() {

    return Point2D<int>(_vp_w, _vp_h);
  }


  /*! bool ViewSet::operator<(const ViewSet& viewset) const
   *	\brief DUMMY!!
   *
   *	Pending Documentation
   *
   *	\todo Remove if not needed!
   */
  inline
  bool ViewSet::operator < ( const ViewSet& /* viewset */ ) const {

    return true;
  }


  /*! void ViewSet::_drawBorder()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::drawBorder() {

//    if(_borders.getSize()>0)
//    {
//      glDisable(GL_LIGHTING);
//      glMatrixMode(GL_PROJECTION);
//      glLoadIdentity();
//      glOrtho( 0, _vp_w, 0, _vp_h, -1, 1 );
//      glMatrixMode(GL_MODELVIEW);
//      glViewport( 0, 0, _vp_w, _vp_h );
//      glColor( _border_color );
//      for( int i=0; i< _borders.getSize(); i++ ) _borders[i]->display();
//      glEnable(GL_LIGHTING);
//    }
  }


  /*! bool ViewSet::_insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_verticaly, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool ViewSet::insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d) {

    if(_cameras.exist(new_cam))
      return false;
    else if(!_cameras.exist(cam_to_split))
      return false;
    else
    {
      _cameras += new_cam;
      if(_cameras.getSize()>2)
        _root.splitCamera(cam_to_split,new_cam,split_vertically,d);
      else
        _root.split( new_cam,split_vertically,d);
      _borders.resetSize();
      _root.prepare( 0, 0,_vp_w, _vp_h, _borders);
      return true;
    }
  }


  /*! void ViewSet::_moveBorder(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::moveBorder(int x, int y) {

    for( int i = 0; i < _selected_borders.getSize(); i++ )
      _selected_borders[i]->move(x,y);
    prepare(_vp_w,_vp_h);
  }


  /*! void ViewSet::_prepare(int w, int h)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::prepare(int w, int h) {

    std::cout << "ViewSet::prepare (w,h): (" << w << "," << h << ")" << std::endl;
    _vp_w = w; _vp_h = h;
    _borders.resetSize();
    _root.prepare(0,0, _vp_w, _vp_h, _borders );
  }


  /*! void ViewSet::removeCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::removeCamera(Camera* cam) {

    if(_cameras.getSize() > 1)
    {
      int i = _cameras.getIndex(cam);
      if(i>=0) removeCamera(i);
    }
  }


  /*! void ViewSet::_removeCamera(int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::removeCamera(int i) {

    if( _cameras.getSize() > 1 ){

      _root.removeCamera(_cameras[i]);
      _cameras.removeIndex(i);
      prepare( _vp_w,_vp_h );
    }
  }

  inline
  Camera* GMWindow::findCamera( int x, int y ) {

    int i;
    find( x, y, i );
    if( i > 0 )
      return _cameras[i];

    return 0x0;
  }

  inline
  Camera* GMWindow::findCamera( const Vector<int,2>& pos ) {

    return findCamera( pos(0), pos(1) );
  }

  inline
  int GMWindow::getCameraIndex( Camera* cam ) const {

    if( !_cameras.exist( cam ) )
      return -1;

    return _cameras.index( cam );
  }

  inline
  int GMWindow::getViewportHeight() const {

    return _h;
  }

  inline
  int GMWindow::getViewportWidth() const {

    return _w;
  }

  inline
  int GMWindow::getViewSetStackSize() const {

    return _view_set_stack.getSize();
  }


  /*! void GMWindow::insertSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::insertSun() {

    _sun = new Sun(); _sun->enable();
  }


  inline
  bool GMWindow::isRunning() const {

    return _running;
  }


  /*! bool GMWindow::isStereoEnabled()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::isStereoEnabled() const {

    return _stereo;
  }


  /*! void GMWindow::removeSun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::removeSun() {

    if(_sun) {

      delete _sun;
      _sun = NULL;
    }
  }


  /*! void GMWindow::reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reset() {

    init();
  }


  /*! void GMWindow::setSunDirection(Angle d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::setSunDirection(Angle d) {

    if(_sun)
      _sun->rotateGlobal(d,Vector3D<float>(1.0,1.0,0.0));
  }


  /*! void GMWindow::swapBuffers()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::swapBuffers() {}


  /*! void GMWindow::display(void)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::display() {

    if( _active_cam > -1 )
      _cameras[_active_cam]->move(_move);

//    simulate();
//    prepare();
//    if(_stereo) {

//      glDrawBuffer(GL_BACK_LEFT);
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      _view_set_stack.back()._drawCamera();
//      swapBuffers();
//      glDrawBuffer(GL_BACK_RIGHT);
//      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//      _view_set_stack.back()._drawCamera(true);
//    }
//    else {

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      OGL::clearRenderBuffer();
      OGL::bindRenderBuffer();
      _view_set_stack.back().drawCamera();
      OGL::releaseRenderBuffer();
//    }



    // Render render-buffer to standard OGL buffer

    float near_plane = -1.0f;
    float far_plane = 1.0f;

    float l, r, b, t, n, f;
    l = 0.0f;
    r = 1.0f;
    b = 0.0f;
    t = 1.0f;
    n = near_plane;
    f = far_plane;

    float A, B, C;
    A = - ( r + l ) / ( r - l );
    B = - ( t + b ) / ( t - b );
    C = - ( f + n ) / ( f - n );

    HqMatrix<float,3> ortho_mat;

    ortho_mat[0][0] = 2 / (r - l);
    ortho_mat[0][1] = 0.0f;
    ortho_mat[0][2] = 0.0f;
    ortho_mat[0][3] = A;

    ortho_mat[1][0] = 0.0f;
    ortho_mat[1][1] = 2 / ( t - b );
    ortho_mat[1][2] = 0.0f;
    ortho_mat[1][3] = B;

    ortho_mat[2][0] = 0.0f;
    ortho_mat[2][1] = 0.0f;
    ortho_mat[2][2] = - 2.0f / (f-n);
    ortho_mat[2][3] = C;

    ortho_mat[3][0] = 0.0f;
    ortho_mat[3][1] = 0.0f;
    ortho_mat[3][2] = 0.0f;
    ortho_mat[3][3] = 1.0f;


    glViewport( 0, 0, _w, _h );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glDisable(GL_DEPTH_TEST);

    GLProgram prog( "render" );

    prog.bind();

    prog.setUniform( "u_mvpmat", ortho_mat, 1, true );
    prog.setUniform( "u_tex", OGL::getRenderColorBuffer(), (GLenum)GL_TEXTURE0, 0 );
    prog.setUniform( "u_tex_selected", OGL::getRenderSelectedBuffer(), (GLenum)GL_TEXTURE1, 1 );
    prog.setUniform( "u_buf_w", float(OGL::getRenderBufferWidth()) );
    prog.setUniform( "u_buf_h", float(OGL::getRenderBufferHeight()) );
    prog.setUniform( "u_select_color", _select_color );

    GLuint vert_loc = prog.getAttributeLocation( "in_vertex" );
    GLuint tex_coord_loc = prog.getAttributeLocation( "in_tex_coord" );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad );
    glVertexAttribPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( vert_loc );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_quad_tex );
    glVertexAttribPointer( tex_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
    glEnableVertexAttribArray( tex_coord_loc );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    glDrawArrays( GL_QUADS, 0, 4 );

    glDisableVertexAttribArray( tex_coord_loc );
    glDisableVertexAttribArray( vert_loc );

    prog.unbind();

    glEnable(GL_DEPTH_TEST);

    swapBuffers();
  }


  /*! void GMWindow::reshape(int w, int h)
   *	\brief	Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::reshape(int w, int h) {

    _w = w; _h = h;
    _view_set_stack.back().prepare(_w,_h);
    OGL::setRenderBufferSize( _w, _h );
    OGL::setSelectBufferSize( _w, _h );
  }


  /*! void GMWindow::message( const std::string& str)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( const std::string& /* str */ ) {}


  /*! void GMWindow::message( SceneObject* d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( SceneObject* /* obj */ ) {}


  /*! void GMWindow::message( Point<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::message( Point<float,3>& /* p */ ) {}


  /*! bool GMWindow::find(int x, int y, int& index)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool GMWindow::find(int x, int y, int& index) {

    if(x<0 || x>_w || y<0 || y>_h)		// Outside window
    {
      index = 0;
      _view_set_stack.back().reset();
      return false;
    }

    Camera* cam;
    if(_view_set_stack.back().find(x,y,cam))		// Camera found
    {
      index = _cameras.index(cam);
      return true;
    }
    else								// border found
    {
      index = -1;
      return false;
    }
  }


  /*! void GMWindow::moveBorder(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void GMWindow::moveBorder(int x, int y) {

    if(x>0 && x <_w && y>0 && y<_h)
      (_view_set_stack.back()).moveBorder(x,y);
  }

} // END namespace GMlib



#endif // __gmWINDOW_H__
