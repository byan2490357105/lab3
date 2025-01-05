#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include<QtSql>
#include<QSqlDatabase>
#include<QDataWidgetMapper>

class IDatabase : public QObject
{
    Q_OBJECT



public:
    static IDatabase &getInstance()
    {
        static IDatabase instance; // Guaranteed to be destroyed.
            // Instantiated on first use.
        return instance;
    }
    bool isadmin;//判断登录用户是否是admin，有关是否能查看医生列表
    QString usern;
    QString userLogin(QString userName,QString password);

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(IDatabase const&)               = delete;
    void operator=(IDatabase const&)  = delete;

    QSqlDatabase database;

    void initDatabase();


signals:

public:
    bool initPatientModel();
    void searchPatientByPage(int start,int limit);
    bool searchPatient(QString filter,int start,int limit);
    int addNewPatient();
    bool deleteCurrentPatient();
    bool submitPatientEdit();
    void revertPatientEdit();

    bool initDoctorModel();
    bool searchDoctor(QString filter);
    int addNewDoctor();
    bool deleteCurrentDoctor();
    bool submitDoctorEdit();
    void revertDoctorEdit();

    bool initMedicalModel();
    bool searchMedical(QString filter);
    int addNewMedical();
    bool deleteCurrentMedical();
    bool submitMedicalEdit();
    void revertMedicalEdit();

    bool initHistoryModel();
    bool searchHistory(QString filter);
    int addNewHistory();
    bool deleteCurrentHistory();
    bool submitHistoryEdit();
    void revertHistoryEdit();

    bool initReportModel();
    bool searchReport(QString filter);
    int addNewReport();
    bool deleteCurrentReport();
    bool submitReportEdit();
    void revertReportEdit();


    QSqlTableModel *PatientTabModel;
    QItemSelectionModel *thePatientSelection;

    QSqlTableModel *DoctorTabModel;
    QItemSelectionModel *theDoctorSelection;

    QSqlTableModel *MedicalTabModel;
    QItemSelectionModel *theMedicalSelection;

    QSqlTableModel *HistoryTabModel;
    QItemSelectionModel *theHistorySelection;

    QSqlTableModel *ReportTabModel=NULL;
    QItemSelectionModel *theReportSelection;

};

#endif // IDATABASE_H
