#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class Welcome;
}

class Welcome : public QWidget
{
    Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome();

private slots:

    void on_Department_clicked();

    void on_Doctor_clicked();

    void on_Patient_clicked();

signals:
    void goDepartmentView();
    void goDoctorView();
    void goPatientView();

private:
    Ui::Welcome *ui;
};

#endif // WELCOMEVIEW_H
