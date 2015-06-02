#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QObject>
#include <QString>
#include <QList>
#include "Resource.h"

class ResourceManager : public QObject
{
	Q_OBJECT
	
public:
	//Functions
	ResourceManager();
	virtual ~ResourceManager();
	Resource getResource(const int &resourceID) const;
	QList<Resource> getAllResources() const;

private:
	//Data Members
	QList<Resource> _resourceList;

public slots:
	void addResource(const Resource &resource);
	void removeResource(const int &resourceID);

signals:
	void resourceListChanged(QList<Resource>);
};

#endif
