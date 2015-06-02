#include "TaskManager.h"

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

Task TaskManager::getTask(const int &taskID) const
{
	for (int i = 0; i < _taskList.size(); i++)
	{	
		Task t = _taskList.at(i);
		if (t.getID() == taskID)
			return _taskList.at(i);
	}
	Task temp;
	return temp;
}

QList<Task> TaskManager::getAllTasks() const
{
	return _taskList;
}

int TaskManager::getNumTasks() const
{
	return _taskList.size();
}

void TaskManager::makeEmpty()
{
	while(!_taskList.isEmpty())
		_taskList.removeFirst();
}

Task TaskManager::getTaskAt(const int &index)
{
	if (index < _taskList.size())
		return _taskList.at(index);
	Task temp;
	return temp;
}

void TaskManager::createNewTask()
{
	emit createNewTaskSignal();
}

void TaskManager::addTask(const Task &task)
{
	_taskList.prepend(task);
	emit taskListChanged(_taskList);
	emit taskListChanged(_taskList, _resourceList);
}

void TaskManager::updateTask(const Task &task)
{
	for(int i = 0; i < _taskList.size(); i++)
	{
		Task t = _taskList.at(i);
		if (t.getID() == task.getID())
		{
			removeTask(t.getID());
			_taskList.prepend(task);
			cout << "Task updated\n";
		}
	}
	emit taskListChanged(_taskList);
	emit taskListChanged(_taskList, _resourceList);
	emit updateTaskSignal(task);
}

void TaskManager::removeTask(const int &taskID)
{
	for (int i = 0; i < _taskList.size(); i++)
	{	
		Task t = _taskList.at(i);
		if (t.getID() == taskID)
		{
			_taskList.removeAt(i);
			cout << "Task Removed\n";
			for (int j = 0; j < _taskList.size(); j++)
			{
				Task temp = _taskList.at(j);
				if (temp.getParent1() == taskID)
					temp.setParent1(0);
				if (temp.getParent2() == taskID)
					temp.setParent2(0);
				if (temp.getParent3() == taskID)
					temp.setParent3(0);
				if (temp.getParent4() == taskID)
					temp.setParent4(0);
				if (temp.getParent5() == taskID)
					temp.setParent5(0);
			}
		}
	}
	emit taskListChanged(_taskList);
	emit taskListChanged(_taskList, _resourceList);
	emit removeTaskSignal(taskID);
}

void TaskManager::addResource(const Resource &resource)
{
	_resourceList.append(resource);
	emit taskListChanged(_taskList);
	emit taskListChanged(_taskList, _resourceList);
}
