#include "duplicates.h"
#include "ui_duplicates.h"


duplicates::duplicates(QWidget *parent) : QWidget(parent),ui(new Ui::duplicates)
{
    ui->setupUi(this);
    thread.start();
    filesMD5.moveToThread(&thread);
    connect(this,&duplicates::sendFilePath,&filesMD5,&controller::duplicateFileDetect);
    connect(&filesMD5,&controller::sendDuplicateFile,this,&duplicates::getDuplicateFiles);
    connect(&filesMD5,&controller::sendProgress,this,&duplicates::setProgressBar);
    qRegisterMetaType<QHash<QByteArray,QStringList> >("QHash<QByteArray,QStringList>");
    connect(&filesMD5,&controller::sendMessageBox,this,&duplicates::setMessageBox);
}

//Przekazanie scieżki do 2 okna odpowiedzialnego za duplikaty
void duplicates::ForcePath(QString root)
{

    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->progressBar->setValue(0);
    emit sendFilePath(root);

}

duplicates::~duplicates()
{
    thread.quit();
    thread.wait();
    delete ui;
}

//Wyswietla Hasze znalesionych duplikatów
void duplicates::getDuplicateFiles(const QHash<QByteArray, QStringList> &duplicateFiles)
{
    ui->listWidget->clear();
    this->duplicateFiles = duplicateFiles;
    QHash<QByteArray,QStringList>::const_iterator itr = duplicateFiles.begin();
    for(itr;itr!=duplicateFiles.end();itr++)
    {
        qDebug()<<"MD5:"<<itr.key()<<"file:"<<itr.value().count();
        if(itr.value().count()>1)
        {
            ui->listWidget->addItem(itr.key());
        }
    }
}

//Pasek postępu szukania duplikatów
void duplicates::setProgressBar(int current, int total)
{
    ui->progressBar->setMaximum(total);
    ui->progressBar->setValue(current);

}

//Jeżeli klikniemy w wybrany przez nas Hasz to w drugiej liscie wyswietlą nam sie wszytkie duplikaty przypisane do tego Hasza
void duplicates::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->listWidget_2->clear();
    currentKey=currentText.toLocal8Bit();
    QStringList fileList=this->duplicateFiles[currentText.toLocal8Bit()];
    ui->listWidget_2->addItems(fileList);

}

//Jezeli klikniemy dwa razy na wybrany z naszej listy plik, otworzy nam się folder z danym plikiem w eksploratorze plików windowsa
void duplicates::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{


        QString path = item->text();
        qDebug()<<path;
        path = path.section("/",0,-2);
        qDebug()<<path;
        QString folderPath = QString("%1%2").arg("file:///").arg(path);
        QDesktopServices::openUrl(QUrl(folderPath, QUrl::TolerantMode));

}

//Przycisk za pomocą którego usuwamy wybrany przez nas z listy duplikat
void duplicates::on_pushButton_clicked()
{
    int currentRow = ui->listWidget_2->currentRow();
        qDebug()<<"currentRow:"<<currentRow;

        if(currentRow<0)
        {
            return;
        }
        QString path = ui->listWidget_2->currentItem()->text();
        if(path.isEmpty())
        {
            return;
        }
        qDebug()<<path;
        QFile::remove(path);
        duplicateFiles[currentKey].removeOne(path);
        QStringList fileList = this->duplicateFiles[currentKey];
        ui->listWidget_2->clear();
        ui->listWidget_2->addItems(fileList);
}

//Jeżeli w wybranym przez nas folderze nie znajdziemy duplikatów wyswietla się poniższa wiadomość
void duplicates::setMessageBox()
{
    QMessageBox::information(this,"Informacja","Brak duplikatów");

}
