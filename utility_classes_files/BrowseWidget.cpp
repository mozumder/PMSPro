#include "BrowseWidget.h"

BrowseWidget::BrowseWidget(QWidget *parent) : QWidget(parent)
{
	browseInput = new QLineEdit;
	browseButton = new QPushButton(tr("Browse..."));
	browseLayout = new QHBoxLayout;
	
	browseLayout->addWidget(browseInput);
	browseLayout->addWidget(browseButton);
	
	setFixedWidth(275);	
	
	setLayout(browseLayout);
	//show();
}
