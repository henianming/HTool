#include "customtable.h"

#include <stdlib.h>
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

	m_widgetItemTable = NULL;

	CreateWidget();

	Show();
}

CustomTable::~CustomTable() {
	Hide();

	ReleaseWidget();

	CleanAllData();
	SAFEDELETE(m_widgetItemTable);

	SAFEDELETE(m_primaryItem);
}

void CustomTable::CreateWidget()
{
	m_itemAreaWidget = new QWidget(this);
}

void CustomTable::ReleaseWidget()
{
	SAFEDELETE(m_itemAreaWidget);
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
	ICustomTableItem **temp = static_cast<ICustomTableItem**>(calloc(static_cast<size_t>(itemCount), sizeof(ICustomTableItem*)));

	//拷贝原有的还有用的数据
	for (int i = 0; i < prevCount; i++) {
		for (int j = 0; j < m_widgetVerticalCount; j++) {
			if (i < m_widgetHorizontalCount) {
				*(temp + j * m_widgetHorizontalCount + i) = *(m_widgetItemTable + j * prevCount + i);
			} else {
				SAFEDELETE(*(m_widgetItemTable + j * prevCount + i));
			}
		}
	}

	//释放原来的保存item指针的空间
	free(m_widgetItemTable);

	//设置新的保存item指针的空间
	m_widgetItemTable = temp;
}

void CustomTable::SetVerticalCount(int count) {
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
	ICustomTableItem **temp = static_cast<ICustomTableItem**>(calloc(static_cast<size_t>(itemCount), sizeof(ICustomTableItem*)));

	//拷贝原有的还有用的数据
	for (int i = 0; i < m_widgetHorizontalCount; i++) {
		for (int j = 0; j < prevCount; j++) {
			if (j < m_widgetVerticalCount) {
				*(temp + j * m_widgetHorizontalCount + i) = *(m_widgetItemTable + j * m_widgetHorizontalCount + i);
			} else {
				SAFEDELETE(*(m_widgetItemTable + j * m_widgetHorizontalCount + i));
			}
		}
	}

	//释放原来的保存item指针的空间
	free(m_widgetItemTable);

	//设置新的保存item指针的空间
	m_widgetItemTable = temp;
}

void CustomTable::SetData(int indexH, int indexV, void const *data) {
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0) {
		return;
	}

	//获取克隆体
	ICustomTableItem **itemPtr = m_widgetItemTable + indexV * m_widgetHorizontalCount + indexH;
	//若无，则创建新的
	if (!(*itemPtr)) {
		//克隆原型
		*itemPtr = m_primaryItem->copy();
		(*itemPtr)->setParent(m_itemAreaWidget);

		//将克隆体移到对应位置
		QSize s = m_primaryItem->size();
		(*itemPtr)->move(indexH * s.width(), indexV * s.height());
	}

	//让克隆体自行绘制
	(*itemPtr)->draw(indexH, indexV, data);
}

void CustomTable::CleanData(int indexH, int indexV) {
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0) {
		return;
	}

	ICustomTableItem **itemPtr = m_widgetItemTable + indexV * m_widgetHorizontalCount + indexH;
	SAFEDELETENULL(*itemPtr);
}

void CustomTable::CleanAllData() {
	for (int i = 0; i < m_widgetHorizontalCount; i++) {
		for (int j = 0; j < m_widgetVerticalCount; j++) {
			CleanData(i, j);
		}
	}
}
