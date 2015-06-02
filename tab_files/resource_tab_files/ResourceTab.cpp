#include "ResourceTab.h"

ResourceTab::ResourceTab(QWidget *parent) : QWidget(parent)
{
	resourceNameLabel = new QLabel(tr("Resource Name:"));
	resourceDescriptionLabel = new QLabel(tr("Resource Description:"));
		
	resourceNameField = new QLineEdit;
	resourceDescriptionField = new QTextEdit;
		
	
	layout = new QGridLayout;
	layout->addWidget(resourceNameLabel, 0,0, Qt::AlignRight);
	layout->addWidget(resourceDescriptionLabel, 1,0, Qt::AlignRight);
	layout->addWidget(resourceNameField, 0,1,1,2);
	layout->addWidget(resourceDescriptionField, 1,1,1,3);
	
	setLayout(layout);
}

void ResourceTab::showResourceValues(Resource &r)
{
	cout << "Showing Resource values\n";

	QString name = r.getName();
	QString description = r.getDescription();
	QTextDocument *descriptionDocument = new QTextDocument(description);

	resourceNameField->setText(name);
	resourceDescriptionField->setDocument(descriptionDocument);	
}

void ResourceTab::updateResource()
{
	QString name = resourceNameField->text();
	QString description = resourceDescriptionField->toPlainText();
	
	/* need to implement this in Resource class
	Resource *resource = new Resource(name, description, tasksInvolved, startDate, endDate);
	
	emit updateResourceSignal(resource);
	*/
}

/*
 * displays data from task object passed from external signal.
 * ui fields are filled in accordingly.
 */
void ResourceTab::drawResource(Resource &resource)
{
	// gather data from resource data members
	QString name = resource.getName();
	QString creator = resource.getCreator();
	QString description = resource.getDescription();
	//QTextDocument *descriptionDocument = new QTextDocument(description);
	//QString calendar = resource.getCalender();
	
	/* this has all changed
	 * we'll see
	 * 
	// fill in ui fields
	_resourceName->setText(name);
	_resourceStartDate->setDateTime(creationDate);
	_resourceDescription->setDocument(descriptionDocument);
	_workLog->setText(workLog);
	*/
}
	
