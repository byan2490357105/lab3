#include "idatabase.h"
#include<QUuid>
void IDatabase::initDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="C:/Users/Lenovo/Desktop/Qt/database/lab4.db";
    database.setDatabaseName(aFile);
    if(!database.open()){
        qDebug()<<"failed to open database";
    }
    else{
        qDebug()<<"open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    PatientTabModel=new QSqlTableModel(this,database);
    PatientTabModel->setTable("Patient");
    PatientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    PatientTabModel->setSort(PatientTabModel->fieldIndex("CREATEDTIMESTAMP"),Qt::AscendingOrder);
    if(!(PatientTabModel->select()))
        return false;
    thePatientSelection=new QItemSelectionModel(PatientTabModel);
    return true;
}

void IDatabase::searchPatientByPage(int start, int limit)
{
    QString queryStr = QString("SELECT * FROM Patient LIMIT %1 OFFSET %2")
        .arg(limit)
        .arg(start);
     PatientTabModel->setQuery(queryStr,database);
}

bool IDatabase::searchPatient(QString filter, int start, int limit)
{
    QString queryStr = QString("SELECT * FROM Patient WHERE name like '%1' LIMIT %2 OFFSET %3")
    .arg(filter)
        .arg(limit)
        .arg(start);
    PatientTabModel->setQuery(queryStr,database);
    // PatientTabModel->setFilter(filter);
    // return PatientTabModel->select();
}

int IDatabase::addNewPatient()
{
    PatientTabModel->insertRow(PatientTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=PatientTabModel->index(PatientTabModel->rowCount()-1,1);
    int curRecNo=curIndex.row();

    QSqlRecord curRec=PatientTabModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    PatientTabModel->setRecord(curRecNo,curRec);
    return curIndex.row();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=thePatientSelection->currentIndex();
    PatientTabModel->removeRow(curIndex.row());
    PatientTabModel->submitAll();
    // PatientTabModel->select();

}

bool IDatabase::submitPatientEdit()
{
    return PatientTabModel->submitAll();
}

void IDatabase::revertPatientEdit()
{
    PatientTabModel->revertAll();
}

bool IDatabase::initDoctorModel()
{
    DoctorTabModel=new QSqlTableModel(this,database);
    DoctorTabModel->setTable("Doctor");
    DoctorTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    DoctorTabModel->setSort(DoctorTabModel->fieldIndex("ID"),Qt::AscendingOrder);
    if(!(DoctorTabModel->select()))
        return false;
    theDoctorSelection=new QItemSelectionModel(DoctorTabModel);
    return true;
}

bool IDatabase::searchDoctor(QString filter)
{
    DoctorTabModel->setFilter(filter);
    return DoctorTabModel->select();
}

int IDatabase::addNewDoctor()
{
    DoctorTabModel->insertRow(DoctorTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=DoctorTabModel->index(DoctorTabModel->rowCount()-1,1);
    int curRecNo=curIndex.row();

    return curIndex.row();
}

bool IDatabase::deleteCurrentDoctor()
{
    QModelIndex curIndex=theDoctorSelection->currentIndex();
    DoctorTabModel->removeRow(curIndex.row());
    DoctorTabModel->submitAll();
    DoctorTabModel->select();
}

bool IDatabase::submitDoctorEdit()
{
    return DoctorTabModel->submitAll();
}

void IDatabase::revertDoctorEdit()
{
    return DoctorTabModel->revertAll();
}

bool IDatabase::initMedicalModel()
{
    MedicalTabModel=new QSqlTableModel(this,database);
    MedicalTabModel->setTable("Medical");
    MedicalTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    MedicalTabModel->setSort(MedicalTabModel->fieldIndex("NUMBER"),Qt::AscendingOrder);
    if(!(MedicalTabModel->select()))
        return false;
    theMedicalSelection=new QItemSelectionModel(MedicalTabModel);
    return true;
}

bool IDatabase::searchMedical(QString filter)
{
    MedicalTabModel->setFilter(filter);
    return MedicalTabModel->select();
}

int IDatabase::addNewMedical()
{
    MedicalTabModel->insertRow(MedicalTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=MedicalTabModel->index(MedicalTabModel->rowCount()-1,1);
    int curRecNo=curIndex.row();

    return curIndex.row();
}

bool IDatabase::deleteCurrentMedical()
{
    QModelIndex curIndex=theMedicalSelection->currentIndex();
    MedicalTabModel->removeRow(curIndex.row());
    MedicalTabModel->submitAll();
    MedicalTabModel->select();
}

bool IDatabase::submitMedicalEdit()
{
    return MedicalTabModel->submitAll();
}

void IDatabase::revertMedicalEdit()
{
    return MedicalTabModel->revertAll();
}

bool IDatabase::initHistoryModel()
{
    HistoryTabModel=new QSqlTableModel(this,database);
    HistoryTabModel->setTable("History");
    HistoryTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    HistoryTabModel->setSort(HistoryTabModel->fieldIndex("TIMESTAMP"),Qt::AscendingOrder);
    if(!(HistoryTabModel->select()))
        return false;
    theHistorySelection=new QItemSelectionModel(HistoryTabModel);
    return true;
}

bool IDatabase::searchHistory(QString filter)
{
    HistoryTabModel->setFilter(filter);
    return HistoryTabModel->select();
}

int IDatabase::addNewHistory()
{
    HistoryTabModel->insertRow(HistoryTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=HistoryTabModel->index(HistoryTabModel->rowCount()-1,1);
    int curRecNo=curIndex.row();

    return curIndex.row();
}

bool IDatabase::deleteCurrentHistory()
{
    QModelIndex curIndex=theHistorySelection->currentIndex();
    HistoryTabModel->removeRow(curIndex.row());
    HistoryTabModel->submitAll();
    HistoryTabModel->select();
}

bool IDatabase::submitHistoryEdit()
{
    return HistoryTabModel->submitAll();
}

void IDatabase::revertHistoryEdit()
{
    return HistoryTabModel->revertAll();
}

bool IDatabase::initReportModel()
{
    if(ReportTabModel!=NULL)
        return true;
    ReportTabModel=new QSqlTableModel(this,database);
    ReportTabModel->setTable("DateReport");
    ReportTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ReportTabModel->setSort(ReportTabModel->fieldIndex("TIMESTAMP"),Qt::AscendingOrder);
    if(!(ReportTabModel->select()))
        return false;
    theReportSelection=new QItemSelectionModel(ReportTabModel);
    return true;
}

bool IDatabase::searchReport(QString filter)
{
    ReportTabModel->setFilter(filter);
    return ReportTabModel->select();
}

int IDatabase::addNewReport()
{
    ReportTabModel->insertRow(ReportTabModel->rowCount(),QModelIndex());
    QModelIndex curIndex=ReportTabModel->index(ReportTabModel->rowCount()-1,1);
    int curRecNo=curIndex.row();

    return curIndex.row();
}

bool IDatabase::deleteCurrentReport()
{
    QModelIndex curIndex=theReportSelection->currentIndex();
    ReportTabModel->removeRow(curIndex.row());
    ReportTabModel->submitAll();
    ReportTabModel->select();
}

bool IDatabase::submitReportEdit()
{
    return ReportTabModel->submitAll();
}

void IDatabase::revertReportEdit()
{
    return ReportTabModel->revertAll();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select USERNAME,PASSWORD from user where username=:USER");
    query.bindValue(":USER",userName);
    query.exec();
    query.first();
    if(query.first() && query.value("USERNAME").isValid()){
        QString passwd=query.value("PASSWORD").toString();
        if(passwd==password){
            if(userName=="admin")
                isadmin=true;
            else
                isadmin=false;
            usern=userName;
            return "LoginOk";
        }
        else{
            return "wrong password";
        }
    }
    else{
        qDebug()<<"no such user";
        return "wrong username";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}
