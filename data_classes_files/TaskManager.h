#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <iostream>
#include "Task.h"
#include "Resource.h"
#include "Milestone.h"

using namespace std;

class TaskManager : public QObject
{
	Q_OBJECT
	
public:
	TaskManager();
	virtual ~TaskManager();

	Task getTask(const int &taskID) const;
	QList<Task> getAllTasks() const;
	int getNumTasks() const;
	void makeEmpty();
	Task getTaskAt(const int &index);

private:
	//Data Members
	QList<Task> _taskList;
	QList<Resource> _resourceList;
	
public slots:
	void createNewTask();
	void addTask(const Task &task);
	void updateTask(const Task &task);
	void removeTask(const int &);
	void addResource(const Resource &resource);

signals:
	void removeTaskSignal(int);
	void createNewTaskSignal();
	void updateTaskSignal(Task);
	void taskListChanged(QList<Task>);
	void taskListChanged(QList<Task>, QList<Resource>);
};

#endif
