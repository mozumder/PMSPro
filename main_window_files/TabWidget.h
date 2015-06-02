#ifndef TABWIDGET_H_
#define TABWIDGET_H_

#include <QTabWidget>
#include <QWidget>
#include "../side_widget_files/SideWidget.h"
#include "../tab_files/task_tab_files/TaskTab.h"
#include "../tab_files/list_tab_files/ListTab.h"
#include "../tab_files/resource_tab_files/ResourceTab.h"
#include "../tab_files/milestone_tab_files/MilestoneTab.h"
/*
	This is the tab menu widget for the main window.
*/

class TabWidget : public QTabWidget
{
	Q_OBJECT
	
	public:
		TabWidget(QWidget *parent = 0);
			
	private:
//		ListTab *listTab;
		SideWidget *_sideWidget;
		TaskTab *taskTab;
		ResourceTab *resourceTab;
		MilestoneTab *milestoneTab;

	public slots:
		void showTaskTab();
		void showMilestoneTab();
		void showResourceTab();
	
	friend class MainWindow;
	friend class Kernel;
};

#endif
