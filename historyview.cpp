#include "historyview.h"
#include "ui_historyview.h"
#include"idatabase.h"
#include<QFileDialog>
#include<QString>
#include<QRegularExpression>
#include<QStandardItem>
#define ColunmCount 6

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

void clearTable(QSqlTableModel* model)
{
    // 删除所有行
    int rowCount = model->rowCount();
    if (rowCount > 0) {
        model->removeRows(0, rowCount);
        if (!model->submitAll()) {
            qDebug() << "Failed to clear data: " << model->lastError().text();
        } else {
            qDebug() << "Data cleared successfully.";
        }
    }
}

void historyview::FileToTable(QStringList &aFileContent)//将文件导入到表格
{
    int rowCnt=aFileContent.count();//文本行数
    QSqlTableModel *theModel=IDatabase::getInstance().HistoryTabModel;
    QStringList tmpList;
    clearTable(theModel);
    theModel->select();
    qDebug()<<theModel->columnCount();
    int j;
    for(int i=1;i<rowCnt;i++)
    {
        theModel->insertRow(i-1);
        QString aLineText=aFileContent.at(i);
        tmpList=aLineText.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
        for(j=0;j<ColunmCount;j++)
        {
            QModelIndex index = theModel->index(i-1, j);
            theModel->setData(index,tmpList.at(j));
        }
    }
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
    QString curPath=QCoreApplication::applicationDirPath();
    QString aFileName=QFileDialog::getOpenFileName(this,"打开要导入的文件，请确保格式正确",
                                                     curPath,"诊断历史文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return ;
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();
            fFileContent.append(str);
        }
        aFile.close();
        FileToTable(fFileContent);
    }
}

