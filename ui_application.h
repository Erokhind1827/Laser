/********************************************************************************
** Form generated from reading UI file 'application.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_application
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *application)
    {
        if (application->objectName().isEmpty())
            application->setObjectName(QString::fromUtf8("application"));
        application->resize(800, 600);
        centralwidget = new QWidget(application);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        application->setCentralWidget(centralwidget);
        menubar = new QMenuBar(application);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        application->setMenuBar(menubar);
        statusbar = new QStatusBar(application);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        application->setStatusBar(statusbar);

        retranslateUi(application);

        QMetaObject::connectSlotsByName(application);
    } // setupUi

    void retranslateUi(QMainWindow *application)
    {
        application->setWindowTitle(QCoreApplication::translate("application", "application", nullptr));
    } // retranslateUi

};

namespace Ui {
    class application: public Ui_application {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
