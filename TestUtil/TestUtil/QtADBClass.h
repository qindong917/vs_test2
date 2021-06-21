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
#include "ui_QtADBClass.h"

class QtADBClass : public QWidget
{
	Q_OBJECT

public:
	QtADBClass(QWidget *parent = Q_NULLPTR);
	~QtADBClass();
	void getDevices();
	QString substring(QString string, int start, int end);

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::QtADBClass ui;
	QProcess *adbProcess;
	QStringListModel *Model;
	QStandardItemModel *ItemModel;

	QProcess *shell;
	QProcess *adb;
	QString currentDevice;
	QStringListModel *model;
	QStringList List;
	bool gettingDir;

public slots:
	void itemClicked(QModelIndex);
	void outputReady();
	void adbOutputReady();
	void slotFinished(int);
};
