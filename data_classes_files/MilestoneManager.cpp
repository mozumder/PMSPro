#include "MilestoneManager.h"

MilestoneManager::MilestoneManager()
{
}

MilestoneManager::~MilestoneManager()
{	
}

Milestone MilestoneManager::getMilestone(const int &milestoneID) const
{
	for (int i = 0; i < _milestoneList.size(); i++){	
		Milestone m = _milestoneList.at(i);
		if (m.getID() == milestoneID)
			return _milestoneList.at(i);
	}
	Milestone temp;
	return temp;
}

QList<Milestone> MilestoneManager::getAllMilestones() const
{
	return _milestoneList;
}

int MilestoneManager::getUserID() const
{
	return _userID;
}

QString MilestoneManager::getUsername() const
{
	return _username;
}

void MilestoneManager::makeEmpty()
{
	while(!_milestoneList.isEmpty())
		_milestoneList.removeFirst();
}

void MilestoneManager::createNewMilestone()
{
	emit createNewMilestoneSignal();
}

void MilestoneManager::addMilestone(const Milestone &milestone)
{
	_milestoneList.prepend(milestone);
	emit milestoneListChanged(_milestoneList);
}

void MilestoneManager::updateMilestone(Milestone milestone)
{
	for(int i = 0; i < _milestoneList.size(); i++)
	{
		Milestone m = _milestoneList.at(i);
		if (m.getID() == milestone.getID())
		{
			removeMilestone(m.getID());
			_milestoneList.prepend(milestone);
			cout << "Milestone updated\n";
		}
	}
	emit milestoneListChanged(_milestoneList);
	emit updateMilestoneSignal(milestone);
}

void MilestoneManager::removeMilestone(const int &milestoneID)
{
	for (int i = 0; i < _milestoneList.size(); i++){	
		Milestone m = _milestoneList.at(i);
		if (m.getID() == milestoneID)
		{
			_milestoneList.removeAt(i);
			cout << "Milestone Removed\n";
		}
	}
	emit milestoneListChanged(_milestoneList);
	emit removeMilestoneSignal(milestoneID);
}

void MilestoneManager::setUserID(const int &userID)
{
	_userID = userID;
}

void MilestoneManager::setUsername(const QString &username)
{
	_username = username;
}
