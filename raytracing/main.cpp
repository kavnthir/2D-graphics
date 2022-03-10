
#include "RayWidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QPainter>
#include <QCursor>
#include <QTimer>
#include <iostream>

int main(int argc, char *argv[]){

	// Create Window
	QApplication app(argc, argv);
	QDesktopWidget desktop;
	QCoreApplication::setApplicationName("Raytracing Demo");

	// Load Stylesheet
	QFile file("default.qss");
	file.open(QFile::ReadOnly);
	QString style = QLatin1String(file.readAll());
	qApp->setStyleSheet(style);

	// Init Window and Timer
	RayWidget source;
	QTimer *timer = new QTimer();
	QObject::connect(timer, SIGNAL(timeout()), &source, SLOT(updatePos()));

	// Start Window and Timer
	source.setFixedSize(desktop.width()*0.7,desktop.height()*0.7);
	source.show();
	timer->start(0);

	return app.exec();
}



