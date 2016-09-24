#include "wndbatchrename.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WndBatchRename w;
	w.show();

	return a.exec();
}
