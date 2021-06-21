/********************************************************************************
** Form generated from reading UI file 'QtADBClasspiwxnF.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTADBCLASSPIWXNF_H
#define QTADBCLASSPIWXNF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtADBClass
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QListView *listView;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_refresh;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QListView *listView_2;

    void setupUi(QWidget *QtADBClass)
    {
        if (QtADBClass->objectName().isEmpty())
            QtADBClass->setObjectName(QString::fromUtf8("QtADBClass"));
        QtADBClass->resize(600, 800);
        gridLayout_3 = new QGridLayout(QtADBClass);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(QtADBClass);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listView = new QListView(groupBox);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setFont(font);
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        pushButton_refresh = new QPushButton(groupBox_3);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));

        gridLayout_5->addWidget(pushButton_refresh, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_3, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(QtADBClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        listView_2 = new QListView(groupBox_2);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));

        gridLayout_2->addWidget(listView_2, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 1, 1, 1);


        retranslateUi(QtADBClass);

        QMetaObject::connectSlotsByName(QtADBClass);
    } // setupUi

    void retranslateUi(QWidget *QtADBClass)
    {
        QtADBClass->setWindowTitle(QApplication::translate("QtADBClass", "QtADBClass", nullptr));
        groupBox->setTitle(QApplication::translate("QtADBClass", "\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        groupBox_3->setTitle(QApplication::translate("QtADBClass", "\345\212\237\350\203\275", nullptr));
        pushButton_refresh->setText(QApplication::translate("QtADBClass", "\345\210\267\346\226\260\350\256\276\345\244\207\345\210\227\350\241\250", nullptr));
        groupBox_2->setTitle(QApplication::translate("QtADBClass", "\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtADBClass: public Ui_QtADBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTADBCLASSPIWXNF_H
