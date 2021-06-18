#pragma once

#include "ui_TestUtil.h"
#include "QtBatchWidgetsClass.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QLineEdit>
#include <QFont>
#include <QRect>
#include <QClipboard>
#include <QMimeData>
#include <QMessageBox>
#include <QInputDialog>
#include <QStyledItemDelegate>
#include <QCursor>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject> 
#include <QJsonDocument>
#include <QJsonArray>

#include <QLocalServer>
#include <QString>
#include <QLocalSocket>
#include <QProcess>
#include <QCloseEvent>
#include <QThreadPool>
#include <QTimer>

#include <iostream>
#include <windows.h>
#include "SqlUtil.h"
#include "printtask.h"

#include <sstream>

#pragma warning(disable : 4996)
using namespace std;






class TestUtil : public QMainWindow
{
	Q_OBJECT

public:
	TestUtil(QWidget *parent = Q_NULLPTR);
	void TestUtil::updataLabel(QString str);
	void showInputDialog();
	void initQProcess(QWidget *parent);
	void initComboBox();


	void sendMsg(QString msg);

protected:
	void closeEvent(QCloseEvent *event);


private:
	Ui::TestUtilClass ui;
	int i = 0, j = 0, h = 0;
	int Url_Type = 1;
	int Pamars_Type = 2;
	int Header_Type = 3;
	int Url_Index = 0;
	int Focus_Index = 0;
	int Pamars_Index = 0;
	int Header_Index = 0;
	int Current_State = 0;
	QList<QtContent*> urllist;
	QList<QtContent*>pamarslist;
	QList<QtContent*>headerlist;
	QLocalServer *server;
	QLocalSocket* socket;
	QProcess *myProcess;
	QProcess *adbProcess;
	QTimer* timer;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_url_clicked();
	void on_pushButton_pamars_clicked();
	void on_pushButton_header_clicked();
	void on_pushButton_copy_clicked();
	void on_pushButton_label_clicked();
	void on_pushButton_ecode_clicked();
	void on_pushButton_dcode_clicked();
	void on_pushButton_batch_clicked();
	void on_pushButton_clear_clicked();
	void on_pushButton_adb_clicked();



	// 信号声明区
signals:
	// 声明信号 mySignal()
	void mySignal(QString msg);

	// 槽声明区
public slots:
	// 声明槽函数 mySlot()
	void mySlot(QString msg);

	void mySlotUrlIndex(int x);

	void mySlotPamarsIndex(int x);

	void mySlotHeaderIndex(int x);

	void mySlotCopy(bool);

	void mySlotCopy2(bool);

	bool eventFilter(QObject *, QEvent *);    //注意这里

	void sendFortune();

	void socketReadyReadHandler();

	void deleteLater();

	void processError(QProcess::ProcessError error);

	void slot_ReplyData(QString data);

	void slot_ErrorData(QString data);

	void onSearchFinished();

};
