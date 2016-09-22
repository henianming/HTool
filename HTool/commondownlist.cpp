#include "commondownlist.h"

CommonDownList::CommonDownList(QWidget *parent)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout();
	m_editAreaWidget = new QWidget();
	m_editAreaLayout = new QHBoxLayout();
	m_lineEdit = new QLineEdit();
	m_pushButton = new QPushButton();
	//m_listView = new QListView();

	Show();
}

CommonDownList::~CommonDownList()
{
	//if (m_listView) {delete m_listView; m_listView = NULL;}
	if (m_pushButton) {delete m_pushButton; m_pushButton = NULL;}
	if (m_lineEdit) {delete m_lineEdit; m_lineEdit = NULL;}
	if (m_editAreaLayout) {delete m_editAreaLayout; m_editAreaLayout = NULL;}
	if (m_editAreaWidget) {delete m_editAreaWidget; m_editAreaWidget = NULL;}
	if (m_mainLayout) {delete m_mainLayout; m_mainLayout = NULL;}
}

void CommonDownList::Show()
{
	this->setLayout(m_mainLayout);

	m_mainLayout->addWidget(m_editAreaWidget);
	//m_mainLayout->addWidget(m_listView);

	m_editAreaWidget->setLayout(m_editAreaLayout);

	m_editAreaLayout->addWidget(m_lineEdit);
	//m_editAreaLayout->addWidget(m_pushButton);

	connect(m_pushButton, SIGNAL(clicked(bool)), this, SLOT(bool));
}

void CommonDownList::Hide()
{

}
/*
void CommonDownList::onBtnClicked(bool b)
{
	if (b)
	{
		std::cout << "true" << std::endl;
	}
	else
	{
		std::cout << "false" << std::endl;
	}
}*/
