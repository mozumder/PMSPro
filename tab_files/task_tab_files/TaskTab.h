#ifndef TASKTAB_H_
#define TASKTAB_H_

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QValidator>
#include <QList>
#include <iostream>
#include "TaskFields.h"
#include "../../utility_classes_files/WorkLog.h"
#include "../../data_classes_files/Task.h"
#include "../../data_classes_files/Resource.h"
#include "DependenciesFields.h"

using namespace std;

/*
 * This widget is the Task tab of the main tab widget.
 */

class TaskTab : public QWidget
{
	Q_OBJECT
	
	public:
		TaskTab(QWidget *parent = 0);
		TaskTab(Task &task);
		
	signals:
		void updateTaskSignal(Task);

	private slots:
		void showTaskValues(Task &, QList<Resource> &);
		void updateTask();
	
	private:
	// rep
		Task _task;
		TaskFields *_taskFields;
		QTextEdit *_resourcesField;
		QLabel *_resourcesLabel;
		QPushButton *_updateTaskButton;
		QGridLayout *_layout;
		WorkLog *_workLog;
		QLineEdit *_durationField;
		QValidator *_validator;
		QLabel *_durationLabel;
		QLabel *_criticalPathLabel;
		QLineEdit *_criticalPathField;
		QLabel *_finishedLabel;
		QLineEdit *_finishedField;
		DependenciesFields *_dependenciesFields;

	friend class Kernel;
};

#endif /*TASKTAB_H_*/
