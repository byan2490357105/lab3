#include "doctoreditview.h"
#include "ui_doctoreditview.h"
#include"idatabase.h"

doctorEditview::doctorEditview(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::doctorEditview)
{
    ui->setupUi(this);
    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().DoctorTabModel;
    dataMapper->setModel(IDatabase::getInstance().DoctorTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->IDEdit,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->bookEdit,tabModel->fieldIndex("EMPLOYEENO"));
    dataMapper->addMapping(ui->nameEdit,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->sexBox,tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->ageEdit,tabModel->fieldIndex("AGE"));
    dataMapper->setCurrentIndex(index);

}

doctorEditview::~doctorEditview()
{
    delete ui;
}

void doctorEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitDoctorEdit();
    emit goPreviousView();
}


void doctorEditview::on_btCancle_clicked()
{
    IDatabase::getInstance().revertDoctorEdit();
    emit goPreviousView();
}

