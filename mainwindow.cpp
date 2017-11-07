#include "mainwindow.h"
#include "glwidget.h"


MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(tr("PBR Render"));
	QPushButton *next = ui.pushButton_1;
	QPushButton *pre = ui.pushButton_2;
	GLWidget *glWidget = ui.openGLWidget;
	//绑定按钮点击事件
	connect(next, &QPushButton::pressed, glWidget, &GLWidget::nextCurrIndex);
	connect(pre, &QPushButton::pressed, glWidget, &GLWidget::preCurrIndex);
	//glWidget = new GLWidget;
	//setCentralWidget(glWidget);
	//setWindowTitle(tr("RenderWindow"));
	/*Ui::hellogl2Class *ui;
	ui->setupUi(this);*/
}
