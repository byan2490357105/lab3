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
    initPage();
    QString temp=QString("%1 \\ %2").arg(page).arg(pagetotal);
    ui->nowPage->setText(temp);
}

void patientview::changePage()
{
    IDatabase &iDatabase=IDatabase::getInstance();
    pagestart=(page-1)*pagelimit;
    if(ui->lineEdit->text()!="")
    {
        QString queryCount=QString("SELECT count(1) FROM Patient WHERE NAME like '%%1%'")
                                 .arg(ui->lineEdit->text());
        QSqlQuery query(queryCount);
        int rowCount;
        if (query.exec()) {
            if (query.next()) {
                rowCount = query.value(0).toInt(); // 获取 COUNT(*) 返回的行数
                qDebug() << "Row count:" << rowCount;
            }
        } else {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        pagetotal=rowCount%pagelimit==0?rowCount/pagelimit:rowCount/pagelimit+1;
        iDatabase.searchPatient(ui->lineEdit->text(),pagestart,pagelimit);
    }
    else
    {
        pagetotal=maxrow%pagelimit==0?maxrow/pagelimit:maxrow/pagelimit+1;
        iDatabase.searchPatientByPage(pagestart,pagelimit);
    }
    QString temp=QString("%1 \\ %2").arg(page).arg(pagetotal);
    ui->nowPage->setText(temp);
}

void patientview::initPage()
{
    IDatabase &iDatabase=IDatabase::getInstance();
    pagelimit=4;//暂时将每页查询设置为4
    maxrow=iDatabase.PatientTabModel->rowCount();//查询总行数
    page=1;
    if(maxrow%pagelimit==0)
        pagetotal=maxrow/pagelimit;
    else
        pagetotal=maxrow/pagelimit+1;
    pagestart=(page-1)*pagelimit;
    iDatabase.searchPatientByPage(pagestart,pagelimit);
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
    page=1;
    changePage();
    // QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    // IDatabase::getInstance().searchPatient(filter,pagestart,pagelimit);
}


void patientview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentPatient();
    changePage();
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
    // theModel->select();
    changePage();
}


void patientview::on_btLPage_clicked()
{
    if(page>1)
        page--;
    qDebug()<<"now page"<<page;
    changePage();
}


void patientview::on_btNPage_clicked()
{
    if(page<pagetotal)
        page++;
    qDebug()<<"now page"<<page;
    changePage();
}

