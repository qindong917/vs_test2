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

public slots:
	void itemClicked(QModelIndex);
	void itemClicked_2(QModelIndex);
	void outputReady();
	void adbOutputReady();
	void TimerOut();
	void TimerOut2();
	void slotFinished(int);
	void slotadbProcessFinished(int);
	void show_contextmenu1(const QPoint& pos);
	void edit_menu1();
	void edit_menu2();
	void edit_menu3();

private slots:
	void on_pushButton_refresh_clicked();
	void on_pushButton_refresh2_clicked();
	void on_pushButton_back_clicked();
};
