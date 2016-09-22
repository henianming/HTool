#ifndef WNDBATCHRENAME_H
#define WNDBATCHRENAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTableView>

class WndBatchRename : public QWidget
{
	Q_OBJECT
private:
	int const m_wndDefWidth = 1280;
	int const m_wndDefHeight = 720;

public:
	WndBatchRename(QWidget *parent = 0);
	~WndBatchRename();
	void Show();
	void Hide();
	void Update();

	//控件区
	//主布局
	QVBoxLayout *m_mainLayout;
	//-对比区域
	QWidget *m_compareAreaWidget;
	QHBoxLayout *m_compareAreaLayout;
	//--左对比区域
	QWidget *m_compareAreaLeftWidget;
	QVBoxLayout *m_compareAreaLeftLayout;
	//---左对比区域列表框
	QTableView *m_listLeftTableView;
	//---左对比区域格式输入框
	QLineEdit *m_fmtLeftLineEdit;
	//--中间控制区
	QWidget *m_controlAreaWidget;
	QVBoxLayout *m_controlAreaLayout;
	//--右对比区域
	QWidget *m_compareAreaRightWidget;
	QVBoxLayout *m_compareAreaRightLayout;
	//---右对比区域列表框
	QTableView *m_listRightTableView;
	//---右对比区域格式输入框
	QLineEdit *m_fmtRightLineEdit;
};

#endif // WNDBATCHRENAME_H
