#include "QtContent.h"

struct QtContentalDataPrivate // 定义私有数据成员类型
{
	QString content;
	QString label;
	QString link;
	int type;
};

// constructor
QtContent::QtContent()
{
	d = new QtContentalDataPrivate;
};

// destructor
QtContent::~QtContent()
{
	delete d;
};

void QtContent::setContent(const QString content)
{
	if (content != d->content)
		d->content = content;
}

QString QtContent::getContent()
{
	return d->content;
}

void QtContent::setLabel(const QString label)
{
	if (label != d->label)
		d->label = label;
}

QString QtContent::getLabel()
{
	return d->label;
}

void QtContent::setLink(const QString link)
{
	if (link != d->link)
		d->link = link;
}

QString QtContent::getLink()
{
	return d->link;
}


void QtContent::setType(const int type)
{
	if (type != d->type)
		d->type = type;
}

int QtContent::getType()
{
	return d->type;
}
