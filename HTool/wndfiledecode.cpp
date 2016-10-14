#include "wndfiledecode.h"

//------------------------------------------------------------------------FileListTableItem
FileListTableItem::FileListTableItem(QWidget *parent)
	: ICustomTableItem(parent) {
	pBtn = new QPushButton(this);
}

FileListTableItem::~FileListTableItem() {
	SAFEDELETE(pBtn);
}

void FileListTableItem::draw(int indexH, int indexV, const void *data) {
	UNUSED(indexH);
	UNUSED(indexV);

	pBtn->setText(*static_cast<QString const*>(data));
}

ICustomTableItem *FileListTableItem::copy() {
	ICustomTableItem *temp = new FileListTableItem();
	temp->setFixedSize(100, 50);
	return temp;
}

//------------------------------------------------------------------------WndFileDecode
WndFileDecode::WndFileDecode(QWidget *parent)
	: QWidget(parent) {
	CreateWidget();

	Show();

	BatchConnect();
}

WndFileDecode::~WndFileDecode() {
	BatchDisconnect();

	Hide();

	ReleaseWidget();
}

void WndFileDecode::CreateWidget() {
	m_mainLayout = new QVBoxLayout();
	m_fileInputWidget = new QWidget();
	m_fileInputLayout = new QHBoxLayout();
	m_fileInputOkBtn = new QPushButton();
	FileListTableItem itemTemp;
	m_fileListTable = new CustomTable(&itemTemp);
	m_fmtWidget = new QWidget();
	m_fmtLayout = new QHBoxLayout();
	m_fmtLabel = new QLabel();
	m_fmtComboBox = new QComboBox();
	m_fmtOkBtn = new QPushButton();
}

void WndFileDecode::ReleaseWidget() {
	SAFEDELETE(m_fmtOkBtn);
	SAFEDELETE(m_fmtComboBox);
	SAFEDELETE(m_fmtLabel);
	SAFEDELETE(m_fmtLayout);
	SAFEDELETE(m_fmtWidget);
	SAFEDELETE(m_fileListTable);
	SAFEDELETE(m_fileInputOkBtn);
	SAFEDELETE(m_fileInputLayout);
	SAFEDELETE(m_fileInputWidget);
	SAFEDELETE(m_mainLayout);
}

void WndFileDecode::BatchConnect() {
	connect(m_fileInputOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFileViewBtnClicked(bool)));
	connect(m_fmtOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFmtOkBtnClicked(bool)));
}

void WndFileDecode::BatchDisconnect() {
	disconnect(m_fmtOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFmtOkBtnClicked(bool)));
	disconnect(m_fileInputOkBtn, SIGNAL(clicked(bool)), this, SLOT(OnFileViewBtnClicked(bool)));
}

void WndFileDecode::Show() {
	this->setLayout(m_mainLayout);

	m_mainLayout->addWidget(m_fileInputWidget);
	m_mainLayout->addWidget(m_fileListTable);
	m_mainLayout->addWidget(m_fmtWidget);
	m_mainLayout->setMargin(0);

	m_fileInputWidget->setLayout(m_fileInputLayout);
	m_fileInputWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_fileInputLayout->addWidget(m_fileInputOkBtn);
	m_fileInputLayout->setAlignment(Qt::AlignRight);
	m_fileInputLayout->setMargin(0);

	m_fileInputOkBtn->setText("浏览");

	QString temp("aaaaaa");
	m_fileListTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_fileListTable->setMinimumSize(QSize(100, 100));
	m_fileListTable->SetHorizontalCount(5);
	m_fileListTable->SetVerticalCount(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			m_fileListTable->SetData(i, j, &temp);
		}
	}

	m_fmtWidget->setLayout(m_fmtLayout);
	m_fmtWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	m_fmtLayout->addWidget(m_fmtLabel);
	m_fmtLayout->addWidget(m_fmtComboBox);
	m_fmtLayout->setStretchFactor(m_fmtComboBox, 1);
	m_fmtLayout->addWidget(m_fmtOkBtn);
	m_fmtLayout->setMargin(0);

	m_fmtLabel->setText("格式文本：");

	m_fmtComboBox->setEditable(true);

	m_fmtOkBtn->setText("解析");
}

void WndFileDecode::Hide() {
}

void WndFileDecode::Update() {
}

void WndFileDecode::OnFileViewBtnClicked(bool) {

}

void WndFileDecode::OnFmtOkBtnClicked(bool) {
	if (fmtHistoryList.count() == m_maxCount) {
		fmtHistoryList.pop_back();
	}
	fmtHistoryList.push_front(m_fmtComboBox->currentText());

	m_fmtComboBox->clear();
	m_fmtComboBox->addItems(fmtHistoryList);
}
