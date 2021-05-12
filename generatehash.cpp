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
//******************************************************************************
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
                return hashFile;
            }
        }
        return hashFile;
    }else return 0;

}
//******************************************************************************
void GenerateHash::myWriteHash(QString nameFileHashing, QString hashFile, QString pathFileForWrite)
{
    qDebug() << nameFileHashing << hashFile << pathFileForWrite;
        QFile FileForWrite(pathFileForWrite);
        if (FileForWrite.open(QIODevice::ReadWrite))
        {
            QTextStream streamFileForWrite(&FileForWrite);
            if (streamFileForWrite.readAll() == 0)
            streamFileForWrite << nameFileHashing << ";" << hashFile;
            else streamFileForWrite << "\n" << nameFileHashing << ";" << hashFile;
            FileForWrite.close();
            myResult(true);
        }else myResult(false);
}
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

//******************************************************************************
//SLOT**************************************************************************
//******************************************************************************
void GenerateHash::on_pushchooseFileForHash_clicked()
{
    ui->PathFile->setText(QFileDialog::getOpenFileName(this));
}
//******************************************************************************
void GenerateHash::on_pushgenerate_clicked()
{
    pathFileHashing = ui->PathFile->text();
    if (pathFileHashing.size() < 1)
        return;
    QString curModeHash =  ui->comboBox->currentText();
    if (curModeHash == "SHA1") Algorythm = QCryptographicHash::Sha1;
    else if (curModeHash == "MD4") Algorythm = QCryptographicHash::Md4;
    else if (curModeHash == "MD5") Algorythm = QCryptographicHash::Md5;
    myGenerateHash(pathFileHashing);

}
//******************************************************************************
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
//******************************************************************************
void GenerateHash::on_pushchooseFileForWriten_clicked()
{
    ui->PathFileFORwriten->setText(QFileDialog::getOpenFileName(this));
}
//******************************************************************************
