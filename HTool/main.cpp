#include "wndbatchrename.h"
#include "commondownlist.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CommonDownList w;
	w.show();

	return a.exec();
}
