#include "customtable.h"

#include <stdlib.h>

CustomTable::CustomTable(ICustomTableItem *item, QWidget *parent)
	: QWidget(parent)
{
	m_primaryItem = item->copy();

	m_widgetHorizontalCount = 0;
	m_widgetVerticalCount = 0;
	m_widgetItemTable = NULL;
}

CustomTable::~CustomTable()
{
	if (m_widgetItemTable) free(m_widgetItemTable);
	if (m_primaryItem) free(m_primaryItem);
}

void CustomTable::SetHorizontalCount(int count)
{
	//数量未变直接返回
	if (m_widgetHorizontalCount == count)
	{
		return;
	}

	//保存以前的水平个数，设置新的水平个数
	int prevCount = m_widgetHorizontalCount;
	m_widgetHorizontalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//若水平个数或垂直个数为0，清空表返回
	if (itemCount == 0)
	{
		CleanAllData();
		return;
	}

	//分配新的保存item指针的空间
	ICustomTableItem **temp = (ICustomTableItem**)calloc(itemCount, sizeof(ICustomTableItem*));

	//拷贝原有的还有用的数据
	for (int i = 0; i < prevCount; i++)
	{
		for (int j = 0; j < m_widgetVerticalCount; j++)
		{
			if (i < m_widgetHorizontalCount)
			{
				*(temp + j * m_widgetHorizontalCount + i) = *(m_widgetItemTable + j * prevCount + i);
			}
			else
			{
				if (*(m_widgetItemTable + j * prevCount + i))
				{
					//移除item
					delete *(m_widgetItemTable + j * prevCount + i);
				}
			}
		}
	}

	//释放原来的保存item指针的空间
	free(m_widgetItemTable);

	//设置新的保存item指针的空间
	m_widgetItemTable = temp;
}

void CustomTable::SetVerticalCount(int count)
{
	//数量未变直接返回
	if (m_widgetVerticalCount == count)
	{
		return;
	}

	//保存以前的垂直个数，设置新的垂直个数
	int prevCount = m_widgetVerticalCount;
	m_widgetVerticalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//若水平个数或垂直个数为0，清空表返回
	if (itemCount == 0)
	{
		CleanAllData();
		return;
	}

	//分配新的保存item指针的空间
	ICustomTableItem **temp = (ICustomTableItem**)calloc(itemCount, sizeof(ICustomTableItem*));

	//拷贝原有的还有用的数据
	for (int i = 0; i < m_widgetHorizontalCount; i++)
	{
		for (int j = 0; j < prevCount; j++)
		{
			if (j < m_widgetVerticalCount)
			{
				*(temp + j * m_widgetHorizontalCount + i) = *(m_widgetItemTable + j * m_widgetHorizontalCount + i);
			}
			else
			{
				if (*(m_widgetItemTable + j * m_widgetHorizontalCount + i))
				{
					//移除item
					delete *(m_widgetItemTable + j * m_widgetHorizontalCount + i);
				}
			}
		}
	}

	//释放原来的保存item指针的空间
	free(m_widgetItemTable);

	//设置新的保存item指针的空间
	m_widgetItemTable = temp;
}

void CustomTable::SetData(int indexH, int indexV, void const *data)
{
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0)
	{
		return;
	}

	ICustomTableItem **itemPtr = m_widgetItemTable + indexV * m_widgetHorizontalCount + indexH;
	if (!(*itemPtr))
	{
		*itemPtr = m_primaryItem->copy();
		(*itemPtr)->setParent(this);
	}

	(*itemPtr)->draw(indexH, indexV, data);
}

void CustomTable::CleanData(int indexH, int indexV)
{
	if (indexH >= m_widgetHorizontalCount
		|| indexH < 0
		|| indexV >= m_widgetVerticalCount
		|| indexV < 0)
	{
		return;
	}

	ICustomTableItem **itemPtr = m_widgetItemTable + indexV * m_widgetHorizontalCount + indexH;
	if (*itemPtr)
	{
		delete *itemPtr;
		*itemPtr = NULL;
	}
}

void CustomTable::CleanAllData()
{
	for (int i = 0; i < m_widgetHorizontalCount; i++)
	{
		for (int j = 0; j < m_widgetVerticalCount; j++)
		{
			CleanData(i, j);
		}
	}
}
