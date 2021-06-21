/********************************************************************************
** Form generated from reading UI file 'QtADBClassrMVhZt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTADBCLASSRMVHZT_H
#define QTADBCLASSRMVHZT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtADBClass
{
public:
    QGridLayout *gridLayout;
    QListView *listView;
    QListView *listView_2;

    void setupUi(QWidget *QtADBClass)
    {
        if (QtADBClass->objectName().isEmpty())
            QtADBClass->setObjectName(QString::fromUtf8("QtADBClass"));
        QtADBClass->resize(800, 600);
        gridLayout = new QGridLayout(QtADBClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listView = new QListView(QtADBClass);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 0, 0, 1, 1);

        listView_2 = new QListView(QtADBClass);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));

        gridLayout->addWidget(listView_2, 0, 1, 1, 1);


        retranslateUi(QtADBClass);

        QMetaObject::connectSlotsByName(QtADBClass);
    } // setupUi

    void retranslateUi(QWidget *QtADBClass)
    {
        QtADBClass->setWindowTitle(QApplication::translate("QtADBClass", "QtADBClass", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtADBClass: public Ui_QtADBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTADBCLASSRMVHZT_H
