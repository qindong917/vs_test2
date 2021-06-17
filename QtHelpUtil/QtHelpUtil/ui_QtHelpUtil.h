/********************************************************************************
** Form generated from reading UI file 'QtHelpUtiltPrCGG.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTHELPUTILTPRCGG_H
#define QTHELPUTILTPRCGG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtHelpUtilClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *QtHelpUtilClass)
    {
        if (QtHelpUtilClass->objectName().isEmpty())
            QtHelpUtilClass->setObjectName(QString::fromUtf8("QtHelpUtilClass"));
        QtHelpUtilClass->setEnabled(false);
        QtHelpUtilClass->resize(94, 16);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QtHelpUtilClass->sizePolicy().hasHeightForWidth());
        QtHelpUtilClass->setSizePolicy(sizePolicy);
        QtHelpUtilClass->setIconSize(QSize(1, 1));
        centralWidget = new QWidget(QtHelpUtilClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtHelpUtilClass->setCentralWidget(centralWidget);

        retranslateUi(QtHelpUtilClass);

        QMetaObject::connectSlotsByName(QtHelpUtilClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtHelpUtilClass)
    {
        QtHelpUtilClass->setWindowTitle(QApplication::translate("QtHelpUtilClass", "QtHelpUtil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtHelpUtilClass: public Ui_QtHelpUtilClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTHELPUTILTPRCGG_H
