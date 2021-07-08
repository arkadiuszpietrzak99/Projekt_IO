#include "controller.h"

controller::controller(QObject* parent): QObject(parent){};

//Funckja pobiera pliki i zapisuje je do pamięci
QStringList controller::getFiles(const QString &path)
{
    QStringList ret;
    QDir dir(path);
    if(dir.isEmpty()){
        return QStringList();
    }
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::Dirs);
    for(int i = 0; i <fileInfoList.count(); ++i){
        if(fileInfoList[i].isDir()){
            QStringList files = getFiles(fileInfoList[i].absoluteFilePath());
            ret.append(files);
        }
        else{
            ret.append(fileInfoList[i].absoluteFilePath());            
        }
    }
    return ret;
}

//Funkcja pobiera Hasz wszystkich plików
QByteArray controller::getFileMd5(const QString &path)
{
    if(path.isEmpty())
    {
        return QByteArray();
    }

    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
    QCryptographicHash hash(QCryptographicHash::Md5);

    while (!file.atEnd()) {
        QByteArray text = file.read(1024*10);
        hash.addData(text);
    }

    QByteArray fileMd5 = hash.result().toHex();
    file.close();
    return fileMd5;
    }
    return QByteArray();
}

//Odfiltrowuje pliki o tym samym rozmiarze
QStringList controller::filesOfDifferentSize(const QStringList &fileList)
{
    if(fileList.isEmpty())
    {
        return QStringList();
    }
    QStringList ret;
    QHash<qint64,QStringList> hash;
    for(int i=0;i<fileList.count();i++)
    {
        QString filePath = fileList.at(i);
        QFileInfo fileInfo(filePath);
        hash[fileInfo.size()].append(filePath);
    }
    QHash<qint64,QStringList>::iterator itr = hash.begin();
    for(itr;itr!=hash.end();itr++)
    {
        if(itr.value().count() > 1)
        {
            ret.append(itr.value());
        }
    }
    return ret;
}

//Funcja która wykrywa duplikaty po Haszu
void controller::duplicateFileDetect(const QString &path)
{
    QStringList files=getFiles(path);
    if(path.isEmpty())
    {
        return;
    }
    QHash<QByteArray,QStringList> duplicateFiles;
    QStringList filesFiltered=filesOfDifferentSize(files);

    int count= filesFiltered.count();
    if(count==0)     {         emit sendMessageBox();     }
    for(int i=0;i<count;i++)
    {
       QString filePath=filesFiltered.at(i);
       QByteArray md5=getFileMd5(filePath);
       duplicateFiles[md5].append(filePath);
       emit sendProgress(100,100);
     }

       emit sendDuplicateFile(duplicateFiles);
       emit sendProgress(100,100);
    }



