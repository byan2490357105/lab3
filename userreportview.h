#ifndef USERREPORTVIEW_H
#define USERREPORTVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
#include"idatabase.h"

namespace Ui {
class userReportview;
}

class userReportview : public QWidget
{
    Q_OBJECT

public:
    explicit userReportview(QWidget *parent = nullptr,int index=0);
    ~userReportview();

private:
    Ui::userReportview *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
private slots:
    void on_btSave_clicked();
    void on_btCancle_clicked();
};

#endif // USERREPORTVIEW_H
