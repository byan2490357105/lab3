#ifndef DOCTORARRANGEVIEW_H
#define DOCTORARRANGEVIEW_H

#include <QWidget>
#include<QItemSelection>
#include<QSqlTableModel>
#include<QMessageBox>

namespace Ui {
class doctorArrangeview;
}

class doctorArrangeview : public QWidget
{
    Q_OBJECT

public:
    explicit doctorArrangeview(QWidget *parent = nullptr);
    void NullToNor();
    ~doctorArrangeview();

private:
    Ui::doctorArrangeview *ui;
    QSqlTableModel *tabModel;

signals:
    void goPreviousView();
private slots:
    void on_btSave_clicked();
    void on_btCancle_clicked();
    void selectionChanged(const QItemSelection &selected);
    void on_pushButton_clicked();
};

#endif // DOCTORARRANGEVIEW_H
