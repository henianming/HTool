#include "edgesensitivewidget.h"

#include <QMouseEvent>

#include <iostream>
using namespace std;

EdgeSensitiveWidget::EdgeSensitiveWidget(int accuracyPix, QWidget *parent)
	: QWidget(parent), m_sensitivePix(accuracyPix)
{
	this->setMouseTracking(true);
}

EdgeSensitiveWidget::~EdgeSensitiveWidget()
{

}

int EdgeSensitiveWidget::getSensitivePix()
{
	return m_sensitivePix;
}

void EdgeSensitiveWidget::setSensitivePix(int sensitivePix)
{
	m_sensitivePix = sensitivePix;
}

EdgeSensitive_Area EdgeSensitiveWidget::isInSensitiveArea(int x, int y)
{
	QRect rc = this->rect();
	QPoint gp = this->mapToGlobal(QPoint(0, 0));
	int height = rc.height();
	int width = rc.width();
	rc.setTop(gp.y());
	rc.setBottom(gp.y() + height - 1);
	rc.setLeft(gp.x());
	rc.setRight(gp.x() + width - 1);

	QPoint mousePoint(x, y);
	if (IsPointInArea(mousePoint, QRect(rc.left() + m_sensitivePix, rc.top(), rc.width() - 2 * m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_Top;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left() + rc.width() - m_sensitivePix, rc.top(), m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_TopRight;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left() + rc.width() - m_sensitivePix, rc.top() + m_sensitivePix, m_sensitivePix, rc.height() - 2 * m_sensitivePix)))
	{
		return EdgeSensitive_Right;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left() + rc.width() - m_sensitivePix, rc.top() + rc.height() - m_sensitivePix, m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_RightBottom;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left() + m_sensitivePix, rc.top() + rc.height() - m_sensitivePix, rc.width() - 2 * m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_Bottom;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left(), rc.top() + rc.height() - m_sensitivePix, m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_BottomLeft;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left(), rc.top() + m_sensitivePix, m_sensitivePix, rc.height() - 2 * m_sensitivePix)))
	{
		return EdgeSensitive_Left;
	}
	else if (IsPointInArea(mousePoint, QRect(rc.left(), rc.top(), m_sensitivePix, m_sensitivePix)))
	{
		return EdgeSensitive_LeftTop;
	}

	return EdgeSensitive_None;
}

void EdgeSensitiveWidget::mousePressEvent(QMouseEvent *event)
{
	/*
	EdgeSensitive_Area s;
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
	*/
}

void EdgeSensitiveWidget::mouseReleaseEvent(QMouseEvent *event)
{
	/*
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
	*/
}

void EdgeSensitiveWidget::mouseMoveEvent(QMouseEvent *event)
{

}
