#ifndef BATCHTASK_H
#define BATCHTASK_H

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

class BatchTask : public QObject, public QRunnable
{
	Q_OBJECT

public:
	BatchTask();
	BatchTask(QString url, QStringList *list, int time, int index);
	~BatchTask();

protected:
	void run();
	QString UrlRequestPost(const QString url, const QString data, const QString header);

private:
	QStringList *mlist;
	int mtime;
	QString url;
	int currentIndex;

signals:
	//注意！要使用信号，采用QObejct 和 QRunnable多继承，记得QObject要放在前面
	void signals_ReplyData(QString msg, int);
	void signals_ErrorData(QString msg, int);

public slots:

	void slot_ReplyData(QString msg, int);
	void slot_ErrorData(QString msg, int);

};

#endif // BATCHTASK_H

