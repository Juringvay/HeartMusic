#include "mainwidget.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginDialog login; //登陆界面
    if(login.exec()==QDialog::Accepted)
    {
         mainWidget w(0,login.getCookieJar());
         w.show();
         return a.exec();
    }
    else return 0;


}
