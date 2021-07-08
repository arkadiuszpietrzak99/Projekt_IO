#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QTableWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:

private slots:

    void on_treeView_clicked(const QModelIndex &index);
    void on_actionOtworz_triggered();
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
    QFileSystemModel *filtermodel;

};
#endif // MAINWINDOW_H
