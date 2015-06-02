#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <QObject>
#include <QString>

class Resource : public QObject
{
	Q_OBJECT
	
public:
	Resource();
	Resource(int &id, int &creatorID, QString &creator, QString &name, QString &description,
		QString &calender);
	virtual ~Resource();
	Resource(const Resource &resource2Copy);
	const Resource & operator=(const Resource &resource2Copy);
	QString toString() const;

	int getID() const;
	int getCreatorID() const;
	QString getCreator() const;
	QString getName() const;
	QString getDescription() const;
	QString getCalender() const;

public slots:
	void setID(const int &id);
	void setCreatorID(const int &creatorID);
	void setCreator(const QString &creator);
	void setName(const QString &name);
	void setDescription(const QString &description);
	void setCalender(const QString &calender);

signals:
	void idChanged(const int &id);
	void creatorIDChanged(const int &creatorID);
	void creatorChanged(const QString &creator);
	void nameChanged(const QString &name);
	void descriptionChanged(const QString &description);
	void calenderChanged(const QString &calender);

private:
	int _id;
	int _creatorID;
	QString _creator;
	QString _name;
	QString _description;
	QString _calender;

	//Used by copy constructor and operator=
	void copyResource(const Resource &resource2Copy);
};

#endif /*RESOURCE_H_*/
