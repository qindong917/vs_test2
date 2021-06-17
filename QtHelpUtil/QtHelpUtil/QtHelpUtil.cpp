#include "QtHelpUtil.h"


std::string desKey = "19aGeD4K";
//调用c#注意:
//1：把要调用的dll复制到代码目录下，
//2：#using "./Helpers.dll"
//3：项目-》属性-》C/C++ -》常规-》公共语言运行时支持cli

QtHelpUtil::QtHelpUtil(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//设置主窗口透明的为0.1
	this->setWindowOpacity(0.1);
	//关闭最小号，最大化，关闭按钮
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	initCliect();
}



QString QtHelpUtil::zipAndEcode(QString qtpamars)
{
	string stdStrp = string(qtpamars.toLocal8Bit());

	qDebug() << "@post pamars:" << qtpamars;

	EncryptHelper ^helper = gcnew EncryptHelper();

	//cli数据注意前缀^
	String^ Clipamars = marshal_as<String^>(stdStrp);//std::string->cli::String

	Text::Encoding ^u8 = Text::Encoding::UTF8;

	cli::array<unsigned char> ^Clipamarsarray = u8->GetBytes(Clipamars);//cli::String->cli::array<unsigned char>

	cli::array<unsigned char> ^Clipamarsarray2 = helper->ZipEncode(Clipamarsarray);//开始压缩

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String（方式2）

	String ^ClipamarsStr = helper->EncryptDESECB(Clipamarsarray2, key);//开始DES加密

	string stdpamarsStr = marshal_as<std::string>(ClipamarsStr);//cli::String->std::string

	//QString qtpamarsStr = QString::fromStdString(stdpamarsStr);//std::string->QString
	QString qtpamarsStr = QString(QString::fromLocal8Bit(stdpamarsStr.c_str()));//std::string->QString 防止乱码

	qDebug() << "@post ecode:" << qtpamarsStr;
	return qtpamarsStr;
}


QString QtHelpUtil::dcodeAndUnzip(QString request)
{
	qDebug() << "@request pamars:" << request;
	//QString->std::string 防止乱码
	string stdStr = string(request.toLocal8Bit());

	char *cstr = new char[stdStr.length() + 1];

	strcpy(cstr, stdStr.c_str());

	String^ stdToCli = marshal_as<String^>(desKey);//std::string->cli::String

	String^ dec = gcnew String(stdStr.c_str());//std::string->cli::String

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String（方式2）

	QString resultStr;
	try {
		EncryptHelper ^helper = gcnew EncryptHelper();

		Text::Encoding ^u8 = Text::Encoding::UTF8;

		cli::array<unsigned char> ^p2cli = helper->DecryptDESECB(dec, key);//开始DES解密

		cli::array<unsigned char> ^p3cli = helper->ZipDecode(p2cli);//开始解压

		String ^p4cli = u8->GetString(p3cli);//cli::array<unsigned char>->cli::String

		string cliToWstring = marshal_as<std::string>(p4cli);//cli::String->std::string

		 resultStr = QString(QString::fromLocal8Bit(cliToWstring.c_str()));//std::string->QString 防止乱码

		qDebug() << "@request pamars:" << resultStr;
	}
	catch (...) {

		qDebug() << request;
	}

	return resultStr;
}

unsigned char * QtHelpUtil::zipAndEcode(unsigned char * request, int nStrLen)
{


	EncryptHelper ^helper = gcnew EncryptHelper();

	cli::array<unsigned char>^ dec = gcnew cli::array<unsigned char>(nStrLen);

	for (int i = 0; i < nStrLen; i++)
	{
		dec[i] = request[i];
	}

	cli::array<unsigned char> ^Clipamarsarray2 = helper->ZipEncode(dec);//开始压缩

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String（方式2）

	String ^ClipamarsStr = helper->EncryptDESECB(Clipamarsarray2, key);//开始DES加密

	Text::Encoding ^u8 = Text::Encoding::UTF8;

	cli::array<unsigned char> ^Clipamarsarray = u8->GetBytes(ClipamarsStr);//cli::String->cli::array<unsigned char>

	unsigned char *b2 = new unsigned char(Clipamarsarray->Length);

	for (int i = 0; i < Clipamarsarray->Length; i++)
	{
		b2[i] = Clipamarsarray[i];
	}

	return b2;
}


unsigned char * QtHelpUtil::dcodeAndUnzip(unsigned char * request, int nStrLen)
{


	cli::array<unsigned char>^ dec = gcnew cli::array<unsigned char>(nStrLen);

	for (int i = 0; i < nStrLen; i++)
	{
		dec[i] = request[i];
	}

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String（方式2）

	QString resultStr;

	try {
		EncryptHelper ^helper = gcnew EncryptHelper();

		Text::Encoding ^u8 = Text::Encoding::UTF8;

		cli::array<unsigned char> ^p2cli = helper->DecryptDESECB(u8->GetString(dec), key);//开始DES解密

		cli::array<unsigned char> ^p3cli = helper->ZipDecode(p2cli);//开始解压

		unsigned char *b2 = new unsigned char(p3cli->Length);

		for (int i = 0; i < p3cli->Length; i++)
		{
			b2[i] = p3cli[i];
		}

		return b2;
	}
	catch (...) {

		return NULL;
	}

	return NULL;
}


void QtHelpUtil::initCliect()
{
	socket = new QLocalSocket(this);
	socket->abort();
	socket->connectToServer(QString("111"));

	connect(socket, SIGNAL(readyRead()), this, SLOT(readFortune()));
	connect(socket, SIGNAL(error(QLocalSocket::LocalSocketError)),
		this, SLOT(displayError(QLocalSocket::LocalSocketError)));

	if (!socket->bytesAvailable())
		socket->waitForReadyRead();
}



// 读取服务器端发送的数据
void QtHelpUtil::readFortune()
{
	// 读取接收到的数据
	QTextStream stream(socket);

	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312")); //路径名支持中文
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312")); //QString支持中文
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312")); //string支持中文

	//后来去掉了那两行，将所有字符串到后使用tr()之后就能正常显示出中文了。

	stream.setCodec(QTextCodec::codecForName("utf-8"));

	QString respond = stream.readAll();

	qDebug() << "readFortune:" << respond;

	if (respond.startsWith("@"))
	{
		respond = respond.mid(1, respond.length());

		qDebug() << "readFortune:" << respond;

		respond = dcodeAndUnzip(respond);

		qDebug() << "dcodeAndUnzip:" << respond;

		sendMsg(respond);
	}
	else
	{
		respond = zipAndEcode(respond);

		qDebug() << "zipAndEcode:" << respond;

		QString p("@");

		p.append(respond);

		sendMsg(p);
	}

	

}

void QtHelpUtil::sendMsg(QString msg)
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

// 发生错误时，进行错误处理
void QtHelpUtil::displayError(QLocalSocket::LocalSocketError socketError)
{
	
	switch (socketError) {
	case QLocalSocket::ServerNotFoundError:
		qDebug() << "The host was not found. Please check the "
				"host name and port settings.";
		break;
	case QLocalSocket::ConnectionRefusedError:
		qDebug() << "The connection was refused by the peer. "
				"Make sure the fortune server is running, "
				"and check that the host name and port "
				"settings are correct.";
		break;
	case QLocalSocket::PeerClosedError:
		break;
	default:
		qDebug() << socket->errorString();
		break;
	}

}