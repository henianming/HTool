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

bool EdgeSensitiveWidget::isInRange(int l, int s, int b)
{
	return (l >= s) && (l <= b);
}

EdgeSensitive_Area EdgeSensitiveWidget::isInSensitiveArea(int x, int y)
{
	int mX = event->pos().x();
	int mY = event->pos().y();
	QRect rc = this->rect();
	QPoint gp = this->mapToGlobal(QPoint(0, 0));
	int height = rc.height();
	int width = rc.width();
	rc.setTop(gp.y());
	rc.setBottom(gp.y() + height - 1);
	rc.setLeft(gp.x());
	rc.setRight(gp.x() + width - 1);

	if (isInRange(mX, rc.left() + m_sensitivePix, rc.right() - m_sensitivePix) && isInRange(mY, rc.top(), rc.top() + m_sensitivePix))
	{
		//EdgeSensitive_Top
	}
	else if (isInRange(mX, rc.right() - m_sensitivePix, rc.right()) && isInRange(mY, rc.top(), rc.top() + m_sensitivePix))
	{
		//EdgeSensitive_TopRight
	}
	else if (isInRange(mX, rc.right() - m_sensitivePix, rc.right()) && isInRange(mY, rc.top() + m_sensitivePix, rc.bottom() - m_sensitivePix))
	{
		//EdgeSensitive_Right
	}
	else if (isInRange(mX, rc.right() - m_sensitivePix, rc.right()) && isInRange(mY, rc.bottom() - m_sensitivePix, rc.bottom()))
	{
		//EdgeSensitive_RightBottom
	}
	else if (isInRange(mX, rc.left() + m_sensitivePix, rc.right() - m_sensitivePix) && isInRange(mY, rc.bottom() - m_sensitivePix, rc.bottom()))
	{
		//EdgeSensitive_Bottom
	}
	else if (isInRange(mX, rc.left(), rc.left() + m_sensitivePix) && isInRange(mY, rc.bottom() - m_sensitivePix, rc.bottom()))
	{
		//EdgeSensitive_BottomLeft
	}
	else if (isInRange(mX, rc.left(), rc.left() + m_sensitivePix) && isInRange(mY, rc.top() + m_sensitivePix, rc.bottom() - m_sensitivePix))
	{
		//EdgeSensitive_Left
	}
	else if (isInRange(mX, rc.left(), rc.left() + m_sensitivePix) && isInRange(mY, rc.top(), rc.top() + m_sensitivePix))
	{
		//EdgeSensitive_LeftTop
	}
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
