#ifndef RESIZEABLEWIDGET_H
#define RESIZEABLEWIDGET_H

#include <QWidget>

class ResizeAbleWidget : public QWidget
{
	Q_OBJECT
private:
	int m_accuracyPix;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

public:
	ResizeAbleWidget(int accuracyPix = 1, QWidget *parent = 0);
	~ResizeAbleWidget();

signals:
	void press()
};

#endif
