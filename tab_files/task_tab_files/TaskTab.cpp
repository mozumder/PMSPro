#include "TaskTab.h"

/*
 * Default constructor.
 * provided for testing purposes only.
 */
TaskTab::TaskTab(QWidget *parent) : QWidget(parent)
{
	// initialize data members	
	_taskFields = new TaskFields();
	_resourcesLabel = new QLabel("Resources:");
	_resourcesField = new QTextEdit;
	_resourcesField->setReadOnly(true);
	_workLog = new WorkLog();
	_updateTaskButton = new QPushButton(tr("Update Task"));
	_finishedLabel = new QLabel(tr("Finished?"));
	_finishedField = new QLineEdit;
	_finishedField->setReadOnly(true);
	_criticalPathLabel = new QLabel(tr("On Critical Path?"));
	_criticalPathField = new QLineEdit;
	_criticalPathField->setReadOnly(true);
	_dependenciesFields = new DependenciesFields();
	
	_layout = new QGridLayout;
	
	//durationField will only accept integers from 0 to 999
	_validator = new QIntValidator(0, 999, this);
	_durationField = new QLineEdit;
	_durationField->setValidator(_validator);
	_durationLabel = new QLabel(tr("Duration:"));
	
	// create layout	
	_layout->addWidget(_taskFields, 0,0,1,6);
	_layout->addWidget(_resourcesLabel, 2,0);
	_layout->addWidget(_resourcesField, 2,1,1,5);
	_layout->addWidget(_durationLabel, 1,0);
	_layout->addWidget(_durationField, 1,1);
	_layout->addWidget(_criticalPathLabel, 1,2);
	_layout->addWidget(_criticalPathField, 1,3);
	_layout->addWidget(_finishedLabel, 1,4);
	_layout->addWidget(_finishedField, 1,5);
	_layout->addWidget(_dependenciesFields, 3,0,1,6);
	_layout->addWidget(_updateTaskButton, 4,0,1,6);
	_layout->addWidget(_workLog, 5,0,1,6);
	setLayout(_layout);
}

/*
 * Default constructor.
 * Takes a Task object as a parameter, and fills in ui fields according to
 * this object's state.
 */
TaskTab::TaskTab(Task &task)
{
	// initialize data members
//	_task = &task;	
	_taskFields = new TaskFields();
	_resourcesLabel = new QLabel("Resources:");
	_resourcesField = new QTextEdit();
	_resourcesField->setReadOnly(true);
	_workLog = new WorkLog();
	_updateTaskButton = new QPushButton(tr("Update Task"));
	_finishedLabel = new QLabel(tr("Finished?"));
	_finishedField = new QLineEdit;
	_finishedField->setReadOnly(true);
	_criticalPathLabel = new QLabel(tr("On Critical Path?"));
	_criticalPathField = new QLineEdit;
	_criticalPathField->setReadOnly(true);
	_layout = new QGridLayout;
	
	//durationField will only accept integers from 0 to 999
	_validator = new QIntValidator(0, 999, this);
	_durationField = new QLineEdit;
	_durationField->setValidator(_validator);
	_durationLabel = new QLabel(tr("Duration:"));
	
	// create layout	
	_layout->addWidget(_taskFields, 0,0,1,6);
	_layout->addWidget(_resourcesLabel, 2,0);
	_layout->addWidget(_resourcesField, 2,1,1,5);
	_layout->addWidget(_durationLabel, 1,0);
	_layout->addWidget(_durationField, 1,1);
	_layout->addWidget(_criticalPathLabel, 1,2);
	_layout->addWidget(_criticalPathField, 1,3);
	_layout->addWidget(_finishedLabel, 1,4);
	_layout->addWidget(_finishedField, 1,5);
	_layout->addWidget(_updateTaskButton, 3,0,1,6);
	_layout->addWidget(_workLog, 4,0,1,6);
	setLayout(_layout);
	
	// get task object info and fill in ui fields accordingly
//	_taskFields->_taskName->setText(_task->getName());
//	//_taskFields->_taskStartDate->setDateTime(_task->getStartDate());
//	//_taskFields->_taskEndDate->setDateTime(_task->getEndDate());
//	_taskFields->_taskDescription->setPlainText(_task->getDescription());
//	_taskFields->_creator->setText(_task->getCreator());
//	_taskFields->_creationDate->setDateTime(_task->getCreationDate());
}

void TaskTab::showTaskValues(Task &t, QList<Resource> &resourceList)
{
	cout << "Showing Task values\n";

	_task = t;
	// get task object info and fill in ui fields accordingly
	_taskFields->_taskName->setText(_task.getName());
	_taskFields->_taskDescription->setPlainText(_task.getDescription());
	_taskFields->_creator->setText(_task.getCreator());
	_taskFields->_creationDate->setDateTime(_task.getCreationDate());
	_taskFields->_taskStartDate->setDateTime(_task.getEstimatedStartDate());
	_durationField->setText(QString::number(_task.getDuration()));

	int resource1 = t.getResource1();
	int resource2 = t.getResource2();
	int resource3 = t.getResource3();
	int resource4 = t.getResource4();
	int resource5 = t.getResource5();
	QString resourceStr;
	for(int i = 0; i < resourceList.size(); i++)
	{
		Resource r = resourceList.at(i);
		if (r.getID() == resource1 ||
			r.getID() == resource2 ||
			r.getID() == resource3 ||
			r.getID() == resource4 ||
			r.getID() == resource5)
		{
			resourceStr += r.getName() + "\n";
		}
	}

	QTextDocument *resourcesDocument = new QTextDocument(resourceStr);
	_resourcesField->setDocument(resourcesDocument);
	
}

/*
 * Updates task object using data from user input fields and
 * emits an update task signal with the new task as a parameter.
 */
void TaskTab::updateTask()
{
	// gather data from ui fields
	QString name = _taskFields->_taskName->text();
	QDateTime startDate = _taskFields->_taskStartDate->dateTime();
	int estTime = _durationField->text().toInt();
	QString description = _taskFields->_taskDescription->toPlainText();
	QString resources = _resourcesField->toPlainText();
	QString workLog = _workLog->getLog();
	
	// use task object mutator methods to update
	_task.setName(name);
	_task.setEstimatedStartDate(startDate);
	_task.setDuration(estTime);
	_task.setDescription(description);
	_task.setWorkLog(workLog);
//	_task->setResources(resources);
	
	// emit signal carries new task object up the heirarchy
	emit updateTaskSignal(_task);
}
