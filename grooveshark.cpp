#include <QDebug>
#include <QCloseEvent>
#include <QWebFrame>
#include <QLabel>
#include "grooveshark.h"
#include "cookiejar.h"

Grooveshark::Grooveshark(QWidget* parent, Qt::WindowFlags flags):
	QMainWindow(parent, flags)
{
	resize(1000, 600);
	view = new QWebView;
	QLabel *l = new QLabel("Loading, wait...");
	l->setAlignment(Qt::AlignCenter);
	setCentralWidget(l);
	
	connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
	connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));
	
	cookieJar = new CookieJar();
	cookieJar->read();
	view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
	view->page()->networkAccessManager()->setCookieJar(cookieJar);
	
	tray = new QSystemTrayIcon;
	menu = new QMenu;
	
	acPlay = new QAction(QIcon(":/play.png"), "Play", tray);
	acNext = new QAction(QIcon(":/next.png"), "Next", tray);
	acPrev = new QAction(QIcon(":/prev.png"), "Previous", tray);
	acClose = new QAction(QIcon(":/close.png"), "Close", tray);
	acRefersh = new QAction(QIcon(":/refresh.png"), "Refresh", tray);
	
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
	tray->setIcon(QIcon(":/icon.png"));
	tray->show();
	
	// Has to be executed after initialisation of actions
	view->load(QUrl("http://grooveshark.com/"));
	
	frame = NULL;
	
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer->start(1000);
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
// 	view->load(QUrl("./cookie.html"));
	if(frame)
		frame->evaluateJavaScript("document.getElementById('player_next').click()");
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
	setCentralWidget(view);
	setWindowTitle("Groveshark");
	frame = view->page()->mainFrame();

	// Advertisment removing
	if(!frame)
		return;
	frame->evaluateJavaScript("var e = document.getElementById('capital');"
							"e.parentNode.removeChild(e);");
}

void Grooveshark::onTimer()
{
	if(!frame)
		return;
	
	QString txt = frame->evaluateJavaScript("document.getElementById('player_play_pause').className").toString();
	txt = txt.right(txt.length()-15);
	if(txt.isEmpty())
		return;
	
	if(txt == "disabled" || txt == "buffering")
	{
		acPlay->setEnabled(false);
		acNext->setEnabled(false);
		acPrev->setEnabled(false);
	}
	else
	{
		acPlay->setEnabled(true);
		acNext->setEnabled(true);
		acPrev->setEnabled(true);
		if(txt == "play")
		{
			acPlay->setText("Play");
			acPlay->setIcon(QIcon(":/play.png"));
		}
		if(txt == "pause")
		{
			acPlay->setText("Pause");
			acPlay->setIcon(QIcon(":/pause.png"));
		}
	}
// 	player_play_pause class play pause
}
