#ifndef MILESTONETAB_H_
#define MILESTONETAB_H_

#include <QLabel>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QGridLayout>
#include <iostream>
#include "../../utility_classes_files/WorkLog.h"
#include "../../data_classes_files/Milestone.h"

using namespace std;

class MilestoneTab : public QWidget
{
	Q_OBJECT
	
	public:
		MilestoneTab(QWidget *parent = 0); 
		MilestoneTab(Milestone &milestone);
		
	signals:
		void updateMilestoneSignal(Milestone);
		
	public slots:
		void showMilestoneValues(Milestone &);
		void updateMilestone();
		
	private:
		//rep
		Milestone _milestone;
		QLabel *_nameLabel;
		QLabel *_deadlineLabel;
		QLineEdit *_nameField;
		QDateTimeEdit *_deadlineField;
		QPushButton *_updateMilestoneButton;	
		WorkLog *_workLog;
		QGridLayout *_layout;

	friend class Kernel;
};

#endif /*MILESTONETAB_H_*/
