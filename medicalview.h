#ifndef MEDICALVIEW_H
#define MEDICALVIEW_H

#include <QWidget>

namespace Ui {
class medicalview;
}

class medicalview : public QWidget
{
    Q_OBJECT

public:
    explicit medicalview(QWidget *parent = nullptr);
    ~medicalview();

private slots:
    void on_btSearch_clicked();

    void on_btAdd_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

    void on_btIn_clicked();

    void on_btOut_clicked();

    void on_sortByNum_clicked();

private:
    Ui::medicalview *ui;

signals:
    void goMedicalEditView(int idx);
};

#endif // MEDICALVIEW_H
