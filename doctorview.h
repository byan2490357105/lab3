#ifndef DOCTORVIEW_H
#define DOCTORVIEW_H

#include <QWidget>

namespace Ui {
class doctorview;
}

class doctorview : public QWidget
{
    Q_OBJECT

public:
    explicit doctorview(QWidget *parent = nullptr);
    ~doctorview();

private slots:
    void on_btAdd_clicked();

    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

signals:
    void goDoctorEditView(int idx);

private:
    Ui::doctorview *ui;
};

#endif // DOCTORVIEW_H
