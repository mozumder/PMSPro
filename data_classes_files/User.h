#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject
{
	Q_OBJECT

public:
	User();
	User(int &id, QString &username, QString &name, QString &password, QString &title,
		QString &description);
	virtual ~User();

	int getID() const;
	QString getUsername() const;
	QString getPassword() const;
	QString getName() const;
	QString getTitle() const;
	QString getDescription() const;

public slots:

	void setID(const int &id);
	void setUsername(const QString &username);
	void setPassword(const QString &password);
	void setName(const QString &name);
	void setTitle(const QString &title);
	void setDescription(const QString &description);

signals:
	void idChanged(const int);
	void usernameChanged(const QString);
	void passwordChanged(const QString);
	void nameChanged(const QString);
	void titleChanged(const QString);
	void descriptionChanged(const QString);

private:
	
	int _id;
	QString _username;
	QString _name;
	QString _password;
	QString _title;
	QString _description;
};

#endif
