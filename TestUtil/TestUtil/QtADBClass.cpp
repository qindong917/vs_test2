#include "QtADBClass.h"

QStringList leftList;
QStringList rightList;

QtADBClass::QtADBClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	rightItemModel = new QStringListModel(this);

	leftItemModel = new QStandardItemModel(this);

	getDevices();

	//connect(ui.listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
	connect(ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));

	//connect(ui.listView_2, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemClicked_2(QModelIndex)));
	connect(ui.listView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked_2(QModelIndex)));
	
}

QtADBClass::~QtADBClass()
{
}

void QtADBClass::closeEvent(QCloseEvent *event)
{
	qDebug() << "close windows";

	QString c = "taskkill /im adb.exe /f";
	int pInt = QProcess::execute(c);    //关闭后台notepad.exe进程，阻塞式运行,一直占用cpu,成功返回0，失败返回1

	shell->kill();

}

QString QtADBClass::substring(QString string, int start, int end)
{
	return string.mid(start, end - start);
}


void QtADBClass::slotFinished(int state)
{
	qDebug() << "QtADBClass::slotFinished:"<< state;
}

void QtADBClass::getDevices()
{

	//windows一定要用\\，真TM的坑
	QString program = ".\\platform-tools\\adb.exe";
	QStringList arguments;
	arguments << "devices";
	adbProcess = new QProcess(this);
	adbProcess->start(program, arguments);
	adbProcess->waitForFinished();

	QStringList outputData;
	QByteArray output = adbProcess->readAllStandardOutput();
	qDebug() << "output is: " << output;

	leftList.clear();

	leftItemModel->removeRows(0, leftItemModel->rowCount());

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

	adbProcess->kill();
}

void QtADBClass::itemClicked(QModelIndex qIndex)
{
	qDebug() << qIndex.row() << "\n" << qIndex.data();

	// start process

	shell = new QProcess();

	qDebug() << "1" << shell->state();

	connect(shell, SIGNAL(finished(int)), this, SLOT(slotFinished(int))); //或者

	QString program = QString(".\\platform-tools\\adb.exe -s %1 shell").arg(qIndex.data().toString());

	shell->start(program);

	shell->waitForStarted();

	shell->write("clear\n");

	shell->write("ls -F\n");

	qDebug() << "4" << shell->state();

	shell->waitForReadyRead();

	qDebug() << "5" << shell->state();

	outputReady();
}

void QtADBClass::outputReady()
{
	qDebug() << "c:" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
	

	rightItemModel->removeRows(0, rightItemModel->rowCount());

	QByteArray outputData = shell->readAllStandardOutput();
	int lastIndex = 0;

	// get rid of first garbage characters
	outputData.remove(0, 7);

	// clear data
	rightList.clear();

	// parse data into list
	for (int i = 0; i < outputData.size(); i++)
	{
		if (outputData[i] == '\n')
		{
			QString string = substring(QString(outputData), lastIndex, i);
			lastIndex = i;
			rightList << string;
		}
	}

	// set model list
	rightItemModel->setStringList(rightList);

	ui.listView_2->setModel(rightItemModel);
	
	qDebug() << "Good output is: " << outputData;
}

void QtADBClass::itemClicked_2(QModelIndex qIndex)
{
	qDebug() << "6" << shell->state();
	qDebug() << qIndex.data().toString();

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
	QString program = QString("cd %1\n").arg(data);

	qDebug() <<"program:" << program;

	shell->write(program.toLocal8Bit());

	shell->write("clear\n");

	shell->write("ls -F\n");

	shell->waitForReadyRead();

	qDebug() << "7" << shell->state();

	outputReady();
}

void QtADBClass::adbOutputReady()
{
	//QByteArray outputData = adb->readAllStandardOutput();

	//qDebug() << "adb output: " << outputData;
}
void QtADBClass::on_pushButton_refresh_clicked()
{
	getDevices();
}


