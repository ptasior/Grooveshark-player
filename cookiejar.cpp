#include "cookiejar.h"
#include <QFile>
#include <QDebug>

CookieJar::CookieJar(QObject* parent):
	QNetworkCookieJar(parent)
{
}

CookieJar::~CookieJar()
{
}

void CookieJar::save() const
{
	qDebug() << "save cookies";
	
	QFile f("./cookies.dat");
	if (!f.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
	
	QList<QNetworkCookie> l = allCookies();
	foreach(QNetworkCookie c, l)
	{
		f.write(c.name()+"\n");
		f.write(c.value()+"\n");
	}
}

void CookieJar::read()
{
	qDebug() << "read cookies";
	
	QFile f("./cookies.dat");
	if(!f.exists())
		return;
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QList<QNetworkCookie> l;

	while (!f.atEnd())
	{
		QNetworkCookie c;
		c.setName(f.readLine());
		c.setValue(f.readLine());
		l.append(c);
	}
	setAllCookies(l);
}
