#ifndef MILESTONEMANAGER_H
#define MILESTONEMANAGER_H

#include <QObject>
#include <QString>
#include <QList>

class Task;
class Resource;
class Milestone;

class MileStoneManager : public QObject
{
	Q_OBJECT
	
public:
	//Functions
	MilestoneManager();
	virtual ~MilestoneManager();

private:
	//Data Members
	QList<Milestone> *milestoneList;

public slots:

		
};

#endif
