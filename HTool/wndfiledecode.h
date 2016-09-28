#ifndef WNDFILEDECODE_H
#define WNDFILEDECODE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include <QFileDialog>
#include <QItemDelegate>
#include <QStandardItemModel>

#include <iostream>

#define AutoDelete(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = nullptr; \
	} \
}while(0)

class CustomItemDelegate : public QItemDelegate
{
	Q_OBJECT
private:


public:
	virtual QWidget *createEditor(QWidget *parent,
								  const QStyleOptionViewItem &option,
								  const QModelIndex &index) const;

	/*
	virtual void destroyEditor(QWidget *editor, const QModelIndex &index) const;

	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

	virtual void setModelData(QWidget *editor,
							  QAbstractItemModel *model,
							  const QModelIndex &index) const;

	virtual void updateEditorGeometry(QWidget *editor,
									  const QStyleOptionViewItem &option,
									  const QModelIndex &index) const;
									  */
};

class CustonModel : public QStandardItemModel
{
	Q_OBJECT
public:
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

class WndFileDecode : public QWidget
{
	Q_OBJECT
public:
	
protected:
	
private:
	//控件区
	//主布局
	QVBoxLayout *m_mainLayout;
	//-文件输入
	QWidget *m_fileInputWidget;
	QHBoxLayout *m_fileInputLayout;
	QPushButton *m_fileInputOkBtn;
	//-列表控制
	QTableView *m_listTableView;
	//-格式输入
	QWidget *m_fmtWidget;
	QHBoxLayout *m_fmtLayout;
	QLabel *m_fmtLabel;
	QComboBox *m_fmtComboBox;
	QPushButton *m_fmtOkBtn;

	int m_maxCount;

	QStringList fmtHistoryList;
	CustomItemDelegate *cid;

public:
	WndFileDecode(QWidget *parent = 0);
	~WndFileDecode();
	void CreateWidget();
	void ReleaseWidget();
	void BatchConnect();
	void BatchDisconnect();
	void Show();
	void Hide();
	void Update();
	
protected:
	
private:


private slots:
	void OnFileViewBtnClicked(bool);
	void OnFmtOkBtnClicked(bool);
	
};

#endif // WNDFILEDECODE_H
