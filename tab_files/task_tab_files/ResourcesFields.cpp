#include "ResourcesFields.h"

ResourcesFields::ResourcesFields(QWidget *parent) : QWidget(parent)
{
	resourcesLabel = new QLabel(tr("Resources:"));
	resourceField = new QTextEdit;
	addResource = new QPushButton(tr("Add\nResource"));
	removeResource = new QPushButton(tr("Remove\nResource"));
	
	layout = new QGridLayout;
	layout->addWidget(resourcesLabel, 0,0, Qt::AlignRight);
	layout->addWidget(addResource, 1,0);
	layout->addWidget(removeResource, 2,0);
	layout->addWidget(resourceField, 0,1,3,1);
	
	setLayout(layout);
}
