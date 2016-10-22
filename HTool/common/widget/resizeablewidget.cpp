#include "resizeablewidget.h"

#include <QMouseEvent>

#include <iostream>
using namespace std;

ResizeAbleWidget::ResizeAbleWidget(int accuracyPix, QWidget *parent)
	: QWidget(parent), m_accuracyPix(accuracyPix)
{
	this->setMouseTracking(true);
}

ResizeAbleWidget::~ResizeAbleWidget()
{

}

void ResizeAbleWidget::mousePressEvent(QMouseEvent *event)
{
	string s;
	switch(event->button())
	{
	case Qt::LeftButton:
		s = "LeftButton";
		break;
	case Qt::MidButton:
		s = "MidButton";
		break;
	case Qt::RightButton:
		s = "RightButton";
		break;
	}
	cout << "mousePress:local->" << s << "  X->" << event->pos().x() << "   Y->" << event->pos().y() << endl;
}

void ResizeAbleWidget::mouseReleaseEvent(QMouseEvent *event)
{
	string s;
	switch(event->button())
	{
	case Qt::LeftButton:
		s = "LeftButton";
		break;
	case Qt::MidButton:
		s = "MidButton";
		break;
	case Qt::RightButton:
		s = "RightButton";
		break;
	}
	cout << "mousePress:local->" << s << "  X->" << event->pos().x() << "   Y->" << event->pos().y() << endl;
}

void ResizeAbleWidget::mouseMoveEvent(QMouseEvent *event)
{
	cout << "mouseMove:X->" << event->x() << "   Y->" << event->y() << endl;
}
