#ifndef OSG_WIDGET_HPP
#define OSG_WIDGET_HPP

#include "SphereUpdateCallback.hpp"
#include "OSGWidgetUtils.hpp"

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

    void add_ball();
    void clear_balls();
    void update_ball_update_rate();
    void update_nozzle();

    BallPhysics* get_physics_ptr();

    float get_ground_plane_size();
    float get_fluid_density();
    float get_radius();
    float get_mass();
    unsigned int get_color();
    Eigen::Vector3f get_position();
    Eigen::Vector3f get_velocity();
    float get_coefficient_of_restitution();
    float get_ball_rate();
    bool is_paused();

    void set_fluid_density(float newDensity);
    void set_gravity(float newGravityRatio);
    void set_radius(float newRadius);
    void set_mass(float newMass);
    void set_color(unsigned int newColor);
    void set_velocity(float newUpwardVelocity);
    void set_coefficient_of_restitution(float newCoefficient);
    void set_ball_rate(float newRate);
    void set_pause_flag(bool pauseState);

protected:
    virtual void paintEvent( QPaintEvent* paintEvent );
    virtual void paintGL();
    virtual void resizeGL( int width, int height );

    void timerEvent(QTimerEvent *);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

    void create_camera();
    void create_manipulator();
    void create_view();
    void create_viewer();
    void add_cylinder();
    void add_ground_plane();
    void configure_update();

    float initialGroundPlaneSize{10};
    float initialFluidDensity{0.5};
    BallPhysics physics{BallPhysics(initialGroundPlaneSize, initialFluidDensity)};
    float fountainHeightScale{3.0};

    float ballsPerSecond{5.0};
    bool pauseFlag{true};

private:
    virtual void on_resize( int width, int height );
    osgGA::EventQueue* getEventQueue() const;

    int simulationUpdateTimerId{0};
    int ballUpdateTimerId{0};
    double framesPerSecond{30};

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
    osg::ref_ptr<osgViewer::View> mView;
    osg::ref_ptr<osg::Group> mRoot;
    osg::Camera* camera;
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator;
};

#endif
