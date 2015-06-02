#ifndef RESOURCEACTIONWIDGET_H_
#define RESOURCEACTIONWIDGET_H_

#include <QPushButton>
#include <QListWidget>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <iostream>
#include "../../data_classes_files/Task.h"
#include "../../data_classes_files/Resource.h"

class ResourceActionWidget : public QWidget
{
	Q_OBJECT
	
	public:
		ResourceActionWidget(QWidget *parent = 0);
		virtual ~ResourceActionWidget();
		
	public slots:
		void drawList(QList<Resource> resourceList);
		
	signals:
		void viewResourceSignal(Resource &);
		
	private:
		// rep
		QLabel *_label;
		QPushButton *_viewButton;
		QListWidget *_displayField;
		QGridLayout *_layout;
		
		QList<Resource> _resourceList;
		
	private slots:
		void resourceToView();
		
	friend class Kernel;
		
};

#endif /*RESOURCEACTIONWIDGET_H_*/
