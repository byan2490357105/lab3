#include "medicalview.h"
#include "ui_medicalview.h"
#include"idatabase.h"

medicalview::medicalview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::medicalview)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initMedicalModel()){
        ui->tableView->setModel(iDatabase.MedicalTabModel);
        ui->tableView->setSelectionModel(iDatabase.theMedicalSelection);
    }
}

medicalview::~medicalview()
{
    delete ui;
}

void medicalview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchMedical(filter);
}


void medicalview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewMedical();
    emit goMedicalEditView(currow);
}


void medicalview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentMedical();
}


void medicalview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().theMedicalSelection->currentIndex();
    emit goMedicalEditView(curIndex.row());
}

