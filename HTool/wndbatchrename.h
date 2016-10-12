#ifndef WNDBATCHRENAME_H
#define WNDBATCHRENAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class WndBatchRename : public QWidget
{
	Q_OBJECT
public:
	
protected:
	
private:
	int const m_wndDefWidth = 1280;
	int const m_wndDefHeight = 720;
	
	//�ؼ���
	//������
	QVBoxLayout *m_mainLayout;
	//-�Ա�����
	QWidget *m_compareAreaWidget;
	QHBoxLayout *m_compareAreaLayout;
	//--��Ա�����------------------------------------׼������
	QWidget *m_compareAreaLeftWidget;
	QVBoxLayout *m_compareAreaLeftLayout;
	//--�м������
	QWidget *m_controlAreaWidget;
	QVBoxLayout *m_controlAreaLayout;
	QPushButton *m_l2rBtn;
	QPushButton *m_r2lBtn;
	//--�ҶԱ�����------------------------------------׼������
	QWidget *m_compareAreaRightWidget;
	QVBoxLayout *m_compareAreaRightLayout;

public:
	WndBatchRename(QWidget *parent = 0);
	~WndBatchRename();
	void Show();
	void Hide();
	void Update();
	
protected:
	
private:

};

#endif // WNDBATCHRENAME_H
