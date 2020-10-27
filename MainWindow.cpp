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
    osgWidget->fluidDensity = newFluidDensity/10.0;
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

void MainWindow::on_pushButton_DefaultParameters_clicked()
{
    QSlider *ballMassSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallMass"));
    ballMassSlider->setSliderPosition(50);

    QSlider *ballSizeSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallSize"));
    ballSizeSlider->setSliderPosition(50);

    QSlider *ballBouncinessSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallBounciness"));
    ballBouncinessSlider->setSliderPosition(70);

    QSlider *ballColorSlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallColor"));
    ballColorSlider->setSliderPosition(0);

    QSlider *ballVelocitySlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallVelocity"));
    ballVelocitySlider->setSliderPosition(20);

    QSlider *ballFrequencySlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_BallFrequency"));
    ballFrequencySlider->setSliderPosition(5);

    QSlider *gravitySlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_Gravity"));
    gravitySlider->setSliderPosition(10);

    QSlider *fluidDensitySlider = qobject_cast<QSlider *>(findChild<QObject *>("horizontalSlider_FluidViscosity"));
    fluidDensitySlider->setSliderPosition(5);
}

void MainWindow::on_pushButton_Reset_clicked()
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->clear_balls();
}

void MainWindow::on_pushButton_Pause_toggled(bool checked)
{
    OSGWidget *osgWidget = qobject_cast<OSGWidget *>(findChild<QObject *>("graphicsView"));
    osgWidget->pauseFlag = checked;
    QPushButton *pausePlayButton = qobject_cast<QPushButton *>(findChild<QObject *>("pushButton_Pause"));
    if(checked)
        pausePlayButton->setText(QString("Play"));
    else
        pausePlayButton->setText(QString("Pause"));
}
