#include "userreportview.h"
#include "ui_userreportview.h"
#include"loginview.h"

userReportview::userReportview(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::userReportview)
{
    ui->setupUi(this);
    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().ReportTabModel;
    dataMapper->setModel(IDatabase::getInstance().ReportTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dnameEdit,tabModel->fieldIndex("USERNAME"));
    dataMapper->addMapping(ui->conditionEdit,tabModel->fieldIndex("CONDITION"));
    dataMapper->addMapping(ui->resultBox,tabModel->fieldIndex("RESULT"));
    dataMapper->addMapping(ui->dateTimeEdit,tabModel->fieldIndex("DATE"));
    dataMapper->addMapping(ui->commentBox,tabModel->fieldIndex("COMMENT"));
    dataMapper->setCurrentIndex(index);
    if(!IDatabase::getInstance().isadmin)
        ui->dnameEdit->setText(IDatabase::getInstance().usern);
}

userReportview::~userReportview()
{
    delete ui;
}

void userReportview::on_btSave_clicked()
{
    IDatabase::getInstance().submitReportEdit();
    emit goPreviousView();
}


void userReportview::on_btCancle_clicked()
{
    IDatabase::getInstance().revertReportEdit();
    emit goPreviousView();
}

