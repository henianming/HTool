#ifndef COMMON_DOWNLIST_H
#define COMMON_DOWNLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListView>

#include <iostream>

class CommonDownList : public QWidget
{
	Q_OBJECT
private:
	bool m_isListVisible;

public:
	CommonDownList(QWidget *parent = 0);
	~CommonDownList();
	void Show();
	void Hide();

	QVBoxLayout *m_mainLayout;
	QWidget *m_editAreaWidget;
	QHBoxLayout *m_editAreaLayout;
	QLineEdit *m_lineEdit;
	QPushButton *m_pushButton;
	QListView *m_listView;
/*
private slots:
	void onBtnClicked(bool b);*/
};

#endif // COMMON_DOWNLIST_H
