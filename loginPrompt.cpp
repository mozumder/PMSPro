     #include <QtGui>

    #include "loginPrompt.h"

    loginPrompt::loginPrompt(QWidget *parent)
        : QDialog(parent)
    {
        hostLabel = new QLabel(tr("Host Name:"));
        hostLineEdit = new QLineEdit("localhost");
        hostLabel->setBuddy(hostLineEdit);

        databaseLabel = new QLabel(tr("Database Name:"));
        databaseLineEdit = new QLineEdit("PMSPro");
        databaseLabel->setBuddy(databaseLineEdit);

        userLabel = new QLabel(tr("User Name:"));
        userLineEdit = new QLineEdit("PMSPro");
        userLabel->setBuddy(userLineEdit);

        projectIDLabel = new QLabel(tr("ProjectID:"));
        projectIDLineEdit = new QLineEdit("1");
        projectIDLabel->setBuddy(projectIDLineEdit);
  
        QGridLayout *gridLayout = new QGridLayout;
        gridLayout->addWidget(hostLabel,0,0);
        gridLayout->addWidget(hostLineEdit,0,1);
        gridLayout->addWidget(databaseLabel,1,0);
        gridLayout->addWidget(databaseLineEdit,1,1);
        gridLayout->addWidget(userLabel,2,0);
        gridLayout->addWidget(userLineEdit,2,1);
        gridLayout->addWidget(projectIDLabel,3,0);
        gridLayout->addWidget(projectIDLineEdit,3,1);

		loginButton = new QPushButton(tr("Login"));
        loginButton->setDefault(true);
		cancelButton = new QPushButton(tr("Cancel"));
        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addStretch(1);
        buttonLayout->addWidget(cancelButton);
        buttonLayout->addWidget(loginButton);
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
        connect(loginButton, SIGNAL(clicked()), this, SLOT(close()));

		QVBoxLayout *topLayout = new QVBoxLayout;
        topLayout->addLayout(gridLayout);
        topLayout->addLayout(buttonLayout);
        topLayout->addStretch(1);
		
		setLayout(topLayout);

        setWindowTitle(tr("PMSPro Login"));
    }
