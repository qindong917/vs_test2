#include "TestUtil.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QString dir = QApplication::applicationDirPath();
	QApplication::addLibraryPath("./images");
	a.setWindowIcon(QIcon("./images/logo.ico"));
    TestUtil w;
	w.setWindowTitle(QString::fromLocal8Bit("???Թ???"));
    w.show();
    return a.exec();
}
