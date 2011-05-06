#include <QtGui/QApplication>
#include <QDebug>
#include "grooveshark.h"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	Q_INIT_RESOURCE(resources);
	
	Grooveshark w;
	w.show();
	return app.exec();
}
