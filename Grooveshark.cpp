#include "Grooveshark.h"
#include <QDebug>
#include <QCloseEvent>
#include <QWebFrame>
#include "cookiejar.h"

Grooveshark::Grooveshark()
{
	resize(1000, 600);
	view = new QWebView;
	setCentralWidget(view);
	
	connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
	connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
	
	cookieJar = new CookieJar();
	cookieJar->read();
	view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	view->page()->networkAccessManager()->setCookieJar(cookieJar);
	
	tray = new QSystemTrayIcon;
	menu = new QMenu;
	
	acPlay = new QAction(/*QIcon(":/favicon.png"),*/ "Play/Pause", tray);
	acNext = new QAction(/*QIcon(":/favicon.png"),*/ "Next", tray);
	acPrev = new QAction(/*QIcon(":/favicon.png"),*/ "Previous", tray);
	acClose = new QAction(/*QIcon(":/favicon.png"),*/ "Close", tray);
	acRefersh = new QAction(/*QIcon(":/favicon.png"),*/ "Refresh", tray);
	
	connect(acPlay, SIGNAL(triggered()), this, SLOT(play()));
	connect(acNext, SIGNAL(triggered()), this, SLOT(next()));
	connect(acPrev, SIGNAL(triggered()), this, SLOT(prev()));
	connect(acClose, SIGNAL(triggered()), this, SLOT(closeAct()));
	connect(acRefersh, SIGNAL(triggered()), this, SLOT(reload()));

	menu->addAction(acPlay);
	menu->addAction(acNext);
	menu->addAction(acPrev);
	menu->addAction(acRefersh);
	menu->addAction(acClose);

	connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	tray->setContextMenu(menu);
	tray->setIcon(QIcon(":/favicon.png"));
	tray->show();
	
	// Has to be executed after initialisation of actions
// 	view->load(QUrl("./cookie.html"));
	view->load(QUrl("http://grooveshark.com/"));
	
	frame = NULL;
}

Grooveshark::~Grooveshark()
{
	cookieJar->save();
	view->close();
}

void Grooveshark::closeEvent(QCloseEvent* event)
{
	if (tray->isVisible())
	{
		hide();
		event->ignore();
	}
}

void Grooveshark::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
		case QSystemTrayIcon::DoubleClick:
		case QSystemTrayIcon::Trigger:
		case QSystemTrayIcon::MiddleClick:
			if(isVisible())
				hide();
			else
				show(); break;
		default: break;
	}
}

void Grooveshark::play()
{
	if(frame)
		frame->evaluateJavaScript("document.getElementById('player_play_pause').click()");
}

void Grooveshark::next()
{
	view->load(QUrl("./cookie.html"));
// 	if(frame)
// 		frame->evaluateJavaScript("document.getElementById('player_next').click()");
}

void Grooveshark::prev()
{
	if(frame)
		frame->evaluateJavaScript("document.getElementById('player_previous').click()");
}

void Grooveshark::closeAct()
{
	tray->hide();
	close();
}

void Grooveshark::reload()
{
	view->reload();
}

void Grooveshark::setProgress(int p)
{
	setWindowTitle(QString("Groveshark (loadnig %1%)").arg(p));
	frame = NULL;
	acPlay->setDisabled(true);
	acNext->setDisabled(true);
	acPrev->setDisabled(true);
}

void Grooveshark::finishLoading(bool done)
{
	setWindowTitle("Groveshark");
	frame = view->page()->mainFrame();
	acPlay->setDisabled(false);
	acNext->setDisabled(false);
	acPrev->setDisabled(false);

	// Advertisment removing
	if(!frame)
		return;
	frame->evaluateJavaScript("var e = document.getElementById('capital');"
							"e.parentNode.removeChild(e);"
							"setTimeout(\"document.getElementById('application').style.marginRight = '0'\",50);");
}

#include "Grooveshark.moc"
