#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QMouseEvent>
namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0, QNetworkCookieJar *cookie = NULL);
    ~mainWidget();

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_pBclose_clicked();

    void on_pBmin_clicked();

private:
    Ui::mainWidget *ui;
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

    QNetworkCookieJar *m_cookJar;

};

#endif // MAINWIDGET_H
