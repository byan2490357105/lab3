#ifndef HISTORYEDITVIEW_H
#define HISTORYEDITVIEW_H

#include <QWidget>
#include"idatabase.h"

namespace Ui {
class historyEditview;
}

class historyEditview : public QWidget
{
    Q_OBJECT

public:
    explicit historyEditview(QWidget *parent = nullptr,int index=0);
    ~historyEditview();

private slots:
    void on_btSave_clicked();

    void on_btCancle_clicked();

private:
    Ui::historyEditview *ui;
    QDataWidgetMapper *dataMapper;

signals:
    void goPreviousView();
};

#endif // HISTORYEDITVIEW_H
