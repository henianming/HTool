#ifndef HELPFUNC_H
#define HELPFUNC_H

#include <QWidget>

#define SAFEDELETE(a) \
do{ \
	if (a) { \
		delete (a); \
	} \
}while(0)

#define SAFEDELETENULL(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = nullptr; \
	} \
}while(0)

#define UNUSED(a) ((void)(a))

void SetWidgetBackgroundColor(QWidget *des, QColor const &c);

#endif //HELPFUNC_H
