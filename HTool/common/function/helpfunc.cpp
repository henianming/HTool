#include "helpfunc.h"

void SetWidgetBackgroundColor(QWidget *des, QColor const &c) {
	des->setAutoFillBackground(true);
	QPalette p;
	p.setColor(QPalette::Background, c);
	des->setPalette(p);
}