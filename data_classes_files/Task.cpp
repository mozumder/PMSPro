#include "Task.h"

Task::Task()
{
}

Task::Task(int &id, int &parent1, int &parent2, int &parent3, int &parent4, int &parent5,
		int &creatorID, QString &creator, int &projectID, QString &name,
		QString &description, QDateTime &creationDate, QDateTime &estimatedStartDate,
		int &duration, bool &isFinished, bool &onCriticalPath, QString &workLog,
		int &resource1, int &resource2, int &resource3, int &resource4, int &resource5)
{
	_id = id;
	_parent1 = parent1;
	_parent2 = parent2;
	_parent3 = parent3;
	_parent4 = parent4;
	_parent5 = parent5;
	_creatorID = creatorID;
	_creator = creator;
	_projectID = projectID;
	_name = name;
	_description = description;
	_creationDate = creationDate;
	_estimatedStartDate = estimatedStartDate;
	_duration = duration;
	_isFinished = isFinished;
	_onCriticalPath = onCriticalPath;
	_workLog = workLog;
	_resource1 = resource1;
	_resource2 = resource2;
	_resource3 = resource3;
	_resource4 = resource4;
	_resource5 = resource5;
}

Task::~Task()
{
}

Task::Task(const Task &task2Copy)
{
	copyTask(task2Copy);
}

const Task & Task::operator=(const Task &task2Copy)
{
	if(this != &task2Copy)
		copyTask(task2Copy);
	
	return *this;
}

void Task::copyTask(const Task &task2Copy)
{
	_id = task2Copy.getID();
	_parent1 = task2Copy.getParent1();
	_parent2 = task2Copy.getParent2();
	_parent3 = task2Copy.getParent3();
	_parent4 = task2Copy.getParent4();
	_parent5 = task2Copy.getParent5();
	_creatorID = task2Copy.getCreatorID();
	_creator = task2Copy.getCreator();
	_projectID = task2Copy.getProjectID();
	_name = task2Copy.getName();
	_description = task2Copy.getDescription();
	_creationDate = task2Copy.getCreationDate();
	_estimatedStartDate = task2Copy.getEstimatedStartDate();
	_duration = task2Copy.getDuration();
	_isFinished = task2Copy.getIsFinished();
	_onCriticalPath = task2Copy.getOnCriticalPath();
	_workLog = task2Copy.getWorkLog();
	_resource1 = task2Copy.getResource1();
	_resource2 = task2Copy.getResource2();
	_resource3 = task2Copy.getResource3();
	_resource4 = task2Copy.getResource4();
	_resource5 = task2Copy.getResource5();
}

QString Task::toString() const
{
	QString str;
	str += QString::number(_id) + "\n";
	str += QString::number(_parent1) + "\n";
	str += QString::number(_parent2) + "\n";
	str += QString::number(_parent3) + "\n";
	str += QString::number(_parent4) + "\n";
	str += QString::number(_parent5) + "\n";
	str += QString::number(_creatorID) + "\n";
	str += _creator + "\n";
	str += QString::number(_projectID) + "\n";
	str += _name + "\n";
	str += _description + "\n";
	str += _creationDate.toString() + "\n";
	str += _estimatedStartDate.toString() + "\n";
	str += QString::number(_duration) + "\n";
	if (_isFinished)
	{
		str += "true";
		str += "\n";
	}
	else
	{
		str += "false";
		str += "\n";
	}
	if (_onCriticalPath)
	{
		str += "true";
		str += "\n";
	}
	else
	{
		str += "false";
		str += "\n";
	}
	str += _workLog + "\n";
	str += QString::number(_resource1) + "\n";
	str += QString::number(_resource2) + "\n";
	str += QString::number(_resource3) + "\n";
	str += QString::number(_resource4) + "\n";
	str += QString::number(_resource5) + "\n";

	return str;
}

int Task::getID() const
{
	return _id;
}

int Task::getParent1() const
{
	return _parent1;
}

int Task::getParent2() const
{
	return _parent2;
}

int Task::getParent3() const
{
	return _parent3;
}

int Task::getParent4() const
{
	return _parent4;
}

int Task::getParent5() const
{
	return _parent5;
}

int Task::getCreatorID() const
{
	return _creatorID;
}

QString Task::getCreator() const
{
	return _creator;
}

int Task::getProjectID() const
{
	return _projectID;
}

QString Task::getName() const
{
	return _name;
}

QString Task::getDescription() const
{
	return _description;
}

QDateTime Task::getCreationDate() const
{
	return _creationDate;
}

QDateTime Task::getEstimatedStartDate() const
{
	return _estimatedStartDate;
}

int Task::getDuration() const
{
	return _duration;
}

bool Task::getIsFinished() const
{
	return _isFinished;
}

bool Task::getOnCriticalPath() const
{
	return _onCriticalPath;
}

QString Task::getWorkLog() const
{
	return _workLog;
}

int Task::getResource1() const
{
	return _resource1;
}

int Task::getResource2() const
{
	return _resource2;
}

int Task::getResource3() const
{
	return _resource3;
}

int Task::getResource4() const
{
	return _resource4;
}

int Task::getResource5() const
{
	return _resource5;
}

void Task::setID(const int &id)
{
	if(_id != id)
	{
		_id = id;
		emit idChanged(_id);
	}
}

void Task::setParent1(const int &parent1)
{
	if(_parent1 != parent1)
	{
		_parent1 = parent1;
		emit parent1Changed(_parent1);
	}
}

void Task::setParent2(const int &parent2)
{
	if(_parent2 != parent2)
	{
		_parent2 = parent2;
		emit parent2Changed(_parent2);
	}
}

void Task::setParent3(const int &parent3)
{
	if(_parent3 != parent3)
	{
		_parent3 = parent3;
		emit parent3Changed(_parent3);
	}
}

void Task::setParent4(const int &parent4)
{
	if(_parent4 != parent4)
	{
		_parent4 = parent4;
		emit parent4Changed(_parent4);
	}
}

void Task::setParent5(const int &parent5)
{
	if(_parent5 != parent5)
	{
		_parent5 = parent5;
		emit parent5Changed(_parent5);
	}
}

void Task::setCreatorID(const int &creatorID)
{
	if(_creatorID != creatorID)
	{
		_creatorID = creatorID;
		emit creatorIDChanged(_creatorID);
	}
}

void Task::setCreator(const QString &creator)
{
	if(_creator != creator)
	{
		_creator = creator;
		emit creatorChanged(_creator);
	}
}

void Task::setProjectID(const int &projectID)
{
	if(_projectID != projectID)
	{
		_projectID = projectID;
		emit projectIDChanged(_projectID);
	}
}

void Task::setName(const QString &name)
{
	if(_name != name)
	{
		_name = name;
		emit nameChanged(_name);
	}
}

void Task::setDescription(const QString &description)
{
	if(_description != description)
	{
		_description = description;
		emit descriptionChanged(_description);
	}
}

void Task::setCreationDate(const QDateTime &creationDate)
{
	if(_creationDate != creationDate)
	{
		_creationDate = creationDate;
		emit creationDateChanged(_creationDate);
	}
}

void Task::setEstimatedStartDate(const QDateTime &estimatedStartDate)
{
	if(_estimatedStartDate != estimatedStartDate)
	{
		_estimatedStartDate = estimatedStartDate;
		emit estimatedStartDateChanged(_estimatedStartDate);
	}
}

void Task::setDuration(const int &duration)
{
	if(_duration != duration)
	{
		_duration = duration;
		emit durationChanged(_duration);
	}
}

void Task::setIsFinished(const bool &isFinished)
{
	if(_isFinished != isFinished)
	{
		_isFinished = isFinished;
		emit isFinishedChanged(_isFinished);
	}
}

void Task::setOnCriticalPath(const bool &onCriticalPath)
{
	if(_onCriticalPath != onCriticalPath)
	{
		_onCriticalPath = onCriticalPath;
		emit onCriticalPathChanged(_onCriticalPath);
	}
}

void Task::setWorkLog(const QString &workLog)
{
	if(_workLog != workLog)
	{
		_workLog = workLog;
		emit workLogChanged(_workLog);
	}
}

void Task::setResource1(const int &resource1)
{
	if(_resource1 != resource1)
	{
		_resource1 = resource1;
		emit resource1Changed(_resource1);
	}
}

void Task::setResource2(const int &resource2)
{
	if(_resource2 != resource2)
	{
		_resource2 = resource2;
		emit resource2Changed(_resource2);
	}
}

void Task::setResource3(const int &resource3)
{
	if(_resource3 != resource3)
	{
		_resource3 = resource3;
		emit resource3Changed(_resource3);
	}
}

void Task::setResource4(const int &resource4)
{
	if(_resource4 != resource4)
	{
		_resource4 = resource4;
		emit resource4Changed(_resource4);
	}
}

void Task::setResource5(const int &resource5)
{
	if(_resource5 != resource5)
	{
		_resource5 = resource5;
		emit resource5Changed(_resource5);
	}
}
