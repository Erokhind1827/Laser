/********************************************************************************
** Form generated from reading UI file 'laser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LASER_H
#define UI_LASER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_laser
{
public:

    void setupUi(QWidget *laser)
    {
        if (laser->objectName().isEmpty())
            laser->setObjectName(QString::fromUtf8("laser"));
        laser->resize(800, 600);

        retranslateUi(laser);

        QMetaObject::connectSlotsByName(laser);
    } // setupUi

    void retranslateUi(QWidget *laser)
    {
        laser->setWindowTitle(QCoreApplication::translate("laser", "laser", nullptr));
    } // retranslateUi

};

namespace Ui {
    class laser: public Ui_laser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LASER_H
