#ifndef DUPLICATES_H
#define DUPLICATES_H
#pragma once
#include <QWidget>
#include <QListWidgetItem>
#include <QDesktopServices>
#include <QFile>
#include <QFileDialog>
#include <QTableWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QListWidgetItem>
#include <QMimeData>
#include <QProcess>
#include <QProgressBar>
#include "controller.h"


namespace Ui {
class duplicates;
}
class duplicates: public QWidget


{
    Q_OBJECT

public:
    explicit duplicates(QWidget *parent = 0);
    ~duplicates();
    void ForcePath(QString root);

private slots:

        void on_listWidget_currentTextChanged(const QString &currentText);
        void getDuplicateFiles(const QHash<QByteArray,QStringList> &duplicateFiles);
        void setProgressBar(int current,int total);
        void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);
        void on_pushButton_clicked();
        void setMessageBox();

signals:
        void sendFilePath(const QString &path);

private:
    Ui::duplicates *ui;
    controller filesMD5;
    QThread thread;
    QHash<QByteArray, QStringList> duplicateFiles;
    QByteArray currentKey;

};

#endif // DUPLICATES_H
