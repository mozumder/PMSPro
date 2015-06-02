#include "FilterButtonWidget.h"

FilterButtonWidget::FilterButtonWidget(QWidget *parent) : QWidget(parent)
{
	clearFiltersButton = new QPushButton(tr("Clear Filters"));
	advancedFilterButton = new QPushButton(tr("Advanced Filter"));
	
	filterLayout = new QVBoxLayout;
	filterLayout->addWidget(clearFiltersButton);
	filterLayout->addWidget(advancedFilterButton);
	
	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	//setFixedWidth(75);
	setLayout(filterLayout);
	show();
}
