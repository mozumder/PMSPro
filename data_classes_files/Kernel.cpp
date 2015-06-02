#include "Kernel.h"

Kernel::Kernel()
{

	//Display tasks in task action widget
	connect(&taskMan, SIGNAL(taskListChanged(QList<Task>, QList<Resource>)),
	window.tabWidget->_sideWidget->_taskActionWidget, SLOT(drawList(QList<Task>,
		QList<Resource>)));

	//Display milestones in milestone action widget
	connect(&milestoneMan, SIGNAL(milestoneListChanged(QList<Milestone>)),
	window.tabWidget->_sideWidget->_milestoneActionWidget, SLOT(drawList(QList<Milestone>)));

	//Display resources in resource action widget
	connect(&resourceMan, SIGNAL(resourceListChanged(QList<Resource>)),
	window.tabWidget->_sideWidget->_resourceActionWidget, SLOT(drawList(QList<Resource>)));

	//Connect task manager to glwidget
	connect(&taskMan, SIGNAL(taskListChanged(QList<Task>)),
	window.GLViewPort, SLOT(buildTasks(QList<Task>)));

	//Connect milestone manager to glwidget
	connect(&milestoneMan, SIGNAL(milestoneListChanged(QList<Milestone>)),
	window.GLViewPort, SLOT(buildMilestones(QList<Milestone>)));

	//Connect task manager to "new task" button on task action widget
	connect(window.tabWidget->_sideWidget->_taskActionWidget->_newButton, SIGNAL(clicked()),
	&taskMan, SLOT(createNewTask()));

	//Connect kernel to task manager to create a new task
	connect(&taskMan, SIGNAL(createNewTaskSignal()),
	SLOT(createNewTask()));

	//Connect milestone manager to "new milestone" button on milestone action widget
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget->_newButton,
		SIGNAL(clicked()),
	&milestoneMan, SLOT(createNewMilestone()));

	//Connect kernel to milestone manager to create a new milestone
	connect(&milestoneMan, SIGNAL(createNewMilestoneSignal()),
	SLOT(createNewMilestone()));

	//Connect milestone action widget to "delete" button
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget->_deleteButton,
		SIGNAL(clicked()),
	window.tabWidget->_sideWidget->_milestoneActionWidget, SLOT(milestoneToDelete()));

	//Connect deleted milestone signal to milestone manager remove milestone
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget,
		SIGNAL(deletedIDSignal(int)),
	&milestoneMan, SLOT(removeMilestone(const int &)));

	//Connect milestone manager signal to kernel to remove milestone from database
	connect(&milestoneMan, SIGNAL(removeMilestoneSignal(int)),
	SLOT(removeMilestone(int)));

	//Connect task aciton widget to "delete" button
	connect(window.tabWidget->_sideWidget->_taskActionWidget->_deleteButton,
		SIGNAL(clicked()),
	window.tabWidget->_sideWidget->_taskActionWidget, SLOT(taskToDelete()));

	//Connect deleted task signal to task manager remove task
	connect(window.tabWidget->_sideWidget->_taskActionWidget, SIGNAL(deletedIDSignal(int)),
	&taskMan, SLOT(removeTask(const int &)));

	//Connect task manager signal to kernel to remove task from database
	connect(&taskMan, SIGNAL(removeTaskSignal(int)),
	SLOT(removeTask(int)));

	//Connect edit milestone button to milestone action widget
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget->_editButton,
		SIGNAL(clicked()),
	window.tabWidget->_sideWidget->_milestoneActionWidget, SLOT(milestoneToEdit()));

	//Connect edit milestone signal to milestone tab
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget,
		SIGNAL(editMilestoneSignal(Milestone &)),
	window.tabWidget->milestoneTab, SLOT(showMilestoneValues(Milestone &)));

	//Connect edit task button to task action widget
	connect(window.tabWidget->_sideWidget->_taskActionWidget->_editButton,
		SIGNAL(clicked()),
	window.tabWidget->_sideWidget->_taskActionWidget, SLOT(taskToEdit()));

	//Connect edit task signal to task tab
	connect(window.tabWidget->_sideWidget->_taskActionWidget,
		SIGNAL(editTaskSignal(Task &, QList<Resource> &)),
	window.tabWidget->taskTab, SLOT(showTaskValues(Task &, QList<Resource> &)));

	//Connect view resource button to resource action widget
	connect(window.tabWidget->_sideWidget->_resourceActionWidget->_viewButton,
		SIGNAL(clicked()),
	window.tabWidget->_sideWidget->_resourceActionWidget, SLOT(resourceToView()));

	//Connect view resource signal to resource tab
	connect(window.tabWidget->_sideWidget->_resourceActionWidget,
		SIGNAL(viewResourceSignal(Resource &)),
	window.tabWidget->resourceTab, SLOT(showResourceValues(Resource &)));

	//Connect signal that edit task button was clicked to tab widget
	connect(window.tabWidget->_sideWidget->_taskActionWidget->_editButton,
		SIGNAL(clicked()),
	window.tabWidget, SLOT(showTaskTab()));

	//Connect signal that edit milestone button was clicked to tab widget
	connect(window.tabWidget->_sideWidget->_milestoneActionWidget->_editButton,
		SIGNAL(clicked()),
	window.tabWidget, SLOT(showMilestoneTab()));

	//Connect signal that view resource button was clicked to tab widget
	connect(window.tabWidget->_sideWidget->_resourceActionWidget->_viewButton,
		SIGNAL(clicked()),
	window.tabWidget, SLOT(showResourceTab()));

	//Connect update milestone button to update milestone function in milestone tab
	connect(window.tabWidget->milestoneTab->_updateMilestoneButton, SIGNAL(clicked()),
	window.tabWidget->milestoneTab, SLOT(updateMilestone()));

	//Connect update milestone to milestone manager
	connect(window.tabWidget->milestoneTab, SIGNAL(updateMilestoneSignal(Milestone)),
	&milestoneMan, SLOT(updateMilestone(Milestone)));

	//Connect update milestone signal in milestone manager to kernel update milestone
	connect(&milestoneMan, SIGNAL(updateMilestoneSignal(Milestone)),
	SLOT(updateMilestone(Milestone)));

	//Connect update task button to update task function in task tab
	connect(window.tabWidget->taskTab->_updateTaskButton, SIGNAL(clicked()),
	window.tabWidget->taskTab, SLOT(updateTask()));

	//Connect update task to task manager
	connect(window.tabWidget->taskTab, SIGNAL(updateTaskSignal(Task)),
	&taskMan, SLOT(updateTask(Task)));

	//Connect update task signal in task manager to kernel update task
	connect(&taskMan, SIGNAL(updateTaskSignal(Task)),
	SLOT(updateTask(Task)));
	
}

Kernel::~Kernel()
{	
}

void Kernel::connectDB()
{
		std::cout << "Opening Database.\n" ;
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");
	
	std::cout << "Starting PMSPro.\n" ;
	
	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;
	
	//Temp data:  login prompt will return this data and it will be checked against
	//the database for verification
	userID = 1;
	username = "swhaley";
	projectID = 1;


	QSqlQuery queryR("SELECT * FROM tblResources");
	Resource r;
	while(queryR.next())
	{
		r.setID(queryR.value(0).toInt());
		r.setCreatorID(queryR.value(1).toInt());
		//r.setCreator
		r.setName(queryR.value(2).toString());
		r.setDescription(queryR.value(3).toString());
		r.setCalender(queryR.value(4).toString());

		resourceMan.addResource(r);
		taskMan.addResource(r);  //Give the task manager the list of Resources as well
	}


	QSqlQuery queryT("SELECT * FROM tblTask where project_ID = 1");
	
	Task t;
	while(queryT.next())
	{
		t.setID(queryT.value(0).toInt());
		t.setParent1(queryT.value(1).toInt());
		t.setParent2(queryT.value(2).toInt());
		t.setParent3(queryT.value(3).toInt());
		t.setParent4(queryT.value(4).toInt());
		t.setParent5(queryT.value(5).toInt());
		t.setCreatorID(queryT.value(6).toInt());
		t.setProjectID(queryT.value(7).toInt());
		t.setName(queryT.value(8).toString());
		t.setDescription(queryT.value(9).toString());
		QDateTime tempCreationDate = QDateTime::fromString(queryT.value(10).toString(),
			Qt::ISODate);
		t.setCreationDate(tempCreationDate);
		QDateTime tempStartDate = QDateTime::fromString(queryT.value(11).toString(),
			Qt::ISODate);
		t.setEstimatedStartDate(tempStartDate);
		t.setDuration(queryT.value(12).toInt());
		
		t.setWorkLog(queryT.value(15).toString());
		t.setResource1(queryT.value(16).toInt());
		t.setResource2(queryT.value(17).toInt());
		t.setResource3(queryT.value(18).toInt());
		t.setResource4(queryT.value(19).toInt());
		t.setResource5(queryT.value(20).toInt());
			
		taskMan.addTask(t);
	}

	//Set additional data in the task manager
	//taskMan.setUserID(1);
	//taskMan.setUsername("swhaley");

	QSqlQuery queryM("SELECT * FROM tblMileStone where project_ID = 1");
	Milestone m;
	while(queryM.next())
	{
		m.setID(queryM.value(0).toInt());
		m.setCreatorID(queryM.value(1).toInt());
		m.setProjectID(queryM.value(2).toInt());
		m.setName(queryM.value(3).toString());
		//m.setCreator(queryM.value(3).toString());
		QDateTime tempDeadline = QDateTime::fromString(queryM.value(4).toString(),
			Qt::ISODate);
		m.setDeadline(tempDeadline);
		m.setDescription(queryM.value(5).toString());
		m.setWorkLog(queryM.value(6).toString());

		milestoneMan.addMilestone(m);
	}

	//Set additional data in the milestone manager
	milestoneMan.setUserID(1);
	milestoneMan.setUsername("swhaley");

	db.close();

}

void Kernel::removeTask(int taskID)
{
	cout << "Removing Task from database\n";

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");

	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	QString queryStr = "delete from tblTask where task_ID = ";
	queryStr += QString::number(taskID);
	queryStr += ";";

	QSqlQuery queryDelete;
	queryDelete.exec(queryStr);

	db.close();
}

void Kernel::removeMilestone(int milestoneID)
{
	cout << "Removing Milestone from database\n";

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");

	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	QString queryStr = "delete from tblMileStone where milestone_ID = ";
	queryStr += QString::number(milestoneID);
	queryStr += ";";

	QSqlQuery queryDelete;
	queryDelete.exec(queryStr);

	db.close();
}


void Kernel::createNewTask()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");
	
	std::cout << "Creating new task\n" ;
	
	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	QString queryStr = "insert into tblTask (creator_ID, project_ID, name, create_date, ";
	queryStr += "estimate_start_date)";
	queryStr += "values (" + QString::number(userID) + ", ";
	queryStr += QString::number(projectID) + ", ";
	queryStr += "'<newTask>', ";
	QDateTime currentDate = QDateTime::currentDateTime();
	queryStr += "'" + currentDate.toString(Qt::ISODate) + "', ";
	queryStr += "'" + currentDate.toString(Qt::ISODate) + "');";

	QSqlQuery queryInsert;
	queryInsert.exec(queryStr);

	taskMan.makeEmpty();

	QSqlQuery queryT("SELECT * FROM tblTask where project_ID = 1");
	
	Task t;
	while(queryT.next())
	{
		t.setID(queryT.value(0).toInt());
		t.setParent1(queryT.value(1).toInt());
		t.setParent2(queryT.value(2).toInt());
		t.setParent3(queryT.value(3).toInt());
		t.setParent4(queryT.value(4).toInt());
		t.setParent5(queryT.value(5).toInt());
		t.setCreatorID(queryT.value(6).toInt());
		t.setProjectID(queryT.value(7).toInt());
		t.setName(queryT.value(8).toString());
		t.setDescription(queryT.value(9).toString());
		QDateTime tempCreationDate = QDateTime::fromString(queryT.value(10).toString(),
			Qt::ISODate);
		t.setCreationDate(tempCreationDate);
		QDateTime tempStartDate = QDateTime::fromString(queryT.value(11).toString(),
			Qt::ISODate);
		t.setEstimatedStartDate(tempStartDate);
		t.setDuration(queryT.value(12).toInt());
		
		t.setWorkLog(queryT.value(15).toString());
		t.setResource1(queryT.value(16).toInt());
		t.setResource2(queryT.value(17).toInt());
		t.setResource3(queryT.value(18).toInt());
		t.setResource4(queryT.value(19).toInt());
		t.setResource5(queryT.value(20).toInt());
	
		taskMan.addTask(t);
	}

	db.close();
}

void Kernel::createNewMilestone()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");
	
	std::cout << "Creating new milestone\n" ;
	
	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	QString queryStr = "insert into tblMileStone (creator_ID, project_ID, name, deadline)";
	queryStr += "values (" + QString::number(userID) + ", ";
	queryStr += QString::number(projectID) + ", ";
	queryStr += "'<newMilestone>', ";
	QDateTime currentDate = QDateTime::currentDateTime();
	queryStr += "'" + currentDate.toString(Qt::ISODate) + "');";

	QSqlQuery queryInsert;
	queryInsert.exec(queryStr);

	milestoneMan.makeEmpty();

	QSqlQuery queryM("SELECT * FROM tblMileStone where project_ID = 1");
	Milestone m;
	while(queryM.next())
	{
		m.setID(queryM.value(0).toInt());
		m.setCreatorID(queryM.value(1).toInt());
		m.setProjectID(queryM.value(2).toInt());
		m.setName(queryM.value(3).toString());
		//m.setCreator(queryM.value(3).toString());
		QDateTime tempDeadline = QDateTime::fromString(queryM.value(4).toString(),
			Qt::ISODate);
		m.setDeadline(tempDeadline);
		m.setDescription(queryM.value(5).toString());
		m.setWorkLog(queryM.value(6).toString());

		milestoneMan.addMilestone(m);
	}
	
	db.close();
}

void Kernel::updateMilestone(Milestone m)
{
	cout << "Updating milestone in database\n";

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");
	
	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	//unsolvable problems with update query
	//did not implement database updates


	db.close();
}

void Kernel::updateTask(Task t)
{
	cout << "Updating task in database\n";

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("localhost");
	db.setDatabaseName("PMSPro");
	db.setUserName("PMSPro");
	
	bool ok = db.open();
	if (ok)
		std::cout << "Opened Database.\n" ;
	else
		std::cout << "Unable to open database!\n" ;

	int taskID = t.getID();
	QString strTaskID = QString::number(taskID);
	
	QString strName = t.getName();
	QString strDescription = t.getDescription();
	QDateTime estimatedStartDate = t.getEstimatedStartDate();
	QString strEstimatedStartDate = estimatedStartDate.toString(Qt::ISODate);
	int duration = t.getDuration();
	QString strDuration = QString::number(duration);
	QString strWorkLog = t.getWorkLog();

	//unsolvable problems with update query
	//did not implement database updates


//	QString queryStr = "update tblTask SET ";
//	queryStr += "name = '" + strName + "', ";
//	queryStr += "description = '" + strDescription + "', ";
//	queryStr += "estimate_start_date = '" + strEstimatedStartDate + "', ";
//	queryStr += "duration = " + strDuration + ", ";
//	queryStr += "workLog = '" + strWorkLog + "' ";
//	queryStr += "WHERE task_ID = " + strTaskID + ";";

//	QString queryStr = "update tblTask SET name = 'better name' WHERE task_ID = 28;";

	
//	QSqlQuery queryUpdate;
//	queryUpdate.exec(queryStr);

	db.close();
}

void Kernel::login()
{
	loginDialog.exec();
}
void Kernel::showMainWindow()
{
	window.showMaximized();
}
