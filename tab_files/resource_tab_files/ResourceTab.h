#ifndef RESOURCETAB_H_
#define RESOURCETAB_H_

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <iostream>
//#include "../../data_classes_files/Resource.h"
#include "Resource.h"

using namespace std;

class ResourceTab : public QWidget
{
	Q_OBJECT
	
	public:
		ResourceTab(QWidget *parent = 0);
		
	signals:
		void updateResourceSignal(const Resource &);
		
	private slots:
		void showResourceValues(Resource &);
		void updateResource();
		void drawResource(Resource &resource);
		
	private:
		QLabel *resourceNameLabel;
		QLabel *resourceDescriptionLabel;
		QLineEdit *resourceNameField;
		QTextEdit *resourceDescriptionField;
		QGridLayout *layout;

	friend class Kernel;
};

#endif /*RESOURCETAB_H_*/
