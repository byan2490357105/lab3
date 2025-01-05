#include "datereportview.h"
#include "ui_datereportview.h"
#include"idatabase.h"
#include"fileAModel.h"

dateReportview::dateReportview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dateReportview)
{
    ui->setupUi(this);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);
    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initReportModel()){
        ui->tableView->setModel(iDatabase.ReportTabModel);
        ui->tableView->setSelectionModel(iDatabase.theReportSelection);
    }
}

dateReportview::~dateReportview()
{
    delete ui;
}

void dateReportview::on_btSearch_clicked()
{
    QString filter=QString("username like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchReport(filter);
}


void dateReportview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewReport();
    emit goUserReportView(currow);
}


void dateReportview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentReport();
}


void dateReportview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().theReportSelection->currentIndex();
    emit goUserReportView(curIndex.row());
}


void dateReportview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().ReportTabModel);
}


void dateReportview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().ReportTabModel);
}


void dateReportview::on_sortByTime_clicked()
{
    QPushButton* btn=(QPushButton*)sender();
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字
    QSqlTableModel *theModel=IDatabase::getInstance().ReportTabModel;
    qDebug()<<"now button:"<<btnObj;
    if(btnObj=="按时间日期升序排序")
    {
        btn->setText("按时间日期降序排序");
        theModel->setSort(theModel->fieldIndex("DATE"),Qt::AscendingOrder);
    }
    else
    {
        btn->setText("按时间日期升序排序");
        theModel->setSort(theModel->fieldIndex("DATE"),Qt::DescendingOrder);
    }
    theModel->select();
}

