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
bool IsInRange(int l, int s, int b);
bool IsPointInArea(const QPoint &point, const QRect &rect);

#endif //HELPFUNC_H
