#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPainter>
#include <cmath>

namespace Ui {class MainWindow;}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent* e);
    ~MainWindow();

public slots:
    void main_function();
    
private:
    Ui::MainWindow *ui;
    QTimer* m_timer;
    QPen pen;

    float gravity=-10;  //gravity constant
    float dt=0.004;     //discrete time step

    //cartesian joints positions
    float cart_joint_pos_x[2];
    float cart_joint_pos_y[2];

    //pendulum centre - static joint cartesian position
    int centre_x=625;
    int centre_y=240;

    float m[2];         //joints masses
    float l[2];         //links lengths
    float fi[2];        //angular position
    float dfi[2];       //angular velocity
    float ddfi[2];      //angular acceleration
    float dfi_prev[2];  //previous angular velocity
    float ddfi_prev[2]; //previous angular acceleration
    float scale=90;     //drawing scale
};

#endif // MAINWINDOW_H
