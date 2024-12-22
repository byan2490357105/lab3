#ifndef FILEAMODEL_H
#define FILEAMODEL_H

#endif // FILEAMODEL_H
#include"idatabase.h"
#include<QFileDialog>
#include<QString>
#include<QRegularExpression>
#include<QStandardItem>
#include<QMessageBox>

void FileToTable(QStringList &aFileContent,QSqlTableModel *theModel);//将文件导入到表格

void FileIn(QWidget *window,QSqlTableModel *theModel);//文件导入

void FileOut(QWidget *window,QSqlTableModel *theModel);//文件导出
