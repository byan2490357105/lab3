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
    ~patientview();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btIn_clicked();

    void on_btOut_clicked();

    void on_sortByTime_clicked();

signals:
    void goPatientEditView(int idx);

private:
    Ui::patientview *ui;
};

#endif // PATIENTVIEW_H
