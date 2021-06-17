#pragma once
#include "ui_QtBatchWidgetsClass.h"
#include "batchtask.h"
#include <qDebug>
#include <QFileDialog>
#include <QTextCodec>
#include <QWidget>
#include <QThreadPool>

#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMessageBox>

#include <iostream>
#include <windows.h>


#pragma warning(disable : 4996)
using namespace std;


class QtBatchWidgetsClass : public QWidget
{
	Q_OBJECT

public:
	QtBatchWidgetsClass(QWidget *parent = Q_NULLPTR);
	~QtBatchWidgetsClass();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void on_pushButton_start_clicked();
	void on_pushButton_select_file_clicked();
	void on_pushButton_help_clicked();

public slots:
	void slot_ReplyData(QString msg, int);
	void slot_ErrorData(QString msg, int);
	void itemClicked(QModelIndex);

private:
	Ui::QtBatchWidgetsClass ui;
	QStringList *list;
	QStringList *mlist;
	QStringList *replylist;
	QThreadPool *pool;

	QStringListModel *Model;
	QStandardItemModel *ItemModel;
};
