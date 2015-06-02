#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>
#include <QFrame>
#include <QSplitter>
#include <QVBoxLayout>
#include <QList>
#include <QAction>
#include <QActionGroup>
#include <QtOpenGL>
#include <QGLWidget>
#include <QtGui>
#include <QIcon>
#include "MainWindow.h"
#include "TabWidget.h"
#include "../glwidget.h"


/*
 * This is the main window of the application.
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

	public:
    	MainWindow();

    private slots:
		void editPreferences();
        void newFile();
        void open();
        void save();
        void print();
        void undo();
        void redo();
        void cut();
        void copy();
        void paste();
        void about();

    private:
        void createActions();
        void createMenus();
        void createToolBars();
        void createStatusBar();
        
        //rep
        TabWidget *tabWidget;
 //       SideWidget *_sideWidget;
        
		QGLWidget *GLViewPort;
		QFrame *GLFrame;
		QSplitter *TopSplitter;
		QGridLayout *GLLayout;
		QGridLayout *FrameLayout;
		QList<int> splitterSizes;
         //ResourceWidget *resWidget;        
        QLabel *modLabel;
                    
		QMenu *fileMenu;
		QToolBar *fileToolBar;
		QAction *prefAct;
		QAction *printAct;
		QAction *newAct;
		QAction *openAct;
		QAction *saveAct;
		QAction *saveAsAct;
		QAction *exitAct;	

		QMenu *editMenu;
		QActionGroup *editGrp;
		QToolBar *editToolBar;
		QAction *selectAct;
		QAction *polygonAddAct;
		QAction *componentAddAct;
		QAction *queryAct;
		QAction *rulerAct;
		QAction *moveAct;
		QAction *deleteAct;
		QAction *cutAct;
		QAction *copyAct;
		QAction *pasteAct;

		QMenu *viewMenu;
		QActionGroup *viewGrp;
		QToolBar *viewToolBar;
		QAction *ganttAct;
		QAction *pertAct;
		QAction *redrawAct;
		QAction *zoomFitAct;
		QAction *zoomInAct;
		QAction *zoomOutAct;
		QAction *panUpAct;
		QAction *panDownAct;
		QAction *panLeftAct;
		QAction *panRightAct;
		QAction *panUpRightAct;
		QAction *panDownRightAct;
		QAction *panUpLeftAct;
		QAction *panDownLeftAct;


		QMenu *helpMenu;
		QAction *aboutAct;
		QAction *aboutQtAct;
        
        QToolBar *toolBar;

	friend class Kernel;
};

#endif
