#include "generatehash.h"
#include "ui_generatehash.h"

GenerateHash::GenerateHash(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateHash)
{
    ui->setupUi(this);
}

GenerateHash::~GenerateHash()
{
    delete ui;
}
