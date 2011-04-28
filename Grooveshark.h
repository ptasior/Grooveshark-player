#ifndef Grooveshark_H
#define Grooveshark_H

#include <QtGui/QMainWindow>
#include <QWebView>
#include <QNetworkCookieJar>
#include <QSystemTrayIcon>
#include <QtGui/QMenu>
#include <QtGui/QAction>

class Grooveshark : public QMainWindow
{
Q_OBJECT
	public:
		Grooveshark();
		virtual ~Grooveshark();
	
	public slots:
		void play();
		void next();
		void prev();
		void close();
		void reload();
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void setProgress(int p);
		void finishLoading(bool done);

	private:
		void closeEvent(QCloseEvent *event);
		
		QSystemTrayIcon *tray;
		QWebView *view;
		QMenu *menu;
		QAction *acPlay;
		QAction *acNext;
		QAction *acPrev;
		QAction *acClose;
		QAction *acRefersh;
};

#endif // Grooveshark_H
