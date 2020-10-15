#include "OSGWidget.hpp"


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
    manipulator->setHomePosition(osg::Vec3d(0.0,-20.0,20.0),osg::Vec3d(0,0,5.0f),osg::Vec3d(0,0,1));
    mView->setCameraManipulator( manipulator );

    mViewer->addView( mView );
    mViewer->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );
    mViewer->realize();
    mView->home();

    osg::Sphere* ball = new osg::Sphere( osg::Vec3( 0.f, 0.f, 1.f ), 2.0f );
    osg::ShapeDrawable* sdBall = new osg::ShapeDrawable( ball );
    sdBall->setColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
    sdBall->setName( "Sphere" );
    osg::Geode* geodeBall = new osg::Geode;
    geodeBall->addDrawable( sdBall );
    osg::StateSet* stateSetBall = geodeBall->getOrCreateStateSet();
    osg::Material* materialBall = new osg::Material;
    materialBall->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSetBall->setAttributeAndModes( materialBall, osg::StateAttribute::ON );
    stateSetBall->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform *transformBall = new osg::PositionAttitudeTransform;
    transformBall->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transformBall->setUpdateCallback(new SphereUpdateCallback());
    transformBall->addChild(geodeBall);
    mRoot->addChild(transformBall);

    osg::Cylinder* nozzle = new osg::Cylinder( osg::Vec3( 0.f, 0.f, 2.f ), 2.0f, 4.0f );
    osg::ShapeDrawable* sdNozzle = new osg::ShapeDrawable( nozzle );
    sdNozzle->setColor( osg::Vec4( 0.5f, 0.5f, 0.5f, 1.f ) );
    sdNozzle->setName( "Nozzle" );
    osg::Geode* geodeNozzle = new osg::Geode;
    geodeNozzle->addDrawable( sdNozzle );
    osg::StateSet* stateSetNozzle = geodeNozzle->getOrCreateStateSet();
    osg::Material* materialNozzle = new osg::Material;
    materialNozzle->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSetNozzle->setAttributeAndModes( materialNozzle, osg::StateAttribute::ON );
    stateSetNozzle->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    osg::PositionAttitudeTransform *transformNozzle = new osg::PositionAttitudeTransform;
    transformNozzle->setPosition(osg::Vec3( 0.f, 0.f, 0.f ));
    transformNozzle->addChild(geodeNozzle);
    mRoot->addChild(transformNozzle);

    osg::ref_ptr<osg::Vec3Array> groundPlaneVertices = new osg::Vec3Array;
    float groundSize = 100;
    groundPlaneVertices->push_back(osg::Vec3(-groundSize, -groundSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(groundSize, -groundSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(groundSize, groundSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(-groundSize, groundSize, 0.0f));
    osg::ref_ptr<osg::Vec3Array> groundPlaneNormals = new osg::Vec3Array;
    groundPlaneNormals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    osg::ref_ptr<osg::Vec4Array> groundColor = new osg::Vec4Array;
    groundColor->push_back(osg::Vec4(0.04f, 0.4f, 0.14f, 0.0f));
    osg::ref_ptr<osg::Geometry> ground = new osg::Geometry;
    ground->setVertexArray(groundPlaneVertices.get());
    ground->setNormalArray(groundPlaneNormals.get());
    ground->setNormalBinding(osg::Geometry::BIND_OVERALL);
    ground->setColorArray(groundColor.get());
    ground->setColorBinding(osg::Geometry::BIND_OVERALL);
    ground->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    osg::Geode* geodeGroundPlane = new osg::Geode;
    geodeGroundPlane->addDrawable( ground.get() );
    osg::StateSet* stateSetGround = geodeGroundPlane->getOrCreateStateSet();
    osg::Material* materialGround = new osg::Material;
    materialGround->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    stateSetGround->setAttributeAndModes( materialGround, osg::StateAttribute::ON );
    stateSetGround->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    mRoot->addChild(geodeGroundPlane);

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

