//******************************************************************************
#ifndef GENERATEHASH_H
#define GENERATEHASH_H
//******************************************************************************
#include <QMainWindow>
#include <QFileDialog>
#include <QCryptographicHash>
#include <QDebug>
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

    QByteArray myhashFunction(QString pathFile);
    void myhashWriteInfo(QString nameFile, QString hashFile);

private slots:

    void on_pushchooseFile_clicked();
    void on_pushgenerate_clicked();

private:
    Ui::GenerateHash *ui;
    QString pathFile, nameFile;
    QCryptographicHash::Algorithm Algorythm;
    QByteArray hashFile;
};

#endif // GENERATEHASH_H
