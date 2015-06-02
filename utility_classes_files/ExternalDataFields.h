#ifndef EXTERNALDATAFIELDS_H_
#define EXTERNALDATAFIELDS_H_

#include <QLabel>
#include <QFrame>
#include <QTextEdit>
#include <QGridLayout>

/*
 * This widget holds the external data input fields for the Task Tab.
 */

class ExternalDataFields : public QWidget
{
	public:
		ExternalDataFields(QWidget *parent = 0);
		
	private:
		QFrame *workLogFrame;
		QLabel *workLogLabel;
		QTextEdit *workLogField;
		QGridLayout *workLogLayout;
		QGridLayout *layout;
};		
		
#endif /*EXTERNALDATAFIELDS_H_*/
