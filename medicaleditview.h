#ifndef MEDICALEDITVIEW_H
#define MEDICALEDITVIEW_H

#include <QWidget>
#include"idatabase.h"

namespace Ui {
class medicalEditview;
}

class medicalEditview : public QWidget
{
    Q_OBJECT

public:
    explicit medicalEditview(QWidget *parent = nullptr,int index=0);
    ~medicalEditview();

private slots:
    void on_btSave_clicked();

    void on_btCancle_clicked();

private:
    Ui::medicalEditview *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // MEDICALEDITVIEW_H
