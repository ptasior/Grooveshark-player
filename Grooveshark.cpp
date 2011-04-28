#include "Grooveshark.h"
#include <QDebug>
#include <QCloseEvent>
#include <QWebFrame>

Grooveshark::Grooveshark()
{
	resize(1000, 600);
	view = new QWebView;
	setCentralWidget(view);
	
	connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
	connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
	
	view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	view->page()->networkAccessManager()->setCookieJar( new QNetworkCookieJar() );
	view->load(QUrl("http://grooveshark.com/"));
	
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
	connect(acClose, SIGNAL(triggered()), this, SLOT(close()));
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
}

Grooveshark::~Grooveshark()
{
	
}

void Grooveshark::closeEvent(QCloseEvent* event)
{
	if (!tray->isVisible())
		return;
	hide();
	event->ignore();
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
	QWebFrame *frame = view->page()->mainFrame();
	frame->evaluateJavaScript("document.getElementById('player_play_pause').click()");
}

void Grooveshark::next()
{
	QWebFrame *frame = view->page()->mainFrame();
	frame->evaluateJavaScript("document.getElementById('player_next').click()");
}

void Grooveshark::prev()
{
	QWebFrame *frame = view->page()->mainFrame();
	frame->evaluateJavaScript("document.getElementById('player_previous').click()");
}

void Grooveshark::close()
{
	close();
}

void Grooveshark::reload()
{
	view->reload();
}

void Grooveshark::setProgress(int p)
{
	setWindowTitle(QString("Groveshark (loadnig %1%)").arg(p));
}

void Grooveshark::finishLoading(bool done)
{
	qDebug() << "loaded";
}

#include "Grooveshark.moc"
