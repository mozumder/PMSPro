#ifndef TASKACTIONWIDGET_H_
#define TASKACTIONWIDGET_H_

#include <QPushButton>
#include <QListWidget>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <iostream>
#include "../../data_classes_files/Task.h"
#include "../../data_classes_files/Resource.h"

using namespace std;


class TaskActionWidget : public QWidget
{
	Q_OBJECT
	
	public:
		TaskActionWidget(QWidget *parent = 0);
		virtual ~TaskActionWidget();
		
	public slots:
		void drawList(QList<Task> taskList, QList<Resource> resourceList);
		
	signals:
		void newTaskSignal();
		void updateTaskSignal(Task &task);
		void editTaskSignal(Task &, QList<Resource> &);
		//void removeTaskSignal(Task &task);
		void deletedIDSignal(int);
				
	private:
		// rep
		QLabel *_label;
		QPushButton *_newButton;
		QPushButton *_editButton;
		QPushButton *_deleteButton;
		QListWidget *_displayField;
		QGridLayout *_layout;
		
		QList<Resource> _resourceList;
		QList<Task> _taskList;

	private slots:
		void taskToEdit();
		void taskToDelete();
		
	friend class Kernel;
};

#endif /*TASKACTIONWIDGET_H_*/
