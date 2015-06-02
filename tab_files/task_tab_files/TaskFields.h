#ifndef TASKFIELDS_H_
#define TASKFIELDS_H_

#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>

/*
 * This widget holds the task input fields for the Task Tab
 */

class TaskFields : public QWidget
{
	Q_OBJECT
	
	public:
		TaskFields(QWidget *parent = 0);
		
	private:
		//rep
		QLabel *_nameLabel;
		QLabel *_startDateLabel;
		QLabel *_endDateLabel;
		QLabel *_descriptionLabel;
		QLabel *_creatorLabel;
		QLineEdit *_creator;
		QLabel *_creationDateLabel;
		QDateTimeEdit *_creationDate;
	
		QLineEdit *_taskName;
		QDateTimeEdit *_taskStartDate;
		QDateTimeEdit *_taskEndDate;
		QTextEdit *_taskDescription;
		
		QGridLayout *_layout;
		
		// the TaskTab class will have access to private data members
		friend class TaskTab;
};

#endif /*TASKFIELDS_H_*/
