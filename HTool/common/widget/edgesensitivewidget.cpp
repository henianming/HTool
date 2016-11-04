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
	emit MousePress(event);
}

void EdgeSensitiveWidget::mouseReleaseEvent(QMouseEvent *event)
{
	emit MouseRelease(event);
}

void EdgeSensitiveWidget::mouseMoveEvent(QMouseEvent *event)
{
	EdgeSensitive_Area area = isInSensitiveArea(event->x(), event->y());

	emit MoveIntoSensitiveArea(area);
}
