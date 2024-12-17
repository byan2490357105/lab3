#include "doctorview.h"
#include "ui_doctorview.h"
#include"idatabase.h"

doctorview::doctorview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::doctorview)
{
    ui->setupUi(this);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initDoctorModel()){
        ui->tableView->setModel(iDatabase.DoctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);
    }
}

doctorview::~doctorview()
{
    delete ui;
}

void doctorview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewDoctor();
    emit goDoctorEditView(currow);
}


void doctorview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchDoctor(filter);
}


void doctorview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentDoctor();
}


void doctorview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().theDoctorSelection->currentIndex();
    emit goDoctorEditView(curIndex.row());
}

