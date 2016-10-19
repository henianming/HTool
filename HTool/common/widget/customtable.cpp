#include "customtable.h"

#include "common.h"

//------------------------------------------------------------------------ICustomTableItem
ICustomTableItem::ICustomTableItem(QWidget *parent)
	: QWidget(parent) {

}

ICustomTableItem::~ICustomTableItem() {

}

//------------------------------------------------------------------------CustomTable
CustomTable::CustomTable(ICustomTableItem *item, QWidget *parent)
	: QScrollArea(parent) {
	m_widgetHorizontalCount = 0;
	m_widgetVerticalCount = 0;

	m_primaryItem = item->copy();

	CreateWidget();

	Show();
}

CustomTable::~CustomTable() {
	int i;

	Hide();

	ReleaseWidget();

	int count = static_cast<int>(m_widgetItemVector.size());
	for(i = 0; i < count; i++) {
		SAFEDELETENULL(m_widgetItemVector.at(static_cast<size_t>(i)));
	}

	SAFEDELETENULL(m_primaryItem);
}

void CustomTable::CreateWidget()
{
	m_itemAreaWidget = new QWidget(this);
}

void CustomTable::ReleaseWidget()
{
	SAFEDELETENULL(m_itemAreaWidget);
}

void CustomTable::Show()
{
	this->setWidget(m_itemAreaWidget);
	//m_itemAreaScrollArea->setGeometry(0,0,300,400);
	//m_itemAreaWidget->setGeometry(0,0,200,200);

	SetWidgetBackgroundColor(m_itemAreaWidget, QColor(200,200,200));
}

void CustomTable::Hide()
{

}

void CustomTable::SetHorizontalCount(int count) {
	int i;

	//数量未变直接返回
	if (m_widgetHorizontalCount == count) {
		return;
	}

	//保存以前的水平个数，设置新的水平个数
	int prevCount = m_widgetHorizontalCount;
	m_widgetHorizontalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//若水平个数或垂直个数为0，清空表返回
	if (itemCount == 0) {
		CleanAllData();
		return;
	}

	//分配新的保存item指针的空间
	std::vector<ICustomTableItem*> temp;
	for(i = 0; i < itemCount; i++) {
		temp.push_back(NULL);
	}

	//拷贝原有的还有用的数据
	for (int i = 0; i < prevCount; i++) {
		for (int j = 0; j < m_widgetVerticalCount; j++) {
			if (i < m_widgetHorizontalCount) {
				temp.at(static_cast<size_t>(j * m_widgetHorizontalCount + i)) = m_widgetItemVector.at(static_cast<size_t>(j * prevCount + i));
			} else {
				SAFEDELETENULL(m_widgetItemVector.at(static_cast<size_t>(j * prevCount + i)));
			}
		}
	}

	//设置新的保存item指针的空间
	m_widgetItemVector.swap(temp);
}

void CustomTable::SetVerticalCount(int count) {
	int i;

	//数量未变直接返回
	if (m_widgetVerticalCount == count) {
		return;
	}

	//保存以前的垂直个数，设置新的垂直个数
	int prevCount = m_widgetVerticalCount;
	m_widgetVerticalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//若水平个数或垂直个数为0，清空表返回
	if (itemCount == 0) {
		CleanAllData();
		return;
	}

	//分配新的保存item指针的空间
	std::vector<ICustomTableItem*> temp;
	for(i = 0; i < itemCount; i++) {
		temp.push_back(NULL);
	}

	//拷贝原有的还有用的数据
	for (int i = 0; i < m_widgetHorizontalCount; i++) {
		for (int j = 0; j < prevCount; j++) {
			if (j < m_widgetVerticalCount) {
				temp.at(static_cast<size_t>(j * m_widgetHorizontalCount + i)) = m_widgetItemVector.at(static_cast<size_t>(j * m_widgetHorizontalCount + i));
			} else {
				SAFEDELETENULL(m_widgetItemVector.at(static_cast<size_t>(j * m_widgetHorizontalCount + i)));
			}
		}
	}

	//设置新的保存item指针的空间
	m_widgetItemVector.swap(temp);
}

void CustomTable::SetData(int indexH, int indexV, void const *data) {
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0) {
		return;
	}

	//获取克隆体
	ICustomTableItem *itemPtr = m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH));
	//若无，则创建新的
	if (!itemPtr) {
		//克隆原型
		m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH)) = m_primaryItem->copy();
		m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH))->setParent(m_itemAreaWidget);

		//将克隆体移到对应位置
		QSize s = m_primaryItem->size();
		m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH))->move(indexH * s.width(), indexV * s.height());
	}

	//让克隆体自行绘制
	m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH))->draw(indexH, indexV, data);
}

void CustomTable::CleanData(int indexH, int indexV) {
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0) {
		return;
	}

	SAFEDELETENULL(m_widgetItemVector.at(static_cast<size_t>(indexV * m_widgetHorizontalCount + indexH)));
}

void CustomTable::CleanAllData() {
	for (int i = 0; i < m_widgetHorizontalCount; i++) {
		for (int j = 0; j < m_widgetVerticalCount; j++) {
			CleanData(i, j);
		}
	}
}
