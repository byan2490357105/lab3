#include "historyeditview.h"
#include "ui_historyeditview.h"

historyEditview::historyEditview(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::historyEditview)
{
    ui->setupUi(this);
    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().HistoryTabModel;
    dataMapper->setModel(IDatabase::getInstance().HistoryTabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->IDEdit,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->pnameEdit,tabModel->fieldIndex("PNAME"));
    dataMapper->addMapping(ui->dnameEdit,tabModel->fieldIndex("DNAME"));
    dataMapper->addMapping(ui->medicalEdit,tabModel->fieldIndex("MEDICAL"));
    dataMapper->addMapping(ui->eventEdit,tabModel->fieldIndex("EVENT"));
    dataMapper->addMapping(ui->dateTimeEdit,tabModel->fieldIndex("TIMESTAMP"));
    dataMapper->setCurrentIndex(index);
}

historyEditview::~historyEditview()
{
    delete ui;
}

void historyEditview::on_btSave_clicked()
{
    QString plainText = ui->eventEdit->toPlainText();
    qDebug()<<dataMapper->currentIndex();

    // 将纯文本更新到模型中
    QSqlTableModel *tabModel = IDatabase::getInstance().HistoryTabModel;
    tabModel->setData(tabModel->index(dataMapper->currentIndex(), tabModel->fieldIndex("EVENT")), plainText);
    IDatabase::getInstance().submitHistoryEdit();
    emit goPreviousView();
}


void historyEditview::on_btCancle_clicked()
{
    IDatabase::getInstance().revertHistoryEdit();
    emit goPreviousView();
}

