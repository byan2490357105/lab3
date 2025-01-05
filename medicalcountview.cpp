#include "medicalcountview.h"
#include "ui_medicalcountview.h"

medicalCountview::medicalCountview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::medicalCountview)
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

medicalCountview::~medicalCountview()
{
    delete ui;
}

void medicalCountview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().MedicalTabModel);
}


void medicalCountview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().MedicalTabModel);
}


void medicalCountview::on_sortByNum_clicked()
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


void medicalCountview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchMedical(filter);
}


void medicalCountview::on_btCountAdd_clicked()
{
    QSqlTableModel *theModel=IDatabase::getInstance().MedicalTabModel;
    QModelIndex curIndex=IDatabase::getInstance().theMedicalSelection->currentIndex();
    int num=ui->spinBox->text().toInt();
    QModelIndex index = theModel->index(curIndex.row(), 3);//对应的是NUMBER，即库存列
    int temp=theModel->record(index.row()).value("NUMBER").toInt();
    theModel->setData(index,temp+num);
    theModel->submitAll();
}


void medicalCountview::on_btDecrease_clicked()
{
    QSqlTableModel *theModel=IDatabase::getInstance().MedicalTabModel;
    QModelIndex curIndex=IDatabase::getInstance().theMedicalSelection->currentIndex();
    int num=ui->spinBox->text().toInt();
    QModelIndex index = theModel->index(curIndex.row(), 3);//对应的是NUMBER，即库存列
    int temp=theModel->record(index.row()).value("NUMBER").toInt();
    if(temp<num){
        QMessageBox::information(this,"库存出入库消息框","当前库存数小于出库数，出库失败",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return ;
    }
    theModel->setData(index,temp-num);
    theModel->submitAll();
}

