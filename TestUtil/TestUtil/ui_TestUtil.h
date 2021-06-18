/********************************************************************************
** Form generated from reading UI file 'TestUtilaBTvlN.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef TESTUTILABTVLN_H
#define TESTUTILABTVLN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestUtilClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QFrame *frame;
    QGridLayout *gridLayout;
    QComboBox *comboBox_url;
    QLabel *label;
    QPushButton *pushButton_url;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_pamars;
    QLabel *label_2;
    QPushButton *pushButton_pamars;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox_header;
    QLabel *label_3;
    QPushButton *pushButton_header;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_copy;
    QPushButton *pushButton_label;
    QPushButton *pushButton_ecode;
    QPushButton *pushButton_dcode;
    QPushButton *pushButton_batch;
    QPushButton *pushButton_adb;
    QPushButton *pushButton_9;
    QPushButton *pushButton_clear;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QTextEdit *et_result;

    void setupUi(QMainWindow *TestUtilClass)
    {
        if (TestUtilClass->objectName().isEmpty())
            TestUtilClass->setObjectName(QString::fromUtf8("TestUtilClass"));
        TestUtilClass->resize(1200, 900);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/TestUtil/images/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        TestUtilClass->setWindowIcon(icon);
        centralWidget = new QWidget(TestUtilClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_url = new QComboBox(frame);
        comboBox_url->setObjectName(QString::fromUtf8("comboBox_url"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_url->sizePolicy().hasHeightForWidth());
        comboBox_url->setSizePolicy(sizePolicy1);
        comboBox_url->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        comboBox_url->setFont(font);

        gridLayout->addWidget(comboBox_url, 0, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(0, 50));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_url = new QPushButton(frame);
        pushButton_url->setObjectName(QString::fromUtf8("pushButton_url"));
        pushButton_url->setMinimumSize(QSize(50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/TestUtil/images/delete_on.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_url->setIcon(icon1);
        pushButton_url->setIconSize(QSize(30, 30));

        gridLayout->addWidget(pushButton_url, 0, 2, 1, 1);


        gridLayout_6->addWidget(frame, 0, 0, 1, 1);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_pamars = new QComboBox(frame_2);
        comboBox_pamars->setObjectName(QString::fromUtf8("comboBox_pamars"));
        sizePolicy1.setHeightForWidth(comboBox_pamars->sizePolicy().hasHeightForWidth());
        comboBox_pamars->setSizePolicy(sizePolicy1);
        comboBox_pamars->setMinimumSize(QSize(0, 50));
        comboBox_pamars->setFont(font);

        gridLayout_2->addWidget(comboBox_pamars, 0, 1, 1, 1);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(0, 50));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        pushButton_pamars = new QPushButton(frame_2);
        pushButton_pamars->setObjectName(QString::fromUtf8("pushButton_pamars"));
        pushButton_pamars->setMinimumSize(QSize(50, 50));
        pushButton_pamars->setIcon(icon1);
        pushButton_pamars->setIconSize(QSize(30, 30));

        gridLayout_2->addWidget(pushButton_pamars, 0, 2, 1, 1);


        gridLayout_6->addWidget(frame_2, 1, 0, 1, 1);

        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        comboBox_header = new QComboBox(frame_3);
        comboBox_header->setObjectName(QString::fromUtf8("comboBox_header"));
        sizePolicy1.setHeightForWidth(comboBox_header->sizePolicy().hasHeightForWidth());
        comboBox_header->setSizePolicy(sizePolicy1);
        comboBox_header->setMinimumSize(QSize(0, 50));
        comboBox_header->setFont(font);

        gridLayout_3->addWidget(comboBox_header, 0, 1, 1, 1);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(0, 50));
        label_3->setFont(font);

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        pushButton_header = new QPushButton(frame_3);
        pushButton_header->setObjectName(QString::fromUtf8("pushButton_header"));
        pushButton_header->setMinimumSize(QSize(50, 50));
        pushButton_header->setIcon(icon1);
        pushButton_header->setIconSize(QSize(30, 30));

        gridLayout_3->addWidget(pushButton_header, 0, 2, 1, 1);


        gridLayout_6->addWidget(frame_3, 2, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_copy = new QPushButton(groupBox);
        pushButton_copy->setObjectName(QString::fromUtf8("pushButton_copy"));
        pushButton_copy->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_copy, 0, 1, 1, 1);

        pushButton_label = new QPushButton(groupBox);
        pushButton_label->setObjectName(QString::fromUtf8("pushButton_label"));
        pushButton_label->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_label, 0, 2, 1, 1);

        pushButton_ecode = new QPushButton(groupBox);
        pushButton_ecode->setObjectName(QString::fromUtf8("pushButton_ecode"));
        pushButton_ecode->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_ecode, 0, 3, 1, 1);

        pushButton_dcode = new QPushButton(groupBox);
        pushButton_dcode->setObjectName(QString::fromUtf8("pushButton_dcode"));
        pushButton_dcode->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_dcode, 0, 4, 1, 1);

        pushButton_batch = new QPushButton(groupBox);
        pushButton_batch->setObjectName(QString::fromUtf8("pushButton_batch"));
        pushButton_batch->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_batch, 0, 5, 1, 1);

        pushButton_adb = new QPushButton(groupBox);
        pushButton_adb->setObjectName(QString::fromUtf8("pushButton_adb"));
        pushButton_adb->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_adb, 0, 6, 1, 1);

        pushButton_9 = new QPushButton(groupBox);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_9, 0, 7, 1, 1);

        pushButton_clear = new QPushButton(groupBox);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));
        pushButton_clear->setMinimumSize(QSize(0, 50));

        gridLayout_4->addWidget(pushButton_clear, 0, 8, 1, 1);


        gridLayout_6->addWidget(groupBox, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        et_result = new QTextEdit(groupBox_2);
        et_result->setObjectName(QString::fromUtf8("et_result"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(et_result->sizePolicy().hasHeightForWidth());
        et_result->setSizePolicy(sizePolicy3);

        gridLayout_5->addWidget(et_result, 0, 0, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 4, 0, 1, 1);

        TestUtilClass->setCentralWidget(centralWidget);

        retranslateUi(TestUtilClass);

        QMetaObject::connectSlotsByName(TestUtilClass);
    } // setupUi

    void retranslateUi(QMainWindow *TestUtilClass)
    {
        TestUtilClass->setWindowTitle(QApplication::translate("TestUtilClass", "TestUtil", nullptr));
        label->setText(QApplication::translate("TestUtilClass", "\350\257\267\346\261\202\345\234\260\345\235\200:", nullptr));
        pushButton_url->setText(QString());
        label_2->setText(QApplication::translate("TestUtilClass", "\350\257\267\346\261\202\345\217\202\346\225\260:", nullptr));
        pushButton_pamars->setText(QString());
        label_3->setText(QApplication::translate("TestUtilClass", "\350\257\267\346\261\202\345\244\264 \357\274\232", nullptr));
        pushButton_header->setText(QString());
        groupBox->setTitle(QApplication::translate("TestUtilClass", "\345\212\237\350\203\275", nullptr));
        pushButton->setText(QApplication::translate("TestUtilClass", "\345\217\221\350\265\267\350\257\267\346\261\202", nullptr));
        pushButton_copy->setText(QApplication::translate("TestUtilClass", "\345\244\215\345\210\266\346\226\207\346\234\254", nullptr));
        pushButton_label->setText(QApplication::translate("TestUtilClass", "\345\212\240\346\240\207\347\255\276", nullptr));
        pushButton_ecode->setText(QApplication::translate("TestUtilClass", "\345\212\240\345\257\206", nullptr));
        pushButton_dcode->setText(QApplication::translate("TestUtilClass", "\350\247\243\345\257\206", nullptr));
        pushButton_batch->setText(QApplication::translate("TestUtilClass", "\346\211\271\351\207\217\350\277\220\350\241\214", nullptr));
        pushButton_adb->setText(QApplication::translate("TestUtilClass", "adb", nullptr));
        pushButton_9->setText(QApplication::translate("TestUtilClass", "\345\276\205\346\211\251\345\261\225", nullptr));
        pushButton_clear->setText(QApplication::translate("TestUtilClass", "\346\270\205\347\251\272", nullptr));
        groupBox_2->setTitle(QApplication::translate("TestUtilClass", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestUtilClass: public Ui_TestUtilClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // TESTUTILABTVLN_H
