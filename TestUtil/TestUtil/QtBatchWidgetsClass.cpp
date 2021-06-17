#include "QtBatchWidgetsClass.h"


bool runingable;

QtBatchWidgetsClass::QtBatchWidgetsClass(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//item���
	ui.listView->setSpacing(5);

	connect(ui.listView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));

	runingable = true;

	//ui.listView->setEnabled(false);

	pool = new QThreadPool();

	pool->setMaxThreadCount(3);

	list = new QStringList();

	replylist = new QStringList();

	ItemModel = new QStandardItemModel(this);

	ui.pushButton_start->setEnabled(false);
}

QtBatchWidgetsClass::~QtBatchWidgetsClass()
{
}


int i = 2;
int j = 0;
void QtBatchWidgetsClass::on_pushButton_start_clicked()
{


	mlist = new QStringList();

	QString pamars = list->at(1);

	QStringList childlist = pamars.split(",");

	for (i = 2; i < list->size(); i++)
	{
		QJsonObject json;

		QString childpamars = list->at(i);

		QStringList childpamarslist = childpamars.split(",");

		// ���� JSON ����
		for (j = 0; j < childlist.size(); j++)
		{

			QString key = childlist.at(j).trimmed();

			QString val = childpamarslist.at(j).trimmed();

			json.insert(key, val);

		}

		// ���� JSON �ĵ�
		QJsonDocument document;

		document.setObject(json);

		QByteArray byteArray = document.toJson(QJsonDocument::Compact);

		QString strJson(byteArray);

		qDebug() << strJson;

		mlist->append(strJson);
	}

	//�����̣߳���������
	BatchTask *task = new BatchTask(list->at(0), mlist, (ui.lineEdit_time->text().trimmed()).toInt(), 0);

	connect(task, SIGNAL(signals_ReplyData(QString, int)), this, SLOT(slot_ReplyData(QString, int)));

	connect(task, SIGNAL(signals_ReplyData(QString, int)), task, SLOT(slot_ReplyData(QString, int)));

	connect(task, SIGNAL(signals_ErrorData(QString, int)), this, SLOT(slot_ErrorData(QString, int)));

	connect(task, SIGNAL(signals_ErrorData(QString, int)), task, SLOT(slot_ErrorData(QString, int)));

	pool->start(task);


}

void QtBatchWidgetsClass::slot_ReplyData(QString data, int index)
{

	qDebug() << "void QtBatchWidgetsClass::slot_ReplyData(QString data, int index):" << data << "---->" << index;

	if (!runingable)
		return;

	replylist->append(data);

	if (index < mlist->size())
	{
		//�����̣߳���������
		BatchTask *task = new BatchTask(list->at(0), mlist, (ui.lineEdit_time->text().trimmed()).toInt(), index);

		connect(task, SIGNAL(signals_ReplyData(QString, int)), this, SLOT(slot_ReplyData(QString, int)));

		connect(task, SIGNAL(signals_ReplyData(QString, int)), task, SLOT(slot_ReplyData(QString, int)));

		connect(task, SIGNAL(signals_ErrorData(QString, int)), this, SLOT(slot_ErrorData(QString, int)));

		connect(task, SIGNAL(signals_ErrorData(QString, int)), task, SLOT(slot_ErrorData(QString, int)));

		pool->start(task);

	}
	QModelIndex qindex = ItemModel->index(index + 1, 0);   //Ĭ��ѡ�� index

	ui.listView->setCurrentIndex(qindex);

	QLabel *label = new QLabel(ui.listView);

	label->setScaledContents(true);

	label->setAlignment(Qt::AlignVCenter);

	if (data != nullptr && data.contains("\"rst\":200"))
	{
		label->setStyleSheet("QLabel{background-color:rgb(169,208,245);font-size:22px;color:rgb(0, 0, 0);}");
	}
	else
	{
		label->setStyleSheet("QLabel{background-color:rgb(245,169,169);font-size:22px;color:rgb(255, 255, 255);}");
	}


	label->setText(list->at(index + 1));

	ui.listView->setIndexWidget(qindex, label);

}

void QtBatchWidgetsClass::slot_ErrorData(QString data, int index)
{

	qDebug() << "void QtBatchWidgetsClass::slot_ErrorData(QString data, int index):" << data << "---->" << index;

	replylist->append(data);

	if (!runingable)
		return;

	if (index < mlist->size())
	{
		//�����̣߳���������
		BatchTask *task = new BatchTask(list->at(0), mlist, (ui.lineEdit_time->text().trimmed()).toInt(), index);

		connect(task, SIGNAL(signals_ReplyData(QString, int)), this, SLOT(slot_ReplyData(QString, int)));

		connect(task, SIGNAL(signals_ReplyData(QString, int)), task, SLOT(slot_ReplyData(QString, int)));

		connect(task, SIGNAL(signals_ErrorData(QString, int)), this, SLOT(slot_ErrorData(QString, int)));

		connect(task, SIGNAL(signals_ErrorData(QString, int)), task, SLOT(slot_ErrorData(QString, int)));

		pool->start(task);

		QModelIndex qindex = ItemModel->index(index, 0);   //Ĭ��ѡ�� index

		ui.listView->setCurrentIndex(qindex);

	}

	QModelIndex qindex = ItemModel->index(index + 1, 0);   //Ĭ��ѡ�� index

	ui.listView->setCurrentIndex(qindex);

	QLabel *label = new QLabel(ui.listView);

	label->setScaledContents(true);

	label->setStyleSheet("QLabel{background-color:rgb(245,169,169);font-size:22px;color:rgb(255, 255, 255);}");

	label->setText(list->at(index + 1));

	ui.listView->setIndexWidget(qindex, label);
}

void QtBatchWidgetsClass::on_pushButton_select_file_clicked()
{

	//�Ӵ��ں��������÷���ͬ
	QFileDialog *fd = new QFileDialog(this, Qt::SubWindow);

	fd->setOption(QFileDialog::DontUseNativeDialog, true);

	QString fileName = fd->getOpenFileName(0, "Select File", "D:\\", "Files (*.txt)", NULL, QFileDialog::DontUseNativeDialog);

	qDebug() << fileName;

	if (fileName.isEmpty())     //���δѡ���ļ���ȷ�ϣ�������
		return;

	ui.lineEdit_file_path->setText(fileName);

	QFile file(fileName);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{

		list->clear();

		replylist->clear();

		while (!file.atEnd())
		{
			QByteArray line = file.readLine();

			QString str(line);

			list->append(str);

			qDebug() << str;

			QStandardItem *item = new QStandardItem(str);

			ItemModel->appendRow(item);


		}

		file.close();
		if (list->size() > 0)
		{
			ui.pushButton_start->setEnabled(true);
		}
		else
		{
			ui.pushButton_start->setEnabled(false);
		}

		QModelIndex qindex = ItemModel->index(2, 0);   //Ĭ��ѡ�� index

		ui.listView->setCurrentIndex(qindex);



		ui.listView->setModel(ItemModel);

		replylist->append("");
		replylist->append("");
		//ui.listView->setFixedSize(200, 300);




	}


}

void showMessageStr(QString msg)
{

	QTextCodec* g_pChnCodec = QTextCodec::codecForName("GBK");

	QPushButton *okbtn = new QPushButton(QString::fromLocal8Bit("��������"));

	QPushButton *cancelbtn = new QPushButton(g_pChnCodec->toUnicode(("�ر�")));

	QMessageBox *mymsgbox = new QMessageBox;

	mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);

	mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);

	mymsgbox->setWindowTitle(g_pChnCodec->toUnicode("��ϸ"));

	mymsgbox->setText(msg);

	mymsgbox->show();

	mymsgbox->exec();

	if (mymsgbox->clickedButton() == okbtn)
	{
		string stdStrp = string(msg.toLocal8Bit());
		//Ŀǰ��֪Ϊ��QT�ļ��а幦�ܲ���ʹ�ã���ʹ��C++��
		HWND hWnd = NULL;
		OpenClipboard(hWnd);//�򿪼��а�
		EmptyClipboard();//��ռ��а�
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 10000);//�����ڴ�
		char* pData = (char*)GlobalLock(hHandle);//�����ڴ棬���������ڴ���׵�ַ
		strcpy_s(pData, 10000, stdStrp.c_str());//��strcpy(pData, "this is a ClipBoard Test.");
		SetClipboardData(CF_TEXT, hHandle);//���ü��а�����
		GlobalUnlock(hHandle);//�������
		CloseClipboard();//�رռ��а�
	}
	else
	{
		mymsgbox->close();
	}

};

void QtBatchWidgetsClass::itemClicked(QModelIndex qIndex)
{
	qDebug() << qIndex.row() << "\n" << qIndex.data();

	showMessageStr(replylist->at(qIndex.row()).toLocal8Bit());
}



void QtBatchWidgetsClass::closeEvent(QCloseEvent *event)
{
	runingable = false;
}

void QtBatchWidgetsClass::on_pushButton_help_clicked()
{

	QDialog	*dialog = new  QDialog();
	dialog->setStyleSheet("background-image:url(./images/help.png);height:991px;width:1503px"); //this works 
	dialog->setGeometry(geometry().x(), geometry().y(), 1503, 991);
	dialog->show();

}
