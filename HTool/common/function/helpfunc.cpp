#include "helpfunc.h"

void SetWidgetBackgroundColor(QWidget *des, QColor const &c) {
	des->setAutoFillBackground(true);
	QPalette p;
	p.setColor(QPalette::Background, c);
	des->setPalette(p);
}

bool IsInRange(int l, int s, int b)
{
	return (l >= s) && (l <= b);
}

bool IsPointInArea(QPoint const &point, QRect const &rect)
{
	return IsInRange(point.x(), rect.left(), rect.right()) && IsInRange(point.y(), rect.top(), rect.bottom());
}
