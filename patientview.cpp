#include "patientview.h"
#include "ui_patientview.h"
#include"idatabase.h"
#include"fileAModel.h"


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


void patientview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().PatientTabModel);
}


void patientview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().PatientTabModel);
}


void patientview::on_sortByTime_clicked()
{
    QPushButton* btn=(QPushButton*)sender();
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字
    QSqlTableModel *theModel=IDatabase::getInstance().PatientTabModel;
    qDebug()<<"now button:"<<btnObj;
    if(btnObj=="按照就诊时间升序")
    {
        btn->setText("按照就诊时间降序");
        theModel->setSort(theModel->fieldIndex("CREATEDTIMESTAMP"),Qt::AscendingOrder);
    }
    else
    {
        btn->setText("按照就诊时间升序");
        theModel->setSort(theModel->fieldIndex("CREATEDTIMESTAMP"),Qt::DescendingOrder);
    }
    theModel->select();
}

