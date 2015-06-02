#include "SearchWidget.h"

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
	searchInput = new QLineEdit(tr("Type search stuff here"));
	searchButton = new QPushButton(tr("Search"));
	searchLayout = new QHBoxLayout;
	
	searchLayout->addWidget(searchInput);
	searchLayout->addWidget(searchButton);
	
	setFixedWidth(275);	
	setLayout(searchLayout);
	//show();
}
