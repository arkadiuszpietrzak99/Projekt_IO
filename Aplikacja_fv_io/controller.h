#ifndef CONTROLLER_H
#define CONTROLLER_H
#pragma once
#include <QObject>
#include <QDir>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
class controller : public QObject
{

    Q_OBJECT

public :

    explicit controller(QObject* parent=nullptr);
    QStringList getFiles(const QString &path);
    QByteArray getFileMd5(const QString &fileName);
    QStringList filesOfDifferentSize(const QStringList &fileList);

signals:
    void sendDuplicateFile(const QHash<QByteArray,QStringList> &duplicateFiles);
    void sendProgress(int current,int total);
    void sendMessageBox();

public slots:

    void duplicateFileDetect(const QString &path);
};


#endif // CONTROLLER_H

