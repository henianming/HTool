#include "resizeablewidget.h"

#include <QMouseEvent>

#include <iostream>
using namespace std;

ResizeAbleWidget::ResizeAbleWidget(QWidget *parent)
	: QWidget(parent), m_tDragEnable(false), m_bDragEnable(false), m_lDragEnable(false), m_rDragEnable(false), m_cDragEnable(false)
{
	this->setMouseTracking(true);
}

ResizeAbleWidget::~ResizeAbleWidget()
{

}

void ResizeAbleWidget::enterEvent(QEvent *event)
{
	cout << "enter" << endl;
}

void ResizeAbleWidget::leaveEvent(QEvent *event)
{
	cout << "leave" << endl;
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

void ResizeAbleWidget::mouseMoveEvent(QMouseEvent *event)
{
	cout << "mouseMove:X->" << event->x() << "   Y->" << event->y() << endl;
}
