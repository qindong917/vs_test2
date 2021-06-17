/********************************************************************************
** Form generated from reading UI file 'QtBatchWidgetsClassyQLhMe.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QTBATCHWIDGETSCLASSYQLHME_H
#define QTBATCHWIDGETSCLASSYQLHME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtBatchWidgetsClass
{
public:
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit_time;
    QPushButton *pushButton_start;
    QPushButton *pushButton_help;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_select_file;
    QLineEdit *lineEdit_file_path;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_4;
    QListView *listView;

    void setupUi(QWidget *QtBatchWidgetsClass)
    {
        if (QtBatchWidgetsClass->objectName().isEmpty())
            QtBatchWidgetsClass->setObjectName(QString::fromUtf8("QtBatchWidgetsClass"));
        QtBatchWidgetsClass->resize(650, 740);
        gridLayout_5 = new QGridLayout(QtBatchWidgetsClass);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(QtBatchWidgetsClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        groupBox->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_time = new QLineEdit(frame);
        lineEdit_time->setObjectName(QString::fromUtf8("lineEdit_time"));
        lineEdit_time->setMinimumSize(QSize(100, 50));
        lineEdit_time->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_time, 0, 1, 1, 1);

        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(pushButton_start, 0, 2, 1, 1);

        pushButton_help = new QPushButton(frame);
        pushButton_help->setObjectName(QString::fromUtf8("pushButton_help"));
        pushButton_help->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(pushButton_help, 0, 3, 1, 1);


        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_select_file = new QPushButton(frame_2);
        pushButton_select_file->setObjectName(QString::fromUtf8("pushButton_select_file"));
        pushButton_select_file->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(pushButton_select_file, 0, 2, 1, 1);

        lineEdit_file_path = new QLineEdit(frame_2);
        lineEdit_file_path->setObjectName(QString::fromUtf8("lineEdit_file_path"));
        lineEdit_file_path->setMinimumSize(QSize(100, 50));
        lineEdit_file_path->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(lineEdit_file_path, 0, 1, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 50));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame_2, 1, 0, 1, 1);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(QtBatchWidgetsClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        listView = new QListView(groupBox_2);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout_4->addWidget(listView, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 1, 0, 1, 1);


        retranslateUi(QtBatchWidgetsClass);

        QMetaObject::connectSlotsByName(QtBatchWidgetsClass);
    } // setupUi

    void retranslateUi(QWidget *QtBatchWidgetsClass)
    {
        QtBatchWidgetsClass->setWindowTitle(QApplication::translate("QtBatchWidgetsClass", "QtBatchWidgetsClass", nullptr));
        groupBox->setTitle(QApplication::translate("QtBatchWidgetsClass", "\350\256\276\347\275\256", nullptr));
        label->setText(QApplication::translate("QtBatchWidgetsClass", "\344\273\273\345\212\241\351\227\264\351\232\224\357\274\232", nullptr));
        lineEdit_time->setText(QApplication::translate("QtBatchWidgetsClass", "0", nullptr));
        pushButton_start->setText(QApplication::translate("QtBatchWidgetsClass", "\345\274\200\345\247\213\344\273\273\345\212\241", nullptr));
        pushButton_help->setText(QApplication::translate("QtBatchWidgetsClass", "\344\275\277\347\224\250\346\226\271\345\274\217", nullptr));
        pushButton_select_file->setText(QApplication::translate("QtBatchWidgetsClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        lineEdit_file_path->setText(QString());
        label_3->setText(QApplication::translate("QtBatchWidgetsClass", "\350\257\273\345\217\226\346\226\207\344\273\266\357\274\232", nullptr));
        groupBox_2->setTitle(QApplication::translate("QtBatchWidgetsClass", "\350\204\232\346\234\254\346\272\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtBatchWidgetsClass: public Ui_QtBatchWidgetsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QTBATCHWIDGETSCLASSYQLHME_H
