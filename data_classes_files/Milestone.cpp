#include "Milestone.h"

Milestone::Milestone()
{
}

Milestone::Milestone(int &id, int &creatorID, QString &creator, int &projectID, QString &name,
		QDateTime &deadline, QString &description, QString &workLog)
{
	_id = id;
	_creatorID = creatorID;
	_creator = creator;
	_projectID = projectID;
	_name = name;
	_deadline = deadline;
	_description = description;
	_workLog = workLog;
}

Milestone::~Milestone()
{
}

Milestone::Milestone(const Milestone &milestone2Copy)
{
	copyMilestone(milestone2Copy);
}

const Milestone & Milestone::operator=(const Milestone &milestone2Copy)
{
	if(this != &milestone2Copy)
		copyMilestone(milestone2Copy);
	
	return *this;
}

void Milestone::copyMilestone(const Milestone &milestone2Copy)
{
	_id = milestone2Copy.getID();
	_creatorID = milestone2Copy.getCreatorID();
	_creator = milestone2Copy.getCreator();
	_projectID = milestone2Copy.getProjectID();
	_name = milestone2Copy.getName();
	_deadline = milestone2Copy.getDeadline();
	_description = milestone2Copy.getDescription();
	_workLog = milestone2Copy.getWorkLog();
}

QString Milestone::toString() const
{
	QString str;
	str += QString::number(_id) + "\n";
	str += QString::number(_creatorID) + "\n";
	str += _creator + "\n";
	str += QString::number(_projectID) + "\n";
	str += _name + "\n";
	str += _deadline.toString() + "\n";
	str += _description + "\n";
	str += _workLog;

	return str;
}

int Milestone::getID() const
{
	return _id;
}

int Milestone::getCreatorID() const
{
	return _creatorID;
}

QString Milestone::getCreator() const
{
	return _creator;
}

int Milestone::getProjectID() const
{
	return _projectID;
}

QString Milestone::getName() const
{
	return _name;
}

QDateTime Milestone::getDeadline() const
{
	return _deadline;
}

QString Milestone::getDescription() const
{
	return _description;
}

QString Milestone::getWorkLog() const
{
	return _workLog;
}

void Milestone::setID(const int &id)
{
	if(_id != id)
	{
		_id = id;
		emit idChanged(_id);
	}
}


void Milestone::setName(const QString &name)
{
	if(_name != name)
	{
		_name = name;
		emit nameChanged(_name);
	}
}

void Milestone::setProjectID(const int &projectID)
{
	if(_projectID != projectID)
	{
		_projectID = projectID;
		emit projectIDChanged(_projectID);
	}
}

void Milestone::setDeadline(const QDateTime &deadline)
{
	if(_deadline != deadline)
	{
		_deadline = deadline;
		emit deadlineChanged(_deadline);
	}
}

void Milestone::setCreatorID(const int &creatorID)
{
	if(_creatorID != creatorID)
	{
		_creatorID = creatorID;
		emit creatorIDChanged(_creatorID);
	}
}

void Milestone::setCreator(const QString &creator)
{
	if(_creator != creator)
	{
		_creator = creator;
		emit creatorChanged(_creator);
	}
}

void Milestone::setDescription(const QString &description)
{
	if(_description != description)
	{
		_description = description;
		emit descriptionChanged(_description);
	}
}

void Milestone::setWorkLog(const QString &workLog)
{
	if(_workLog != workLog)
	{
		_workLog = workLog;
		emit workLogChanged(_workLog);
	}
}
