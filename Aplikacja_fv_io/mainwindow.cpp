#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDir>
#include <QtAlgorithms>
#include "duplicates.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

 QString  mPath = QDir::homePath();

 //Wyswietlanie struktury dysków za pomocą drzewa
 dirmodel = new QFileSystemModel(this);
 dirmodel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);
 dirmodel->setRootPath(mPath);
 ui->treeView->setModel(dirmodel);
 ui->treeView->hideColumn(1);

//Wyswietlanie wszystkich plików znajdujących sie w konkretnym folderze za pomocą listy
 filemodel = new QFileSystemModel(this);
 filemodel->setFilter(QDir::NoDotAndDotDot|QDir::Files);
 filemodel->setRootPath(mPath);
 ui->tableView->setModel(filemodel);

 //Wyswietlanie wybranych typów plików znajdujących sie w konkretnym folderze za pomocą listy
 filtermodel=new QFileSystemModel(this);
  filtermodel->setFilter(QDir::NoDotAndDotDot|QDir::Files);
 filtermodel->setRootPath(mPath);
 ui->tableView_2->setModel(filtermodel);

}


MainWindow::~MainWindow()
{
    delete ui;
}

//Jeżli klikniemy w wybrany folder w drzewku to wyswietlą nam sie pliki w drugiej liście
void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
             QString mPath = dirmodel->fileInfo(index).absoluteFilePath();
             ui->tableView->setRootIndex(filemodel->setRootPath(mPath));

             //Przyciski służące do filtracji plików po rozszerzeniu
            if(ui->radioButton->isChecked()){
             QStringList filters;
              filters << "*.txt";
              filtermodel->setNameFilterDisables(false);

             filtermodel->setNameFilters(filters);
              ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }

            if(ui->radioButton_2->isChecked()){
             QStringList filters;
              filters << "*.jpg";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }

            if(ui->radioButton_11->isChecked()){
             QStringList filters;
              filters << "*.mp4";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
              ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }
            if(ui->radioButton_4->isChecked()){
             QStringList filters;
              filters << "*.exe";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
              ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }
            if(ui->radioButton_5->isChecked()){
             QStringList filters;
              filters << "*.pdf";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
              ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }

            if(ui->radioButton_6->isChecked()){
             QStringList filters;
              filters << "*.mp3";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }

            if(ui->radioButton_8->isChecked()){
             QStringList filters;
              filters << "*.xlsx";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }

            if(ui->radioButton_9->isChecked()){
             QStringList filters;
              filters << "*.png";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }
            if(ui->radioButton_10->isChecked()){
             QStringList filters;
              filters << "*.rar";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }
            if(ui->radioButton_3->isChecked()){
             QStringList filters;
              filters << "*.doc";
               filtermodel->setNameFilterDisables(false);
             filtermodel->setNameFilters(filters);
             ui->tableView_2->setRootIndex(filtermodel->setRootPath(mPath));
            }


}


//Przycisk na pasku za pomocą którego wybieramy folder w którym chcemy znaleść duplikaty
void MainWindow::on_actionOtworz_triggered()
{

    duplicates *duplicate_window=new duplicates;
    QFileDialog dialogwindow(this);
    dialogwindow.setFileMode(QFileDialog::Directory);
    QStringList duplicate_directory;
    if (dialogwindow.exec()) duplicate_directory = dialogwindow.selectedFiles();
    if (duplicate_directory.isEmpty())
    {
        QMessageBox msg;
        msg.setText("Please select a folder.");
        msg.exec();
    }
    duplicate_window->ForcePath(duplicate_directory[0]);
    duplicate_window->show();
}


//Jezeli klikniemy dwa razy na wybrany z naszej listy plik, otworzy nam się folder z danym plikiem w eksploratorze plików windows
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
     QString mPath = dirmodel->fileInfo(index).absoluteFilePath();
     mPath = mPath.section("/",0,-2);
     qDebug()<<mPath;
     QString folderPath = QString("%1%2").arg("file:///").arg(mPath);
     QDesktopServices::openUrl(QUrl(folderPath, QUrl::TolerantMode));
}

