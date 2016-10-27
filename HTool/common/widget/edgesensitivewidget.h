#ifndef RESIZEABLEWIDGET_H
#define RESIZEABLEWIDGET_H

#include <QWidget>
#include "common.h"

enum EdgeSensitive_Area
{
	EdgeSensitive_None = 0,
	EdgeSensitive_Top,
	EdgeSensitive_TopRight,
	EdgeSensitive_Right,
	EdgeSensitive_RightBottom,
	EdgeSensitive_Bottom,
	EdgeSensitive_BottomLeft,
	EdgeSensitive_Left,
	EdgeSensitive_LeftTop,
	EdgeSensitive_Center,
};

class EdgeSensitiveWidget : public QWidget
{
	Q_OBJECT
private:
	int m_sensitivePix;

private:
	EdgeSensitive_Area isInSensitiveArea(int x, int y);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	EdgeSensitiveWidget(int sensitivePix = 1, QWidget *parent = 0);
	~EdgeSensitiveWidget();

	int getSensitivePix();
	void setSensitivePix(int sensitivePix);
};

#endif
