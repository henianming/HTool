#ifndef RESIZABLELIST_H
#define RESIZABLELIST_H

#include <QWidget>
#include "customtable.h"
#include "edgesensitivewidget.h"

class IResizableListItem : public EdgeSensitiveWidget{
	Q_OBJECT
public:
	IResizableListItem(QWidget *parent = 0);
	virtual ~IResizableListItem();

	virtual void draw(int index, void const *data) = 0;
	virtual IResizableListItem* copy() = 0;
};

class ResizableList : public QWidget
{
	enum DIRECTION
	{
		DIRECTION_HORIZONTAL = 0,
		DIRECTION_VERTICAL,
	};

	Q_OBJECT
private:
	QWidget *m_itemAreaWidget;
	DIRECTION m_direction;

	int m_widgetCount;
	IResizableListItem *m_primaryItem;
	std::vector<IResizableListItem*> m_widgetItemVector;

public:
	ResizableList(IResizableListItem *item, DIRECTION direct = DIRECTION_HORIZONTAL, QWidget *parent = 0);
	~ResizableList();
	void InitWidget();
	void BatchConnect();
	void BatchDisconnect();
	void Show();
	void Hide();
	void Update();

	void SetCount(int count);
	void SetDirection(DIRECTION direction);
	void SetData(int index, void const *data);
	void CleanData(int index);
	void CleanAllData();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
};

#endif // RESIZABLELIST_H
