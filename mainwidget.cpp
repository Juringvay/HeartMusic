#include "mainwidget.h"
#include "ui_mainwidget.h"

mainWidget::mainWidget(QWidget *parent,QNetworkCookieJar *cookie) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_cookJar = cookie;

}

mainWidget::~mainWidget()
{
    delete ui;
}

void mainWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePressed&&( e->buttons()&&Qt::LeftButton ) ){
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void mainWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void mainWidget::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void mainWidget::on_pBclose_clicked()
{
     qApp->quit();
     //可扩展
}

void mainWidget::on_pBmin_clicked()
{
    this->showMinimized();
}
