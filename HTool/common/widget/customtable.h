#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QWidget>
#include <QScrollArea>
#include <vector>

class ICustomTableItem : public QWidget {
	Q_OBJECT
public:
	ICustomTableItem(QWidget *parent = 0);
	virtual ~ICustomTableItem();

	virtual void draw(int indexH, int indexV, void const *data) = 0;
	virtual ICustomTableItem* copy() = 0;
};

class CustomTable : public QScrollArea {
	Q_OBJECT
private:
	QWidget *m_itemAreaWidget;

	int m_widgetHorizontalCount;
	int m_widgetVerticalCount;
	ICustomTableItem *m_primaryItem;
	//ICustomTableItem **m_widgetItemTable;
	std::vector<ICustomTableItem*> m_widgetItemVector;

public:
	CustomTable(ICustomTableItem *item, QWidget *parent = 0);
	~CustomTable();
	void CreateWidget();
	void ReleaseWidget();
	void BatchConnect();
	void BatchDisconnect();
	void Show();
	void Hide();
	void Update();

	void SetHorizontalCount(int count);
	void SetVerticalCount(int count);
	void SetData(int indexH, int indexV, void const *data);
	void CleanData(int indexH, int indexV);
	void CleanAllData();
};

#endif // CUSTOMTABLE_H
