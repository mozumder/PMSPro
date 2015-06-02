#include "TaskFields.h"

TaskFields::TaskFields(QWidget *parent) : QWidget(parent)
{
	// initialize data members
	_nameLabel = new QLabel(tr("Task Name:"));
	_startDateLabel = new QLabel(tr("Estimated Start Date:"));
	_endDateLabel = new QLabel(tr("Task End Date:"));
	_descriptionLabel = new QLabel(tr("Task Description:"));
	_creatorLabel = new QLabel(tr("Created by:"));
	_creationDateLabel = new QLabel(tr("Creation date:"));
	
	_creator = new QLineEdit;
	_creator->setReadOnly(true);
	_creationDate = new QDateTimeEdit;
	_creationDate->setReadOnly(true);
		
	_taskName = new QLineEdit;
	_taskStartDate = new QDateTimeEdit;
	_taskEndDate = new QDateTimeEdit;
	_taskDescription = new QTextEdit;
	
	_layout = new QGridLayout;
	
	/*
	 *  create layout	
	 */
	// add labels
	_layout->addWidget(_nameLabel, 0,0, Qt::AlignRight);
	_layout->addWidget(_startDateLabel, 1,0, Qt::AlignRight);
	//_layout->addWidget(_endDateLabel, 2,0, Qt::AlignRight);
	_layout->addWidget(_descriptionLabel, 0,2,1,2, Qt::AlignRight);
	_layout->addWidget(_creatorLabel, 2,0, Qt::AlignRight);
	_layout->addWidget(_creationDateLabel, 3,0, Qt::AlignRight);
	
	// add ui fields	
	_layout->addWidget(_taskName, 0,1);
	_layout->addWidget(_taskStartDate, 1,1);
	//_layout->addWidget(_taskEndDate, 2,1,1,2);
	_layout->addWidget(_taskDescription, 0,4,4,1, Qt::AlignRight);
	_layout->addWidget(_creator, 2,1);
	_layout->addWidget(_creationDate, 3,1,1,2);
	
	_layout->setColumnMinimumWidth(2,70);
	setLayout(_layout);
}
