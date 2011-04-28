#include <QtGui/QApplication>
#include "Grooveshark.h"
#include <QDebug>


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	Q_INIT_RESOURCE(resources);
	Grooveshark foo;
	try
	{
		foo.show();
		return app.exec();
	}
	catch(...)
	{
		qDebug() << "crash!!!!";
	}
}
