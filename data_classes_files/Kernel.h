#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QString>
#include <QList>
#include <QtSql>
#include <QDateTime>
#include <QApplication>
#include "Task.h"
#include "Resource.h"
#include "Milestone.h"
#include "TaskManager.h"
#include "MilestoneManager.h"
#include "ResourceManager.h"
#include "../main_window_files/MainWindow.h"
#include "../main_window_files/side_widget_files/SideWidget.h"
#include "../main_window_files/side_widget_files/TaskActionWidget.h"
#include "../main_window_files/side_widget_files/MilestoneActionWidget.h"
#include "loginPrompt.h"

/* This class loads information from the database and creates objects
   that can be used by the GUI. 
*/

class Kernel : public QObject
{
	Q_OBJECT
	
public:
	//Functions
	Kernel();
	virtual ~Kernel();

	void connectDB();
	void showMainWindow();
	void login();

private:
	//Data Members
	TaskManager taskMan;
	MilestoneManager milestoneMan;
	ResourceManager resourceMan;
	MainWindow window;
	loginPrompt loginDialog;
	int userID;
	QString username;
	int projectID;
	QString dbHostName ;
	QString dbDatabaseName ;
	QString dbUserName ;

public slots:
	void removeTask(int);
	void removeMilestone(int);
	void createNewTask();
	void createNewMilestone();
	void updateMilestone(Milestone);
	void updateTask(Task);
		
};

#endif
