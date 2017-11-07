#include <QApplication>
#include <QDesktopWidget>
#include <QSurfaceFormat>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.show();
	
	return app.exec();
}