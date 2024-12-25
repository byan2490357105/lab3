#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>

namespace Ui {
class patientview;
}

class patientview : public QWidget
{
    Q_OBJECT

public:
    explicit patientview(QWidget *parent = nullptr);
    int page;//当前页数
    int pagestart;//记录到的查询开始行数,limit是从第几行+到第几+pagelimit行
    int pagetotal;//记录总页数
    int pagelimit;//设置查询条数
    void changePage();
    ~patientview();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btIn_clicked();

    void on_btOut_clicked();

    void on_sortByTime_clicked();

    void on_btLPage_clicked();

    void on_btNPage_clicked();

signals:
    void goPatientEditView(int idx);

private:
    Ui::patientview *ui;
};

#endif // PATIENTVIEW_H
