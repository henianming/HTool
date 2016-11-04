#include "resizablelist.h"

IResizableListItem::IResizableListItem(QWidget *parent)
	: EdgeSensitiveWidget(1, parent)
{

}

IResizableListItem::~IResizableListItem()
{

}

ResizableList::ResizableList(IResizableListItem *item, DIRECTION direct, QWidget *parent)
	: QWidget(parent),  m_direction(direct)
{
	m_widgetCount = 0;

	m_primaryItem = item->copy();

	InitWidget();

	Show();
}

ResizableList::~ResizableList()
{
	Hide();

	SAFEDELETE(m_primaryItem);
}

void ResizableList::InitWidget()
{
	m_itemAreaWidget = new QWidget(this);
}

void ResizableList::Show()
{

	SetWidgetBackgroundColor(m_itemAreaWidget, QColor(200,200,200));
}

void ResizableList::Hide()
{

}

void ResizableList::Update()
{
	//将克隆体移到对应位置
	QSize s = m_primaryItem->size();
	//m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH))->move(indexH * s.width(), indexV * s.height());

	std::vector<IResizableListItem*>::iterator vIt = m_widgetItemVector.begin();
	int idx = 0;
	while (vIt != m_widgetItemVector.end())
	{
		if (*vIt)
		{
			if (m_direction == DIRECTION_HORIZONTAL)
			{
				(*vIt)->move(idx * s.width(), 0);
			}
			else if (m_direction == DIRECTION_VERTICAL)
			{
				(*vIt)->move(0, idx * s.height());
			}
		}

		vIt++;
		idx++;
	}
}

void ResizableList::SetCount(int count)
{
	//数量未变直接返回
	if (m_widgetCount == count) {
		return;
	}

	//保存以前的水平个数，设置新的水平个数
	int prevCount = m_widgetCount;
	m_widgetCount = count;

	//若水平个数或垂直个数为0，清空表返回
	if (m_widgetCount == 0) {
		CleanAllData();
		return;
	}

	std::vector<IResizableListItem*> temp;

	//拷贝原有的还有用的数据
	int needDealCount = (prevCount > m_widgetCount) ? prevCount : m_widgetCount;
	for (int i = 0; i < needDealCount; i++) {
		if (i >= prevCount && i < m_widgetCount) {
			temp.push_back(NULL);
		}
		else if(i >= m_widgetCount && i < prevCount) {
			SAFEDELETE(m_widgetItemVector.at(static_cast<size_t>(i)));
		}
		else {
			temp.push_back(m_widgetItemVector.at(static_cast<size_t>(i)));
		}
	}

	//设置新的保存item指针的空间
	m_widgetItemVector.swap(temp);
}

void ResizableList::SetDirection(DIRECTION direction)
{
	m_direction = direction;
	Update();
}

void ResizableList::SetData(int index, void const *data)
{
	if (index >= m_widgetCount || index < 0) {
		return;
	}

	IResizableListItem *itemPtr = m_widgetItemVector.at(static_cast<size_t>(index));
	if (!itemPtr)
	{
		m_widgetItemVector.at(static_cast<size_t>(index)) = m_primaryItem->copy();
		m_widgetItemVector.at(static_cast<size_t>(index))->setParent(m_itemAreaWidget);

		Update();
	}

	m_widgetItemVector.at(static_cast<size_t>(index))->draw(index, data);
}

void ResizableList::CleanData(int index)
{
	if (index >= m_widgetCount || index < 0) {
		return;
	}

	SAFEDELETENULL(m_widgetItemVector.at(static_cast<size_t>(index)));
}

void ResizableList::CleanAllData()
{
	for (int i = 0; i < m_widgetCount; i++)
	{
		CleanData(i);
	}
}

void ResizableList::mousePressEvent(QMouseEvent *event)
{

}

void ResizableList::mouseReleaseEvent(QMouseEvent *event)
{

}

void ResizableList::mouseMoveEvent(QMouseEvent *event)
{

}
