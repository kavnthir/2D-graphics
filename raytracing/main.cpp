
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QFile>
#include <QPainter>

int main(int argc, char *argv[]){

	// Create Window
	QApplication app(argc, argv);
	QDesktopWidget desktop;
	QCoreApplication::setApplicationName("Raytracing Demo");
	QMainWindow* window = new QMainWindow;

	// Load Stylesheet
	QFile file("default.qss");
	file.open(QFile::ReadOnly);
	QString style = QLatin1String(file.readAll());
	qApp->setStyleSheet(style);

	// Set Window Visibility
	window->setFixedSize(desktop.width()*0.7,desktop.height()*0.7);
	window->setVisible(true);
	app.exec();
}

