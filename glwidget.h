#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QDate>
#include <QTime>
#include <QString>
#include <QDateTime>
#include <QTextStream>
#include <iostream>
#include "./data_classes_files/Task.h"
#include "./data_classes_files/Milestone.h"
#include <QHash>

class GLcoordinate
{
public:
        GLdouble x ;
        GLdouble y ;
};

class GLrectangle
{
public:
        GLcoordinate ll ;
        GLcoordinate ur ;
};

class GLviewpoint : public GLcoordinate
{
public:
        GLfloat zoom ;
        GLfloat aspectRatio ;
};

class taskElement
{
public:
	int taskID ;
	int rootID ;
	int level ;
	int criticalParent ;
	int duration ;
	bool started ;
	bool finished ;
	QDateTime estimatedStart ;
	QDateTime actualStart ;
	QList<int> parents ;
	QList<int> children ;
	QString name ;
	void addChild(int);
	void addParent(int);
};


class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
	void buildTasks(QList<Task>);
	void buildMilestones(QList<Milestone>);
	
    void pan(GLcoordinate);
    void select(GLcoordinate);
    void zoomFit();
    void zoomIn();
    void zoomOut();
    void panUp();
    void panDown();
    void panLeft();
    void panRight();
    void panUpRight();
    void panDownRight();
    void panUpLeft();
    void panDownLeft();
	void ganttMode();
	void pertMode();

signals:
	void message(const QString &);
	void mouseLocation(double, double);
	void popupMenu(const QPoint &);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent( QWheelEvent *m );

private:
	
	QList<Milestone> milestones ;
	QList<taskElement> taskGraph;
	void buildTaskGraph(QList<Task>);
	void findRootStartTimes();
	void updateChildStart(int, QDateTime, int, int);
	int getTaskPosition(int);
	
	double addGanttTask(int, double);
	double addPertTask(int, double);
	QList<int> tasksGanttDrawn;
	QList<int> tasksPertDrawn;
	void drawTaskBox(double start, double end, double y, double height, bool hasParents, bool hasChildren, QString name);
			
	int furthestTime ;
	double furthestDistance ;
	double offset ;
	double pushOut ;
	QDateTime measuredTime ;

	void draw();
	GLviewpoint view;
	GLcoordinate worldMouse;
	GLcoordinate center;
	GLcoordinate increment;
	GLcoordinate diff;
	int atX;
	int atY;
	int diffX ;
	int diffY ;

	GLdouble shiftScale, zoomScale ;
	GLfloat fadeThreshold ;
	GLfloat axisThreshold ;
	GLfloat brightness ;
	GLfloat fade ;
	GLfloat gamma ;

	GLdouble baseGrid ;
	GLdouble grid ;
	double gridXMin, gridXMax, gridYMin, gridYMax;
	
	double mouseGrid ;
	
	GLrectangle window;
	int windowX ;
	int windowY ;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLrectangle world;
	GLdouble wz;
	GLdouble monthLineY ;
	GLdouble dayLineY ;
	GLdouble markerY ;
	GLdouble markerDiff ;
	GLdouble characterHeight ;
	GLdouble ganttHeight ;
	GLdouble pertHeight ;
	GLrectangle ganttBoundary ;
	GLrectangle pertBoundary ;
	GLrectangle fitBoundary ;
	
	int displayLists ;
    GLuint displayListStart;
	
    bool pert ;

	void drawGanttChart();
	void drawPertChart();
	void drawGrid();
	void drawAxis();
	void drawGanttBackground();
	void drawMilestones();
	void drawCalendar();
	void drawCalendarHeader();
	void drawDateAxis();
	void drawMilestoneMarker(GLfloat x);
	void drawMilestoneTriangle(GLfloat x);
	void drawDateMarker(GLfloat x);
	void drawMarkerTriangle(GLfloat x);
	void drawDayLabel(GLfloat x, GLfloat y, QDate date);
	void drawMonthLabel(GLfloat x, GLfloat y, QDate date);
	void drawToday();

	void drawGanttGraph();
	void drawPertGraph();
	
	
	QDate today ;
	QDateTime todayTime ;
	QTime time ;
	QDate graphMark ;
	QDate graphStart ;
	QDate graphStop ;
	
	friend class Kernel;
};

#endif
