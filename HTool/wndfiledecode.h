#ifndef WNDFILEDECODE_H
#define WNDFILEDECODE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableView>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

#include <QFileDialog>

#include "common.h"

#include <iostream>

class FileListTableItem : public ICustomTableItem
{
	Q_OBJECT
private:
	QPushButton *pBtn;

public:
	FileListTableItem(QWidget *parent = 0);
	~FileListTableItem();

	virtual void draw(int indexH, int indexV, void const *data);
	virtual ICustomTableItem *copy();
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
	CustomTable *m_fileListTable;
	//-格式输入
	QWidget *m_fmtWidget;
	QHBoxLayout *m_fmtLayout;
	QLabel *m_fmtLabel;
	QComboBox *m_fmtComboBox;
	QPushButton *m_fmtOkBtn;

	int m_maxCount;

	QStringList fmtHistoryList;

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
