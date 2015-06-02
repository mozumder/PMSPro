#ifndef FILTERBUTTONWIDGET_H
#define FILTERBUTTONWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>

/*
 * This class represents the filter button group for the main window.
 */
 
 class FilterButtonWidget : public QWidget
 {
 	Q_OBJECT
	
	public:
		FilterButtonWidget(QWidget *parent = 0);
	
	private:
		QPushButton *clearFiltersButton;
		QPushButton *advancedFilterButton;
		QVBoxLayout *filterLayout;
 };

#endif /*FILTERBUTTONWIDGET_H*/
