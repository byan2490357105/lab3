#ifndef HISTORYVIEW_H
#define HISTORYVIEW_H

#include <QWidget>

namespace Ui {
class historyview;
}

class historyview : public QWidget
{
    Q_OBJECT

public:
    explicit historyview(QWidget *parent = nullptr);
    ~historyview();

private:
    Ui::historyview *ui;
     void FileToTable(QStringList &aFileContent);

signals:
    void goHistoryEditView(int idx);
private slots:
    void on_btSearch_clicked();
    void on_btAdd_clicked();
    void on_btDelete_clicked();
    void on_btEdit_clicked();
    void on_sortByTime_clicked();
    void on_btIn_clicked();
};

#endif // HISTORYVIEW_H
