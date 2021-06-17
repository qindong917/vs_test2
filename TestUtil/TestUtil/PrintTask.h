#ifndef PRINTTASK_H
#define PRINTTASK_H

#include <QObject>
#include <QRunnable>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>

#include <QJsonObject> 
#include <QJsonDocument>
#include <QJsonArray>

class PrintTask : public QObject, public QRunnable
{
	Q_OBJECT

public:
	PrintTask();
	PrintTask(QString url, QString qtpamarsStr, QString qtheader);
	~PrintTask();
protected:
	void run();
	QString UrlRequestPost(const QString url, const QString data, const QString header);

private:
	QString url;
	QString qtpamarsStr;
	QString qtheader;

signals:
	//ע�⣡Ҫʹ���źţ�����QObejct �� QRunnable��̳У��ǵ�QObjectҪ����ǰ��
	void signals_ReplyData(QString msg);
	void signals_ErrorData(QString msg);
};

#endif // PRINTTASK_H