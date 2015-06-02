#include "ListTab.h"

ListTab::ListTab(QWidget *parent) : QWidget(parent)
{
	tasksLabel = new QLabel(tr("Tasks:"));
	resourcesLabel = new QLabel(tr("Resources:"));
	milestonesLabel = new QLabel(tr("Milestones:"));
	tasksField = new QTextEdit;
	resourcesField = new QTextEdit;
	milestonesField = new QTextEdit;
	layout = new QGridLayout;
	
	// set styles for the text fields
	tasksField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	resourcesField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	milestonesField->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	
	// create the layout
	layout->addWidget(tasksLabel, 0,0, Qt::AlignLeft);
	layout->addWidget(resourcesLabel, 0,1, Qt::AlignLeft);
	layout->addWidget(milestonesLabel, 0,2, Qt::AlignLeft);
	layout->addWidget(tasksField, 1,0);
	layout->addWidget(resourcesField, 1,1);
	layout->addWidget(milestonesField, 1,2);
	
	setLayout(layout);
}
