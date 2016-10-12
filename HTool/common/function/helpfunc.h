#ifndef HELPFUNC_H
#define HELPFUNC_H

#include <QWidget>

#define AutoDelete(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = nullptr; \
			} \
}while(0)

void SetWidgetBackgroundColor(QWidget *des, QColor const &c);

#endif //HELPFUNC_H
