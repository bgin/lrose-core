// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
#ifndef PolarWidget_HH
#define PolarWidget_HH

#ifndef DLL_EXPORT
#ifdef WIN32
#ifdef QT_PLUGIN
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif
#endif

#include <string>
#include <vector>

#include <QDialog>
#include <QWidget>
#include <QResizeEvent>
#include <QImage>
#include <QTimer>
#include <QRubberBand>
#include <QPoint>
#include <QTransform>

#include "Params.hh"
#include "PolarBeam.hh"
#include "FieldRenderer.hh"
#include "ScaledLabel.hh"
#include "WorldPlot.hh"

class PolarManager;

/// Base class for widgets displaying PPI or RHI scans.
///
/// A beam is the basic building block for the scan. It has
/// a starting angle, ending angle, a fixed number of range 
/// gates, and a fixed number of fields that can be rendered 
/// on the beam.
///
/// The scan is given color maps for each of the fields. 
/// It is then simply called with the data for all fields
/// for a given beam. As each beam is received, the current field
/// and any fields in the beam that are being background rendered
/// are rendered into QImages.  The QImage for the current field is
/// then popped up on the display.  When the selected field is changed,
/// the image is cleared, and either the QImage for the new field is
/// popped up on the display or the new field is rendered. This
/// allows for quick switches between fields being rendered in the
/// background (which are the most recently viewed fields), without
/// the overhead of rendering all fields in the background.
///
/// The user specifies the number of gates along each beam, 
/// and the distance span of each beam. The latter is used to 
/// to create range rings in real world units.
///
/// Internally, we use a coordinate system which places the display in
/// the region x,y between -Beam::RENDER_PIXELS and Beam::RENDER_PIXELS.
/// The radar is located at 0, 0.
///
/// Zooming is accomplished by changing the limits of the Qt window.

class DLL_EXPORT PolarWidget : public QWidget
{

  // must include this if you use Qt signals/slots
  Q_OBJECT

 public:

  ////////////////////
  // Public methods //
  ////////////////////

  /**
   * @brief Constructor.
   *
   * @param[in] parent         Parent widget.
   * @param[in] params         TDRP parameters.
   */

  PolarWidget(QWidget* parent, 
              const PolarManager &manager,
              const Params &params,
              size_t n_fields);

  /**
   * @brief Destructor.
   */

  virtual ~PolarWidget();

  /**
   * @brief Configure the PolarWidget for range.
   */

  virtual void configureRange(double max_range) = 0;

  /**
   * @brief Select the field to display.
   *
   * @param[in] index   Index of the field to display, zero based.
   */

  void selectVar(const size_t index);

  /**
   * @brief Clear the specified field.
   *
   * @param[in] index    Index of the field to be cleared, zero based.
   *
   * @notes This method is not currently called anywhere.
   */

  void clearVar(const size_t index);

  /**
   * @brief Add a new beam to the display. Data for all fields and all
   *        gates are provided, as well as color maps for all fields.
   *        addBeam() will map the field values to  the correct color, and
   *        render the beam for each field in the appropriate pixamp. The
   *        existing wedge for this beam will be discarded.
   *
   * @param[in] start_angle    The starting angle for the beam.
   * @param[in] stop_angle     The ending angle for the beam.
   * @param[in] gates          The number of gates (must match beam_data vector
   *                             sizes).
   * @param[in] beam_data      Vectors of data, one for each field.
   */

  virtual void addBeam(const RadxRay *ray,
                       const float start_angle, const float stop_angle,
		       const std::vector< std::vector< double > > &beam_data,
		       const std::vector< DisplayField* > &fields);

  /**
   * @brief Specify the background color.
   *
   * @param[in] color     The background color.
   *
   * @notes This method is not currently called anywhere.
   */

  void backgroundColor(const QColor &color);

  /**
   * @brief Specify the grid and rings color.
   *
   * @params[in] color   The grid/rings color.
   *
   * @notes This method is not currently called anywhere.
   */

  void gridRingsColor(const QColor &color);

  /**
   * @brief Get the current number of beams. This is interesting to monitor
   *        when PolarWidget is operating in the dynamically allocated beam mode.
   *
   * @return Returns the current number of beams.
   *
   * @notes This method is not currently called anywhere.
   */

  int numBeams() const;

  /**
   * @brief Capture an image of the display.
   *
   * @return Returns the image. The caller must delete it when finished
   *         with it.
   *
   * @notes This method is not currently called anywhere.
   */

  QImage *getImage();

  /**
   * @brief Capture a pixmap of the display.
   *
   * @return Returns the pixmap. The caller must delete it when finished
   *         with it.
   *
   * @notes This method is not currently called anywhere.
   */

  QPixmap *getPixmap();
		      
  /**
   * @brief Get the aspect ratio of the display.
   *
   * @return Returns the aspect ratio of the display.
   */

  double getAspectRatio() const
  {
    return _aspectRatio;
  }

  ////////////////
  // Qt signals //
  ////////////////

 signals:

  void locationClicked(double xkm, double ykm, const RadxRay *closestRay);

  //////////////
  // Qt slots //
  //////////////

 public slots:

  /**
   * @brief Slot called when a beam has finished rendering.
   *
   * @params[in] field_num   The index of the field that was rendered.  This
   *                         is used to check if this was the selected field.
   */

  void displayImage(const size_t field_num);

  /**
   * @brief Unzoom the view.
   */

  void unzoomView();

  /**
   * @brief Clear the data in the view.
   */

  void clear();

  /**
   * @brief Resize the window.
   *
   */

  void resize(const int width, const int height);

  /**
   * @brief Set ring visibility.
   *
   * @param[in] enabled    True to show them, false otherwise.
   */

  void setRings(const bool enabled);

  /**
   * @brief Set grids visibility.
   *
   * @param[in] enabled   True to show them, false otherwise.
   */

  void setGrids(const bool enabled);

  /**
   * @brief Set azimuth lines visibility.
   *
   * @param[in] enabled    True to show them, false otherwise.
   */

  void setAzLines(const bool enabled);


 protected:

  /////////////////////////
  // Protected constants //
  /////////////////////////

  /**
   * @brief The sine of 45 degrees.  Used for positioning the labels on the
   *        45 degree lines.
   */

  static const double SIN_45;
  
  /**
   * @brief The sine of 30 degrees.  Used for positioning the azimuth lines on
   *        the 30 degree lines.
   */

  static const double SIN_30;
  
  /**
   * @brief The cosine of 30 degrees.  Used for positioning the azimuth lines on
   *        the 30 degree lines.
   */

  static const double COS_30;
  

  ///////////////////////
  // Protected members //
  ///////////////////////

  /**
   * @brief Parent widget.
   */

  QWidget *_parent;
  const PolarManager &_manager;

  /**
   * @brief TDRP params.
   */

  const Params &_params;

  /**
   * @brief The number of fields we are representing. A QImage will be
   *        created for each field.
   */

  size_t _nFields;

  /**
   * @brief Pointers to all of the active beams are saved here.
   */

  std::vector<PolarBeam*> _beams;

  /**
   * @brief The renderer for each field.
   */

  vector<FieldRenderer*> _fieldRenderers;
  
  /**
   * @brief The index of the field selected for display.
   */

  size_t _selectedField;

  /**
   * @brief The color for the grid and rings.
   */

  QColor _gridRingsColor;

  /**
   * @brief The brush for the background.
   */

  QBrush _backgroundBrush;

  /**
   * @brief True if the ring display is enabled.
   */

  bool _ringsEnabled;

  /**
   * @brief True if the grids display is enabled.
   */

  bool _gridsEnabled;

  /**
   * @brief True if the az lines enabled.
   */

  bool _azLinesEnabled;

  /**
   * @brief This will create labels wiith nicely scaled values and
   *        approriate units.
   */

  ScaledLabel _scaledLabel;

  /**
   * @brief The maximum range of the beams, in km.  It affects the
   *        labelling of the range rings
   */

  double _maxRange;

  /**
   * @brief Last X,Y location of the mouse during mouse move events; used for
   *        panning.
   */

  bool _pointClicked;
  int _mousePressX, _mousePressY;
  int _mouseReleaseX, _mouseReleaseY;
  int _zoomCornerX, _zoomCornerY;
  
  /**
   * @brief Location world of the latest click point.
   */
  
  double _worldPressX, _worldPressY;
  double _worldReleaseX, _worldReleaseY;

  /**
   * @brief Rubber band for zooming.
   */

  QRubberBand *_rubberBand;

  /**
   * @brief The rubber band origin.
   */

  QPoint _rubberBandOrigin;

  /**
   * @brief The current ring spacing in km.  This value is changed when we
   *        zoom.
   */

  double _ringSpacing;
  
  /**
   * @brief The aspect ratio of the display area.
   */

  double _aspectRatio;
  
  /**
   * @brief The full window rendering dimensions.  These are different for
   *        PPI windows and RHI windows.
   */

  QTransform _fullTransform;
  WorldPlot _fullWorld;
  
  /**
   * @brief The window to use for rendering.  This is where the zoom is
   *        implemented.
   */

  bool _isZoomed;
  QTransform _zoomTransform;
  WorldPlot _zoomWorld;
  

  ///////////////////////
  // Protected methods //
  ///////////////////////

  /**
   * @brief Refresh the images.  Note that this is an expensive method and
   *        should only be called where needed.
   */

  void _refreshImages();

  /**
   * @brief For dynamically allocated beams, cull the beam list, removing
   *        beams that are hidden by the given new beam.
   *
   * @params[in] beamAB     The new beam being added to the list.  Note that
   *                        this beam must not already be added to the list
   *                        when this method is called or it will be immediately
   *                        removed again.
   */

  void _cullBeams(const PolarBeam *beamAB);
  
  /**
   * @brief Find the index in the _beams array of the beam that corresponds
   *        to this angle. The beam angles must sweep in a counter clockwise,
   *         i.e. cartessian, direction.
   *
   * @param[in] start_angle    Beginning angle of the beam.
   * @param[in] stop_angle     Ending angle of the beam.
   *
   * @return Returns the index for the given beam.
   */

  inline int _beamIndex(const double start_angle, const double stop_angle);

  /**
   * @brief Render the rings and grid. The current value of _ringsGridColor
   *        will be used for the color.
   *
   * @param[in] painter    Painter to use for rendering.
   */

  void _drawOverlays(QPainter &painter);

  /**
   * @brief Determine a ring spacing which will give even distances, and
   *        fit a reasonable number of rings in the display.
   *
   * @return Returns the ring spacing in kilometers.
   */

  void _setRingSpacing();

  /**
   * @brief Initialize the full window transform to use for the widget.
   *
   * @param[in] window    The full window to use for the widget.
   */

  void _setTransform(const QTransform &transform);

  /////////////////////////////////
  // Overridden QtWidget methods //
  /////////////////////////////////

  /**
   * @brief Capture mouse move event for panning/zooming.
   *
   * @param[in] event   The mouse event.
   */

  virtual void mouseMoveEvent(QMouseEvent* event);

  /**
   * @brief Capture mouse press event which signals the start of
   *        panning/zooming.
   *
   * @param[in] event    The mouse press event.
   */

  virtual void mousePressEvent(QMouseEvent* event);

  /**
   * @brief Capture mouse release event which signals the start of
   * panning/zooming.
   *
   * @param[in] event    The mouse event.
   */

  virtual void mouseReleaseEvent(QMouseEvent* event);

  /**
   * @brief The method that is called when a repaint event is triggered.
   *
   * @param[in] event   The repaint event.
   */

  void paintEvent(QPaintEvent *event);

  /**
   * @brief Handle a resize event. A timer is used to prevent refreshes until
   *        the resize is finished.
   *
   * @brief event   The resize event.
   */

  virtual void resizeEvent(QResizeEvent * event);

  // reset the world coords

  void _resetWorld(int width, int height);

  // rendering

  void _performRendering();

  // get ray closest to click point

  virtual const RadxRay *_getClosestRay(double x_km, double y_km) = 0;

};

#endif
