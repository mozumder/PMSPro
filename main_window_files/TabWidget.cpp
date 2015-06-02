#include "TabWidget.h"

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
	taskTab = new TaskTab();
//	listTab = new ListTab();
	resourceTab = new ResourceTab();
	milestoneTab = new MilestoneTab();	
    	_sideWidget = new SideWidget();
	
	addTab(_sideWidget, tr("List View"));
	addTab(taskTab, tr("Task View"));
	addTab(resourceTab, tr("Resource View"));
	addTab(milestoneTab, tr("Milestone View"));
	
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void TabWidget::showTaskTab()
{
	setCurrentWidget(taskTab);
}

void TabWidget::showMilestoneTab()
{
	setCurrentWidget(milestoneTab);
}

void TabWidget::showResourceTab()
{
	setCurrentWidget(resourceTab);
}
