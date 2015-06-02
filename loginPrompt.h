  #ifndef DIALOG_H
    #define DIALOG_H

    #include <QDialog>

    class QCheckBox;
    class QGroupBox;
    class QLabel;
    class QLineEdit;
    class QPushButton;

    class loginPrompt : public QDialog
    {
        Q_OBJECT
    public:
        loginPrompt(QWidget *parent = 0);

    private:
        QLabel *hostLabel;
        QLineEdit *hostLineEdit;
        QLabel *databaseLabel;
        QLineEdit *databaseLineEdit;
        QLabel *userLabel;
        QLineEdit *userLineEdit;
        QLabel *projectIDLabel;
        QLineEdit *projectIDLineEdit;
        QPushButton *cancelButton;
        QPushButton *loginButton;
    };

    #endif

