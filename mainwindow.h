#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ui_hellogl2.h"
//class GLWidget;
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	//GLWidget *glWidget;
private:
	Ui::hellogl2Class ui;
};

#endif