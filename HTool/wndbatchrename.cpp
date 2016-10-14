#include "wndbatchrename.h"

WndBatchRename::WndBatchRename(QWidget *parent)
	: QWidget(parent) {
	m_mainLayout = new QVBoxLayout();
	m_compareAreaWidget = new QWidget();
	m_compareAreaLayout = new QHBoxLayout();
	m_compareAreaLeftWidget = new QWidget();
	m_compareAreaLeftLayout = new QVBoxLayout();
	m_controlAreaWidget = new QWidget();
	m_controlAreaLayout = new QVBoxLayout();
	m_l2rBtn = new QPushButton();
	m_r2lBtn = new QPushButton();
	m_compareAreaRightWidget = new QWidget();
	m_compareAreaRightLayout = new QVBoxLayout();

	Show();
}

WndBatchRename::~WndBatchRename() {
	if (m_compareAreaRightLayout) {
		delete m_compareAreaRightLayout; m_compareAreaRightLayout = NULL;
	}
	if (m_compareAreaRightWidget) {
		delete m_compareAreaRightWidget; m_compareAreaRightWidget = NULL;
	}
	if (m_r2lBtn) {
		delete m_r2lBtn; m_r2lBtn = NULL;
	}
	if (m_l2rBtn) {
		delete m_l2rBtn; m_l2rBtn = NULL;
	}
	if (m_controlAreaLayout) {
		delete m_controlAreaLayout; m_controlAreaLayout = NULL;
	}
	if (m_controlAreaWidget) {
		delete m_controlAreaWidget; m_controlAreaWidget = NULL;
	}
	if (m_compareAreaLeftLayout) {
		delete m_compareAreaLeftLayout; m_compareAreaLeftLayout = NULL;
	}
	if (m_compareAreaLeftWidget) {
		delete m_compareAreaLeftWidget; m_compareAreaLeftWidget = NULL;
	}
	if (m_compareAreaLayout) {
		delete m_compareAreaLayout; m_compareAreaLayout = NULL;
	}
	if (m_compareAreaWidget) {
		delete m_compareAreaWidget; m_compareAreaWidget = NULL;
	}
	if (m_mainLayout) {
		delete m_mainLayout; m_mainLayout = NULL;
	}
}

void WndBatchRename::Show() {
	this->setWindowTitle("工具包");
	this->resize(m_wndDefWidth, m_wndDefHeight);
	this->setLayout(m_mainLayout);

	m_mainLayout->addWidget(m_compareAreaWidget);

	m_compareAreaWidget->setLayout(m_compareAreaLayout);

	m_compareAreaLayout->addWidget(m_compareAreaLeftWidget);
	m_compareAreaLayout->addWidget(m_controlAreaWidget);
	m_compareAreaLayout->addWidget(m_compareAreaRightWidget);

	m_compareAreaLeftWidget->setLayout(m_compareAreaLeftLayout);

	m_controlAreaWidget->setLayout(m_controlAreaLayout);

	m_controlAreaLayout->addWidget(m_l2rBtn);
	m_controlAreaLayout->addWidget(m_r2lBtn);

	m_l2rBtn->setText("->");

	m_r2lBtn->setText("<-");

	m_compareAreaRightWidget->setLayout(m_compareAreaRightLayout);
}

void WndBatchRename::Hide() {
}

void WndBatchRename::Update() {
}
