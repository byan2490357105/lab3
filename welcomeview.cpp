#include "welcomeview.h"
#include "ui_welcomeview.h"

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




void Welcome::on_Department_clicked()
{
    emit goDepartmentView();
}


void Welcome::on_Doctor_clicked()
{
    emit goDoctorView();
}


void Welcome::on_Patient_clicked()
{
    emit goPatientView();
}

