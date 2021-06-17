#include "printtask.h"
#include <QThread>
#include <iostream>



PrintTask::PrintTask()
{
}

PrintTask::PrintTask(QString url1, QString qtpamarsStr1, QString qtheader1)
{
	this->url = url1;
	this->qtpamarsStr = qtpamarsStr1;
	this->qtheader = qtheader1;

}

PrintTask::~PrintTask()
{

}

//线程真正执行的内容
void PrintTask::run()
{

	QString request = UrlRequestPost(url, qtpamarsStr, qtheader);//qtPost
}

QString PrintTask::UrlRequestPost(const QString url, const QString data, const QString header)

{
	if (!(url != nullptr && (url.startsWith("http://") || url.startsWith("https://"))))
	{
		emit signals_ErrorData("Please enter the correct URL");
		return "";
	}
	QNetworkAccessManager qnam;

	const QUrl aurl(url);

	QNetworkRequest qnr(aurl);

	qnr.setRawHeader("Content-Type", "application/json;charset=UTF-8");

	if (nullptr != header) {

		QJsonDocument jsonResponse = QJsonDocument::fromJson(header.toUtf8());

		QJsonObject jo = jsonResponse.object();

		QJsonObject::const_iterator it = jo.constBegin();

		QJsonObject::const_iterator end = jo.constEnd();

		while (it != end)
		{
			QString key = it.key();
			QString value = it.value().toString();
			it++;
			qnr.setRawHeader(key.toUtf8(), value.toUtf8());
		}
	}

	//请求参数
	QNetworkReply *reply = qnam.post(qnr, data.toUtf8());

	QEventLoop eventloop;

	reply->connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));

	eventloop.exec(QEventLoop::ExcludeUserInputEvents);

	if (reply->error())
	{
		qDebug() << reply->errorString();

		emit signals_ErrorData(reply->errorString());
		//go(reply->errorString());

		return "";
	}

	QTextCodec *codec = QTextCodec::codecForName("utf8");

	//QString replyData =QString::fromLocal8Bit( reply->readAll());
	QString replyData = codec->toUnicode(reply->readAll());

	reply->deleteLater();

	reply = 0;

	emit signals_ReplyData(replyData);

	return replyData;

}
