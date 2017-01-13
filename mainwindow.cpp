#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_timer = new QTimer;
    m_timer->setInterval(4);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(main_function()));
    m_timer->start();

    //initialize angular position and velocity
    fi[1]=1.6;fi[0]=1.6;
    dfi[0]=0;dfi[1]=0;

    //set links length and joints masses
    m[0]=2;m[1]=1;
    l[0]=2;l[1]=2;
}

void MainWindow::main_function()
{
    //calculate acceleration - equations determined based on Lagrangian formula
    ddfi[0] =-(-gravity*m[0]*sin(fi[0])-gravity*m[1]*sin(fi[0])+(dfi[1]*dfi[1])*l[1]*m[1]*sin(fi[0]-fi[1])+gravity*m[1]*sin(fi[1])*cos(fi[0]-fi[1])+(dfi[0]*dfi[0])*l[0]*m[1]*cos(fi[0]-fi[1])*sin(fi[0]-fi[1]))/(l[0]*(m[0]+m[1]-m[1]*pow(cos(fi[0]-fi[1]),2.0)));
    ddfi[1] =(gravity*m[0]*sin(fi[1])+gravity*m[1]*sin(fi[1])+(dfi[0]*dfi[0])*l[0]*m[0]*sin(fi[0]-fi[1])+(dfi[0]*dfi[0])*l[0]*m[1]*sin(fi[0]-fi[1])-gravity*m[0]*sin(fi[0])*cos(fi[0]-fi[1])-gravity*m[1]*sin(fi[0])*cos(fi[0]-fi[1])+(dfi[1]*dfi[1])*l[1]*m[1]*cos(fi[0]-fi[1])*sin(fi[0]-fi[1]))/(l[1]*(m[0]+m[1]-m[1]*pow(cos(fi[0]-fi[1]),2.0)));

    //integration - simplest rectangle method
    dfi[0]=dfi[0]+ddfi[0]*dt;
    fi[0]=fi[0]+dfi[0]*dt;
    dfi[1]=dfi[1]+ddfi[1]*dt;
    fi[1]=fi[1]+dfi[1]*dt;
    ddfi_prev[0]=ddfi[0];ddfi_prev[1]=ddfi[1];
    dfi_prev[0]=dfi[0];dfi_prev[1]=dfi[1];

    //update joints position for drawing
    cart_joint_pos_x[0]=l[0]*scale*sin(fi[0])+centre_x;
    cart_joint_pos_y[0]=l[0]*scale*cos(fi[0])+centre_y;
    cart_joint_pos_x[1]=l[1]*scale*sin(fi[1])+cart_joint_pos_x[0];
    cart_joint_pos_y[1]=l[1]*scale*cos(fi[1])+cart_joint_pos_y[0];

    //draw pendulum
    update();
}

void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    //draw links
    pen.setColor(QColor(100,100,100,255));
    pen.setWidth(7);
    painter.setBrush(QBrush(QColor(255,255,255,255)));
    painter.setPen(pen);
    painter.drawLine(cart_joint_pos_x[0],cart_joint_pos_y[0],centre_x,centre_y);
    painter.drawLine(cart_joint_pos_x[0],cart_joint_pos_y[0],cart_joint_pos_x[1],cart_joint_pos_y[1]);

    //draw joints
    pen.setWidth(5);
    painter.setPen(pen);
    painter.drawEllipse(centre_x-8,centre_y-8,16,16);
    painter.drawEllipse(cart_joint_pos_x[0]-8,cart_joint_pos_y[0]-8,16,16);

    //draw endpoint
    pen.setColor(QColor(255,255,255,255));
    painter.setPen(pen);
    painter.drawEllipse(cart_joint_pos_x[1]-5,cart_joint_pos_y[1]-5,10,10);
}

MainWindow::~MainWindow()
{
    delete ui;
}
