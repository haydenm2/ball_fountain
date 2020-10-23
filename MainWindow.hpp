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

public slots:
    void on_actionExit_triggered();

private slots:
    void on_horizontalSlider_BallMass_valueChanged(int newMass);

    void on_horizontalSlider_BallSize_valueChanged(int newRadius);

    void on_horizontalSlider_BallVelocity_valueChanged(int newVelocity);

    void on_horizontalSlider_BallColor_valueChanged(int newColor);

private:
    Ui::MainWindowForm *mMainWindowUI;
};

#endif
