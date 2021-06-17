#include "QtHelpUtil.h"


std::string desKey = "19aGeD4K";
//����c#ע��:
//1����Ҫ���õ�dll���Ƶ�����Ŀ¼�£�
//2��#using "./Helpers.dll"
//3����Ŀ-������-��C/C++ -������-��������������ʱ֧��cli

QtHelpUtil::QtHelpUtil(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//����������͸����Ϊ0.1
	this->setWindowOpacity(0.1);
	//�ر���С�ţ���󻯣��رհ�ť
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	initCliect();
}



QString QtHelpUtil::zipAndEcode(QString qtpamars)
{
	string stdStrp = string(qtpamars.toLocal8Bit());

	qDebug() << "@post pamars:" << qtpamars;

	EncryptHelper ^helper = gcnew EncryptHelper();

	//cli����ע��ǰ׺^
	String^ Clipamars = marshal_as<String^>(stdStrp);//std::string->cli::String

	Text::Encoding ^u8 = Text::Encoding::UTF8;

	cli::array<unsigned char> ^Clipamarsarray = u8->GetBytes(Clipamars);//cli::String->cli::array<unsigned char>

	cli::array<unsigned char> ^Clipamarsarray2 = helper->ZipEncode(Clipamarsarray);//��ʼѹ��

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String����ʽ2��

	String ^ClipamarsStr = helper->EncryptDESECB(Clipamarsarray2, key);//��ʼDES����

	string stdpamarsStr = marshal_as<std::string>(ClipamarsStr);//cli::String->std::string

	//QString qtpamarsStr = QString::fromStdString(stdpamarsStr);//std::string->QString
	QString qtpamarsStr = QString(QString::fromLocal8Bit(stdpamarsStr.c_str()));//std::string->QString ��ֹ����

	qDebug() << "@post ecode:" << qtpamarsStr;
	return qtpamarsStr;
}


QString QtHelpUtil::dcodeAndUnzip(QString request)
{
	qDebug() << "@request pamars:" << request;
	//QString->std::string ��ֹ����
	string stdStr = string(request.toLocal8Bit());

	char *cstr = new char[stdStr.length() + 1];

	strcpy(cstr, stdStr.c_str());

	String^ stdToCli = marshal_as<String^>(desKey);//std::string->cli::String

	String^ dec = gcnew String(stdStr.c_str());//std::string->cli::String

	String^ key = gcnew String(desKey.c_str());//std::string->cli::String����ʽ2��

	QString resultStr;
	try {
		EncryptHelper ^helper = gcnew EncryptHelper();

		Text::Encoding ^u8 = Text::Encoding::UTF8;

		cli::array<unsigned char> ^p2cli = helper->DecryptDESECB(dec, key);//��ʼDES����

		cli::array<unsigned char> ^p3cli = helper->ZipDecode(p2cli);//��ʼ��ѹ

		String ^p4cli = u8->GetString(p3cli);//cli::array<unsigned char>->cli::String

		string cliToWstring = marshal_as<std::string>(p4cli);//cli::String->std::string

		 resultStr = QString(QString::fromLocal8Bit(cliToWstring.c_str()));//std::string->QString ��ֹ����

		qDebug() << "@request pamars:" << resultStr;
	}
	catch (...) {

		qDebug() << request;
	}

	return resultStr;
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



// ��ȡ�������˷��͵�����
void QtHelpUtil::readFortune()
{
	// ��ȡ���յ�������
	QTextStream stream(socket);

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
	socket->write(msg.toStdString().c_str());
	socket->flush();
}

// ��������ʱ�����д�����
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