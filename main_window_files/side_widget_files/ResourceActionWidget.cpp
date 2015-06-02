#include "ResourceActionWidget.h"

ResourceActionWidget::ResourceActionWidget(QWidget *parent) : QWidget(parent)
{
	// initialize data members
	_label = new QLabel(tr("Resources:"));
	_viewButton = new QPushButton("View");
	_displayField = new QListWidget;
	_layout = new QGridLayout;
	
	// connect edit button with edit method
	connect(_viewButton, SIGNAL(clicked()), this, SLOT(resourceToView()));

	// create layout
	_layout->addWidget(_label, 0,0);
	_layout->addWidget(_displayField, 1,0,1,3);
	_layout->addWidget(_viewButton, 2,0);
	setLayout(_layout);
}

ResourceActionWidget::~ResourceActionWidget()
{
}

void ResourceActionWidget::drawList(QList<Resource> resourceList)

{
	_resourceList = resourceList;
	
	_displayField->clear();

	for(int i=0; i<_resourceList.size(); i++)
		_resourceList.removeFirst();
	
	for(int i=0; i<resourceList.size(); i++)
	{
		Resource r = resourceList.at(i);
		_displayField->addItem(r.getName());
	}
	for(int i=resourceList.size()-1; i >= 0; i--)
	{
		Resource r = resourceList.at(i);
		_resourceList.prepend(r);

	}
}

/*
 * finds the currently selected resource in the list and emits it via the
 * view resource signal
 */
void ResourceActionWidget::resourceToView()
{
	// get the numerical position of the currently selected item;
	// it matches the position of the corresponding Resource in the Resource list
	int position = _displayField->currentRow();
	Resource r = _resourceList.at(position);
	emit viewResourceSignal(r);
}
