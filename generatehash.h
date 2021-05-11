#ifndef GENERATEHASH_H
#define GENERATEHASH_H

#include <QMainWindow>

namespace Ui {
class GenerateHash;
}

class GenerateHash : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateHash(QWidget *parent = 0);
    ~GenerateHash();

private:
    Ui::GenerateHash *ui;
};

#endif // GENERATEHASH_H
