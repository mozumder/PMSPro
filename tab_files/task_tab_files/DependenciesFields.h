#ifndef DEPENDENCIESFIELDS_H_
#define DEPENDENCIESFIELDS_H_

#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QGridLayout>

/*
 * This widget holds the dependencies input fields for the Task Tab.
 */

class DependenciesFields : public QWidget
{
	Q_OBJECT
	
	public:
		DependenciesFields(QWidget *parent = 0);
		
	private:
		QLabel *_dependenciesLabel;
		QTextEdit *_taskField;
		QTextEdit *_dependentField;
		QPushButton *_addDependency;
		QPushButton *_removeDependency;
		QGridLayout *_layout;
};

#endif /*DEPENDENCIESFIELDS_H_*/
