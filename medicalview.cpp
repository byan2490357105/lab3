#include "medicalview.h"
#include "ui_medicalview.h"
#include"idatabase.h"
#include"fileAModel.h"

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


void medicalview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().MedicalTabModel);
}


void medicalview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().MedicalTabModel);
}


void medicalview::on_sortByNum_clicked()
{
    QPushButton* btn=(QPushButton*)sender();
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字
    QSqlTableModel *theModel=IDatabase::getInstance().MedicalTabModel;
    qDebug()<<"now button:"<<btnObj;
    if(btnObj=="按照排库存数升序")
    {
        btn->setText("按照排库存数降序");
        theModel->setSort(theModel->fieldIndex("NUMBER"),Qt::AscendingOrder);
    }
    else
    {
        btn->setText("按照排库存数升序");
        theModel->setSort(theModel->fieldIndex("NUMBER"),Qt::DescendingOrder);
    }
    theModel->select();
}

