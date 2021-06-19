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
	// 告诉服务器监听传入连接的名字。如果服务器当前正在监听，那么将返回false。监听成功返回true，否则为false
	if (!server->listen("111")) {
		QMessageBox::critical(this, tr("Fortune Server"),
			tr("Unable to start the server: %1.")
			.arg(server->errorString()));
		close();
		return;
	}

	// 有新客户端进行连接时，发送数据
	connect(server, SIGNAL(newConnection()), this, SLOT(sendFortune()));


	// 发送数据
	//windows一定要用\\，真TM的坑
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

		stream.setCodec(QTextCodec::codecForName("utf-8"));

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

			ui.et_result->setText(qtpamarsStr.toUtf8());

		}
		else
		{
			//注意编码统一，真坑啊
			//msg.toLocal8Bit();
			//msg.toUtf8();
			//msg.toLatin1();//是完全不懂的编码格式，千万不要混用了
			//tr()是专门格式化std::数组的
			QJsonParseError err;

			QJsonDocument jsonResponse = QJsonDocument::fromJson(qtpamarsStr.toUtf8(),&err);

			if (jsonResponse.isNull() || err.error != QJsonParseError::NoError)
			{
				ui.et_result->setText(qtpamarsStr.toUtf8());

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

				//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Compact);  //紧凑格式
				//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Indented);   //标准JSON格式
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

		//注意编码统一，真坑啊
		//msg.toLocal8Bit();
		//msg.toUtf8();
		//msg.toLatin1();//是完全不懂的编码格式，千万不要混用了
		//tr()是专门格式化std::数组的
		QTextStream stream(socket);
		stream.setCodec(QTextCodec::codecForName("utf-8"));
		stream << tr(msg.toStdString().data());
		//socket->write(msg.toStdString().data());
		//socket->flush();
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


	// 将信号 mySignal() 与槽 mySlot() 相关联
	connect(this, SIGNAL(mySignal(QString)), this, SLOT(mySlot(QString)));
	// 将信号 mySignal(int) 与槽 mySlot(int) 相关联
	//connect(ui.comboBox_url, SIGNAL(currentIndexChanged(int)), this, SLOT(mySlotUrlIndex(int)));
	connect(ui.comboBox_url, SIGNAL(activated(int)), this, SLOT(mySlotUrlIndex(int)));
	//connect(ui.comboBox_pamars, SIGNAL(currentIndexChanged(int)), this, SLOT(mySlotPamarsIndex(int)));
	connect(ui.comboBox_pamars, SIGNAL(activated(int)), this, SLOT(mySlotPamarsIndex(int)));
	connect(ui.comboBox_header, SIGNAL(activated(int)), this, SLOT(mySlotHeaderIndex(int)));

	connect(ui.et_result, SIGNAL(copyAvailable(bool)), this, SLOT(mySlotCopy(bool)));

	ui.et_result->installEventFilter(this);  //在窗体上为et_result安装过滤器
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


//%a, %A 读入一个浮点值(仅C99有效)
//% c 读入一个字符
//%d 读入十进制整数
//%i 读入十进制，八进制，十六进制整数
//%o 读入八进制整数
//%x, %X 读入十六进制整数
//%s 读入一个字符串，遇空格、制表符或换行符结束。
//%f, %F, %e, %E, %g, %G 用来输入实数，可以用小数形式或指数形式输入
//%p 读入一个指针
//%u 读入一个无符号十进制整数
//%n 至此已读入值的等价字符数
//%[] 扫描字符集合


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

	//qDebug() << "@请求URL:"<< url;

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

	QPushButton *okbtn = new QPushButton(g_pChnCodec->toUnicode(("确定")));

	QPushButton *cancelbtn = new QPushButton(g_pChnCodec->toUnicode(("取消")));

	QMessageBox *mymsgbox = new QMessageBox;

	mymsgbox->addButton(okbtn, QMessageBox::AcceptRole);

	mymsgbox->addButton(cancelbtn, QMessageBox::RejectRole);

	mymsgbox->setWindowTitle(g_pChnCodec->toUnicode(("输入新标签")));

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

	QPushButton *okbtn = new QPushButton(g_pChnCodec->toUnicode(("确定")));

	QString text = QInputDialog::getText(NULL,
		g_pChnCodec->toUnicode(("提示")),
		g_pChnCodec->toUnicode(("输入新标签")),
		//	QLineEdit::Password,	//输入的是密码，不显示明文
		QLineEdit::Normal,			//输入框明文
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
		//目前不知为何QT的剪切板功能不能使用？，使用C++的
		HWND hWnd = NULL;
		OpenClipboard(hWnd);//打开剪切板
		EmptyClipboard();//清空剪切板
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000000);//分配内存
		char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
		strcpy_s(pData, 1000000, stdStrp.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
		SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
		GlobalUnlock(hHandle);//解除锁定
		CloseClipboard();//关闭剪切板
	}
	catch (...) {
		QMessageBox::about(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("复制内容过多"));
	}
}

//加密
void TestUtil::on_pushButton_ecode_clicked()
{
	QString qtpamars = ui.et_result->document()->toPlainText().trimmed();
	//QString->std::string 防止乱码
	Current_State = 1;

	sendMsg(qtpamars);
}

//解密
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
	QByteArray root_str = jsonDocument.toJson(QJsonDocument::Compact);  //紧凑格式
	//QByteArray root_str = jsonDocument.toJson(QJsonDocument::Indented);   //标准JSON格式

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


void go(QString msg) { // 普通函数go

	for (QWidget *w : qApp->topLevelWidgets()) { // 获取顶级窗口

		qDebug() << w->objectName();
		if (w->objectName() == "QtWidgetsApplication1Class") // 判断是否是主窗口类名：主窗口类 + Class
		{                                                // 我的主窗口类是：QtGuiApplication1
			TestUtil* qw = (TestUtil*)w; // 转换并获取主窗口指针
			emit qw->mySignal(msg);
		}
	}
}

// 定义槽函数 mySlot()
void TestUtil::mySlot(QString msg)
{

	ui.et_result->setText(msg);
	//QMessageBox::about(this, "异常信息", msg);

}
// 定义槽函数 mySlotUrlIndex(int)
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
// 定义槽函数 mySlotPamarsIndex(int)
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

// 定义槽函数 mySlotPamarsIndex(int)
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
			//目前不知为何QT的剪切板功能不能使用？，使用C++的
			HWND hWnd = NULL;
			OpenClipboard(hWnd);//打开剪切板
			EmptyClipboard();//清空剪切板
			HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000000);//分配内存
			char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
			strcpy_s(pData, 1000000, stdStrp.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
			SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
			GlobalUnlock(hHandle);//解除锁定
			CloseClipboard();//关闭剪切板
		}
		catch (...) {
			QMessageBox::about(this, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("复制内容过多"));
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
	if (watched == ui.et_result)         //首先判断控件(这里指 lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.et_result->setPalette(p);
			Focus_Index = 3;
		}
		else if (event->type() == QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.et_result->setPalette(p);
		}
	}

	if (watched == ui.comboBox_url)         //首先判断控件(这里指 lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_url->setPalette(p);
			Focus_Index = 0;
		}
		else if (event->type() == QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_url->setPalette(p);
		}
	}

	if (watched == ui.comboBox_pamars)         //首先判断控件(这里指 lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_pamars->setPalette(p);
			Focus_Index = 1;
		}
		else if (event->type() == QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_pamars->setPalette(p);
		}
	}

	if (watched == ui.comboBox_header)         //首先判断控件(这里指 lineEdit1)
	{
		if (event->type() == QEvent::FocusIn)     //然后再判断控件的具体事件 (这里指获得焦点事件)
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, QColor(color_r, color_g, color_b, 255));
			ui.comboBox_header->setPalette(p);
			Focus_Index = 2;
		}
		else if (event->type() == QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
		{
			QPalette p = QPalette();
			p.setColor(QPalette::Base, Qt::white);
			ui.comboBox_header->setPalette(p);
		}
	}

	return QWidget::eventFilter(watched, event);     // 最后将事件交给上层对话框
}

void  TestUtil::on_pushButton_batch_clicked()
{

	/*总结：
	index mainForm;
	mainForm.show();
	mainForm创建在stack上，生命期是大括号内

	index *mainForm;
	mainForm = new index();
	mainForm.show();
	mainForm 通过new创建在heap上， 在程序退出时才会被析构*/

	QtBatchWidgetsClass *w;

	w = new QtBatchWidgetsClass();

	QTextCodec* g_pChnCodec = QTextCodec::codecForName("GBK");

	w->setWindowTitle(g_pChnCodec->toUnicode("批量任务"));

	w->show();

	//this->hide();

}

void TestUtil::closeEvent(QCloseEvent *event)
{
	qDebug() << "close windows";

	QString c = "taskkill /im QtHelpUtil.exe /f";
	int pInt = QProcess::execute(c);    //关闭后台notepad.exe进程，阻塞式运行,一直占用cpu,成功返回0，失败返回1

}

QString substring(QString string, int start, int end)
{
	return string.mid(start, end - start);
}
void TestUtil::on_pushButton_adb_clicked()
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

	// now parse devices
	QStringList devices;
	int lastItem = 0;
	for (int i = 0; i < output.size(); i++)
	{
		if (output[i] == '\n' || output[i] == '\t')
		{
			outputData << substring(QString(output), lastItem, i);
			lastItem = i;
		}
	}

	// add to class device list array
	for (int i = 1; i < outputData.size() - 1; i++)
	{
		if (i % 2 == 1)
		{
			devices << outputData[i];
			qDebug() << devices;
		}
	}

	//for (int i = 0; i < devices.size(); ++i) {
	//	QStandardItem *item = new QStandardItem(devices.at(i));

	//	ItemModel->appendRow(item);
	//}

	//QModelIndex qindex = ItemModel->index(0, 0);   //默认选中 index

	//ui->listView->setCurrentIndex(qindex);

	//ui->listView->setModel(ItemModel);

	//timer = new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(onSearchFinished()));
	//timer->start(1000);
}

void TestUtil::onSearchFinished()
{
	
	QStringList outputData;
	QByteArray output = adbProcess->readAllStandardOutput();
	qDebug() << "output is: " << output;
	
	//timer->stop();
}





