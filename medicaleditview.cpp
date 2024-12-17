#include "medicaleditview.h"
#include "ui_medicaleditview.h"

medicalEditview::medicalEditview(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::medicalEditview)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().MedicalTabModel;
    dataMapper->setModel(IDatabase::getInstance().MedicalTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->IDEdit,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->nameEdit,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->MLEdit,tabModel->fieldIndex("ML"));
    dataMapper->addMapping(ui->numEdit,tabModel->fieldIndex("NUMBER"));
    dataMapper->setCurrentIndex(index);
}

medicalEditview::~medicalEditview()
{
    delete ui;
}

void medicalEditview::on_btSave_clicked()
{
    IDatabase::getInstance().submitMedicalEdit();
    emit goPreviousView();
}


void medicalEditview::on_btCancle_clicked()
{
    IDatabase::getInstance().revertMedicalEdit();
    emit goPreviousView();
}

