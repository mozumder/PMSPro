#ifndef SIDEWIDGET_H_
#define SIDEWIDGET_H_

#include <QWidget>
#include <QGridLayout>

class MilestoneActionWidget;
class TaskActionWidget;
#include "ResourceActionWidget.h"

/*
 * This is the parent widget for the menus which appear on the left side
 * of the screen.  It includes child widgets for Task and Milestone actions.
 */

class SideWidget: public QWidget
{
	Q_OBJECT
	
	public:
		
		SideWidget(QWidget *parent = 0);
		virtual ~SideWidget();
		
	private:	
		//rep
		MilestoneActionWidget *_milestoneActionWidget;
		TaskActionWidget *_taskActionWidget;
		ResourceActionWidget *_resourceActionWidget;
		QGridLayout *_layout;

	friend class Kernel;
};

#endif /*SIDEWIDGET_H_*/
