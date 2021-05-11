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
QByteArray GenerateHash::myhashFunction(QString pathFile)
{
    if (QFile::exists(pathFile))
    {
        QFile fileData(pathFile);
        QFileInfo fileInfo(fileData.fileName());
        nameFile = fileInfo.fileName();
        if(fileData.open(QIODevice::ReadOnly))
        {
            QCryptographicHash objHashByte(Algorythm);
            if(objHashByte.addData(&fileData))
            {
                QString objHashString = (objHashByte.result()).toHex();
                ui->txteditresult->setPlainText(objHashString);
                hashFile = objHashByte.result();
                return hashFile;
            }
        }
        return hashFile;
    }else return 0;

}
//******************************************************************************
void GenerateHash::myhashWriteInfo(QString nameFile, QString hashFile)
{
    qDebug() << nameFile << hashFile;
}
//******************************************************************************
void GenerateHash::on_pushchooseFile_clicked()
{
    ui->PathFile->setText(QFileDialog::getOpenFileName(this));
}
//******************************************************************************
void GenerateHash::on_pushgenerate_clicked()
{
    pathFile = ui->PathFile->text();
    if (pathFile.size() < 1)
        return;
    QString curModeHash =  ui->comboBox->currentText();
    if (curModeHash == "SHA1") Algorythm = QCryptographicHash::Sha1;
    else if (curModeHash == "MD4") Algorythm = QCryptographicHash::Md4;
    else if (curModeHash == "MD5") Algorythm = QCryptographicHash::Md5;
    myhashFunction(pathFile);
    myhashWriteInfo(nameFile, hashFile);
}
//******************************************************************************
