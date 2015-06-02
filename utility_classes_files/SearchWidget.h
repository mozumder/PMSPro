#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

/*
 * This is a reusable widget which provides a search input field and button.
 */

class SearchWidget : public QWidget
{
	Q_OBJECT
	
	public:
		SearchWidget(QWidget *parent = 0);
	
	private:
		QPushButton *searchButton;
		QLineEdit *searchInput;
		QHBoxLayout *searchLayout;		
};

#endif
