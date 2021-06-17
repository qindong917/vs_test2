#include "BatchTask.h"
#include <QThread>

BatchTask::BatchTask()
{

}

BatchTask::BatchTask(QString url, QStringList *list, int time, int index)
{
	this->url = url;

	this->mtime = time * 1000;

	this->mlist = list;

	this->currentIndex = index;
}

BatchTask::~BatchTask()
{
}

//线程真正执行的内容
void BatchTask::run()
{
	if (mtime > 0)
	{
		QThread::msleep(mtime);
	}

	QString request = UrlRequestPost(url, mlist->at(currentIndex), "");

}

void BatchTask::slot_ReplyData(QString data, int index)
{


}

void BatchTask::slot_ErrorData(QString data, int index)
{


}

QString BatchTask::UrlRequestPost(const QString url, const QString data, const QString header)

{
	if (!(url != nullptr && (url.startsWith("http://") || url.startsWith("https://"))))
	{
		emit signals_ErrorData("Please enter the correct URL", ++currentIndex);
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
	QNetworkReply *reply = qnam.post(qnr, data.toLocal8Bit());

	QEventLoop eventloop;

	reply->connect(reply, SIGNAL(finished()), &eventloop, SLOT(quit()));

	eventloop.exec(QEventLoop::ExcludeUserInputEvents);

	if (reply->error())
	{
		qDebug() << reply->errorString();

		emit signals_ErrorData(reply->errorString(), ++currentIndex);
		//go(reply->errorString());

		return "";
	}

	

	QString replyData =QString::fromLocal8Bit(reply->readAll());

	reply->deleteLater();

	reply = 0;

	emit signals_ReplyData(replyData, ++currentIndex);

	return replyData;

}
