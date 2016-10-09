#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QWidget>

class ICustomTableItem : public QWidget
{
	Q_OBJECT
public:
	ICustomTableItem(QWidget *parent = 0);
	virtual ~ICustomTableItem();

	virtual void draw(int indexH, int indexV, void const *data) = 0;
	virtual ICustomTableItem* copy() = 0;
};

class CustomTable : public QWidget
{
	Q_OBJECT
private:
	int m_widgetHorizontalCount;
	int m_widgetVerticalCount;
	ICustomTableItem *m_primaryItem;
	ICustomTableItem **m_widgetItemTable;

public:
	CustomTable(ICustomTableItem *item, QWidget *parent = 0);
	~CustomTable();

	void SetHorizontalCount(int count);
	void SetVerticalCount(int count);
	void SetData(int indexH, int indexV, void const *data);
	void CleanData(int indexH, int indexV);
	void CleanAllData();
};

#endif // CUSTOMTABLE_H
