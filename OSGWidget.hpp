#ifndef OSG_WIDGET_HPP
#define OSG_WIDGET_HPP

#include "SphereUpdateCallback.hpp"

#include <cassert>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>
#include <QOpenGLWidget>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <osg/Camera>
#include <osg/DisplaySettings>
#include <osg/Geode>
#include <osg/Material>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osgDB/WriteFile>
#include <osgGA/EventQueue>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/LineWidth>

class OSGWidget : public QOpenGLWidget
{
  Q_OBJECT

public:
  OSGWidget( QWidget* parent = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();

  osg::Camera* create_camera();
  osg::ref_ptr<osgGA::TrackballManipulator>create_manipulator(osg::Vec3 &initialPosition, osg::Vec3 &initialPointingPosition, osg::Vec3 &upVector);
  osgViewer::View* create_view(osg::Camera *camera, osg::ref_ptr<osgGA::TrackballManipulator> &manipulator);
  osgViewer::CompositeViewer* create_viewer(osgViewer::View *view);
  void add_ball(osg::Vec3 &initialBallPosition, float &ballRadius, osg::Vec4 &ballColor);
  void add_cylinder(osg::Vec3 &initialCylinderPosition, float &cylinderRadius, float &cylinderHeight, osg::Vec4 &cylinderColor);
  void add_ground_plane(float &groundPlaneSize, osg::Vec4 &groundColor);
  void configure_update();

protected:
  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  void timerEvent(QTimerEvent *);

private:
  virtual void on_resize( int width, int height );
  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
  osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
  osg::ref_ptr<osgViewer::View> mView;
  osg::ref_ptr<osg::Group> mRoot;
  int mTimerId{0};
  double mFramesPerSecond{30};
};

#endif
