#include "cookiejar.h"
#include <QFile>
#include <QDebug>
#include <QDateTime>

CookieJar::CookieJar(QObject* parent):
	QNetworkCookieJar(parent)
{
}

CookieJar::~CookieJar()
{
}

void CookieJar::save() const
{
// 	qDebug() << "save cookies";
	
	QFile f("./cookies.dat");
	if (!f.open(QIODevice::ReadWrite | QIODevice::Text))
         return;
	
	QList<QNetworkCookie> l = allCookies();
	
	QMap<QByteArray, QByteArray> unique;
	foreach(QNetworkCookie c, l)
		if(!c.name().isEmpty() && !c.value().isEmpty())
			f.write(c.toRawForm()+"\n");
}

void CookieJar::read()
{
// 	qDebug() << "read cookies";
	
	QFile f("./cookies.dat");
	if(!f.exists())
		return;
	if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
		return;
	
	QList<QNetworkCookie> list;
	
	while (!f.atEnd())
	{
		QList<QByteArray> spl = f.readLine().split(';');
		QList<QByteArray> cookie = spl[0].split('=');

		if(cookie.length() < 2 || cookie[0].isEmpty() || cookie[1].isEmpty())
			continue;
		
		QMap<QByteArray, QByteArray> add;
		for(int cnt = 1; spl.length() > cnt; cnt++)
		{
			QList<QByteArray> t = spl[cnt].split('=');
			add[t[0].trimmed()] = t[1].trimmed();
		}
		
// 		qDebug() << "k: " << cookie[0] << " v: " << cookie[1];
// 		qDebug() << "path: " <<  add["path"]<< " domain: " << add["domain"]<< " exp: " << add["expires"];
		QNetworkCookie c;
		c.setName(cookie[0]);
		c.setValue(cookie[1]);
		c.setPath(add["path"]);
		c.setDomain(add["domain"]);
		c.setExpirationDate(QDateTime::fromString(add["expires"]));
		list.append(c);
	}
	setAllCookies(list);
}
