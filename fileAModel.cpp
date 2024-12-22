#include"fileAModel.h"

void clearTable(QSqlTableModel* model)
{
    // 删除所有行
    int rowCount = model->rowCount();
    if (rowCount > 0) {
        model->removeRows(0, rowCount);
        if (!model->submitAll()) {
            qDebug() << "Failed to clear data: " << model->lastError().text();
        } else {
            qDebug() << "Data cleared successfully.";
        }
    }
}

void FileToTable(QStringList &aFileContent, QSqlTableModel *theModel)
{
    int rowCnt=aFileContent.count();//文本行数
    int curRow=theModel->rowCount()-1;
    QStringList tmpList;
    //clearTable(theModel);
    theModel->select();
    int j;
    for(int i=1;i<rowCnt;i++)
    {
        theModel->insertRow(i+curRow);
        QString aLineText=aFileContent.at(i);
        tmpList=aLineText.split(QRegularExpression("\\s+"),Qt::SkipEmptyParts);
        for(j=0;j<theModel->columnCount();j++)
        {
            QModelIndex index = theModel->index(i+curRow, j);
            theModel->setData(index,tmpList.at(j));
        }
    }
    theModel->submitAll();
}


void FileIn(QWidget *window,QSqlTableModel *theModel)
{
    QString curPath=QCoreApplication::applicationDirPath();
    QString aFileName=QFileDialog::getOpenFileName(window,"打开要导入的文件，请确保格式正确",
                                                     curPath,"诊断历史文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return ;
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        while(!aStream.atEnd())
        {
            QString str=aStream.readLine();
            fFileContent.append(str);
        }
        aFile.close();
        FileToTable(fFileContent,theModel);
    }
}

void FileOut(QWidget *window,QSqlTableModel *theModel)
{
    QString fileName = QFileDialog::getSaveFileName(nullptr, "保存表格数据", "", "Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) {
        qWarning() << "用户未选择文件";
        return;  // 如果用户取消选择，直接返回
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件" << fileName;
        return;
    }

    QTextStream out(&file);
    QStringList headerData;
    for (int col = 0; col < theModel->columnCount(); ++col) {
        // 获取列名并保存到headerData
        QString header = theModel->headerData(col, Qt::Horizontal).toString();
        headerData << header;
    }
    // 将表头以Tab分隔并写入文件
    out << headerData.join("\t") << "\n";

    // 遍历QSqlTableModel的行和列
    for (int row = 0; row < theModel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < theModel->columnCount(); ++col) {
            // 获取单元格的内容，并用Tab键分隔
            QVariant data = theModel->data(theModel->index(row, col));
            rowData << data.toString();
        }
        // 将一行数据以Tab分隔并写入文件
        out << rowData.join("\t") << "\n";
    }

    // 关闭文件
    file.close();
    qDebug() << "数据已保存到文件：" << fileName;
    QMessageBox::information(window,"导出文件消息框","数据已保存到"+fileName,
                             QMessageBox::Ok,QMessageBox::NoButton);
}
