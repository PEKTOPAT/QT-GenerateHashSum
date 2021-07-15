//******************************************************************************
#include "generatehash.h"
#include "ui_generatehash.h"
//******************************************************************************
GenerateHash::GenerateHash(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateHash)
{
    ui->setupUi(this);
}
//******************************************************************************
GenerateHash::~GenerateHash()
{
    delete ui;
}
//*************************************************************************************************
//Хеширование**********************************************************
//*************************************************************************************************
QString GenerateHash::myGenerateHash(QString pathFileHashing)
{
    if (QFile::exists(pathFileHashing))
    {
        QFile fileData(pathFileHashing);
        QFileInfo fileInfo(fileData.fileName());
        nameFileHashing = fileInfo.fileName();
        if(fileData.open(QIODevice::ReadOnly))
        {
            QCryptographicHash objHashByte(Algorythm);
            if(objHashByte.addData(&fileData))
            {
                hashFile = (objHashByte.result()).toHex();
                ui->txteditresult->setPlainText(hashFile);
                ui->lblInfo->setText("");
                return hashFile;
            }
        }
        return hashFile;
    }else return 0;

}
//*************************************************************************************************
//Запись в файл (имя - метод хеширования - хеш) ***************************************************
//*************************************************************************************************
void GenerateHash::myWriteHash(QString nameFileHashing, QString hashFile, QString pathFileForWrite)
{
    qDebug() << nameFileHashing << hashFile << pathFileForWrite;
        QFile FileForWrite(pathFileForWrite);
        QFileInfo fileinfo(pathFileForWrite);
        QString newPathFileForWrite = fileinfo.path() + "/" + fileinfo.completeBaseName() + ".conf";
        QFile::rename(pathFileForWrite, newPathFileForWrite);
        qDebug() << pathFileForWrite;
        if (FileForWrite.open(QIODevice::ReadWrite))
        {
            QTextStream streamFileForWrite(&FileForWrite);
            if (streamFileForWrite.readAll() == 0)
            streamFileForWrite << pathFileHashing << ";" << nameFileHashing << ";" << CryptoAlgorythm << ";" << hashFile;
            else streamFileForWrite << "\n" << pathFileHashing << ";" << nameFileHashing << ";" << CryptoAlgorythm << ";"  << hashFile;
            FileForWrite.close();

//            QFile::rename(pathFileForWrite, )
            myResult(true);
        }else myResult(false);
}
//******************************************************************************
//Вывод информации результата записи на ui *************************************
//******************************************************************************
void GenerateHash::myResult(bool type)
{
    if (type)
    {
        ui->lblInfo->setText("Успешно!");
        ui->lblInfo->setStyleSheet("color: rgb(0, 255, 0)");
    }else
    {
        ui->lblInfo->setText("Ошибка!");
        ui->lblInfo->setStyleSheet("color: rgb(255, 0, 0)");
    }
}

//*******\/**
//SLOT***||**
//*******\/**

//Выбор файла для хеширования, заполнение TextEdit *****************************
void GenerateHash::on_pushchooseFileForHash_clicked()
{
    ui->PathFile->setText(QFileDialog::getOpenFileName(this));
}
//Хеширование согласно установленному алгоритму ********************************
void GenerateHash::on_pushgenerate_clicked()
{
    pathFileHashing = ui->PathFile->text();
    if (pathFileHashing.size() < 1)
        return;
    QString curModeHash =  ui->comboBox->currentText();
    if (curModeHash == "SHA1") {Algorythm = QCryptographicHash::Sha1; CryptoAlgorythm = "Sha1";}
    else if (curModeHash == "MD4") {Algorythm = QCryptographicHash::Md4; CryptoAlgorythm = "Md4";}
    else if (curModeHash == "MD5") {Algorythm = QCryptographicHash::Md5; CryptoAlgorythm = "Md5";}
    myGenerateHash(pathFileHashing);

}
//Выбор файла для записи хеша, заполнение TextEdit *****************************
void GenerateHash::on_pushchooseFileForWriten_clicked()
{
    ui->PathFileFORwriten->setText(QFileDialog::getOpenFileName(this));
}
//Запись данных хеша и информации о файле в файл *******************************
void GenerateHash::on_pushWriten_clicked()
{
    pathFileForWrite = ui->PathFileFORwriten->text();
    if (pathFileHashing.size() == 0 || hashFile.size() == 0 || pathFileForWrite.size() < 1)
    {
        myResult(false);
        return;

    }
    myWriteHash(nameFileHashing, hashFile, pathFileForWrite);
}
