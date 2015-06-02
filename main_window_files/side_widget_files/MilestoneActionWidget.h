#ifndef MILESTONEACTIONWIDGET_H_
#define MILESTONEACTIONWIDGET_H_

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <iostream>
#include "../../data_classes_files/Milestone.h"

using namespace std;

class MilestoneActionWidget : public QWidget
{

	Q_OBJECT

	public:
		MilestoneActionWidget(QWidget *parent = 0);
		virtual ~MilestoneActionWidget();
	
	public slots:
		void drawList(QList<Milestone> milestoneList);
		
	signals:
		void newMilestoneSignal();
		void updateMilestoneSignal(Milestone &milestone);
		//void removeMilestoneSignal(Milestone &milestone);
		void editMilestoneSignal(Milestone &);
		void deletedIDSignal(int);
		
	private slots:
		void milestoneToEdit();
		void milestoneToDelete();
		
	private:
		// rep
		QLabel *_label;
		QPushButton *_newButton;
		QPushButton *_editButton;
		QPushButton *_deleteButton;
		QListWidget *_displayField;
		QGridLayout *_layout;
		QList<Milestone> _milestoneList;

	friend class Kernel;
};

#endif /*MILESTONEACTIONWIDGET_H_*/
