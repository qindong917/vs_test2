#include "TestUtil.h"


SqlUtil sql;
QThreadPool pool;
QJsonObject getJsonObjectFromString(const QString jsonString);
QString getStringFromJsonObject(const QJsonObject& jsonObject);
void go(const QString msg);


TestUtil::TestUtil(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initComboBox();

	initQProcess(parent);

	pool.setMaxThreadCount(3);

}

void TestUtil::initQProcess(QWidget *parent)
{
	server = new QLocalServer(this);
	// ���߷����������������ӵ����֡������������ǰ���ڼ�������ô������false�������ɹ�����true������Ϊfalse
	if (!server->listen("111")) {
		QMessageBox::critical(this, tr("Fortune Server"),
			tr("Unable to start the server: %1.")
			.arg(server->errorString()));
		close();
		return;
	}

	// ���¿ͻ��˽�������ʱ����������
	connect(server, SIGNAL(newConnection()), this, SLOT(sendFortune()));


	// ��������
	//windowsһ��Ҫ��\\����TM�Ŀ�
	QString program = ".\\Release\\QtHelpUtil.exe";
	QStringList arguments;
	arguments << program;
	myProcess = new QProcess(parent);
	myProcess->start(program, arguments);
	QObject::connect(myProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(processError(QProcess::ProcessError)));

}

void TestUtil::processError(QProcess::ProcessError error)
{
	qDebug() << error;
}

void TestUtil::sendFortune() {

	socket = server->nextPendingConnection();
	connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadyReadHandler()));
	connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));

}

void TestUtil::socketReadyReadHandler()
{

	if (socket)
	{
		QTextStream stream(socket);

		QString qtpamarsStr = stream.readAll();

		if (qtpamarsStr.startsWith("@") && Current_State == 0)
		{
			QString qtheader = ui.comboBox_header->currentText().trimmed();

			QString url = ui.comboBox_url->currentText().trimmed();

			qtpamarsStr = qtpamarsStr.mid(1, qtpamarsStr.length());

			PrintTask *task = new PrintTask(url, qtpamarsStr, qtheader);

			connect(task, SIGNAL(signals_ReplyData(QString)), this, SLOT(slot_ReplyData(QString)));

			connect(task, SIGNAL(signals_ErrorData(QString)), this, SLOT(slot_ErrorData(QString)));

			pool.start(task);

		}
		else if (Current_State == 1 || Current_State == 2)
		{
			if (qtpamarsStr.startsWith("@"))
			{
				qtpamarsStr = qtpamarsStr.mid(1, qtpamarsStr.length());
			}	

			ui.et_result->setText(qtpamarsStr.toLocal8Bit());

		}
		else
		{

			QJsonParseError err;

			QJsonDocument jsonResponse = QJsonDocument::fromJson(qtpamarsStr.trimmed().toLocal8Bit(),&err);

			if (jsonResponse.isNull() || err.error != QJsonParseError::NoError)
			{
				ui.et_result->setText(qtpamarsStr.toLocal8Bit());

				qDebug() << "QJsonParseError:" << err.errorString();
			}
			else
			{
				QJsonObject jo = jsonResponse.object();

				if (jo.contains("total"))
				{
					int total = jo.value("total").toInt();
					int rst = jo.value("rst").toInt();
					int cost = jo.value("cost").toInt();
					int count = jo.value("count").toInt();
					QJsonObject userinfo = jo.value("userinfo").toObject();
					QJsonArray  list = jo.value("list").toArray();
					int i = 0;
					for (i = 0; i < list.size(); i++)
					{
						QJsonObject jo2 = list.at(i).toObject();

						int cost = jo2.value("cost").toInt();
						int isrefund = jo2.value("isrefund").toInt();
						int paytype = jo2.value("paytype").toInt();
						int status = jo2.value("ptistatusme").toInt();
						string name = jo2.value("name").toString().toStdString();
						string payorderid = jo2.value("payorderid").toString().toStdString();
						string paytypename = jo2.value("paytypename").toString().toStdString();
						string ptime = jo2.value("ptime").toString().toStdString();
					}
				}

				//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Compact);  //���ո�ʽ
				//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Indented);   //��׼JSON��ʽ
				qDebug() << QJsonDocument(jo).toJson(QJsonDocument::Indented);
				ui.et_result->setText(QJsonDocument(jo).toJson(QJsonDocument::Indented));
			}

		}
	}
}

void  TestUtil::slot_ReplyData(QString request)
{
	if (request.length() > 0)
	{
		QString p("@");

		p.append(request);

		sendMsg(p);
	}

	ui.pushButton->setEnabled(true);
}

void  TestUtil::slot_ErrorData(QString data)
{
	ui.et_result->setText(data.toLocal8Bit());

	ui.pushButton->setEnabled(true);
}


void TestUtil::deleteLater()
{

}
void TestUtil::sendMsg(QString msg)
{

	if (socket)
	{
		socket->write(msg.toLocal8Bit());
		socket->flush();
	}

}



void TestUtil::initComboBox()
{
	QString str = "QComboBox QAbstractItemView:item{"
		"font-family: PingFangSC-Regular;"
		"font-size:26px;"
		"min-height:50px;"
		"min-width:20px;}"

		"QComboBox { "
		"min-height: 50px;"
		"font-size:26px;}";

	QStyledItemDelegate* styledItemDelegate = new QStyledItemDelegate();

	ui.comboBox_url->setItemDelegate(styledItemDelegate);
	ui.comboBox_url->setStyleSheet(str);

	ui.comboBox_pamars->setItemDelegate(styledItemDelegate);
	ui.comboBox_pamars->setStyleSheet(str);

	ui.comboBox_header->setItemDelegate(styledItemDelegate);
	ui.comboBox_header->setStyleSheet(str);


	// ���ź� mySignal() ��� mySlot() �����
	connect(this, SIGNAL(mySignal(QString)), this, SLOT(mySlot(QString)));
	// ���ź� mySignal(int) ��� mySlot(int) �����
	//connect(ui.comboBox_url, SIGNAL(currentIndexChanged(int)), this, SLOT(mySlotUrlIndex(int)));
	connect(ui.comboBox_url, SIGNAL(activated(int)), this, SLOT(mySlotUrlIndex(int)));
	//connect(ui.comboBox_pamars, SIGNAL(currentIndexChanged(int)), this, SLOT(mySlotPamarsIndex(int)));
	connect(ui.comboBox_pamars, SIGNAL(activated(int)), this, SLOT(mySlotPamarsIndex(int)));
	connect(ui.comboBox_header, SIGNAL(activated(int)), this, SLOT(mySlotHeaderIndex(int)));

	connect(ui.et_result, SIGNAL(copyAvailable(bool)), this, SLOT(mySlotCopy(bool)));

	ui.et_result->installEventFilter(this);  //�ڴ�����Ϊet_result��װ������
	ui.comboBox_url->installEventFilter(this);
	ui.comboBox_pamars->installEventFilter(this);
	ui.comboBox_header->installEventFilter(this);

	urllist = sql.query(sql.OpenSql(), Url_Type);
	pamarslist = sql.query(sql.OpenSql(), Pamars_Type);
	headerlist = sql.query(sql.OpenSql(), Header_Type);

	sql.closeDB();

	ui.comboBox_url->setEditable(true);
	for (i = 0; i < urllist.size(); i++)
	{
		QtContent* bean = urllist.at(i);
		if (bean->getLabel() == nullptr)
		{
			ui.comboBox_url->addItem(bean->getContent());
		}
		else {
			QString temp("(");
			temp.append(bean->getLabel());
			temp.append(")   ");
			temp.append(bean->getContent());
			ui.comboBox_url->addItem(temp);
		}
	}
	if (urllist.size() > 0)
		ui.comboBox_url->setEditText(urllist.at(0)->getContent());
	else
	{
		ui.comboBox_url->setEditText("");
	}

	ui.comboBox_pamars->setEditable(true);
	for (i = 0; i < pamarslist.size(); i++)
	{
		QtContent* bean = pamarslist.at(i);
		if (bean->getLabel() == nullptr)
		{
			ui.comboBox_pamars->addItem(bean->getContent());
		}
		else {
			QString temp("(");
			temp.append(bean->getLabel());
			temp.append(")   ");
			temp.append(bean->getContent());
			ui.comboBox_pamars->addItem(temp);
		}
	}

	if (pamarslist.size() > 0)
		ui.comboBox_pamars->setEditText(pamarslist.at(0)->getContent());
	else
	{
		ui.comboBox_pamars->setEditText("");
	}

	ui.comboBox_header->setEditable(true);
	for (i = 0; i < headerlist.size(); i++)
	{
		QtContent* bean = headerlist.at(i);
		if (bean->getLabel() == nullptr)
		{
			ui.comboBox_header->addItem(bean->getContent());
		}
		else {
			QString temp("(");
			temp.append(bean->getLabel());
			temp.append(")   ");
			temp.append(bean->getContent());
			ui.comboBox_header->addItem(temp);
		}
	}

	if (headerlist.size() > 0)
		ui.comboBox_header->setEditText(headerlist.at(0)->getContent());
	else
	{
		ui.comboBox_header->setEditText("");
	}
}


//%a, %A ����һ������ֵ(��C99��Ч)
//% c ����һ���ַ�
//%d ����ʮ��������
//%i ����ʮ���ƣ��˽��ƣ�ʮ����������
//%o ����˽�������
//%x, %X ����ʮ����������
//%s ����һ���ַ��������ո��Ʊ������з�������
//%f, %F, %e, %E, %g, %G ��������ʵ����������С����ʽ��ָ����ʽ����
//%p ����һ��ָ��
//%u ����һ���޷���ʮ��������
//%n �����Ѷ���ֵ�ĵȼ��ַ���
//%[] ɨ���ַ�����


void TestUtil::on_pushButton_clicked()
{

	Current_State = 0;

	QString url = ui.comboBox_url->currentText().trimmed();

	if (url.length() <= 0)
		return;

	ui.pushButton->setEnabled(false);

	if (sql.insert(sql.OpenSql(), Url_Type, url) > 0)
	{
		ui.comboBox_url->clear();

		urllist = sql.query(sql.OpenSql(), Url_Type);

		for (i = 0; i < urllist.size(); i++)
		{
			QtContent* bean = urllist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_url->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_url->addItem(temp);
			}
		}

		ui.comboBox_url->setEditText(url);

		QString qtpamars = ui.comboBox_pamars->currentText().trimmed();

		sql.updateLink(sql.OpenSql(), qtpamars, url);

	};

	//qDebug() << "@����URL:"<< url;

	QString qtpamars = ui.comboBox_pamars->currentText().trimmed();

	if (nullptr != qtpamars && sql.insert(sql.OpenSql(), Pamars_Type, qtpamars) > 0)
	{
		qDebug() << 3;
		ui.comboBox_pamars->clear();

		pamarslist = sql.query(sql.OpenSql(), Pamars_Type);

		for (i = 0; i < pamarslist.size(); i++)
		{
			QtContent* bean = pamarslist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_pamars->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_pamars->addItem(temp);
			}
		}

		ui.comboBox_pamars->setEditText(qtpamars);
	};

	QString qtheader = ui.comboBox_header->currentText().trimmed();

	if (nullptr != qtheader && sql.insert(sql.OpenSql(), Header_Type, qtheader) > 0)
	{
		ui.comboBox_header->clear();

		headerlist = sql.query(sql.OpenSql(), Header_Type);

		for (i = 0; i < headerlist.size(); i++)
		{
			QtContent* bean = headerlist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_header->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_header->addItem(temp);
			}
		}

		ui.comboBox_header->setEditText(qtheader);
	};

	sql.closeDB();

	sendMsg(qtpamars);
}

void TestUtil::on_pushButton_url_clicked()
{
	if (urllist.size() <= 0)
		return;

	QtContent* q = urllist.at(Url_Index);
	QString c = q->getContent();
	if (sql.deletedata(sql.OpenSql(), c) > 0)
	{
		ui.comboBox_url->clear();

		urllist = sql.query(sql.OpenSql(), Url_Type);

		for (i = 0; i < urllist.size(); i++)
		{
			QtContent* bean = urllist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_url->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_url->addItem(temp);
			}
		}
		ui.comboBox_url->setEditText("");
	};
	sql.closeDB();
}

void TestUtil::on_pushButton_pamars_clicked()
{
	if (pamarslist.size() <= 0)
		return;

	QtContent* q = pamarslist.at(Pamars_Index);
	QString c = q->getContent();
	if (sql.deletedata(sql.OpenSql(), c) > 0)
	{
		ui.comboBox_pamars->clear();

		pamarslist = sql.query(sql.OpenSql(), Pamars_Type);

		for (i = 0; i < pamarslist.size(); i++)
		{
			QtContent* bean = pamarslist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_pamars->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_pamars->addItem(temp);
			}
		}
		ui.comboBox_pamars->setEditText("");
	};

	sql.closeDB();
}

void TestUtil::on_pushButton_header_clicked()
{
	if (headerlist.size() <= 0)
		return;

	QtContent* q = headerlist.at(Header_Index);
	QString c = q->getContent();
	if (sql.deletedata(sql.OpenSql(), c) > 0)
	{
		ui.comboBox_header->clear();

		headerlist = sql.query(sql.OpenSql(), Header_Type);

		for (i = 0; i < headerlist.size(); i++)
		{
			QtContent* bean = headerlist.at(i);
			if (bean->getLabel() == nullptr)
			{
				ui.comboBox_header->addItem(bean->getContent());
			}
			else {
				QString temp("(");
				temp.append(bean->getLabel());
				temp.append(")   ");
				temp.append(bean->getContent());
				ui.comboBox_header->addItem(temp);
			}
		}
		ui.comboBox_header->setEditText("");
	};

	sql.closeDB();
}

void showMessageStr()
{
	QTextCodec* g_pChnCodec = QTextCodec::codecForName("GBK");

	QPushButton *okbtn = new QPushButton(g_pChnCodec->toUnicode(("ȷ��")));

	QPushButton *cancelbtn = new QPushButton(g_pChnCodec->toUnicode(("ȡ��")));

	QMessageBox *mymsgbox = new QMessageBox;

	mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);

	mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);

	mymsgbox->setWindowTitle(g_pChnCodec->toUnicode(("�����±�ǩ")));

	mymsgbox->show();

};



void TestUtil::updataLabel(QString str)
{
	switch (Focus_Index)
	{
	case 0:
	{
		if (urllist.size() <= 0)
			return;

		QtContent* q = urllist.at(Url_Index);
		QString c = q->getContent();
		if (sql.update(sql.OpenSql(), str, c) > 0)
		{
			ui.comboBox_url->clear();

			urllist = sql.query(sql.OpenSql(), Url_Type);

			for (i = 0; i < urllist.size(); i++)
			{
				QtContent* bean = urllist.at(i);
				if (bean->getLabel() == nullptr)
				{
					ui.comboBox_url->addItem(bean->getContent());
				}
				else {
					QString temp("(");
					temp.append(bean->getLabel());
					temp.append(")   ");
					temp.append(bean->getContent());
					ui.comboBox_url->addItem(temp);
				}
			}
			ui.comboBox_url->setEditText(c);
		};

		sql.closeDB();
	}
	break;
	case 1:
	{
		if (pamarslist.size() <= 0)
			return;

		QtContent* q = pamarslist.at(Pamars_Index);
		QString c = q->getContent();
		if (sql.update(sql.OpenSql(), str, c) > 0)
		{
			ui.comboBox_pamars->clear();

			pamarslist = sql.query(sql.OpenSql(), Pamars_Type);

			for (i = 0; i < pamarslist.size(); i++)
			{
				QtContent* bean = pamarslist.at(i);
				if (bean->getLabel() == nullptr)
				{
					ui.comboBox_pamars->addItem(bean->getContent());
				}
				else {
					QString temp("(");
					temp.append(bean->getLabel());
					temp.append(")   ");
					temp.append(bean->getContent());
					ui.comboBox_pamars->addItem(temp);
				}
			}

			ui.comboBox_pamars->setEditText(c);
		};

		sql.closeDB();
	}
	break;

	case 2:
	{
		if (headerlist.size() <= 0)
			return;

		QtContent* q = headerlist.at(Header_Index);
		QString c = q->getContent();
		if (sql.update(sql.OpenSql(), str, c) > 0)
		{
			ui.comboBox_header->clear();

			headerlist = sql.query(sql.OpenSql(), Header_Type);

			for (i = 0; i < headerlist.size(); i++)
			{
				QtContent* bean = headerlist.at(i);
				if (bean->getLabel() == nullptr)
				{
					ui.comboBox_header->addItem(bean->getContent());
				}
				else {
					QString temp("(");
					temp.append(bean->getLabel());
					temp.append(")   ");
					temp.append(bean->getContent());
					ui.comboBox_header->addItem(temp);
				}
			}

			ui.comboBox_header->setEditText(c);
		};

		sql.closeDB();
	}
	break;
	default:
		break;
	}
}

void TestUtil::on_pushButton_clear_clicked()
{
	switch (Focus_Index)
	{
	case 0:
		ui.comboBox_url->lineEdit()->clear();
		break;
	case 1:
		ui.comboBox_pamars->lineEdit()->clear();
		break;
	case 2:
		ui.comboBox_header->lineEdit()->clear();
		break;
	case 3:
		ui.et_result->clear();
		break;
	default:
		break;
	}
}



void TestUtil::showInputDialog()
{
	bool isOK;

	QTextCodec* g_pChnCodec = QTextCodec::codecForName("GBK");

	QPushButton *okbtn = new QPushButton(g_pChnCodec->toUnicode(("ȷ��")));

	QString text = QInputDialog::getText(NULL,
		g_pChnCodec->toUnicode(("��ʾ")),
		g_pChnCodec->toUnicode(("�����±�ǩ")),
		//	QLineEdit::Password,	//����������룬����ʾ����
		QLineEdit::Normal,			//���������
		NULL,
		&isOK);

	if (isOK) {
		/*QMessageBox::information(NULL, "Information",
			"Your comment is: <b>" + text + "</b>",
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes);*/
		updataLabel(text);
	}
}

void TestUtil::on_pushButton_label_clicked()
{
	showInputDialog();

}

void TestUtil::on_pushButton_copy_clicked()
{

	QString str;


	switch (Focus_Index)
	{
	case 0:
		str = ui.comboBox_url->currentText();
		break;
	case 1:
		str = ui.comboBox_pamars->currentText();
		break;
	case 2:
		str = ui.comboBox_header->currentText();
		break;
	case 3:
		str = ui.et_result->document()->toPlainText();
		break;
	default:
		break;
	}

	
	try
	{

		string stdStrp = string(str.toLocal8Bit());
		//Ŀǰ��֪Ϊ��QT�ļ��а幦�ܲ���ʹ�ã���ʹ��C++��
		HWND hWnd = NULL;
		OpenClipboard(hWnd);//�򿪼��а�
		EmptyClipboard();//��ռ��а�
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000000);//�����ڴ�
		char* pData = (char*)GlobalLock(hHandle);//�����ڴ棬���������ڴ���׵�ַ
		strcpy_s(pData, 1000000, stdStrp.c_str());//��strcpy(pData, "this is a ClipBoard Test.");
		SetClipboardData(CF_TEXT, hHandle);//���ü��а�����
		GlobalUnlock(hHandle);//�������
		CloseClipboard();//�رռ��а�
	}
	catch (...) {
		QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ݹ���"));
	}
}

//����
void TestUtil::on_pushButton_ecode_clicked()
{
	QString qtpamars = ui.et_result->document()->toPlainText().trimmed();
	//QString->std::string ��ֹ����
	Current_State = 1;

	sendMsg(qtpamars);
}

//����
void TestUtil::on_pushButton_dcode_clicked()
{
	QString request = ui.et_result->document()->toPlainText().trimmed();

	Current_State = 2;

	QString p("@");

	p.append(request);

	sendMsg(p);
}


// QString >> QJson

QJsonObject getJsonObjectFromString(const QString jsonString) {

	QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
	QByteArray root_str = jsonDocument.toJson(QJsonDocument::Compact);  //���ո�ʽ
	//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Indented);   //��׼JSON��ʽ

	if (jsonDocument.isNull()) {

		qDebug() << "===> please check the string " << jsonString.toLocal8Bit().data();

	}

	QJsonObject jsonObject = jsonDocument.object();

	return jsonObject;

}

// QJson >> QString

QString getStringFromJsonObject(const QJsonObject& jsonObject) {

	return QString(QJsonDocument(jsonObject).toJson());

}


void go(QString msg) { // ��ͨ����go

	for (QWidget *w : qApp->topLevelWidgets()) { // ��ȡ��������

		qDebug() << w->objectName();
		if (w->objectName() == "QtWidgetsApplication1Class") // �ж��Ƿ����������������������� + Class
		{                                                // �ҵ����������ǣ�QtGuiApplication1
			TestUtil* qw = (TestUtil*)w; // ת������ȡ������ָ��
			emit qw->mySignal(msg);
		}
	}
}

// ����ۺ��� mySlot()
void TestUtil::mySlot(QString msg)
{

	ui.et_result->setText(msg);
	//QMessageBox::about(this, "�쳣��Ϣ", msg);

}
// ����ۺ��� mySlotUrlIndex(int)
void TestUtil::mySlotUrlIndex(int x)
{
	if (x < 0)
		return;
	Url_Index = x;
	if (Url_Index < urllist.size()) {
		QtContent* q = urllist.at(Url_Index);
		QString c = q->getContent();

		ui.comboBox_url->setEditText(c);

		QString l = q->getLink();
		if (nullptr != l)
		{
			ui.comboBox_pamars->setEditText(l);
		}

		//qDebug() << c << "\n" << l;
	}

}
// ����ۺ��� mySlotPamarsIndex(int)
void TestUtil::mySlotPamarsIndex(int x)
{
	if (x < 0)
		return;
	Pamars_Index = x;
	if (Pamars_Index < pamarslist.size()) {
		QtContent* q = pamarslist.at(Pamars_Index);
		QString c = q->getContent();
		ui.comboBox_pamars->setEditText(c);
		//qDebug() << c;
	}
}

// ����ۺ��� mySlotPamarsIndex(int)
void TestUtil::mySlotHeaderIndex(int x)
{
	if (x < 0)
		return;
	Header_Index = x;
	if (Header_Index < headerlist.size()) {
		QtContent* q = headerlist.at(Header_Index);
		QString c = q->getContent();
		ui.comboBox_header->setEditText(c);
		//qDebug() << c;
	}
}

void TestUtil::mySlotCopy(bool yes)
{

	if (yes) {
		try
		{

			QString str = ui.et_result->document()->toPlainText();

			string stdStrp = string(str.toLocal8Bit());
			//Ŀǰ��֪Ϊ��QT�ļ��а幦�ܲ���ʹ�ã���ʹ��C++��
			HWND hWnd = NULL;
			OpenClipboard(hWnd);//�򿪼��а�
			EmptyClipboard();//��ռ��а�
			HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000000);//�����ڴ�
			char* pData = (char*)GlobalLock(hHandle);//�����ڴ棬���������ڴ���׵�ַ
			strcpy_s(pData, 1000000, stdStrp.c_str());//��strcpy(pData, "this is a ClipBoard Test.");
			SetClipboardData(CF_TEXT, hHandle);//���ü��а�����
			GlobalUnlock(hHandle);//�������
			CloseClipboard();//�رռ��а�
		}
		catch (...) {
			QMessageBox::about(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�������ݹ���"));
		}

	}
}

void TestUtil::mySlotCopy2(bool yes)
{

}

int color_r = 169;
int color_g = 208;
int color_b = 245;
bool TestUtil::eventFilter(QObject * watched, QEvent * event)
{
	if (watched == ui.et_result)         //�����жϿؼ�(����ָ lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //Ȼ�����жϿؼ��ľ����¼� (����ָ��ý����¼�)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.et_result->setPalette(p);
			Focus_Index = 3;
		}
		else if (event->type() == QEvent::FocusOut)    // ����ָ lineEdit1 �ؼ���ʧȥ�����¼�
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.et_result->setPalette(p);
		}
	}

	if (watched == ui.comboBox_url)         //�����жϿؼ�(����ָ lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //Ȼ�����жϿؼ��ľ����¼� (����ָ��ý����¼�)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_url->setPalette(p);
			Focus_Index = 0;
		}
		else if (event->type() == QEvent::FocusOut)    // ����ָ lineEdit1 �ؼ���ʧȥ�����¼�
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_url->setPalette(p);
		}
	}

	if (watched == ui.comboBox_pamars)         //�����жϿؼ�(����ָ lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //Ȼ�����жϿؼ��ľ����¼� (����ָ��ý����¼�)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_pamars->setPalette(p);
			Focus_Index = 1;
		}
		else if (event->type() == QEvent::FocusOut)    // ����ָ lineEdit1 �ؼ���ʧȥ�����¼�
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_pamars->setPalette(p);
		}
	}

	if (watched == ui.comboBox_header)         //�����жϿؼ�(����ָ lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //Ȼ�����жϿؼ��ľ����¼� (����ָ��ý����¼�)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_header->setPalette(p);
			Focus_Index = 2;
		}
		else if (event->type() == QEvent::FocusOut)    // ����ָ lineEdit1 �ؼ���ʧȥ�����¼�
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_header->setPalette(p);
		}
	}

	return QWidget::eventFilter(watched, event);     // ����¼������ϲ�Ի���
}

void  TestUtil::on_pushButton_batch_clicked()
{

	/*�ܽ᣺
	index mainForm;
	mainForm.show();
	mainForm������stack�ϣ��������Ǵ�������

	index *mainForm;
	mainForm = new index();
	mainForm.show();
	mainForm ͨ��new������heap�ϣ� �ڳ����˳�ʱ�Żᱻ����*/

	QtBatchWidgetsClass *w;

	w = new QtBatchWidgetsClass();

	QTextCodec* g_pChnCodec = QTextCodec::codecForName("GBK");

	w->setWindowTitle(g_pChnCodec->toUnicode("��������"));

	w->show();

	//this->hide();

}

void TestUtil::closeEvent(QCloseEvent *event)
{
	qDebug() << "close windows";

	QString c = "taskkill /im QtHelpUtil.exe /f";
	int pInt = QProcess::execute(c);    //�رպ�̨notepad.exe���̣�����ʽ����,һֱռ��cpu,�ɹ�����0��ʧ�ܷ���1
}



