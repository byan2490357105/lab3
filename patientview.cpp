#include "patientview.h"
#include "ui_patientview.h"
#include"idatabase.h"


patientview::patientview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::patientview)
{
    ui->setupUi(this);


    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initPatientModel()){
        ui->tableView->setModel(iDatabase.PatientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    }
}

patientview::~patientview()
{
    delete ui;
}

void patientview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewPatient();
    emit goPatientEditView(currow);
}


void patientview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchPatient(filter);
}


void patientview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
}


void patientview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().thePatientSelection->currentIndex();
    emit goPatientEditView(curIndex.row());

}

