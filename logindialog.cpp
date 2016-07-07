#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_user->setPlaceholderText("请输入百度账号");
    ui->lineEdit_password->setPlaceholderText("请输入密码");
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);//使密码显示为小黑点
    ui->lineEdit_user->setFocus();//将光标转到账号输入框
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    m_cookJar = new QNetworkCookieJar;

    int iCheck = 0;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "JuringvayFM", "JuringvayFM");
    settings.beginGroup("User");
    iCheck = settings.value("RememberMe").toInt();
    ui->checkBox->setChecked(iCheck);
    m_userName = settings.value("UserName").toString();
    m_passWd = settings.value("PassWd").toString();

    if(iCheck)
    {
       ui->lineEdit_user->setText(m_userName);
       ui->lineEdit_password->setText(m_passWd);
    }
     settings.endGroup();
}

loginDialog::~loginDialog()
{
    delete ui;
}

int loginDialog::logIn()
{
    getWebResponse("http://www.baidu.com");
    getWebResponse("https://passport.baidu.com/v2/api/?login");
    QString url = "https://passport.baidu.com/v2/api/?login";
    QByteArray ba;

    ba.append("ppui_logintime=");
    ba.append(QString::number(getRandNum(), 10));
    ba.append("&charset=utf-8");
    ba.append("&codestring=");
    ba.append("&token=");
    ba.append( getToken(tokenUrl));
    ba.append("&isPhone=false");
    ba.append("&index=0");
    ba.append("&u=");
    ba.append("&safeflg=0");
    ba.append("&staticpage=http%3A%2F%2Fwww.baidu.com%2Fcache%2Fuser%2Fhtml%2Fjump.html");
    ba.append("&loginType=1");
    ba.append("&tpl=mn");
    ba.append("&callback=parent.bdPass.api.login._postCallback");
    ba.append("&username=");
    ba.append(m_userName);
    ba.append("&password=");
    ba.append(m_passWd);
    ba.append("&verifycode=");
    ba.append("&mem_pass=on");

    QString postRet = postWebResponse(url, ba);

    if(postRet.contains("error=0"))
    {
        qDebug() << "登录成功" << m_userName;
        m_iLoginError = LONIN_SUCCESS_ERROR;
    }
    else if(postRet.contains("error=2"))
    {
        qDebug() << "用户名密码错误";
        m_iLoginError = USER_PASSWD_ERROR;
    }

    return m_iLoginError;
}

void loginDialog::mouseMoveEvent(QMouseEvent *e)
{
    if(mousePressed&&( e->buttons()&&Qt::LeftButton ) ){
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void loginDialog::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void loginDialog::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void loginDialog::on_pBclose_clicked()
{
    qApp->quit();
}

void loginDialog::on_pBlogin_clicked()
{
    if(ui->lineEdit_user->text().isEmpty())
    {
        QMessageBox::warning(NULL, "warning", "请输入用户名" , QMessageBox::Yes);
        return;
    }
    else if(ui->lineEdit_password->text().isEmpty())
    {
        QMessageBox::warning(NULL, "warning", "请输入密码" , QMessageBox::Yes);
        return;
    }

    m_userName = ui->lineEdit_user->text();
    m_passWd = ui->lineEdit_password->text();
    Qt::CheckState check = ui->checkBox->checkState();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "JuringvayFM", "JuringvayFM");
    settings.beginGroup("User");
    settings.setValue("RememberMe", check);
    if(check)
    {
        settings.setValue("UserName", m_userName);
        settings.setValue("PassWd", m_passWd);
    }
    settings.endGroup();

    int iLoginSuccess = logIn();
    if(iLoginSuccess == LONIN_SUCCESS_ERROR)
    {
        accept();
    }
    else if(iLoginSuccess == USER_PASSWD_ERROR)
    {
        QMessageBox::warning(NULL, "warning", "密码错误" , QMessageBox::Yes);
    }

}

void loginDialog::on_pBmin_clicked()
{
    this->showMinimized();
}

int loginDialog::getRandNum()
{
    int irandNum = qrand() %(99999-10000+1)+10000;
    return irandNum;
}

QString loginDialog::getWebResponse(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;
    QByteArray responseData;

    manager->setCookieJar(m_cookJar);
    //设置网址
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    responseData = reply->readAll();

    reply->deleteLater();

    return QString(responseData); //返回取到的源码字符串
}

QString loginDialog::getToken(QString url)
{
    QString response;
    response = getWebResponse(url);

    QRegExp rx;
    rx.setPattern("token='([0-9 | a-f]{1,})");

    //下面就是匹配字符串（其实用正则更好）
    int start = rx.indexIn(response);
    int end = rx.matchedLength();

    QString token = response.mid(start, end);

    token = token.mid(7, token.size());

    return token; //返回获取的token
}

QString loginDialog::postWebResponse(QString url, QByteArray postData)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;
    QNetworkRequest request;
    QByteArray responseData;

    manager->setCookieJar(m_cookJar);
    //设置网址
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    request.setUrl(QUrl(url));
    QNetworkReply *reply = manager->post(request, postData);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    responseData = reply->readAll();

    reply->deleteLater();

    return QString(responseData); //返回取到的源码字符串
}
