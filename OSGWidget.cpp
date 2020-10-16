#include "OSGWidget.hpp"


OSGWidget::OSGWidget(QWidget* parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent,flags},
    mGraphicsWindow{new osgViewer::GraphicsWindowEmbedded{this->x(),
                                                          this->y(),
                                                          this->width(),
                                                          this->height()}},
    mRoot{new osg::Group}
{

    osg::Camera* camera = create_camera();

    osg::Vec3 initialManipulatorPosition{0.0, -50.0, 50.0};
    osg::Vec3 initialManipulatorPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = create_manipulator(initialManipulatorPosition, initialManipulatorPointingPosition, upVector);

    mView = create_view(camera, manipulator);

    mViewer = create_viewer(mView);

    osg::Vec3 initialBallPosition{0.f, 0.f, 4.f};
    float ballRadius{2.0f};
    osg::Vec4 ballColor{0.f, 0.f, 1.f, 1.f};
    add_ball(initialBallPosition, ballRadius, ballColor);

    osg::Vec3 initialCylinderPosition{0.f, 0.f, 2.f};
    float cylinderRadius{2.0f};
    float cylinderHeight{4.0f};
    osg::Vec4 cylinderColor{0.5f, 0.5f, 0.5f, 1.f};
    add_cylinder(initialCylinderPosition, cylinderRadius, cylinderHeight, cylinderColor);

    float groundPlaneSize{100};
    osg::Vec4 groundColor{0.04f, 0.4f, 0.14f, 0.0f};
    add_ground_plane(groundPlaneSize, groundColor);

    configure_update();
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

void OSGWidget::paintEvent(QPaintEvent* /* paintEvent */)
{
    this->makeCurrent();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    this->paintGL();

    painter.end();

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL(int width, int height)
{
    this->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    mGraphicsWindow->resized(this->x(), this->y(), width, height);

    this->on_resize(width, height);
}

void OSGWidget::on_resize(int width, int height)
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras(cameras);

    auto pixelRatio = this->devicePixelRatio();

    cameras[0]->setViewport(0, 0, width * pixelRatio, height * pixelRatio);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

osg::Camera* OSGWidget::create_camera()
{
    osg::Camera* camera = new osg::Camera;
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    camera->setViewport(0, 0, this->width()*pixelRatio, this->height()*pixelRatio);
    camera->setClearColor(osg::Vec4(0.8f, 0.8f, 0.8f, 0.7f));
    camera->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(this->mGraphicsWindow);
    return camera;
}

osg::ref_ptr<osgGA::TrackballManipulator> OSGWidget::create_manipulator(osg::Vec3 &initialPosition, osg::Vec3 &initialPointingPosition, osg::Vec3 &upVector)
{
    osg::ref_ptr<osgGA::TrackballManipulator> manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(initialPosition, initialPointingPosition, upVector);
    return manipulator;
}

osgViewer::View* OSGWidget::create_view(osg::Camera *camera, osg::ref_ptr<osgGA::TrackballManipulator> &manipulator)
{
    osgViewer::View* view = new osgViewer::View;
    view->setCamera(camera);
    view->setSceneData(this->mRoot.get());
    view->addEventHandler(new osgViewer::StatsHandler);
    view->setCameraManipulator(manipulator);
    return view;
}

osgViewer::CompositeViewer* OSGWidget::create_viewer(osgViewer::View *view)
{
    osgViewer::CompositeViewer* viewer = new osgViewer::CompositeViewer;
    viewer->addView(view);
    viewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    viewer->realize();
    view->home();
    return viewer;
}

void OSGWidget::add_ball(osg::Vec3 &initialBallPosition, float &ballRadius, osg::Vec4 &ballColor)
{
    osg::Sphere* ball = new osg::Sphere(initialBallPosition, ballRadius);
    osg::ShapeDrawable* sdBall = new osg::ShapeDrawable(ball);
    sdBall->setColor(ballColor);
    sdBall->setName("Sphere");
    osg::Geode* geodeBall = new osg::Geode;
    geodeBall->addDrawable(sdBall);
    osg::StateSet* stateSetBall = geodeBall->getOrCreateStateSet();
    osg::Material* materialBall = new osg::Material;
    materialBall->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateSetBall->setAttributeAndModes(materialBall, osg::StateAttribute::ON);
    stateSetBall->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    osg::PositionAttitudeTransform *transformBall = new osg::PositionAttitudeTransform;
    transformBall->setPosition(initialBallPosition);
    transformBall->setUpdateCallback(new SphereUpdateCallback());
    transformBall->addChild(geodeBall);
    this->mRoot->addChild(transformBall);
}

void OSGWidget::add_cylinder(osg::Vec3 &initialCylinderPosition, float &cylinderRadius, float &cylinderHeight, osg::Vec4 &cylinderColor)
{
    osg::Cylinder* cylinder = new osg::Cylinder(initialCylinderPosition, cylinderRadius, cylinderHeight);
    osg::ShapeDrawable* sdCylinder = new osg::ShapeDrawable(cylinder);
    sdCylinder->setColor(cylinderColor);
    sdCylinder->setName("Cylinder");
    osg::Geode* geodeCylinder = new osg::Geode;
    geodeCylinder->addDrawable(sdCylinder);
    osg::StateSet* stateSetCylinder = geodeCylinder->getOrCreateStateSet();
    osg::Material* materialCylinder = new osg::Material;
    materialCylinder->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateSetCylinder->setAttributeAndModes(materialCylinder, osg::StateAttribute::ON);
    stateSetCylinder->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    osg::PositionAttitudeTransform *transformCylinder = new osg::PositionAttitudeTransform;
    transformCylinder->setPosition(initialCylinderPosition);
    transformCylinder->addChild(geodeCylinder);
    this->mRoot->addChild(transformCylinder);
}

void OSGWidget::add_ground_plane(float &groundPlaneSize, osg::Vec4 &groundPlaneColor)
{
    osg::ref_ptr<osg::Vec3Array> groundPlaneVertices = new osg::Vec3Array;
    groundPlaneVertices->push_back(osg::Vec3(-groundPlaneSize, -groundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(groundPlaneSize, -groundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(groundPlaneSize, groundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(-groundPlaneSize, groundPlaneSize, 0.0f));
    osg::ref_ptr<osg::Vec3Array> groundPlaneNormals = new osg::Vec3Array;
    groundPlaneNormals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    osg::ref_ptr<osg::Vec4Array> groundColor = new osg::Vec4Array;
    groundColor->push_back(groundPlaneColor);
    osg::ref_ptr<osg::Geometry> groundGeometry = new osg::Geometry;
    groundGeometry->setVertexArray(groundPlaneVertices.get());
    groundGeometry->setNormalArray(groundPlaneNormals.get());
    groundGeometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    groundGeometry->setColorArray(groundColor.get());
    groundGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    groundGeometry->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
    osg::Geode* geodeGroundPlane = new osg::Geode;
    geodeGroundPlane->addDrawable(groundGeometry.get());
    osg::StateSet* stateSetGround = geodeGroundPlane->getOrCreateStateSet();
    osg::Material* materialGround = new osg::Material;
    materialGround->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    stateSetGround->setAttributeAndModes(materialGround, osg::StateAttribute::ON);
    stateSetGround->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
    this->mRoot->addChild(geodeGroundPlane);
}

void OSGWidget::configure_update()
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setMinimumSize(100, 100);
    this->setMouseTracking(true);

    this->update();

    double timeStep{1.0/this->mFramesPerSecond};
    double timerDurationInMilliSeconds{timeStep * 1000};
    this->mTimerId = startTimer(timerDurationInMilliSeconds);
}
