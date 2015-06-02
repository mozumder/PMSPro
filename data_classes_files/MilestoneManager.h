#ifndef MILESTONEMANAGER_H
#define MILESTONEMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include <iostream>
#include "Task.h"
#include "Resource.h"
#include "Milestone.h"

using namespace std;

class MilestoneManager : public QObject
{
	Q_OBJECT
	
public:
	//Functions
	MilestoneManager();
	virtual ~MilestoneManager();

	Milestone getMilestone(const int &milestoneID) const;
	QList<Milestone> getAllMilestones() const;
	int getUserID() const;
	QString getUsername() const;
	void makeEmpty();

private:
	//Data Members
	QList<Milestone> _milestoneList;
	int _userID;
	QString _username;

public slots:
	void createNewMilestone();
	void addMilestone(const Milestone &milestone);
	void updateMilestone(Milestone);
	void removeMilestone(const int &);
	void setUserID(const int &userID);
	void setUsername(const QString &username);

signals:
	void removeMilestoneSignal(int);
	void createNewMilestoneSignal();
	void updateMilestoneSignal(Milestone);
	void milestoneListChanged(QList<Milestone>);
		
};

#endif
