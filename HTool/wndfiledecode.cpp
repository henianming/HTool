#include "wndfiledecode.h"

WndFileDecode::WndFileDecode(QWidget *parent)
	: QWidget(parent)
{
	m_maxCount = 5;

	CreateWidget();

	Show();

	BatchConnect();
}

WndFileDecode::~WndFileDecode()
{
	BatchDisconnect();

	Hide();

	ReleaseWidget();
}

void WndFileDecode::CreateWidget()
{
	m_mainLayout = new QVBoxLayout();
	m_fileInputWidget = new QWidget();
	m_fileInputLayout = new QHBoxLayout();
	m_fileInputOkBtn = new QPushButton();
	m_listTableView = new QTableView();
	m_fmtWidget = new QWidget();
	m_fmtLayout = new QHBoxLayout();
	m_fmtLabel = new QLabel();
	m_fmtComboBox = new QComboBox();
	m_fmtOkBtn = new QPushButton();
}

void WndFileDecode::ReleaseWidget()
{
	AutoDelete(m_fmtOkBtn);
	AutoDelete(m_fmtComboBox);
	AutoDelete(m_fmtLabel);
	AutoDelete(m_fmtLayout);
	AutoDelete(m_fmtWidget);
	AutoDelete(m_listTableView);
	AutoDelete(m_fileInputOkBtn);
	AutoDelete(m_fileInputLayout);
	AutoDelete(m_fileInputWidget);
	AutoDelete(m_mainLayout);
}

void WndFileDecode::BatchConnect()
{
	connect(m_fileInputOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFileViewBtnClicked(bool)));
	connect(m_fmtOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFmtOkBtnClicked(bool)));
}

void WndFileDecode::BatchDisconnect()
{
	disconnect(m_fmtOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFmtOkBtnClicked(bool)));
	disconnect(m_fileInputOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFileViewBtnClicked(bool)));
}

void WndFileDecode::Show()
{
	this->setLayout(m_mainLayout);

	m_mainLayout->addWidget(m_fileInputWidget);
	m_mainLayout->addWidget(m_listTableView);
	m_mainLayout->addWidget(m_fmtWidget);
	m_mainLayout->setMargin(0);

	m_fileInputWidget->setLayout(m_fileInputLayout);

	m_fileInputLayout->addWidget(m_fileInputOkBtn);
	m_fileInputLayout->setMargin(0);

	m_fileInputOkBtn->setText("浏览");

	m_fmtWidget->setLayout(m_fmtLayout);

	m_fmtLayout->addWidget(m_fmtLabel);
	m_fmtLayout->addWidget(m_fmtComboBox);
	m_fmtLayout->setStretchFactor(m_fmtComboBox, 1);
	m_fmtLayout->addWidget(m_fmtOkBtn);
	m_fmtLayout->setMargin(0);

	m_fmtLabel->setText("格式文本：");

	m_fmtComboBox->setEditable(true);

	m_fmtOkBtn->setText("解析");
}

void WndFileDecode::Hide()
{
}

void WndFileDecode::Update()
{
}

void WndFileDecode::OnFileViewBtnClicked(bool)
{

}

void WndFileDecode::OnFmtOkBtnClicked(bool)
{
	if (fmtHistoryList.count() == m_maxCount)
	{
		fmtHistoryList.pop_back();
	}
	fmtHistoryList.push_front(m_fmtComboBox->currentText());

	m_fmtComboBox->clear();
	m_fmtComboBox->addItems(fmtHistoryList);
}

QWidget *CustomItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QWidget *m = new QWidget(parent);
	QVBoxLayout *vl = new QVBoxLayout(m);
	QPushButton *b1 = new QPushButton(m);
	QPushButton *b2 = new QPushButton(m);

	m->setLayout(vl);

	vl->addWidget(b1);
	vl->addWidget(b2);
	vl->setMargin(0);

	return m;
}

/*
void CustomItemDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{

}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}

void CustomItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

}
*/
