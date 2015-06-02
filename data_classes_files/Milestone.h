#ifndef MILESTONE_H
#define MILESTONE_H

#include <QObject>
#include <QString>
#include <QDateTime>


class Milestone : public QObject
{
	Q_OBJECT
	
public:
	Milestone();
	Milestone(int &id, int &creatorID, QString &creator, int &projectID, QString &name,
		QDateTime &deadline, QString &description, QString &workLog);
	virtual ~Milestone();
	Milestone(const Milestone &milestone2Copy);
	const Milestone & operator=(const Milestone &milestone2Copy);
	QString toString() const;

	int getID() const;
	int getCreatorID() const;
	int getProjectID() const;
	QString getName() const;
	QDateTime getDeadline() const;
	QString getCreator() const;
	QString getDescription() const;
	QString getWorkLog() const;

public slots:
	void setID(const int &id);
	void setCreatorID(const int &creatorID);
	void setName(const QString &name);
	void setProjectID(const int &projectID);
	void setDeadline(const QDateTime &deadline);
	void setDescription(const QString &description);
	void setCreator(const QString &creator);
	void setWorkLog(const QString &notes);

signals:
	void idChanged(const int &id);
	void creatorIDChanged(const int &creatorID);
	void creatorChanged(const QString &creator);
	void projectIDChanged(const int &projectID);
	void nameChanged(const QString &name);
	void deadlineChanged(const QDateTime &deadline);
	void descriptionChanged(const QString &description);
	void workLogChanged(const QString &notes);

private:
	//Data Members
	int _id;
	int _creatorID;
	QString _creator;
	int _projectID;
	QString _name;
	QDateTime _deadline;
	QString _description;
	QString _workLog;

	//Used by copy constructor and operator=
	void copyMilestone(const Milestone &milestone2Copy);
};

#endif
