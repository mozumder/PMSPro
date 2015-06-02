#include "SideWidget.h"
#include "MilestoneActionWidget.h"
#include "TaskActionWidget.h"

SideWidget::SideWidget(QWidget *parent) : QWidget(parent)
{
	// initialize data members
	_milestoneActionWidget = new MilestoneActionWidget();
	_taskActionWidget = new TaskActionWidget();
	_resourceActionWidget = new ResourceActionWidget();
	_layout = new QGridLayout;
	
	// create layout
	_layout->addWidget(_milestoneActionWidget, 0,0);
	_layout->addWidget(_taskActionWidget, 1,0);
	_layout->addWidget(_resourceActionWidget, 2,0);
	setLayout(_layout);
}

SideWidget::~SideWidget()
{
}
