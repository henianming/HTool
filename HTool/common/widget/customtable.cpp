#include "customtable.h"

#include <stdlib.h>
#include "common.h"

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
	//����δ��ֱ�ӷ���
	if (m_widgetHorizontalCount == count)
	{
		return;
	}

	//������ǰ��ˮƽ�����������µ�ˮƽ����
	int prevCount = m_widgetHorizontalCount;
	m_widgetHorizontalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//��ˮƽ������ֱ����Ϊ0����ձ���
	if (itemCount == 0)
	{
		CleanAllData();
		return;
	}

	//�����µı���itemָ��Ŀռ�
	ICustomTableItem **temp = (ICustomTableItem**)calloc(itemCount, sizeof(ICustomTableItem*));

	//����ԭ�еĻ����õ�����
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
					//�Ƴ�item
					delete *(m_widgetItemTable + j * prevCount + i);
				}
			}
		}
	}

	//�ͷ�ԭ���ı���itemָ��Ŀռ�
	free(m_widgetItemTable);

	//�����µı���itemָ��Ŀռ�
	m_widgetItemTable = temp;
}

void CustomTable::SetVerticalCount(int count)
{
	//����δ��ֱ�ӷ���
	if (m_widgetVerticalCount == count)
	{
		return;
	}

	//������ǰ�Ĵ�ֱ�����������µĴ�ֱ����
	int prevCount = m_widgetVerticalCount;
	m_widgetVerticalCount = count;

	int itemCount = m_widgetHorizontalCount * m_widgetVerticalCount;
	//��ˮƽ������ֱ����Ϊ0����ձ���
	if (itemCount == 0)
	{
		CleanAllData();
		return;
	}

	//�����µı���itemָ��Ŀռ�
	ICustomTableItem **temp = (ICustomTableItem**)calloc(itemCount, sizeof(ICustomTableItem*));

	//����ԭ�еĻ����õ�����
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
					//�Ƴ�item
					delete *(m_widgetItemTable + j * m_widgetHorizontalCount + i);
				}
			}
		}
	}

	//�ͷ�ԭ���ı���itemָ��Ŀռ�
	free(m_widgetItemTable);

	//�����µı���itemָ��Ŀռ�
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
		SetWidgetBackgroundColor(*itemPtr, QColor(indexH % 25 * 10, indexV % 25 * 10, 0));

		QSize s = m_primaryItem->size();
		(*itemPtr)->move(indexH * s.width(), indexV * s.height());
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
