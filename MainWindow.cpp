#include "MainWindow.hpp"
#include "ui_MainWindowForm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow{parent},
    mMainWindowUI{new Ui::MainWindowForm}
{
    mMainWindowUI->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mMainWindowUI;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_horizontalSlider_BallMass_valueChanged(int newMass)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->mass = newMass;
}

void MainWindow::on_horizontalSlider_BallSize_valueChanged(int newRadius)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->radius = newRadius/100.0;
    osgWidget->update_nozzle(newRadius/100.0);
}

void MainWindow::on_horizontalSlider_BallVelocity_valueChanged(int newVelocity)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->velocity[2] = newVelocity;
}

void MainWindow::on_horizontalSlider_BallColor_valueChanged(int newColor)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->color = newColor;
}

void MainWindow::on_horizontalSlider_BallFrequency_valueChanged(int newFrequency)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->ballsPerSecond = newFrequency;
    osgWidget->update_ball_update_rate();
}

void MainWindow::on_horizontalSlider_FluidViscosity_valueChanged(int newFluidDensity)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->physics.fluidDensity = newFluidDensity/10.0;
}

void MainWindow::on_horizontalSlider_Gravity_valueChanged(int newGravity)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->physics.gravity = -9.81*(newGravity/10.0);
}

void MainWindow::on_horizontalSlider_BallBounciness_valueChanged(int newCoefficient)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->coefficientOfRestitution = newCoefficient/100.0;
}
