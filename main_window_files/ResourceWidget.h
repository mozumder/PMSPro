#ifndef RESOURCEWIDGET_H
#define RESOURCEWIDGET_H

#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QComboBox>

/*
	This is the resource widget for the main window.
*/

class ResourceWidget : public QFrame
{
	Q_OBJECT
	
	public:
		ResourceWidget(QWidget *parent = 0);
		
	private:
		QComboBox *categoriesMenu;
		QVBoxLayout *layout;
		QTextEdit *textArea;
		QLabel *resourceLabel;
};

#endif
