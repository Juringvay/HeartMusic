#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QSettings>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

const QString tokenUrl = "https://passport.baidu.com/v2/api/?getapi&class=login&tpl=mn&tangram=true";

enum LOGIN_ERROR
{
    LONIN_SUCCESS_ERROR,
    USER_PASSWD_ERROR,
};

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();
    int logIn();

    QNetworkCookieJar *getCookieJar(){
        return m_cookJar;
    }

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_pBclose_clicked();

    void on_pBlogin_clicked();

    void on_pBmin_clicked();

private:
    Ui::loginDialog *ui;
    QPoint mousePoint;              //鼠标拖动自定义标题栏时的坐标
    bool mousePressed;              //鼠标是否按下

    int getRandNum();
    QString getWebResponse(QString url);
    QString getToken(QString url);
    QString postWebResponse(QString url, QByteArray postData);

    QNetworkCookieJar *m_cookJar;
    QString m_userName;
    QString m_passWd;
    int m_iLoginError;
};

#endif // LOGINDIALOG_H
