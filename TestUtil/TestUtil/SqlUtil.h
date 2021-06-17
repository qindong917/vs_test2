#pragma once
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QUuid>
#include "QtContent.h"

class SqlUtil
{
public:
	QSqlQuery OpenSql(void);


	int insert(QSqlQuery sql_query, int type, QString content);


	int update(QSqlQuery sql_query, QString label, QString content);

	int updateLink(QSqlQuery sql_query, QString link, QString content);

	QList<QtContent*> query(QSqlQuery sql_query, int type);


	int deletedata(QSqlQuery sql_query, QString content);


	int deletetable(QSqlQuery sql_query);


	int closeDB(void);

private:
	QSqlDatabase database;
};

