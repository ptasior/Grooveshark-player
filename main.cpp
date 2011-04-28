#include <QtGui/QApplication>
#include "Grooveshark.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Grooveshark foo;
    foo.show();
    return app.exec();
}
