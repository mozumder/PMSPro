#include <QtGui>
#include <QtOpenGL>
#include <math.h>

#include "glwidget.h"

void taskElement::addParent(int tmpID)
{
	if (!parents.contains(tmpID))
	{
		parents.append(tmpID);
	}
}
void taskElement::addChild(int tmpID)
{
	if (!children.contains(tmpID))
	{
		children.append(tmpID);
	}
}

void GLWidget::buildTaskGraph(QList<Task> database)
{
	taskElement tmpTaskElement ;
	taskElement subTaskElement ;

	taskGraph.clear();
	Task tmpTask ;
	foreach (tmpTask, database)
	{
		
		tmpTaskElement.taskID = tmpTask.getID();
		tmpTaskElement.actualStart = tmpTask.getEstimatedStartDate();
		tmpTaskElement.estimatedStart = tmpTaskElement.actualStart ;
		tmpTaskElement.name = tmpTask.getName();
		tmpTaskElement.level = 0;
		tmpTaskElement.duration = tmpTask.getDuration() * 86400;
		tmpTaskElement.parents.clear() ;
		if (tmpTask.getParent1() != 0)
			tmpTaskElement.parents.append(tmpTask.getParent1());
		if (tmpTask.getParent2() != 0)
			tmpTaskElement.parents.append(tmpTask.getParent2());
		if (tmpTask.getParent3() != 0)
			tmpTaskElement.parents.append(tmpTask.getParent3());
		if (tmpTask.getParent4() != 0)
			tmpTaskElement.parents.append(tmpTask.getParent4());
		if (tmpTask.getParent5() != 0)
			tmpTaskElement.parents.append(tmpTask.getParent5());
		taskGraph.append(tmpTaskElement);
	}
	foreach (tmpTaskElement, taskGraph)
	{
		int parent ;
		int i ;
		foreach (parent, tmpTaskElement.parents)
		{
			i = 0 ;
			foreach (subTaskElement, taskGraph)
			{
				if (subTaskElement.taskID == parent)
				taskGraph[i].addChild(tmpTaskElement.taskID);
				i = i + 1 ;				
			}
		}
	}
	
	foreach (tmpTaskElement, taskGraph)
	{
		if (tmpTaskElement.parents.size() == 0)
		{
			QDateTime parentEndTime ;
			parentEndTime = tmpTaskElement.estimatedStart.addSecs(tmpTaskElement.duration) ;
			tmpTaskElement.rootID = tmpTaskElement.taskID;
			int childTask ;
			foreach(childTask, tmpTaskElement.children)
			{
				updateChildStart(childTask, parentEndTime, tmpTaskElement.taskID, 1);
			}
		}
	}
	
}

int GLWidget::getTaskPosition(int taskNumber)
{
	taskElement tmpTaskElement ;
	int i = 0;
	foreach (tmpTaskElement, taskGraph)
	{
		if (tmpTaskElement.taskID == taskNumber)
		{
			return i ;
		}
		i = i + 1 ;
	}
	return 0 ;
}

void GLWidget::updateChildStart(int thisTaskID, QDateTime parentEndTime, int parentTaskID, int nextLevel)
{
	taskElement thisTaskElement ;

	int thisTaskPosition ;
	thisTaskPosition = getTaskPosition(thisTaskID);
	
	thisTaskElement = taskGraph[thisTaskPosition];
	taskGraph[thisTaskPosition].level = nextLevel ;

	if (parentEndTime > thisTaskElement.estimatedStart)
		{
			taskGraph[thisTaskPosition].actualStart = parentEndTime ;
			taskGraph[thisTaskPosition].criticalParent = parentTaskID ;
		};		
	QDateTime newEndTime ;
	newEndTime = thisTaskElement.actualStart.addSecs(thisTaskElement.duration) ;
	int childTask ;
	foreach(childTask,  thisTaskElement.children)
	{
		updateChildStart(childTask, newEndTime,  thisTaskID, nextLevel + 1);
	}
}

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
	displayLists = 1;
    displayListStart = 0;

	today = QDate(QDate::currentDate()) ;
	time = QTime(QTime::currentTime()) ;
	todayTime = QDateTime(today);
	
}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(displayListStart, displayLists);
}

void GLWidget::initializeGL()
{
    pert = 0 ;
		
	view.x = -320 ;
	view.y = 260 ;
	view.zoom = 1 ;			// default object scale
	view.aspectRatio = 1 ;			// default object scale

	worldMouse.x = 0;
	worldMouse.y = 0;

	shiftScale = 500 ;
	zoomScale = 1.25 ;
	fadeThreshold = .2 ;
	axisThreshold = .6 ;
	gamma = .2;
	baseGrid = .005 ;
	grid = baseGrid * 100000 ;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	displayLists = 3 ;

	displayListStart = glGenLists( displayLists );
	
}

void GLWidget::buildMilestones(QList<Milestone> allMilestones)
{
	Milestone tmpMilestone ;
	milestones.clear();
	foreach(tmpMilestone, allMilestones)
	{
		milestones.append(tmpMilestone);
	}
	updateGL();
}

double GLWidget::addGanttTask(int taskNumber, double y)
{
	taskElement drawTask ;
	drawTask = taskGraph[getTaskPosition(taskNumber)];
	double newY ;
	newY = y;
	
	if (tasksGanttDrawn.contains(taskNumber) == false)
	{
		double actualStartX = 0 ;
		double actualStopX = 0 ;
		double estimateStartX = 0 ;
		double estimateStopX = 0 ;
		double length ;
	
		actualStartX = -(double)(drawTask.actualStart.secsTo(todayTime))/864;
		estimateStartX = -(double)(drawTask.estimatedStart.secsTo(todayTime))/864;
		length = (double)drawTask.duration/86400 * 100 ;

		actualStopX = actualStartX + length ;
		estimateStopX = estimateStartX + length ;
		glColor4f(0.15,0.15,0.15,0.5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(estimateStartX, y);
			glVertex2f(estimateStopX, y);
			glVertex2f(estimateStopX, y - 50);
			glVertex2f(estimateStartX, y - 50);
		glEnd();
		glColor4f(.3,0.3,0.3,.7);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
			glVertex2f(estimateStartX, y);
			glVertex2f(estimateStopX, y);
			glVertex2f(estimateStopX, y - 50);
			glVertex2f(estimateStartX, y - 50);
		glEnd();
		glColor4f(0.4,0.4,0.4,0.9);

		drawTaskBox( actualStartX, actualStopX, y, ganttHeight, drawTask.parents.size(), drawTask.children.size(), drawTask.name);
		newY = y - ganttHeight ;
		
		if (ganttBoundary.ur.x > actualStopX)
		{
			ganttBoundary.ur.x = actualStopX;
		};
		
		if (ganttBoundary.ll.y < newY)
		{
			ganttBoundary.ll.y = newY;
		};
	
	};
	
	tasksGanttDrawn.append(taskNumber);
		
	int childTask ;
	foreach(childTask, drawTask.children)
	{
		newY = addGanttTask(childTask, newY);
	}
	return newY ;
}

void GLWidget::drawTaskBox(double start, double end, double y, double height, bool hasParents, bool hasChildren, QString name)
{
	glColor4f(0.4,0.4,0.4,0.9);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
		glVertex2f(start, y);
		glVertex2f(end, y);
		glVertex2f(end, y - height);
		glVertex2f(start, y - height);
	glEnd();
	glColor4f(.8,0.8,0.8,1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2f(start, y);
		glVertex2f(end, y);
		glVertex2f(end, y - height);
		glVertex2f(start, y - height);
	glEnd();
	if (hasParents == 0)
	{
	glBegin(GL_POLYGON);
		glVertex2f(start, y);
		glVertex2f(start + height/2, y - height/2);
		glVertex2f(start, y - height);
	glEnd();		
	}
	else
	{
	glBegin(GL_POLYGON);
		glVertex2f(start + height/5, y - 2*height/5);
		glVertex2f(start, y );
		glVertex2f(start - height/5, y - 2*height/5);
	glEnd();		
	};
	if (hasChildren == 0)
	{
	glBegin(GL_POLYGON);
		glVertex2f(end, y);
		glVertex2f(end - height/2, y - height/2);
		glVertex2f(end, y - height);
	glEnd();		
	}
	else
	{
	glBegin(GL_POLYGON);
		glVertex2f(end + height/5, y - 3*height/5);
		glVertex2f(end, y - height);
		glVertex2f(end - height/5, y - 3*height/5);
	glEnd();		
	};

	glColor4f(.8,.8,.8,1);
	renderText(start, y-height , 0 , name);
}

double GLWidget::addPertTask(int taskNumber, double y)
{
	taskElement drawTask ;
	drawTask = taskGraph[getTaskPosition(taskNumber)];
	double length ;
	double taskX ;
	double endX ;
	length = pertHeight * 5 ;

	double newY ;
	newY = y;
	
	if (tasksPertDrawn.contains(taskNumber) == false)
	{
		taskX = drawTask.level * length  ;
		endX = taskX + length ;
		
		drawTaskBox( taskX, endX, y, pertHeight, drawTask.parents.size(), drawTask.children.size(), drawTask.name);

		if (pertBoundary.ll.y < y)
		{
			pertBoundary.ll.y = y;
		};
	
		if (pertBoundary.ll.x > taskX)
		{
			pertBoundary.ll.x = taskX;
		};
	
		newY = y - 50 ;
	}
	tasksPertDrawn.append(taskNumber);
	
	int childTask ;
	foreach(childTask, drawTask.children)
	{
		newY = addPertTask(childTask, newY);
	}
	return newY ;
}

void GLWidget::buildTasks(QList<Task> allTasks)
{
	buildTaskGraph(allTasks);

	ganttHeight = 50 ;
	ganttBoundary.ll.x = 0 ;
	ganttBoundary.ur.x = 0 ;
	ganttBoundary.ll.x = 0 ;
	ganttBoundary.ur.x = 0 ;

	taskElement tmpTaskElement ;

	tasksGanttDrawn.clear();
	double y = 0 ;
	glNewList(displayListStart, GL_COMPILE);
	foreach (tmpTaskElement, taskGraph)
	{
		if (tmpTaskElement.parents.size() == 0)
		{
			y = addGanttTask(tmpTaskElement.taskID, y);
		}
	}
	glEndList();
	
	pertHeight = 50 ;
	pertBoundary.ll.x = 0 ;
	pertBoundary.ur.x = 0 ;
	pertBoundary.ll.x = 0 ;
	pertBoundary.ur.x = 0 ;

	tasksPertDrawn.clear();
	y = 0 ;
	glNewList(displayListStart + 1, GL_COMPILE);
	foreach (tmpTaskElement, taskGraph)
	{
		if (tmpTaskElement.parents.size() == 0)
		{
			y = addPertTask(tmpTaskElement.taskID, y);
		}
	}
	glEndList();
		
	updateGL();
}

void GLWidget::paintGL()
{
	glClear( GL_COLOR_BUFFER_BIT );
	draw();
}

void GLWidget::draw()
{
	glLoadIdentity();
	glScalef( view.zoom * view.aspectRatio, view.zoom, 1 );
//	glScalef( view.zoom, 1, 1 );
	glTranslatef( view.x, view.y, 0 );

	glGetIntegerv(GL_VIEWPORT,viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX,projmatrix);
	gluUnProject(window.ll.x, window.ll.y, 0, mvmatrix, projmatrix, viewport, &world.ll.x, &world.ll.y, &wz );
	gluUnProject(window.ur.x, window.ur.y, 0, mvmatrix, projmatrix, viewport, &world.ur.x, &world.ur.y, &wz );
	gluUnProject(window.ur.x, window.ur.y - 15, 0, mvmatrix, projmatrix, viewport, &world.ur.x, &monthLineY, &wz );
	gluUnProject(window.ur.x, window.ur.y - 30, 0, mvmatrix, projmatrix, viewport, &world.ur.x, &dayLineY, &wz );
	gluUnProject(window.ur.x, window.ur.y - 40, 0, mvmatrix, projmatrix, viewport, &world.ur.x, &markerY, &wz );

	GLdouble throwawayY ;
	GLdouble throwawayZ ;
	GLdouble markerProjection ;
	gluProject(world.ll.x, 0, 0, mvmatrix, projmatrix, viewport, &markerProjection, &throwawayY, &throwawayZ );
	GLdouble min ;
	gluUnProject(markerProjection-10, window.ll.y, 0, mvmatrix, projmatrix, viewport, &min, &throwawayY, &throwawayZ );
	markerDiff = world.ll.x - min ;
	gluUnProject(markerProjection-20, window.ll.y, 0, mvmatrix, projmatrix, viewport, &min, &throwawayY, &throwawayZ );
	characterHeight = (world.ll.x - min) * 1;

	if (pert)
	{
		drawPertChart();
	}
	else
	{
		drawGanttChart();
	};
	
}


void GLWidget::resizeGL(int width, int height)
{
	glViewport( 0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	window.ll.x = -(GLfloat)width;
	window.ll.y = -(GLfloat)height;
	window.ur.x = (GLfloat)width;
	window.ur.y = (GLfloat)height;
	gluOrtho2D(window.ll.x, window.ur.x, window.ll.y, window.ur.y);    
	glMatrixMode( GL_MODELVIEW );
	windowX = width ;
	windowY = height ;
	
}
void GLWidget::ganttMode() 
{
	pert = 0;
	updateGL();
	fitBoundary = ganttBoundary ;
	zoomFit();
}
void GLWidget::pertMode() 
{
	pert = 1;
	updateGL();
	fitBoundary = pertBoundary ;
	zoomFit();
}


QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(1600, 1200);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	
	int x = event->x();
	int y = windowY - event->y();
	mouseGrid = (double)grid;
	gluUnProject(x, y, 0, mvmatrix, projmatrix, viewport, &worldMouse.x, &worldMouse.y, &wz );
    if ( event->button() & Qt::RightButton ) {
        emit popupMenu(event->globalPos());
        return;
    };
    if ( event->button() & Qt::MidButton ) {
		gluUnProject((windowX/2), (windowY/2), 0, mvmatrix, projmatrix, viewport, &center.x, &center.y, &wz );
		gluUnProject((windowX/2)+1, (windowY/2)+1, 0, mvmatrix, projmatrix, viewport, &increment.x, &increment.y, &wz );
		increment.x = increment.x - center.x;
		increment.y = increment.y - center.y;
		atX = x;
		atY = y;
	};
    if ( event->button() & Qt::LeftButton ) {
		select(worldMouse);
	}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x() ;
	int y = windowY - event->y() ;
	mouseGrid = (double)grid;
	gluUnProject(x, y, 0, mvmatrix, projmatrix, viewport, &worldMouse.x, &worldMouse.y, &wz );
    if ( event->buttons() & Qt::MidButton ) {
		diffX = -(atX - x);
		diffY = -(atY - y);
		worldMouse.x = center.x - (increment.x * diffX);
		worldMouse.y = center.y - (increment.y * diffY);
		pan(worldMouse);
	};
	emit mouseLocation((double)worldMouse.x,(double)worldMouse.y);
}

void GLWidget::wheelEvent( QWheelEvent *event )
{

	if (event->delta() < 0){
		zoomIn();
		}
		else
		{
		zoomOut();
		};
	int x = event->x();
	int y = windowY - event->y();
	mouseGrid = (double)grid;
	gluUnProject(x, y, 0, mvmatrix, projmatrix, viewport, &worldMouse.x, &worldMouse.y, &wz );
}

void GLWidget::select(GLcoordinate panPoint)
{
	pan(panPoint);
//	updateGL();
}
void GLWidget::zoomFit()
{
	view.zoom = view.aspectRatio = 1;
//	view.x = (fitBoundary.ur.x - fitBoundary.ll.x) / 2 + fitBoundary.ur.x ;
//	view.y = (fitBoundary.ur.y - fitBoundary.ll.y) / 2 + fitBoundary.ur.y ;
//	view.zoom = (fitBoundary.ur.x - fitBoundary.ll.x) / 50 ;
	view.x = 0 ;
	view.y = 0 ;
	updateGL();
}
void GLWidget::zoomIn()
{
	view.zoom = view.zoom * zoomScale ;
	if (view.zoom > 1E4)
		view.zoom = 1E4;
	updateGL();
}
void GLWidget::zoomOut()
{
	view.zoom = view.zoom / zoomScale ;
	if (view.zoom < 1E-3)
		view.zoom = 1E-3;
	updateGL();
}
void GLWidget::pan( GLcoordinate pan)
{
	view.x = -pan.x;
    view.y = -pan.y;
	updateGL();
}
void GLWidget::panUp()
{
	view.y = view.y - (shiftScale/view.zoom);
	if (view.y < -1000000)
		view.y = -1000000;
	updateGL();
}
void GLWidget::panDown()
{
	view.y = view.y + (shiftScale/view.zoom);
	if (view.y > 1000000)
		view.y = 1000000;
	updateGL();
}
void GLWidget::panLeft()
{
	view.x = view.x + (shiftScale/view.zoom);
	if (view.x > 1000000)
		view.x = 1000000;
	updateGL();
}
void GLWidget::panRight()
{
	view.x = view.x - (shiftScale/view.zoom);
	if (view.x < -1000000)
		view.x = -1000000;
	updateGL();
}

void GLWidget::panUpRight()
{
	view.y = view.y - (shiftScale/view.zoom);
	if (view.y < -1000000)
		view.y = -1000000;
	view.x = view.x - (shiftScale/view.zoom);
	if (view.x < -1000000)
		view.x = -1000000;
	updateGL();
}
void GLWidget::panDownRight()
{
	view.y = view.y + (shiftScale/view.zoom);
	if (view.y > 1000000)
		view.y = 1000000;
	view.x = view.x - (shiftScale/view.zoom);
	if (view.x < -1000000)
		view.x = -1000000;
	updateGL();
}
void GLWidget::panUpLeft()
{
	view.y = view.y - (shiftScale/view.zoom);
	if (view.y < -1000000)
		view.y = -1000000;
	view.x = view.x + (shiftScale/view.zoom);
	if (view.x > 1000000)
		view.x = 1000000;
	updateGL();
}
void GLWidget::panDownLeft()
{
	view.y = view.y + (shiftScale/view.zoom);
	if (view.y > 1000000)
		view.y = 1000000;
	view.x = view.x + (shiftScale/view.zoom);
	if (view.x > 1000000)
		view.x = 1000000;
	updateGL();
}

void GLWidget::drawGanttChart()
{
	renderText(0, 0, 0.00 , ".");
	drawGanttBackground();
	drawGanttGraph();
	drawMilestones();
	drawToday();
	drawCalendarHeader();
	drawCalendar();
	drawDateAxis();
}

void GLWidget::drawGanttBackground()
{
	fade = view.zoom;
	grid = 100;
	gridXMin = floor(((double)world.ll.x)/grid)*grid ;
	gridYMin = floor(((double)world.ll.y)/grid)*grid ;
	gridXMax = ceil(((double)world.ur.x)/grid)*grid ;
	gridYMax = ceil(((double)world.ur.y)/grid)*grid ;
	for (double row = gridYMin; row < gridYMax; row = row + grid)
	{
		glColor4f(.1,0.1,0.1,.3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(world.ll.x,row);
			glVertex2f(world.ur.x,row);
			glVertex2f(world.ur.x,row + (grid/2));
			glVertex2f(world.ll.x,row + (grid/2));
		glEnd();
		glColor4f(0,0,0,.3);
		glBegin(GL_POLYGON);
			glVertex2f(world.ll.x,row + (grid/2));
			glVertex2f(world.ur.x,row + (grid/2));
			glVertex2f(world.ur.x,row + grid);
			glVertex2f(world.ll.x,row + grid);
		glEnd();
		glColor4f(1,1,1,1);
	};
	gridXMin = floor(((double)world.ll.x)/grid)*grid ;
	gridYMin = floor(((double)world.ll.y)/grid)*grid ;
	gridXMax = ceil(((double)world.ur.x)/grid)*grid ;
	gridYMax = ceil(((double)world.ur.y)/grid)*grid ;
	for (double column = gridXMin; column < gridXMax; column = column + grid)
	{
		brightness = (fade * 3 - gamma)/2 ;
		if (brightness > 0)
		{
			glColor4f(brightness,brightness,brightness,brightness);
			glBegin(GL_LINES);
				glVertex2f((GLfloat)column,dayLineY);
				glVertex2f((GLfloat)column,(GLfloat)world.ll.y);
			glEnd();
		};
	};
}

void GLWidget::drawGanttGraph()
{
	glCallList(displayListStart);
}

void GLWidget::drawCalendar()
{
	gridXMin = floor(((double)world.ll.x)/grid)*grid ;
	gridYMin = floor(((double)world.ll.y)/grid)*grid ;
	gridXMax = ceil(((double)world.ur.x)/grid)*grid ;
	gridYMax = ceil(((double)world.ur.y)/grid)*grid ;
	int dateCount ;
	for (double column = gridXMin; column < gridXMax; column = column + grid)
	{
		dateCount = (int)(column/grid) ; 
		brightness = fade - gamma ;
		if (brightness > 0)
		{
			glColor4f(.8,.8,.8,brightness);
			drawDayLabel((GLfloat)column, dayLineY, today.addDays(dateCount));
		};
		brightness = (fade * 3 - gamma)/2 ;
		if (brightness > 0)
		{
			glColor4f(brightness,brightness,brightness,brightness);
			glBegin(GL_LINES);
				glVertex2f((GLfloat)column,dayLineY);
				glVertex2f((GLfloat)column,monthLineY);
			glEnd();
		};
		brightness = (fade * 40 - gamma)/2 ;
		if ((today.addDays(dateCount).day() == 1) and (brightness > 0))
		{
			glColor4f(brightness,brightness,brightness,brightness);
			drawMonthLabel((GLfloat)column, monthLineY, today.addDays(dateCount));
			glBegin(GL_LINES);
				glVertex2f((GLfloat)column,(GLfloat)world.ur.y);
				glVertex2f((GLfloat)column,monthLineY);
			glEnd();
		};
	};
}

void GLWidget::drawDateAxis()
{
	glColor3f(.666,0.4,0.4);
	glBegin(GL_LINES);
		glVertex2f(world.ll.x,dayLineY);
		glVertex2f(world.ur.x,dayLineY);
	glEnd();
	glColor3f(1,0.6,0.6);
	glBegin(GL_LINES);
		glVertex2f(world.ll.x,monthLineY);
		glVertex2f(world.ur.x,monthLineY);
	glEnd();
	glColor3f(1,1,1);
}

void GLWidget::drawCalendarHeader()
{
	glColor4f(.3,0.2,0.2,.3);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
		glVertex2f(world.ll.x,dayLineY);
		glVertex2f(world.ur.x,dayLineY);
		glVertex2f(world.ur.x,world.ur.y);
		glVertex2f(world.ll.x,world.ur.y);
	glEnd();
	glColor4f(1,1,1,1);
}
void GLWidget::drawToday()
{
	drawDateMarker(0.0) ;
}

void GLWidget::drawDateMarker(GLfloat x)
{
	glColor4f(.6,.4,.2,1);
	glBegin(GL_LINES);
		glVertex2f(x,dayLineY);
		glVertex2f(x,world.ll.y);
	glEnd();
	glColor4f(1,1,1,1);
	drawMarkerTriangle(x);
}
void GLWidget::drawMarkerTriangle(GLfloat x)
{
		glColor4f(0.4,0.4,0.4,0.5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(x, markerY);
			glVertex2f(x - markerDiff, markerY + markerDiff);
			glVertex2f(x + markerDiff, markerY + markerDiff);
		glEnd();
		glColor4f(.8,0.8,0.8,1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
			glVertex2f(x, markerY);
			glVertex2f(x - markerDiff, markerY + markerDiff);
			glVertex2f(x + markerDiff, markerY + markerDiff);
		glEnd();
		glColor4f(1,1,1,1);
}
void GLWidget::drawMilestones()
{
	double x = 0 ;
	Milestone tmpMilestone ;
	QString milestoneName ;
	QString milestoneCharacter ;
	foreach(tmpMilestone, milestones)
	{
		double y = markerY ;
		x = -(double)(tmpMilestone.getDeadline().secsTo(todayTime))/864 ;
		drawMilestoneMarker(x) ;
		milestoneName = tmpMilestone.getName() ;
//		x = x - characterHeight/2 ;
		for (int i = 0; i < milestoneName.size(); ++i ) {
			milestoneCharacter = milestoneName.at(i);
			renderText(x,y , 0 , milestoneCharacter);
			y = y - characterHeight;
		}
	}
}

void GLWidget::drawMilestoneMarker(GLfloat x)
{
	glColor4f(.8,0,0,1);
	glBegin(GL_LINES);
		glVertex2f(x,dayLineY);
		glVertex2f(x,world.ll.y);
	glEnd();
	glColor4f(1,1,1,1);
	drawMilestoneTriangle(x);
}

void GLWidget::drawMilestoneTriangle(GLfloat x)
{
		glColor4f(0.4,0,0,0.5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			glVertex2f(x, markerY);
			glVertex2f(x - markerDiff, markerY + markerDiff);
			glVertex2f(x + markerDiff, markerY + markerDiff);
		glEnd();
		glColor4f(.8,0,0,1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_POLYGON);
			glVertex2f(x, markerY);
			glVertex2f(x - markerDiff, markerY + markerDiff);
			glVertex2f(x + markerDiff, markerY + markerDiff);
		glEnd();
		glColor4f(1,1,1,1);
}
void GLWidget::drawDayLabel(GLfloat x, GLfloat y, QDate date)
{
	renderText(x, y, 0.00 , date.toString("d"));
}
void GLWidget::drawMonthLabel(GLfloat x, GLfloat y, QDate date)
{
	renderText(x, y, 0.00 , date.toString("MMMM"));
}

void GLWidget::drawPertChart()
{
	fade = view.zoom / 10000;
	if (fade > fadeThreshold)
	{
		grid = baseGrid ;
		gridXMin = floor(((double)world.ll.x)/grid)*grid ;
		gridYMin = floor(((double)world.ll.y)/grid)*grid ;
		gridXMax = ceil(((double)world.ur.x)/grid)*grid ;
		gridYMax = ceil(((double)world.ur.y)/grid)*grid ;
		brightness = (fade - gamma) *.4;
		glColor3f(brightness,brightness,brightness);
		glBegin(GL_LINES);
		for (double row = gridYMin; row < gridYMax; row = row + grid )
		{
			glVertex2f(gridXMin, (GLfloat)row);
			glVertex2f(gridXMax, (GLfloat)row);
		};
		for (double column = gridXMin; column < gridXMax; column = column + grid)
		{
			glVertex2f((GLfloat)column, gridYMin);
			glVertex2f((GLfloat)column, gridYMax);
		}
		glEnd();
	};

	drawAxis();

	fade = view.zoom / 1000;
	if (fade > fadeThreshold)
	{
		grid = baseGrid * 10 ;
		drawGrid();
		if (fade < axisThreshold)
		{
			drawAxis();
		};
	};

	fade = view.zoom / 100;
	if (fade > fadeThreshold)
	{
		grid = baseGrid * 100 ;
		drawGrid();
		if (fade < axisThreshold)
		{
			drawAxis();
		};
	};

	fade = view.zoom / 10;
	if (fade > fadeThreshold)
	{
		grid = baseGrid * 1000 ;
		drawGrid();
		if (fade < axisThreshold)
		{
			drawAxis();
		};
	}

	fade = view.zoom;
	if (fade > fadeThreshold)
	{
		grid = baseGrid * 10000 ;
		drawGrid();
		if (fade < axisThreshold)
		{
			drawAxis();
		};
	};

	glCallList(displayListStart+1);
}

void GLWidget::drawGrid()
{
	gridXMin = floor(((double)world.ll.x)/grid)*grid ;
	gridYMin = floor(((double)world.ll.y)/grid)*grid ;
	gridXMax = ceil(((double)world.ur.x)/grid)*grid ;
	gridYMax = ceil(((double)world.ur.y)/grid)*grid ;
	brightness = fade - gamma ;
	glColor3f(brightness,brightness,brightness);
	glBegin(GL_POINTS);
	for (double row = gridYMin ; row < gridYMax; row = row + grid)
	{
		for (double column = gridXMin; column < gridXMax; column = column + grid)
		{
			glVertex2f((GLfloat)column, (GLfloat)row);
		};	
	};
	glEnd();
}

void GLWidget::drawAxis()
{
	//Axis
	glColor3f(0.6,0.6,0.6);
	glBegin(GL_LINES);
		glVertex2f(world.ll.x,0.0);
		glVertex2f(world.ur.x,0.0);
		glVertex2f(0.0,world.ll.y);
		glVertex2f(0.0,world.ur.y);
	glEnd();
	glColor3f(1,1,1);
}
