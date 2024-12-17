#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();
    bool isadmin;//验证是否有权限查看医生界面

private slots:
    void on_btSignIn_clicked();

signals:
    void loginSuccess();
    void loginFailed();

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
