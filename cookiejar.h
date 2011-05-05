#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>

class CookieJar : public QNetworkCookieJar
{
	public:
		CookieJar(QObject* parent = 0);
		~CookieJar();
		
		void save() const;
		void read();
};

#endif // COOKIEJAR_H
