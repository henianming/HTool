#include "wndbatchrename.h"

WndBatchRename::WndBatchRename(QWidget *parent)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout();
	m_compareAreaWidget = new QWidget();
	m_compareAreaLayout = new QHBoxLayout();
	m_compareAreaLeftWidget = new QWidget();
	m_compareAreaLeftLayout = new QVBoxLayout();
	m_listLeftTableView = new QTableView();
	m_fmtLeftLineEdit = new QLineEdit();
	m_controlAreaWidget = new QWidget();
	m_controlAreaLayout = new QVBoxLayout();
	m_compareAreaRightWidget = new QWidget();
	m_compareAreaRightLayout = new QVBoxLayout();
	m_listRightTableView = new QTableView();
	m_fmtRightLineEdit = new QLineEdit();

	Show();
}

WndBatchRename::~WndBatchRename()
{
	if (m_fmtRightLineEdit) {delete m_fmtRightLineEdit; m_fmtRightLineEdit = NULL;}
	if (m_listRightTableView) {delete m_listRightTableView; m_listRightTableView = NULL;}
	if (m_compareAreaRightLayout) {delete m_compareAreaRightLayout; m_compareAreaRightLayout = NULL;}
	if (m_compareAreaRightWidget) {delete m_compareAreaRightWidget; m_compareAreaRightWidget = NULL;}
	if (m_controlAreaLayout) {delete m_controlAreaLayout; m_controlAreaLayout = NULL;}
	if (m_controlAreaWidget) {delete m_controlAreaWidget; m_controlAreaWidget = NULL;}
	if (m_fmtLeftLineEdit) {delete m_fmtLeftLineEdit; m_fmtLeftLineEdit = NULL;}
	if (m_listLeftTableView) {delete m_listLeftTableView; m_listLeftTableView = NULL;}
	if (m_compareAreaLeftLayout) {delete m_compareAreaLeftLayout; m_compareAreaLeftLayout = NULL;}
	if (m_compareAreaLeftWidget) {delete m_compareAreaLeftWidget; m_compareAreaLeftWidget = NULL;}
	if (m_compareAreaLayout) {delete m_compareAreaLayout; m_compareAreaLayout = NULL;}
	if (m_compareAreaWidget) {delete m_compareAreaWidget; m_compareAreaWidget = NULL;}
	if (m_mainLayout) {delete m_mainLayout; m_mainLayout = NULL;}
}

void WndBatchRename::Show()
{
	this->setWindowTitle("工具包");
	this->resize(m_wndDefWidth, m_wndDefHeight);
	this->setLayout(m_mainLayout);

	m_mainLayout->addWidget(m_compareAreaWidget);

	m_compareAreaWidget->setLayout(m_compareAreaLayout);

	m_compareAreaLayout->addWidget(m_compareAreaLeftWidget);
	m_compareAreaLayout->addWidget(m_controlAreaWidget);
	m_compareAreaLayout->addWidget(m_compareAreaRightWidget);

	m_compareAreaLeftWidget->setLayout(m_compareAreaLeftLayout);

	m_compareAreaLeftLayout->addWidget(m_listLeftTableView);
	m_compareAreaLeftLayout->addWidget(m_fmtLeftLineEdit);

	m_controlAreaWidget->setLayout(m_controlAreaLayout);

	m_compareAreaRightWidget->setLayout(m_compareAreaRightLayout);

	m_compareAreaRightLayout->addWidget(m_listRightTableView);
	m_compareAreaRightLayout->addWidget(m_fmtRightLineEdit);
}

void WndBatchRename::Hide()
{
}

void WndBatchRename::Update()
{
}
