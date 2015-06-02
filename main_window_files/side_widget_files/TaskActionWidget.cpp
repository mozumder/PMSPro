#include "TaskActionWidget.h"


#include <iostream>

using namespace std;

TaskActionWidget::TaskActionWidget(QWidget *parent) : QWidget(parent)
{
	// initialize data members
	_label = new QLabel(tr("Tasks:"));
	_newButton = new QPushButton("New");
	_editButton = new QPushButton("Edit");
	_deleteButton = new QPushButton("Delete");
	_displayField = new QListWidget;
	//_displayField->setSelectionMode(SingleSelection); // only one item allowed at a time
	_layout = new QGridLayout;
	
	// connect edit button with edit method
	connect(_editButton, SIGNAL(clicked()), this, SLOT(taskToEdit()));

	// create layout
	_layout->addWidget(_label, 0,0);
	_layout->addWidget(_displayField, 1,0,1,3);
	_layout->addWidget(_newButton, 2,0);
	_layout->addWidget(_editButton, 2,1);
	_layout->addWidget(_deleteButton, 2,2);
	setLayout(_layout);
}

TaskActionWidget::~TaskActionWidget()
{
}

void TaskActionWidget::drawList(QList<Task> taskList, QList<Resource> resourceList)

{
	_taskList = taskList;
	//_resourceList = resourceList;

	if(_resourceList.isEmpty())
	{
		//for(int i=0; i<_resourceList.size(); i++)
		//	_resourceList.removeFirst();
		for(int i=0; i < resourceList.size(); i++)
		{
			Resource r = resourceList.at(i);
			_resourceList.append(r);
		}
	}
	
	_displayField->clear();

	for(int i=0; i<_taskList.size(); i++)
		_taskList.removeFirst();
	for(int i=0; i<taskList.size(); i++)
	{
		Task t = taskList.at(i);
		_displayField->addItem(t.getName());
	}
	for(int i=taskList.size()-1; i >= 0; i--)
	{
		Task t = taskList.at(i);
		_taskList.prepend(t);
		//_taskList.append(t);
	}

}

/*
 * finds the currently selected task in the task list and emits it using the
 * edit task signal
 */
void TaskActionWidget::taskToEdit()
{
	// get the numerical position of the currently selected item;
	// it matches the position of the corresponding task in the task list
	int position = _displayField->currentRow();
	Task t = _taskList.at(position);
	emit editTaskSignal(t, _resourceList);
	
	
	/*
	// get the name of the currently selected item
	QListWidgetItem *item = _displayField->currentItem();
	QString *name = item->text();	
	
	// match it to an item in the list
	for(int i=0; i<taskList.size(); i++)
	{
		if name == taskList.at(i).getName
	}
	*/
}

/*
 * finds the currently selected task in the task list and emits it using the
 * remove task signal
 */
void TaskActionWidget::taskToDelete()
{
	// get the numerical position of the currently selected item;
	// it matches the position of the corresponding task in the task list
	int position = _displayField->currentRow();
	Task t = _taskList.at(position);
	//emit removeTaskSignal(t);
	int ID = t.getID();
	emit deletedIDSignal(ID);
	
}
