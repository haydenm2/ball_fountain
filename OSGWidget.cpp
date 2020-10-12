#include "OSGWidget.hpp"

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
#include <osg/NodeVisitor>
#include <osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
#include <osg/PositionAttitudeTransform>

#include <cassert>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

class SphereUpdateCallback: public osg::NodeCallback
{
public:
    SphereUpdateCallback(){}

    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        mCount++;

        osg::Vec3d position(0.0, 0.0, mScaleStep*mCount);
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *> (node);
        pat->setPosition(position);

        traverse(node, nv);

        if(mCount>=20)
            mCount=0;
    }
protected:
    bool mUp{true};
    unsigned int mCount{0};
    double mScaleStep{1.0/1.0};
};



OSGWidget::OSGWidget( QWidget* parent, Qt::WindowFlags flags ):
    QOpenGLWidget{ parent,flags },
    mGraphicsWindow{ new osgViewer::GraphicsWindowEmbedded{ this->x(),
                                                            this->y(),
                                                            this->width(),
                                                            this->height() } }
  , mViewer{ new osgViewer::CompositeViewer }
{
    mRoot = new osg::Group;

    mView = new osgViewer::View;

    float aspectRatio = static_cast<float>( this->width() ) / static_cast<float>( this->height() );
    auto pixelRatio   = this->devicePixelRatio();

    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width() * pixelRatio, this->height() * pixelRatio );

    camera->setClearColor( osg::Vec4( 0.8f, 0.8f, 0.8f, 0.7f ) );
    camera->setProjectionMatrixAsPerspective( 45.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( mGraphicsWindow );
    mView->setCamera( camera );

    mView->setSceneData( mRoot.get() );
    mView->addEventHandler( new osgViewer::StatsHandler );

    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,3.0),osg::Vec3d(0,0,5.0f),osg::Vec3d(0,0,1));
    mView->setCameraManipulator( manipulator );

    mViewer->addView( mView );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();
    mView->home();

    osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 1.f ), 2.0f );
    osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
    sd->setColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    sd->setName( "Sphere" );
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable( sd );
    osg::StateSet* stateSet = geode->getOrCreateStateSet();
    osg::Material* material = new osg::Material;
    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform *transform = new osg::PositionAttitudeTransform;
    transform->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transform->setUpdateCallback(new SphereUpdateCallback());
    transform->addChild(geode);
    mRoot->addChild(transform);

    osg::Cylinder* cannon    = new osg::Cylinder( osg::Vec3( 0.f, 0.f, 2.f ), 2.0f, 4.0f );
    osg::ShapeDrawable* sd1 = new osg::ShapeDrawable( cannon );
    sd1->setColor( osg::Vec4( 0.5f, 0.5f, 0.5f, 1.f ) );
    sd1->setName( "Nozzle" );
    osg::Geode* geode1 = new osg::Geode;
    geode1->addDrawable( sd1 );
    osg::StateSet* stateSet1 = geode1->getOrCreateStateSet();
    osg::Material* material1 = new osg::Material;
    material1->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet1->setAttributeAndModes( material1, osg::StateAttribute::ON );
    stateSet1->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform *transform1 = new osg::PositionAttitudeTransform;
    transform1->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transform1->addChild(geode1);
    mRoot->addChild(transform1);

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    float groundSize = 100;
    vertices->push_back(osg::Vec3(-groundSize, -groundSize, 0.0f));
    vertices->push_back(osg::Vec3(groundSize, -groundSize, 0.0f));
    vertices->push_back(osg::Vec3(groundSize, groundSize, 0.0f));
    vertices->push_back(osg::Vec3(-groundSize, groundSize, 0.0f));
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.04f, 0.4f, 0.14f, 0.0f));
    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setColorArray(colors.get());
    quad->setColorBinding(osg::Geometry::BIND_OVERALL);
    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    osg::Geode* geode2 = new osg::Geode;
    geode2->addDrawable( quad.get() );
    osg::StateSet* stateSet2 = geode2->getOrCreateStateSet();
    osg::Material* material2 = new osg::Material;
    material2->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSet2->setAttributeAndModes( material2, osg::StateAttribute::ON );
    stateSet2->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    mRoot->addChild(geode2);

    this->setFocusPolicy( Qt::StrongFocus );
    this->setMinimumSize( 100, 100 );
    this->setMouseTracking( true );

    this->update();

    double framesPerSecond{30};
    double timeStep{1.0/framesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    mTimerId=startTimer(timerDurationInMilliSeconds);
}

OSGWidget::~OSGWidget()
{
    killTimer(mTimerId);
    delete mViewer;
}

void OSGWidget::timerEvent(QTimerEvent *)
{
    update();
}

void OSGWidget::paintEvent( QPaintEvent* /* paintEvent */ )
{
    this->makeCurrent();

    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
    this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
    mGraphicsWindow->resized( this->x(), this->y(), width, height );

    this->on_resize( width, height );
}

void OSGWidget::on_resize( int width, int height )
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras( cameras );

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport( 0, 0, width * pixelRatio, height * pixelRatio );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}

