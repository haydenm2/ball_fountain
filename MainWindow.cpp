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
    osgWidget->updateBallUpdateRate();
}

void MainWindow::on_horizontalSlider_MaxBallCount_valueChanged(int newMaxBallCount)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->physics.maxBallCount = newMaxBallCount;
    if(osgWidget->physics.ballCount > osgWidget->physics.maxBallCount)
    {
        osgWidget->physics.ballCount = osgWidget->physics.maxBallCount;
        osgWidget->physics.ballReplaceIndex = 0;
        while(osgWidget->physics.ballCount > osgWidget->physics.maxBallCount)
        {
            osgWidget->remove_ball();
        }
    }
}

void MainWindow::on_horizontalSlider_FluidViscosity_valueChanged(int newFluidDensity)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->physics.fluidDensity = newFluidDensity/10.0;
}
