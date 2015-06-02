#include "ExternalDataFields.h"

ExternalDataFields::ExternalDataFields(QWidget *parent) : QWidget(parent)
{
	workLogFrame = new QFrame;
	workLogLabel = new QLabel(tr("Work Log:"));
	workLogField = new QTextEdit;
		
	//layout for the work log frame
	workLogLayout = new QGridLayout;
	workLogLayout->addWidget(workLogLabel, 0,0);
	workLogLayout->addWidget(workLogField, 1,0);
	workLogFrame->setLayout(workLogLayout);
	workLogFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	
	//layout for the outer widget
	layout = new QGridLayout;
	layout->addWidget(workLogFrame);
	
	setLayout(layout);
}
