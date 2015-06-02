#include "User.h"

User::User()
{
}

User::User(int &id, QString &username, QString &name, QString &password, QString &title,
		QString &description)
{
	_id = id;
	_username = username;
	_name = name;
	_password = password;
	_title = title;
	_description = description;
}

User::~User()
{
}

int User::getID() const
{
	return _id;
}

QString User::getUsername() const
{
	return _username;
}

QString User::getName() const
{
	return _name;
}

QString User::getPassword() const
{
	return _password;
}

QString User::getTitle() const
{
	return _title;
}

QString User::getDescription() const
{
	return _description;
}

void User::setID(const int &id)
{
	if(_id != id)
	{
		_id = id;
		emit idChanged(_id);
	}
}

void User::setUsername(const QString &username)
{
	if(_username != username)
	{
		_username = username;
		emit usernameChanged(_username);
	}
}

void User::setName(const QString &name)
{
	if(_name != name)
	{
		_name = name;
		emit nameChanged(_name);
	}
}

void User::setTitle(const QString &title)
{
	if(_title != title)
	{
		_title = title;
		emit titleChanged(_title);
	}
}

void User::setDescription(const QString &description)
{
	if(_description != description)
	{
		_description = description;
		emit descriptionChanged(_description);
	}
}

void User::setPassword(const QString &password)
{
	if(_password != password)
	{
		_password = password;
		emit passwordChanged(_password);
	}
}
