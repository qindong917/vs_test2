#pragma once

#include <QtWidgets/QMainWindow>
#include <qDebug>
#include <QTextCodec>
#include <QLocalSocket>
#include "ui_QtHelpUtil.h"


#include <iostream>
#include <windows.h>

#using "./Helpers.dll"
#using "./ICSharpCode.SharpZipLib.dll"
#include <msclr\marshal_cppstd.h>
#include <sstream>

#pragma warning(disable : 4996)

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace std;
using namespace msclr::interop;
using namespace Helpers;

class QtHelpUtil : public QMainWindow
{
    Q_OBJECT

public:
    QtHelpUtil(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtHelpUtilClass ui;

public:
	QLocalSocket *socket;

public:
	void initCliect();
	void sendMsg(QString msg);
	
	
public slots:

	QString zipAndEcode(QString msg);
	QString dcodeAndUnzip(QString msg);

	unsigned char * zipAndEcode(unsigned char * request, int nStrLen);
	unsigned char * dcodeAndUnzip(unsigned char * request, int nStrLen);

	void readFortune();
	void displayError(QLocalSocket::LocalSocketError socketError);

};
