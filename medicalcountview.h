#ifndef MEDICALCOUNTVIEW_H
#define MEDICALCOUNTVIEW_H

#include <QWidget>
#include"fileAModel.h"
#include"idatabase.h"

namespace Ui {
class medicalCountview;
}

class medicalCountview : public QWidget
{
    Q_OBJECT

public:
    explicit medicalCountview(QWidget *parent = nullptr);
    ~medicalCountview();

private:
    Ui::medicalCountview *ui;

signals:
    void goPreviousView();
private slots:
    void on_btIn_clicked();
    void on_btOut_clicked();
    void on_sortByNum_clicked();
    void on_btSearch_clicked();
    void on_btCountAdd_clicked();
    void on_btDecrease_clicked();
};

#endif // MEDICALCOUNTVIEW_H
