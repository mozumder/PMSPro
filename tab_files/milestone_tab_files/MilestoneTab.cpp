#include "MilestoneTab.h"

/*
 * default constructor.
 * provided for testing purposes only.
 */
MilestoneTab::MilestoneTab(QWidget *parent) : QWidget(parent)
{
	// initialize data members	
	_nameLabel = new QLabel(tr("Milestone Name:"));
	_deadlineLabel = new QLabel(tr("Milestone Deadline:"));
	_nameField = new QLineEdit;
	_deadlineField = new QDateTimeEdit;
	_updateMilestoneButton = new QPushButton(tr("Update Milestone"));
	_workLog = new WorkLog();
	_layout = new QGridLayout;
	
	// create layout
	_layout->addWidget(_nameLabel, 0,0, Qt::AlignRight);
	_layout->addWidget(_nameField, 0,1);
	_layout->addWidget(_deadlineLabel, 1,0, Qt::AlignRight);
	_layout->addWidget(_deadlineField, 1,1);
	_layout->addWidget(_updateMilestoneButton, 2,1,1,2);
	_layout->addWidget(_workLog, 3,0,1,2);	
	setLayout(_layout);
}

/*
 * Default constructor.
 * Takes a Milestone object as a parameter, and fills in ui fields according to
 * this object's state.
 */
MilestoneTab::MilestoneTab(Milestone &milestone)
{
	// initialize data members
	//_milestone = &milestone;	
	_nameLabel = new QLabel(tr("Milestone Name:"));
	_deadlineLabel = new QLabel(tr("Milestone Deadline:"));
	_nameField = new QLineEdit;
	_deadlineField = new QDateTimeEdit;
	_updateMilestoneButton = new QPushButton(tr("Update Milestone"));
	_workLog = new WorkLog();
	_layout = new QGridLayout;
	
	// create layout
	_layout->addWidget(_nameLabel, 0,0, Qt::AlignRight);
	_layout->addWidget(_nameField, 0,1);
	_layout->addWidget(_deadlineLabel, 1,0, Qt::AlignRight);
	_layout->addWidget(_deadlineField, 1,1);
	_layout->addWidget(_updateMilestoneButton, 2,1,1,2);
	_layout->addWidget(_workLog, 3,0,1,2);	
	setLayout(_layout);
	
	// set ui fields according to milestone object info
	//_nameField->setText(_milestone->getName());
	//_deadlineField->setDateTime(_milestone->getDeadline());
	//_workLog->setText(_milestone->getWorkLog());
}

void MilestoneTab::showMilestoneValues(Milestone &m)
{
	cout << "Showing Milestone values\n";

	_milestone = m;
	// set ui fields according to milestone object info
	_nameField->setText(_milestone.getName());
	_deadlineField->setDateTime(_milestone.getDeadline());
	_workLog->setText(_milestone.getWorkLog());
}

void MilestoneTab::updateMilestone()
{
	// gather data from ui fields
	QString name = _nameField->text();
	QDateTime deadline = _deadlineField->dateTime();	
	QString workLog = _workLog->getLog();
	
	// use milestone object mutator methods to update
	_milestone.setName(name);
	_milestone.setDeadline(deadline);
	_milestone.setWorkLog(workLog);
	
	// emit signal carries new milestone object up the heirarchy
	emit updateMilestoneSignal(_milestone);
}
