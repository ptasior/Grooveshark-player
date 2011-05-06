#ifndef GROOVESHARK_H
#define GROOVESHARK_H

#include <QtGui/QMainWindow>
#include <QWebView>
#include <QSystemTrayIcon>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include "cookiejar.h"
#include <QTimer>

class Grooveshark : public QMainWindow
{
Q_OBJECT
	public:
		Grooveshark(QWidget* parent = 0, Qt::WindowFlags flags = 0);
		virtual ~Grooveshark();
	
	public slots:
		void play();
		void next();
		void prev();
		void closeAct();
		void reload();
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void setProgress(int p);
		void finishLoading(bool done);
		void onTimer();

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
		QWebFrame *frame;
		CookieJar *cookieJar;
		QTimer *timer;
};

#endif // GROOVESHARK_H
