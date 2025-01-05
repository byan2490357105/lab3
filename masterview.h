#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include"loginview.h"
#include"patientview.h"
#include"patienteditview.h"
#include"welcomeview.h"
#include"doctorview.h"
#include"doctoreditview.h"
#include"medicaleditview.h"
#include"medicalview.h"
#include"historyeditview.h"
#include"historyview.h"
#include"medicalcountview.h"
#include"datereportview.h"
#include"userreportview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();
public slots:
    void goLoginView();
    void goPatientView();
    void goPatientEditView(int rowNo);
    void goWelcomeView();
    void goPreviousView();
    void goDoctorView();
    void goDoctorEditView(int rowNo);
    void goMedicalView();
    void goMedicalEditView(int rowNo);
    void goHistoryView();
    void goHistoryEditView(int rowNo);
    void goMedicalCountView();
    void goDateReportView();
    void goUserReportView(int rowNo);


private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:

    void pushWidgetToStackView(QWidget *widget);

    Ui::MasterView *ui;

    Welcome *welcomeView;
    LoginView *loginView;
    patientEditview *patienteditView;
    patientview *patientView;
    doctorview *doctorView;
    doctorEditview *doctoreditView;
    medicalview *medicalView;
    medicalEditview *medicaleditView;
    historyview *historyView;
    historyEditview *historyeditView;
    medicalCountview *medicalcountView;
    dateReportview *datereportView;
    userReportview *userreportView;

};
#endif // MASTERVIEW_H
