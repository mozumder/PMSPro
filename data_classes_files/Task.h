#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QList>
#include "Resource.h"

/*
 * This class represents an individual task in the schedule
 * 
 */

class Task : public QObject
{
	Q_OBJECT
	
public:
	Task();
	Task(int &id, int &parent1, int &parent2, int &parent3, int &parent4, int &parent5,
		int &creatorID, QString &creator, int &projectID, QString &name,
		QString &description, QDateTime &creationDate, QDateTime &estimatedStartDate,
		int &duration, bool &isFinished, bool &onCriticalPath, QString &workLog,
		int &resource1, int &resource2, int &resource3, int &resource4, int &resource5);
	virtual ~Task();
	Task(const Task &task2Copy);
	const Task & operator=(const Task &task2Copy);
	QString toString() const;

	int getID() const;
	int getParent1() const;
	int getParent2() const;
	int getParent3() const;
	int getParent4() const;
	int getParent5() const;
	int getCreatorID() const;
	QString getCreator() const;
	int getProjectID() const;
	QString getName() const;
	QString getDescription() const;
	QDateTime getCreationDate() const;
	QDateTime getEstimatedStartDate() const;
	int getDuration() const;
	bool getIsFinished() const;
	bool getOnCriticalPath() const;
	QString getWorkLog() const;
	int getResource1() const;
	int getResource2() const;
	int getResource3() const;
	int getResource4() const;
	int getResource5() const;
		
		
public slots:
	void setID(const int &id);
	void setParent1(const int &parent1);
	void setParent2(const int &parent2);
	void setParent3(const int &parent3);
	void setParent4(const int &parent4);
	void setParent5(const int &parent5);
	void setCreatorID(const int &creatorID);
	void setCreator(const QString &creator);
	void setProjectID(const int &projectID);
	void setName(const QString &name);
	void setDescription(const QString &description);
	void setCreationDate(const QDateTime &creationDate);
	void setEstimatedStartDate(const QDateTime &estimatedTime);
	void setDuration(const int &duration);
	void setIsFinished(const bool &isFinished);
	void setOnCriticalPath(const bool &onCriticalPath);
	void setWorkLog(const QString &workLog);
	void setResource1(const int &resource1);
	void setResource2(const int &resource2);
	void setResource3(const int &resource3);
	void setResource4(const int &resource4);
	void setResource5(const int &resource5);
		
signals:
	void idChanged(const int &id);
	void parent1Changed(const int &parent1);
	void parent2Changed(const int &parent2);
	void parent3Changed(const int &parent3);
	void parent4Changed(const int &parent4);
	void parent5Changed(const int &parent5);
	void creatorIDChanged(const int &creatorID);
	void creatorChanged(const QString &creator);
	void projectIDChanged(const int &projectID);
	void nameChanged(const QString &name);
	void descriptionChanged(const QString &description);
	void creationDateChanged(const QDateTime &creationDate);
	void estimatedStartDateChanged(const QDateTime &estimatedTime);
	void durationChanged(const int &duration);
	void isFinishedChanged(const bool &isFinished);
	void onCriticalPathChanged(const bool &onCriticalPath);
	void workLogChanged(const QString &workLog);
	void resource1Changed(const int &resource1);
	void resource2Changed(const int &resource2);
	void resource3Changed(const int &resource3);
	void resource4Changed(const int &resource4);
	void resource5Changed(const int &resource5);
	
private:
	//Data Members
	int _id;
	int _parent1;
	int _parent2;
	int _parent3;
	int _parent4;
	int _parent5;
	int _creatorID;
	QString _creator;
	int _projectID;
	QString _name;
	QString _description;
	QDateTime _creationDate;
	QDateTime _estimatedStartDate;
	int _duration;
	bool _isFinished;
	bool _onCriticalPath;
	QString _workLog;
	int _resource1;
	int _resource2;
	int _resource3;
	int _resource4;
	int _resource5;

	//Used by copy constructor and operator=
	void copyTask(const Task &task2Copy);
};

#endif
