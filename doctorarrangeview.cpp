#include "doctorarrangeview.h"
#include "ui_doctorarrangeview.h"
#include"idatabase.h"
#include"fileAModel.h"

doctorArrangeview::doctorArrangeview(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::doctorArrangeview)
{
    ui->setupUi(this);

    IDatabase &iDatabase=IDatabase::getInstance();
    if(iDatabase.initArrangeModel()){
        ui->tableView->setModel(iDatabase.ArrangeTabModel);
        ui->tableView->setSelectionModel(iDatabase.theArrangeSelection);
    }
    tabModel=iDatabase.ArrangeTabModel;
    if(!IDatabase::getInstance().isadmin)
        connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &doctorArrangeview::selectionChanged);
    NullToNor();
}

void doctorArrangeview::NullToNor()
{
    for(int i=0;i<tabModel->rowCount();i++)
    {
        for(int j=0;j<tabModel->columnCount();j++)
        {
            QModelIndex index=tabModel->index(i,j);
            if(tabModel->data(index)=="")
                tabModel->setData(index,"点击选择");
        }
    }
}

doctorArrangeview::~doctorArrangeview()
{
    delete ui;
}

void doctorArrangeview::on_btSave_clicked()
{
    IDatabase::getInstance().submitArrangeEdit();
}


void doctorArrangeview::on_btCancle_clicked()
{
    IDatabase::getInstance().revertArrangeEdit();
}

void doctorArrangeview::selectionChanged(const QItemSelection &selected)
{
    QModelIndexList selectedIndexes = selected.indexes();
    if (!selectedIndexes.isEmpty()) {
        QModelIndex index = selectedIndexes.first();

        // 修改该单元格的数据为 "用户名"
        IDatabase::getInstance().ArrangeTabModel->setData(index, IDatabase::getInstance().usern);
    }
}


void doctorArrangeview::on_pushButton_clicked()
{
    if(!IDatabase::getInstance().isadmin)
    {
        QMessageBox::information(this,"医生安排消息框","您不是admin用户，无法执行该操作",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return ;
    }
    QModelIndex index=IDatabase::getInstance().theArrangeSelection->currentIndex();
    tabModel->setData(index,"点击选择");

}

