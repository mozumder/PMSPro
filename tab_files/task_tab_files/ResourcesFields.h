#ifndef RESOURCESFIELDS_H_
#define RESOURCESFIELDS_H_

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

/*
 * This widget holds the resources input fields for the Task Tab.
 */

class ResourcesFields : public QWidget
{
	Q_OBJECT
	
	public:
		ResourcesFields(QWidget *parent = 0);
		
	private:
		QLabel *resourcesLabel;
		QTextEdit *resourceField;
		QPushButton *addResource;
		QPushButton *removeResource;
		QGridLayout *layout;
};

#endif /*RESOURCESFIELDS_H_*/
