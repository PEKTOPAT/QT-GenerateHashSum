#include "generatehash.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenerateHash w;
    w.show();

    return a.exec();
}
