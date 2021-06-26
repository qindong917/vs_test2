#pragma once

#include <QWidget>
#include <QProcess>
#include <qDebug>
#include <QStandardItem>
#include <QStringListModel>

#include <QScrollBar>
#include <QString>
#include <QFileDialog>
#include <QInputDialog>
#include <QDateTime>
#include <QTimer>
#include <QPoint>
#include <QMenu>
#include <QRegExp>
#include <QTextCodec>
#include <QMessageBox>
#include <QSize>

#include <iostream>
#include <windows.h>

#pragma warning(disable : 4996)
using namespace std;

#include "ui_QtADBClass.h"

class QtADBClass : public QWidget
{
	Q_OBJECT

public:
	QtADBClass(QWidget *parent = Q_NULLPTR);
	~QtADBClass();
	void getDevices();
	QString substring(QString string, int start, int end);
	void processEvent();
	void showMessageStr(QString msg);

protected:
	void closeEvent(QCloseEvent *event);

private:

	Ui::QtADBClass ui;
	QProcess *adbProcess;

	QStringListModel *rightItemModel;
	QStandardItemModel *leftItemModel;

	QProcess *shell;
	QProcess *adb;

	QTimer *timer;

	QDialog *packagesDialog;
	QListView *packageslistview;
	QStringListModel *packagesItemModel;

public slots:
	void itemClicked(QModelIndex);
	void itemClicked_2(QModelIndex);
	void outputReady();
	void adbOutputReady();
	void TimerOut();
	void TimerOut3();
	void TimerOut2();
	void TimerOut4();
	void TimerOut5();
	void TimerOut6();

	void slotFinished(int);
	void slotadbProcessFinished(int);
	void show_contextmenu1(const QPoint& pos);
	void show_contextmenu2(const QPoint& pos);
	void edit_menu1();
	void edit_menu2();
	void edit_menu3();
	void edit_menu4();
	void edit_menu5();

private slots:
	void on_pushButton_refresh_clicked();
	void on_pushButton_refresh2_clicked();
	void on_pushButton_back_clicked();
	void on_pushButton_getlj_clicked();
	void on_pushButton_install_clicked();
	void on_pushButton_applist_clicked();
};
