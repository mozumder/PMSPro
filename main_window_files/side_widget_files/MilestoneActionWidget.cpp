#include "MilestoneActionWidget.h"

MilestoneActionWidget::MilestoneActionWidget(QWidget *parent) : QWidget(parent)
{
	// initialize data members
	_label = new QLabel(tr("Milestones:"));
	_newButton = new QPushButton("New");
	_editButton = new QPushButton("Edit");
	_deleteButton = new QPushButton("Delete");
	_displayField = new QListWidget;
	_layout = new QGridLayout;
	
	// create layout
	_layout->addWidget(_label, 0,0);
	_layout->addWidget(_displayField, 1,0,1,3);
	_layout->addWidget(_newButton, 2,0);
	_layout->addWidget(_editButton, 2,1);
	_layout->addWidget(_deleteButton, 2,2);
	setLayout(_layout);
}

MilestoneActionWidget::~MilestoneActionWidget()
{
}

void MilestoneActionWidget::drawList(QList<Milestone> milestoneList)
{
	_displayField->clear();

	for(int i=0; i<_milestoneList.size(); i++)
		_milestoneList.removeFirst();

	for(int i=0; i<milestoneList.size(); i++)
	{
		Milestone m = milestoneList.at(i);
		_displayField->addItem(m.getName());
	}
	for(int i=milestoneList.size()-1; i >= 0; i--)
	{
		Milestone m = milestoneList.at(i);
		_milestoneList.prepend(m);
	}
}

/*
 * finds the currently selected task in the task list and emits it using the
 * edit task signal
 */
void MilestoneActionWidget::milestoneToEdit()
{
	// get the numerical position of the currently selected item;
	// it matches the position of the corresponding milestone in the milestone list
	int position = _displayField->currentRow();
	Milestone m = _milestoneList.at(position);
	emit editMilestoneSignal(m);
	
	/*
	// get the name of the currently selected item
	QListWidgetItem *item = _displayField->currentItem();
	QString *name = item->text();	
	
	// match it to an item in the list
	for(int i=0; i<milestoneList.size(); i++)
	{
		if name == milestoneList.at(i).getName
	}
	*/
}

/*
 * finds the currently selected task in the task list and emits it using the
 * remove task signal
 */
void MilestoneActionWidget::milestoneToDelete()
{
	// get the numerical position of the currently selected item;
	// it matches the position of the corresponding milestone in the milestone list
	int position = _displayField->currentRow();
	Milestone m = _milestoneList.at(position);
//	emit removeMilestoneSignal(m);
	int ID = m.getID();
	emit deletedIDSignal(ID);
	
	
}

