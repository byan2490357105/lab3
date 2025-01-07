#include "welcomeview.h"
#include "ui_welcomeview.h"
#include"idatabase.h"
#include<QMessageBox>

Welcome::Welcome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Welcome)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}




void Welcome::on_Medical_clicked()
{
    emit goMedicalView();
}


void Welcome::on_Doctor_clicked()
{
    if(IDatabase::getInstance().isadmin)
        emit goDoctorView();
    else
        QMessageBox::information(this,"登录提示消息框","您不是admin用户，无权查看",
                                 QMessageBox::Ok,QMessageBox::NoButton);
}


void Welcome::on_Patient_clicked()
{
    emit goPatientView();
}


void Welcome::on_History_clicked()
{
    emit goHistoryView();
}


void Welcome::on_MedicalCount_clicked()
{
    emit goMedicalCountView();
}


void Welcome::on_DateReport_clicked()
{
    if(IDatabase::getInstance().isadmin)
        emit goDateReportView();
    else{
        if(IDatabase::getInstance().initReportModel()){

        }
        emit goUserReportView(IDatabase::getInstance().addNewReport());
    }
}


void Welcome::on_DoctorArrange_clicked()
{
    emit goDoctorArrangeView();
}

