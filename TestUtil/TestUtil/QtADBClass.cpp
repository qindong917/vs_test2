#include "QtADBClass.h"

QStringList leftList;
QStringList rightList;
QStringList packagesList;
QString command;
QString device;

QtADBClass::QtADBClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	

	rightItemModel = new QStringListModel(this);

	leftItemModel = new QStandardItemModel(this);

	adbProcess = new QProcess();

	connect(adbProcess, SIGNAL(finished(int)), this, SLOT(slotadbProcessFinished(int))); //或者

	shell = new QProcess();

	connect(shell, SIGNAL(finished(int)), this, SLOT(slotFinished(int))); //或者

	getDevices();

	//connect(ui.listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
	connect(ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));

	//connect(ui.listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemClicked_2(QModelIndex)));
	connect(ui.listView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked_2(QModelIndex)));

	ui.listView_2->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.listView_2, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(show_contextmenu1(const QPoint&)));

	packagesDialog = new QDialog(this);
	packageslistview = new QListView(packagesDialog);
	packagesItemModel = new QStringListModel(this);
	packagesDialog->resize(QSize(800, 800));
	packageslistview->resize(QSize(800, 800));
	packageslistview->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(packageslistview, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(show_contextmenu2(const QPoint&)));
	
}

QtADBClass::~QtADBClass()
{

}

QModelIndex currentIndex;
void QtADBClass::show_contextmenu1(const QPoint& pos)
{
	// if(cmenu)//保证同时只存在一个menu，及时释放内存
	// {
	// delete cmenu;
	// cmenu = NULL;
	// }
	currentIndex = ui.listView_2->indexAt(pos);
	qDebug() << "show_contextmenu1";
	QMenu *cmenu = new QMenu(ui.listView_2);
	QAction *down = cmenu->addAction(QString::fromLocal8Bit("下载"));
	QAction *del = cmenu->addAction(QString::fromLocal8Bit("删除"));
	QAction *update = cmenu->addAction(QString::fromLocal8Bit("上传"));
;
	connect(down, SIGNAL(triggered(bool)), this, SLOT(edit_menu1()));
	connect(del, SIGNAL(triggered(bool)), this, SLOT(edit_menu2()));
	connect(update, SIGNAL(triggered(bool)), this, SLOT(edit_menu3()));
	cmenu->exec(QCursor::pos());//在当前鼠标位置显示
	//cmenu->exec(pos)是在viewport显示

}
void QtADBClass::show_contextmenu2(const QPoint& pos)
{
	// if(cmenu)//保证同时只存在一个menu，及时释放内存
	// {
	// delete cmenu;
	// cmenu = NULL;
	// }
	currentIndex = packageslistview->indexAt(pos);
	qDebug() << "show_contextmenu1";
	QMenu *cmenu = new QMenu(ui.listView_2);
	QAction *unins = cmenu->addAction(QString::fromLocal8Bit("卸载"));
	QAction *dcapk = cmenu->addAction(QString::fromLocal8Bit("导出apk"));
	
	connect(unins, SIGNAL(triggered(bool)), this, SLOT(edit_menu4()));
	connect(dcapk, SIGNAL(triggered(bool)), this, SLOT(edit_menu5()));
	
	cmenu->exec(QCursor::pos());//在当前鼠标位置显示
	//cmenu->exec(pos)是在viewport显示

}


void QtADBClass::edit_menu1()
{

	qDebug() << "down:"<< currentIndex.row()<<"->"<<currentIndex.data();

	//子窗口和主窗口用法不同
	QFileDialog *fd = new QFileDialog(this, Qt::SubWindow);

	fd->setOption(QFileDialog::DontUseNativeDialog, true);

	QString PCfileName = fd->getExistingDirectory(0, "Save File", "D:\\", QFileDialog::DontUseNativeDialog);

	PCfileName = PCfileName.append("/").append(currentIndex.data().toString().trimmed());

	PCfileName = PCfileName.replace(QRegExp("//"), "/");

	PCfileName = PCfileName.replace(QRegExp("/"), "\\");

	qDebug() << "PCfileName: " << PCfileName;

	QString PhonefilePath(ui.label_lujing->text().trimmed());

	PhonefilePath = PhonefilePath.append("/").append(currentIndex.data().toString().trimmed());

	qDebug() << "PhonefilePath: " << PhonefilePath;

	adb = new QProcess();

	QString adbCommand = QString(".\\platform-tools\\adb.exe -s %1 pull %2 %3").arg(device, PhonefilePath, PCfileName);

	ui.textEdit_ml->append(adbCommand);

	qDebug() << "program is: " << adbCommand;

	adb->start(adbCommand);

	processEvent();

	QByteArray output = adb->readAllStandardOutput();

	ui.textEdit_jg->append(output);

	qDebug() << "pull is: " << output;

	showMessageStr(PCfileName);

}

void QtADBClass::edit_menu2()
{
	qDebug() << "del" << currentIndex.row() << "->" << currentIndex.data();

	QString PhonefilePath(ui.label_lujing->text().trimmed());

	PhonefilePath = PhonefilePath.append("/").append(currentIndex.data().toString().trimmed());

	qDebug() << "PhonefilePath: " << PhonefilePath;

	command = QString("rm -r %1\n").arg(PhonefilePath);;

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	QByteArray outputData = shell->readAllStandardOutput();

	ui.textEdit_jg->append(outputData);


	on_pushButton_refresh2_clicked();
}

void QtADBClass::edit_menu3()
{
	qDebug() << "update" << currentIndex.row() << "->" << currentIndex.data();

	//子窗口和主窗口用法不同
	QFileDialog *fd = new QFileDialog(this, Qt::SubWindow);

	fd->setOption(QFileDialog::DontUseNativeDialog, true);

	QString PCfileName = fd->getOpenFileName(0, "Select File", "D:\\", "Files (*.* *)", NULL, QFileDialog::DontUseNativeDialog);

	PCfileName = PCfileName.replace(QRegExp("//"), "/");

	PCfileName = PCfileName.replace(QRegExp("/"), "\\");

	qDebug() << "PCfileName: " << PCfileName;

	QString PhonefilePath(ui.label_lujing->text().trimmed());

	PhonefilePath = PhonefilePath.append("/");

	qDebug() << "PhonefilePath: " << PhonefilePath;

	adb = new QProcess();

	QString adbCommand = QString(".\\platform-tools\\adb.exe -s %1 push %2 %3").arg(device, PCfileName, PhonefilePath);

	ui.textEdit_ml->append(adbCommand);

	qDebug() << "program is: " << adbCommand;

	adb->start(adbCommand);

	processEvent();

	QByteArray output = adb->readAllStandardOutput();

	ui.textEdit_jg->append(output);

	qDebug() << "push is: " << output;

	on_pushButton_refresh2_clicked();
}

void QtADBClass::edit_menu4()
{
	QString packagesname;

	packagesname = packagesname.append(currentIndex.data().toString().trimmed());


	adb = new QProcess();

	QString adbCommand = QString(".\\platform-tools\\adb.exe -s %1 uninstall %2").arg(device, packagesname);

	ui.textEdit_ml->append(adbCommand);

	qDebug() << "program is: " << adbCommand;

	adb->start(adbCommand);

	processEvent();

	QByteArray output = adb->readAllStandardOutput();

	ui.textEdit_jg->append(output);

	qDebug() << "push is: " << output;

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut7()));

	timer->start(2000);
	
}

void QtADBClass::TimerOut7()
{
	timer->stop();

	on_pushButton_applist_clicked();

}

void QtADBClass::edit_menu5()
{

}

void QtADBClass::closeEvent(QCloseEvent *event)
{
	qDebug() << "close windows";

	QString c = "taskkill /im adb.exe /f";
	int pInt = QProcess::execute(c);    //关闭后台notepad.exe进程，阻塞式运行,一直占用cpu,成功返回0，失败返回1

}

QString QtADBClass::substring(QString string, int start, int end)
{
	return string.mid(start, end - start);
}

void QtADBClass::getDevices()
{
	if (shell->state() == QProcess::Running)
	{
		shell->write("exit\n");
		processEvent();
	}

	ui.textEdit_ml->setText("");
	ui.textEdit_jg->setText("");

	//windows一定要用\\，真TM的坑
	command = ".\\platform-tools\\adb.exe devices";
	
	
	adbProcess->start(command);

	adbProcess->waitForReadyRead();

	ui.textEdit_ml->append(command);

	QStringList outputData;

	QByteArray output = adbProcess->readAllStandardOutput();

	ui.textEdit_jg->append(output);

	qDebug() << "output is: " << output;

	leftList.clear();

	leftItemModel->removeRows(0, leftItemModel->rowCount());

	rightList.clear();

	rightItemModel->removeRows(0, rightItemModel->rowCount());

	int lastItem = 0;
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i] == '\n' || output[i] == '\t')
		{
			outputData << substring(QString(output), lastItem, i).trimmed();
			lastItem = i;
		}
	}

	// add to class device list array
	for (int i = 1; i < outputData.size() - 1; i++)
	{
		if (i % 2 == 1)
		{
			//leftList << outputData[i];
			leftList.append(outputData[i]);
			qDebug() << leftList;
		}
	}

	for (int i = 0; i < leftList.size(); ++i) {
		QStandardItem *item = new QStandardItem(leftList.at(i));

		leftItemModel->appendRow(item);
	}

	QModelIndex qindex = leftItemModel->index(0, 0);   //默认选中 index

	ui.listView->setCurrentIndex(qindex);

	ui.listView->setModel(leftItemModel);
}

void QtADBClass::itemClicked(QModelIndex qIndex)
{
	qDebug() << qIndex.row() << "\n" << qIndex.data();

	device = qIndex.data().toString();
	// start process

	
	if (shell->state() != QProcess::Running)
	{
		command = QString(".\\platform-tools\\adb.exe -s %1 shell").arg(qIndex.data().toString());

		ui.textEdit_ml->append(command);

		shell->start(command);

		shell->waitForStarted();

		processEvent();

		QByteArray outputData = shell->readAllStandardOutput();

		ui.textEdit_jg->append(outputData);

		qDebug() << "start--->" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	}

	

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut()));

	timer->start(0);

}




void QtADBClass::TimerOut()
{	

	timer->stop();
	//wait出问题看这个
	//https://blog.csdn.net/yzt629/article/details/105777550
	//shell->write("clear\n");

	command = QString("ls -F\n");

	qDebug() << "2" << shell->state();

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	outputReady();

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut3()));

	timer->start(100);

	
}

void QtADBClass::TimerOut3()
{
	
	timer->stop();

	command = QString("ls -F\n");

	qDebug() << "22" << shell->state();

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	outputReady();

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut5()));

	timer->start(100);
	
}

void QtADBClass::TimerOut5()
{
	timer->stop();
	
	on_pushButton_getlj_clicked();
	
}




void QtADBClass::TimerOut2()
{
	
	timer->stop();

	command = QString("ls -F\n");

	qDebug() << "22" << shell->state();

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	outputReady();

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut3()));

	timer->start(100);

	
}

void QtADBClass::processEvent()
{
	shell->waitForReadyRead(10);

	qApp->processEvents();
}



void QtADBClass::outputReady()
{
	qDebug()<<"end--->" <<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	
	rightList.clear();

	rightItemModel->removeRows(0, rightItemModel->rowCount());

	QByteArray outputData = shell->readAllStandardOutput();

	qDebug() << "Good output is: " << outputData;

	ui.textEdit_jg->append(outputData);

	int lastIndex = 0;

	//outputData.remove(0, 7);
	
	for (int i = 0; i < outputData.size(); i++)
	{
		if (outputData[i] == '\n')
		{
			QString string = substring(QString(outputData), lastIndex, i);

			lastIndex = i;

			rightList << string;
		}
	}

	rightItemModel->setStringList(rightList);

	ui.listView_2->setModel(rightItemModel);

	
	
	
}

void QtADBClass::itemClicked_2(QModelIndex qIndex)
{

	QString data=qIndex.data().toString().trimmed();

	if (data.endsWith("@")||data.endsWith("\\\\"))
	{
		data = data.mid(0, data.length() - 1);
	}
	if (data.endsWith("/r"))
	{
		data = data.mid(0, data.length() - 2);
	}
	if (data.endsWith("/"))
	{
		data = data.mid(0, data.length() - 1);
	}

	if (data.contains(" "))
	{
		data = data.split(" ").at(1);
	}
	

	command = QString("cd %1\n").arg(data);

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);
	//shell->write("clear\n");

	qDebug() << "start--->" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut2()));

	timer->start(0);

}

void QtADBClass::adbOutputReady()
{

}
void QtADBClass::slotadbProcessFinished(int state)
{
	qDebug() << "adbProcess::slotadbProcessFinished";
}


void QtADBClass::slotFinished(int state)
{
	qDebug() << "shell::slotFinished:" << state;
}


void QtADBClass::on_pushButton_refresh_clicked()
{
	getDevices();
}
void QtADBClass::on_pushButton_refresh2_clicked()
{
	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut()));

	timer->start(0);
}
void QtADBClass::on_pushButton_back_clicked()
{
	command = QString("cd ..\n");

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut()));

	timer->start(0);
}

void QtADBClass::on_pushButton_getlj_clicked()
{
	command = QString("pwd\n");

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	QByteArray outputData = shell->readAllStandardOutput();

	ui.textEdit_jg->append(outputData);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut4()));

	timer->start(100);
}

void QtADBClass::TimerOut4()
{

	timer->stop();

	command = QString("pwd\n");

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	QByteArray outputData = shell->readAllStandardOutput();

	ui.textEdit_jg->append(outputData);

	ui.label_lujing->setText(outputData);

}

void QtADBClass::on_pushButton_install_clicked()
{

	//子窗口和主窗口用法不同
	QFileDialog *fd = new QFileDialog(this, Qt::SubWindow);

	fd->setOption(QFileDialog::DontUseNativeDialog, true);

	QString PCfileName = fd->getOpenFileName(0, "Select File", "D:\\", "Files (*.apk *.APK)", NULL, QFileDialog::DontUseNativeDialog);

	PCfileName = PCfileName.replace(QRegExp("//"), "/");

	PCfileName = PCfileName.replace(QRegExp("/"), "\\");

	qDebug() << "PCfileName: " << PCfileName;

	QString PhonefilePath(ui.label_lujing->text().trimmed());

	PhonefilePath = PhonefilePath.append("/");

	qDebug() << "PhonefilePath: " << PhonefilePath;

	adb = new QProcess();

	QString adbCommand = QString(".\\platform-tools\\adb.exe -s %1 install -r %2").arg(device, PCfileName);

	ui.textEdit_ml->append(adbCommand);

	qDebug() << "program is: " << adbCommand;

	adb->start(adbCommand);

	processEvent();

	QByteArray output = adb->readAllStandardOutput();

	ui.textEdit_jg->append(output);

	qDebug() << "push is: " << output;


}

void QtADBClass::on_pushButton_applist_clicked()
{

	if(!shell->state()==QProcess::Running)
	{ 
		qDebug() << shell->state();
		return;
	}

	command = QString("pm list packages\n");

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	QByteArray outputData = shell->readAllStandardOutput();

	ui.textEdit_jg->append(outputData);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(TimerOut6()));

	timer->start(100);

	

}

void QtADBClass::TimerOut6()
{

	timer->stop();

	command = QString("pm list packages\n");

	qDebug() << "command:" << command;

	shell->write(command.toLocal8Bit());

	processEvent();

	ui.textEdit_ml->append(command);

	QByteArray outputData = shell->readAllStandardOutput();

	qDebug() << "pm list packages is: " << outputData;

	ui.textEdit_jg->append(outputData);

	packagesList.clear();

	packagesItemModel->removeRows(0, packagesItemModel->rowCount());

	int lastIndex = 0;

	for (int i = 0; i < outputData.size(); i++)
	{
		if (outputData[i] == '\n')
		{
			QString string = substring(QString(outputData), lastIndex, i);

			lastIndex = i;

			if (string.contains(":"))
			{
				string = string.split(":").at(1);
			}

			if (string.startsWith("android"))
				continue;

			if (string.startsWith("com.android"))
				continue;
			
			if (string.startsWith("com.google"))
				continue;

			if (string.startsWith("com.miui"))
				continue;

			if (string.startsWith("miui"))
				continue;

			if (string.startsWith("com.xiaomi"))
				continue;

			if (string.startsWith("com.qti"))
				continue;

			if (string.startsWith("vendor.qti"))
				continue;
			
			if (string.startsWith("com.qualcomm"))
				continue;


			packagesList << string;
		}
	}

	//std排序
	sort(packagesList.begin(), packagesList.end(),
		[](const QString & str1, const QString & str2) {return str1.compare(str2, Qt::CaseInsensitive) < 0; });


	packagesItemModel->setStringList(packagesList);

	packageslistview->setModel(packagesItemModel);

	packagesDialog->open();

}


void QtADBClass::showMessageStr(QString msg)
{

	QTextCodec *codec = QTextCodec::codecForName("GBK");

	QPushButton *okbtn = new QPushButton(QString::fromLocal8Bit("复制内容"));

	QPushButton *cancelbtn = new QPushButton(codec->toUnicode(("关闭")));

	QMessageBox *mymsgbox = new QMessageBox;

	mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);

	mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);

	mymsgbox->setWindowTitle(codec->toUnicode("位置"));

	mymsgbox->setText(msg);

	mymsgbox->show();

	mymsgbox->exec();

	if (mymsgbox->clickedButton() == okbtn)
	{
		string stdStrp = string(msg.toLocal8Bit());
		//目前不知为何QT的剪切板功能不能使用？，使用C++的
		HWND hWnd = NULL;
		OpenClipboard(hWnd);//打开剪切板
		EmptyClipboard();//清空剪切板
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 10000);//分配内存
		char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
		strcpy_s(pData, 10000, stdStrp.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
		SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
		GlobalUnlock(hHandle);//解除锁定
		CloseClipboard();//关闭剪切板
	}
	else
	{
		mymsgbox->close();
	}

};


