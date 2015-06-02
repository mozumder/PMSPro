#ifndef LISTTAB_H_
#define LISTTAB_H_

#include <QTextEdit>
#include <QLabel>
#include <QGridLayout>

/*
 * This widget is the List tab of the main tab widget.
 */

class ListTab : public QWidget
{
	Q_OBJECT
	
	public:
		ListTab(QWidget *parent = 0);
		
	private:
		QLabel *tasksLabel;
		QLabel *resourcesLabel;
		QLabel *milestonesLabel;
		QTextEdit *tasksField;
		QTextEdit *resourcesField;
		QTextEdit *milestonesField;
		QGridLayout *layout;
};

#endif /*LISTTAB_H_*/
