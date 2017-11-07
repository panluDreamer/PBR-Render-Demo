/********************************************************************************
** Form generated from reading UI file 'hellogl2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOGL2_H
#define UI_HELLOGL2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_hellogl2Class
{
public:
    QWidget *centralWidget;
    GLWidget *openGLWidget;
    QPushButton *pushButton_1;
    QPushButton *pushButton_2;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *hellogl2Class)
    {
        if (hellogl2Class->objectName().isEmpty())
            hellogl2Class->setObjectName(QStringLiteral("hellogl2Class"));
        hellogl2Class->resize(1083, 803);
        centralWidget = new QWidget(hellogl2Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new GLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 10, 911, 751));
        pushButton_1 = new QPushButton(centralWidget);
        pushButton_1->setObjectName(QStringLiteral("pushButton_1"));
        pushButton_1->setGeometry(QRect(970, 170, 81, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(970, 260, 81, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(980, 130, 101, 21));
        hellogl2Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(hellogl2Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1083, 23));
        hellogl2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(hellogl2Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        hellogl2Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(hellogl2Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        hellogl2Class->setStatusBar(statusBar);

        retranslateUi(hellogl2Class);

        QMetaObject::connectSlotsByName(hellogl2Class);
    } // setupUi

    void retranslateUi(QMainWindow *hellogl2Class)
    {
        hellogl2Class->setWindowTitle(QApplication::translate("hellogl2Class", "hellogl2", Q_NULLPTR));
        pushButton_1->setText(QApplication::translate("hellogl2Class", "next", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("hellogl2Class", "pre", Q_NULLPTR));
        label->setText(QApplication::translate("hellogl2Class", "\345\210\207\346\215\242\344\270\215\345\220\214\346\235\220\350\264\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class hellogl2Class: public Ui_hellogl2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOGL2_H
