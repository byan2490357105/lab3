#ifndef DATEREPORTVIEW_H
#define DATEREPORTVIEW_H

#include <QWidget>

namespace Ui {
class dateReportview;
}

class dateReportview : public QWidget
{
    Q_OBJECT

public:
    explicit dateReportview(QWidget *parent = nullptr);
    ~dateReportview();

private:
    Ui::dateReportview *ui;

signals:
    void goUserReportView(int idx);
private slots:
    void on_btSearch_clicked();
    void on_btAdd_clicked();
    void on_btDelete_clicked();
    void on_btEdit_clicked();
    void on_btIn_clicked();
    void on_btOut_clicked();
    void on_sortByTime_clicked();
};

#endif // DATEREPORTVIEW_H
