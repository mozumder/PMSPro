#ifndef BROWSEWIDGET_H_
#define BROWSEWIDGET_H_

#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

/*
 * This is a reusable widget which provides a browse input field and a button.
 */

class BrowseWidget : public QWidget
{
	Q_OBJECT
	
	public:
		BrowseWidget(QWidget *parent = 0);
	
	private:
		QPushButton *browseButton;
		QLineEdit *browseInput;
		QHBoxLayout *browseLayout;		
};

#endif /*BROWSEWIDGET_H_*/
