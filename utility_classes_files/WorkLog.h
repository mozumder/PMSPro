#ifndef WORKLOG_H_
#define WORKLOG_H_

#include <QLabel>
#include <QFrame>
#include <QTextEdit>
#include <QGridLayout>

/*
 * This is the work log text input field which is used in several tabs.
 */

class WorkLog : public QWidget
{
	public:
		WorkLog(QWidget *parent = 0);
		
	public slots:
		// accessor functions
		QString getLog();
		
		// mutator functions
		void setText(const QString &text);
		
	private:
		// rep
		QFrame *_workLogFrame;
		QLabel *_workLogLabel;
		QTextEdit *_workLogField;
		QGridLayout *_workLogLayout;
		QGridLayout *_layout;
};		
		
#endif /*WORKLOG_H_*/
