#ifndef RESIZEABLEWIDGET_H
#define RESIZEABLEWIDGET_H

#include <QWidget>

class ResizeAbleWidget : public QWidget
{
	Q_OBJECT
private:
	bool m_tDragEnable;
	bool m_bDragEnable;
	bool m_lDragEnable;
	bool m_rDragEnable;
	bool m_cDragEnable;

protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	ResizeAbleWidget(QWidget *parent = 0);
	~ResizeAbleWidget();
};

#endif
