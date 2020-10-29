#include "OSGWidget.hpp"


OSGWidget::OSGWidget(QWidget* parent, Qt::WindowFlags flags):
    QOpenGLWidget{parent,flags},
    mGraphicsWindow{new osgViewer::GraphicsWindowEmbedded{this->x(),
                                                          this->y(),
                                                          this->width(),
                                                          this->height()}},
    mRoot{new osg::Group},
    mView{new osgViewer::View},
    mViewer{new osgViewer::CompositeViewer},
    camera{new osg::Camera},
    manipulator{new osgGA::TrackballManipulator}
{
    create_camera();
    create_manipulator();
    create_view();
    create_viewer();
    add_cylinder();
    add_ground_plane();
    configure_update();
}

OSGWidget::~OSGWidget()
{
    killTimer(simulationUpdateTimerId);
    killTimer(ballUpdateTimerId);
}

void OSGWidget::timerEvent(QTimerEvent *event)
{
    if(!pauseFlag)
    {
        if(event->timerId() == simulationUpdateTimerId)
            physics.update(1/framesPerSecond);
        else if(event->timerId() == ballUpdateTimerId)
            add_ball();
    }
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

void OSGWidget::keyPressEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::keyReleaseEvent(QKeyEvent* event)
{
    QString keyString = event->text();
    const char* keyData = keyString.toLocal8Bit().data();
    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::mouseMoveEvent(QMouseEvent* event)
{
    auto pixelRatio = this->devicePixelRatio();
    this->getEventQueue()->mouseMotion(static_cast<float>(event->x()*pixelRatio),
                                       static_cast<float>(event->y()*pixelRatio));
}

void OSGWidget::mousePressEvent(QMouseEvent* event)
{
    auto pixelRatio = this->devicePixelRatio();
    unsigned int button = 0;

        switch(event->button())
        {
        case Qt::LeftButton:
            button = 1;
            break;

        case Qt::MiddleButton:
            button = 2;
            break;

        case Qt::RightButton:
            button = 3;
            break;

        default:
            break;
        }
    this->getEventQueue()->mouseButtonPress(static_cast<float>( event->x() * pixelRatio),
                                            static_cast<float>( event->y() * pixelRatio),
                                            button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
{
    auto pixelRatio = this->devicePixelRatio();
    unsigned int button = 0;

        switch(event->button())
        {
        case Qt::LeftButton:
            button = 1;
            break;

        case Qt::MiddleButton:
            button = 2;
            break;

        case Qt::RightButton:
            button = 3;
            break;

        default:
            break;
        }
    this->getEventQueue()->mouseButtonRelease(static_cast<float>(pixelRatio*event->x()),
                                              static_cast<float>(pixelRatio*event->y()),
                                              button);
}

void OSGWidget::wheelEvent(QWheelEvent* event)
{
    event->accept();
    int delta = event->delta();
    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
    this->getEventQueue()->mouseScroll(motion);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if(eventQueue)
        return eventQueue;
    else
        throw std::runtime_error("Unable to obtain valid event queue");
}

void OSGWidget::create_camera()
{
    float aspectRatio = static_cast<float>(this->width())/static_cast<float>(this->height());
    auto pixelRatio = this->devicePixelRatio();
    camera->setViewport(0, 0, this->width()*pixelRatio, this->height()*pixelRatio);
    camera->setClearColor(osg::Vec4(0.8f, 0.8f, 0.8f, 0.7f));
    camera->setProjectionMatrixAsPerspective(45.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(this->mGraphicsWindow);
}

void OSGWidget::create_manipulator()
{
    osg::Vec3 initialPosition{0.0, -15.0, 15.0};
    osg::Vec3 initialPointingPosition{0, 0, 0};
    osg::Vec3 upVector{0,0,1};
    manipulator->setAllowThrow( false );
    manipulator->setHomePosition(initialPosition, initialPointingPosition, upVector);
}

void OSGWidget::create_view()
{
    mView->setCamera(camera);
    mView->setSceneData(this->mRoot.get());
    mView->addEventHandler(new osgViewer::StatsHandler);
    mView->setCameraManipulator(manipulator);
}

void OSGWidget::create_viewer()
{
    mViewer->addView(mView);
    mViewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    mViewer->realize();
    mView->home();
}

void OSGWidget::add_cylinder()
{
    float cylinderRadius{physics.get_new_ball_radius()};
    float cylinderHeight{fountainHeightScale*physics.get_new_ball_radius()};
    osg::Vec3 initialCylinderPosition{0.f, 0.f, float(cylinderHeight/2.0)};
    osg::Vec4 cylinderColor{0.5f, 0.5f, 0.5f, 1.f};
    osg::Cylinder* cylinder = new osg::Cylinder(osg::Vec3{0.f, 0.f, 0.f}, cylinderRadius, cylinderHeight);
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

void OSGWidget::add_ground_plane()
{
    osg::Vec4 groundPlaneColor{0.04f, 0.4f, 0.14f, 0.0f};
    osg::ref_ptr<osg::Vec3Array> groundPlaneVertices = new osg::Vec3Array;
    groundPlaneVertices->push_back(osg::Vec3(-initialGroundPlaneSize, -initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(initialGroundPlaneSize, -initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(initialGroundPlaneSize, initialGroundPlaneSize, 0.0f));
    groundPlaneVertices->push_back(osg::Vec3(-initialGroundPlaneSize, initialGroundPlaneSize, 0.0f));
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

    double simulationUpdateTimeStep{1.0/this->framesPerSecond};
    double simulationTimerDurationInMilliSeconds{simulationUpdateTimeStep * 1000};
    this->simulationUpdateTimerId = startTimer(simulationTimerDurationInMilliSeconds);

    double ballUpdateTimeStep{1.0/this->ballsPerSecond};
    double ballTimerDurationInMilliSeconds{ballUpdateTimeStep * 1000};
    this->ballUpdateTimerId = startTimer(ballTimerDurationInMilliSeconds);
}

void OSGWidget::add_ball()
{
    Eigen::Vector3f noisyVelocity{osgwidgetutils::get_small_random_float(), osgwidgetutils::get_small_random_float(), physics.get_new_ball_velocity()[2]};
    this->physics.set_new_ball_velocity(noisyVelocity);
    physics.add_ball();

    if(physics.get_ball_count() < physics.get_max_ball_count())
    {
        osg::Vec3 initialBallPosition{0.f, 0.f, 3*physics.get_new_ball_radius()};
        osg::Vec4 initialBallColor{osgwidgetutils::hue_to_osg_rgba_decimal(physics.get_new_ball_color())};
        osg::Sphere* ball = new osg::Sphere(osg::Vec3{0.f, 0.f, 0.f}, physics.get_new_ball_radius());
        osg::ShapeDrawable* sdBall = new osg::ShapeDrawable(ball);
        sdBall->setColor(initialBallColor);
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
        transformBall->setUpdateCallback(new SphereUpdateCallback(&physics));
        transformBall->addChild(geodeBall);
        this->mRoot->addChild(transformBall);
    }
}

void OSGWidget::clear_balls()
{
    mRoot->removeChildren(2, physics.get_ball_count());
    physics.clear_balls();
    update();
}

void OSGWidget::update_ball_update_rate()
{
    killTimer(ballUpdateTimerId);
    double ballUpdateTimeStep{1.0/ballsPerSecond};
    double ballTimerDurationInMilliSeconds{ballUpdateTimeStep * 1000};
    ballUpdateTimerId = startTimer(ballTimerDurationInMilliSeconds);
}

void OSGWidget::update_nozzle()
{
    osg::PositionAttitudeTransform *nozzleTransform = dynamic_cast<osg::PositionAttitudeTransform *> (this->mRoot->getChild(0));
    osg::Geode *nozzleGeode = nozzleTransform->getChild(0)->asGeode();
    osg::ShapeDrawable *nozzleShapeDrawable = dynamic_cast<osg::ShapeDrawable *> (nozzleGeode->getDrawable(0));
    osg::Cylinder *nozzle = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), physics.get_new_ball_radius(), physics.get_new_ball_radius()*fountainHeightScale);
    nozzleShapeDrawable->setShape(nozzle);
}

BallPhysics* OSGWidget::get_physics_ptr()
{
    return &(this->physics);
}

float OSGWidget::get_ground_plane_size()
{
    return this->initialGroundPlaneSize;
}

float OSGWidget::get_fluid_density()
{
    return this->physics.get_fluid_density();
}

float OSGWidget::get_radius()
{
    return this->physics.get_new_ball_radius();
}

float OSGWidget::get_mass()
{
    return this->physics.get_new_ball_mass();
}

unsigned int OSGWidget::get_color()
{
    return this->physics.get_new_ball_color();
}

Eigen::Vector3f OSGWidget::get_position()
{
    return this->physics.get_new_ball_position();
}

Eigen::Vector3f OSGWidget::get_velocity()
{
    return this->physics.get_new_ball_velocity();
}

float OSGWidget::get_coefficient_of_restitution()
{
    return this->physics.get_new_ball_coefficient_of_restitution();
}

float OSGWidget::get_ball_rate()
{
    return this->ballsPerSecond;
}

bool OSGWidget::is_paused()
{
    return this->pauseFlag;
}

void OSGWidget::set_fluid_density(float newDensity)
{
    this->get_physics_ptr()->set_fluid_density(newDensity/10.0);
}

void OSGWidget::set_gravity(float newGravity)
{
    this->get_physics_ptr()->set_gravity(newGravity);
}

void OSGWidget::set_radius(float newRadius)
{
    this->physics.set_new_ball_radius(newRadius);
    this->physics.set_new_ball_height(fountainHeightScale*physics.get_new_ball_radius());
}

void OSGWidget::set_mass(float newMass)
{
    this->physics.set_new_ball_mass(newMass);
}

void OSGWidget::set_color(unsigned int newColor)
{
    this->physics.set_new_ball_color(newColor);
}

void OSGWidget::set_velocity(float newUpwardVelocity)
{
    Eigen::Vector3f newVelocity{osgwidgetutils::get_small_random_float(), osgwidgetutils::get_small_random_float(), newUpwardVelocity};
    this->physics.set_new_ball_velocity(newVelocity);
}

void OSGWidget::set_coefficient_of_restitution(float newCoefficient)
{
    this->physics.set_new_ball_coefficient_of_restitution(newCoefficient);
}

void OSGWidget::set_ball_rate(float newRate)
{
    this->ballsPerSecond = newRate;
}

void OSGWidget::set_pause_flag(bool pauseState)
{
    this->pauseFlag = pauseState;
}

