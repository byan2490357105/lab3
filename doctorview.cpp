#include "doctorview.h"
#include "ui_doctorview.h"
#include"idatabase.h"
#include"fileAModel.h"

doctorview::doctorview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::doctorview)
{
    ui->setupUi(this);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initDoctorModel()){
        ui->tableView->setModel(iDatabase.DoctorTabModel);
        ui->tableView->setSelectionModel(iDatabase.theDoctorSelection);
    }
}

doctorview::~doctorview()
{
    delete ui;
}

void doctorview::on_btAdd_clicked()
{
    int currow=IDatabase::getInstance().addNewDoctor();
    emit goDoctorEditView(currow);
}


void doctorview::on_btSearch_clicked()
{
    QString filter=QString("name like '%%1%'").arg(ui->lineEdit->text());
    IDatabase::getInstance().searchDoctor(filter);
}


void doctorview::on_btDelete_clicked()
{
    IDatabase::getInstance().deleteCurrentDoctor();
}


void doctorview::on_btEdit_clicked()
{
    QModelIndex curIndex=IDatabase::getInstance().theDoctorSelection->currentIndex();
    emit goDoctorEditView(curIndex.row());
}


void doctorview::on_btIn_clicked()
{
    FileIn(this,IDatabase::getInstance().DoctorTabModel);
}


void doctorview::on_btOut_clicked()
{
    FileOut(this,IDatabase::getInstance().DoctorTabModel);
}


void doctorview::on_sortByID_clicked()
{
    QPushButton* btn=(QPushButton*)sender();
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字
    QSqlTableModel *theModel=IDatabase::getInstance().DoctorTabModel;
    qDebug()<<"now button:"<<btnObj;
    if(btnObj=="按照ID升序")
    {
        btn->setText("按照ID降序");
        theModel->setSort(theModel->fieldIndex("ID"),Qt::AscendingOrder);
    }
    else
    {
        btn->setText("按照ID升序");
        theModel->setSort(theModel->fieldIndex("ID"),Qt::DescendingOrder);
    }
    theModel->select();
}

