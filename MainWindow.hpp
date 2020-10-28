#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtCore>

#include "OSGWidget.hpp"

namespace Ui {
class MainWindowForm;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_horizontalSlider_BallMass_valueChanged(int newMass);

    void on_horizontalSlider_BallSize_valueChanged(int newRadius);

    void on_horizontalSlider_BallVelocity_valueChanged(int newVelocity);

    void on_horizontalSlider_BallColor_valueChanged(int newColor);

    void on_horizontalSlider_BallFrequency_valueChanged(int newFrequency);

    void on_horizontalSlider_FluidViscosity_valueChanged(int newViscosity);

    void on_horizontalSlider_Gravity_valueChanged(int newGravity);

    void on_horizontalSlider_BallBounciness_valueChanged(int newCoefficient);

    void on_pushButton_DefaultParameters_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_Pause_toggled(bool checked);

private:
    Ui::MainWindowForm *mMainWindowUI;
};

#endif
