//******************************************************************************
#ifndef GENERATEHASH_H
#define GENERATEHASH_H
//******************************************************************************
#include <QMainWindow>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QDebug>
//******************************************************************************
#define DEFINE_MD4 0
#define DEFINE_MD5 1
#define DEFINE_SHA1 2
//******************************************************************************
namespace Ui {
class GenerateHash;
}
//******************************************************************************
class GenerateHash : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateHash(QWidget *parent = 0);
    ~GenerateHash();

    QString myGenerateHash(QString pathFileHashing);


private slots:

 void on_pushchooseFileForHash_clicked();
 void on_pushgenerate_clicked();
 void on_pushchooseFileForWriten_clicked();
 void on_pushWriten_clicked();

private:
    Ui::GenerateHash *ui;
    void myWriteHash(QString nameFileHashing, QString hashFile, QString pathFileForWrite);
    void myResult(bool type);

    QString pathFileHashing, nameFileHashing;
    QString pathFileForWrite;
    QCryptographicHash::Algorithm Algorythm;
    QString CryptoAlgorythm;
    QByteArray hashFile;
};

#endif // GENERATEHASH_H
