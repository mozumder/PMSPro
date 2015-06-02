#include "ResourceWidget.h"

ResourceWidget::ResourceWidget(QWidget *parent) : QFrame(parent)
{    
    resourceLabel = new QLabel(tr("Resources"), this);
    resourceLabel->setPalette(QPalette(QColor("red"),QColor("blue")));
    //resourceLabel->setLineWidth(2);
    resourceLabel->setFrameStyle(QFrame::Box | QFrame::Plain);
    
    QStringList list;
    list << tr("Resource categories") << tr("Item 1") << tr("Item 2") << tr("Item 3");
    categoriesMenu = new QComboBox(this);
    categoriesMenu->addItems(list);
  
    textArea = new QTextEdit(tr("Resource information here..."), this);
    textArea->setFrameStyle(QFrame::Panel | QFrame::Sunken);
       
    //setPalette(QPalette(QColor("lightGray")));        
    //setAutoFillBackground(true);
    	
	layout = new QVBoxLayout;
	layout->addWidget(resourceLabel);
    layout->addWidget(categoriesMenu);
    layout->addWidget(textArea);
    layout->setSpacing(20);
    
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFixedWidth(275);
    
    setLayout(layout);
}
