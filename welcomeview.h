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

    void on_Medical_clicked();

    void on_Doctor_clicked();

    void on_Patient_clicked();

    void on_History_clicked();

    void on_MedicalCount_clicked();

    void on_DateReport_clicked();

    void on_DoctorArrange_clicked();

signals:
    void goMedicalView();
    void goDoctorView();
    void goPatientView();
    void goHistoryView();
    void goMedicalCountView();
    void goDateReportView();
    void goUserReportView(int index);
    void goDoctorArrangeView();

private:
    Ui::Welcome *ui;
};

#endif // WELCOMEVIEW_H
