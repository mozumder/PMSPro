#include "DependenciesFields.h"

DependenciesFields::DependenciesFields(QWidget *parent) : QWidget(parent)
{
	_dependenciesLabel = new QLabel(tr("Dependencies:"));
	_taskField = new QTextEdit(tr("Task A<br>Task B"));
	_dependentField = new QTextEdit(tr("Child<br>Dependent On"));
	_addDependency = new QPushButton(tr("Add\nDependency"));
	_removeDependency = new QPushButton(tr("Remove\nDependency"));
	
	_layout = new QGridLayout;
	_layout->addWidget(_dependenciesLabel, 0,0, Qt::AlignRight);
	_layout->addWidget(_addDependency, 1,0);
	_layout->addWidget(_removeDependency, 2,0);
	_layout->addWidget(_taskField, 0,1,3,1);
	_layout->addWidget(_dependentField, 0,2,3,1);
	
	setLayout(_layout);
}
