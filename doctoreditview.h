#ifndef DOCTOREDITVIEW_H
#define DOCTOREDITVIEW_H

#include <QWidget>
#include<QDataWidgetMapper>
namespace Ui {
class doctorEditview;
}

class doctorEditview : public QWidget
{
    Q_OBJECT

public:
    explicit doctorEditview(QWidget *parent = nullptr,int index=0);
    ~doctorEditview();

private slots:
    void on_saveButton_clicked();

    void on_btsave_clicked();

    void on_btcan_clicked();

    void on_btSave_clicked();

    void on_btCancle_clicked();

private:
    QDataWidgetMapper *dataMapper;
    Ui::doctorEditview *ui;

signals:
    void goPreviousView();
};

#endif // DOCTOREDITVIEW_H
