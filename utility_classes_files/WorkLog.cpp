#include "WorkLog.h"

WorkLog::WorkLog(QWidget *parent) : QWidget(parent)
{
	_workLogFrame = new QFrame;
	_workLogLabel = new QLabel(tr("Work Log:"));
	_workLogField = new QTextEdit;
		
	//layout for the work log frame
	_workLogLayout = new QGridLayout;
	_workLogLayout->addWidget(_workLogLabel, 0,0);
	_workLogLayout->addWidget(_workLogField, 1,0);
	_workLogFrame->setLayout(_workLogLayout);
	_workLogFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	
	//layout for the outer widget
	_layout = new QGridLayout;
	_layout->addWidget(_workLogFrame);
	
	setLayout(_layout);
}

/*
 * Returns contents of the log as a QString
 */
QString WorkLog::getLog()
{
	return _workLogField->toPlainText();
}

void WorkLog::setText(const QString &text)
{
	_workLogField->setPlainText(text);
}

