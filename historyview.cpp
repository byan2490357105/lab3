#include "historyview.h"
#include "ui_historyview.h"
#include"idatabase.h"
#include<QFileDialog>
#include<QString>
#include<QRegularExpression>
#include<QStandardItem>
#include<QMessageBox>
#include"fileAModel.h"

historyview::historyview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::historyview)
{
    ui->setupUi(this);

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initHistoryModel()){
        ui->tableView->setModel(iDatabase.HistoryTabModel);
        ui->tableView->setSelectionModel(iDatabase.theHistorySelection);
    }
}

historyview::~historyview()
{
    delete ui;
}



void historyview::on_btSearch_clicked()
{
    QString filter=QString("pname like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchHistory(filter);
}


void historyview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewHistory();
    emit goHistoryEditView(currow);
}


void historyview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentHistory();
}


void historyview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().theHistorySelection->currentIndex();
    emit goHistoryEditView(curIndex.row());
}

void historyview::on_sortByTime_clicked()
{
    QPushButton* btn=(QPushButton*)sender();
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字
    qDebug()<<"now button:"<<btnObj;
    if(btnObj=="按时间日期升序排序")
    {
        btn->setText("按时间日期降序排序");
        IDatabase::getInstance().HistoryTabModel->setSort(IDatabase::getInstance().HistoryTabModel->fieldIndex("TIMESTAMP"),Qt::AscendingOrder);
    }
    else
    {
        btn->setText("按时间日期升序排序");
        IDatabase::getInstance().HistoryTabModel->setSort(IDatabase::getInstance().HistoryTabModel->fieldIndex("TIMESTAMP"),Qt::DescendingOrder);
    }
     IDatabase::getInstance().HistoryTabModel->select();
}


void historyview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().HistoryTabModel);
}


void historyview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().HistoryTabModel);
}

