#include "Resource.h"

Resource::Resource()
{
}

Resource::Resource(int &id, int &creatorID, QString &creator, QString &name, QString &description,
		QString &calender)
{
	_id = id;
	_creatorID = creatorID;
	_creator = creator;
	_name = name;
	_description = description;
	_calender = calender;
}

Resource::~Resource()
{
}

Resource::Resource(const Resource &resource2Copy)
{
	copyResource(resource2Copy);
}

const Resource & Resource::operator=(const Resource &resource2Copy)
{
	if(this != &resource2Copy)
		copyResource(resource2Copy);
	
	return *this;
}

void Resource::copyResource(const Resource &resource2Copy)
{
	_id = resource2Copy.getID();
	_creatorID = resource2Copy.getCreatorID();
	_creator = resource2Copy.getCreator();
	_name = resource2Copy.getName();
	_description = resource2Copy.getDescription();
	_calender = resource2Copy.getCalender();
}

QString Resource::toString() const
{
	QString str;
	str += QString::number(_id) + "\n";
	str += QString::number(_creatorID) + "\n";
	str += _creator + "\n";
	str += _name + "\n";
	str += _description + "\n";
	str += _calender;

	return str;
}

int Resource::getID() const
{
	return _id;
}

int Resource::getCreatorID() const
{
	return _creatorID;
}

QString Resource::getCreator() const
{
	return _creator;
}

QString Resource::getName() const
{
	return _name;
}

QString Resource::getDescription() const
{
	return _description;
}

QString Resource::getCalender() const
{
	return _calender;
}

void Resource::setID(const int &id)
{
	if(_id != id)
	{
		_id = id;
		emit idChanged(_id);
	}
}

void Resource::setCreatorID(const int &creatorID)
{
	if(_creatorID != creatorID)
	{
		_creatorID = creatorID;
		emit creatorIDChanged(_creatorID);
	}
}

void Resource::setCreator(const QString &creator)
{
	if(_creator != creator)
	{
		_creator = creator;
		emit creatorChanged(_creator);
	}
}

void Resource::setName(const QString &name)
{
	if(_name != name)
	{
		_name = name;
		emit nameChanged(_name);
	}
}

void Resource::setDescription(const QString &description)
{
	if(_description != description)
	{
		_description = description;
		emit descriptionChanged(_description);
	}
}

void Resource::setCalender(const QString &calender)
{
	if(_calender != calender)
	{
		_calender = calender;
		emit calenderChanged(_calender);
	}
}
