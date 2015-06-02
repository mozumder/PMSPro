#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{	
}

Resource ResourceManager::getResource(const int &resourceID) const
{
	for (int i = 0; i < _resourceList.size(); ++i){	
		Resource m = _resourceList.at(i);
		if (m.getID() == resourceID)
			return _resourceList.at(i);
	}
	Resource temp;
	return temp;
}

QList<Resource> ResourceManager::getAllResources() const
{
	return _resourceList;
}

void ResourceManager::addResource(const Resource &resource)
{
	_resourceList.append(resource);
	emit resourceListChanged(_resourceList);
}

void ResourceManager::removeResource(const int &resourceID)
{
	for (int i = 0; i < _resourceList.size(); ++i){	
		Resource t = _resourceList.at(i);
		if (t.getID() == resourceID)
			_resourceList.removeAt(i);
	}
	emit resourceListChanged(_resourceList);
}
