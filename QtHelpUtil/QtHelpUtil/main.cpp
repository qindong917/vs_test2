#include "QtHelpUtil.h"
#include <QtWidgets/QApplication>
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QString dir = QApplication::applicationDirPath();
	QApplication::addLibraryPath("./images");
	a.setWindowIcon(QIcon("./images/logo.ico"));

    QtHelpUtil w;
	w.setWindowTitle("调试挂件");
	w.setWindowFlags(Qt::Tool);//关闭任务栏图标
    w.show();
    return a.exec();
}
