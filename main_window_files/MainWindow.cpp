#include <QtGui>

#include "MainWindow.h"

MainWindow::MainWindow()
{
	
    QSplitter *topSplitter = new QSplitter;
    setCentralWidget(topSplitter);

	GLFrame = new QFrame(topSplitter);
	GLFrame->setFrameStyle( QFrame::Sunken | QFrame::Panel );
	GLFrame->setLineWidth( 1 );
	GLFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	GLViewPort = new GLWidget(GLFrame);
	GLViewPort->setFocusPolicy(Qt::ClickFocus);
	GLViewPort->setMouseTracking(TRUE);
	GLViewPort->setFocus();
	
	GLLayout = new QGridLayout(GLFrame);
	GLLayout->addWidget( GLViewPort,0,1 );

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    tabWidget = new TabWidget();

    setWindowTitle(tr("PMSPro"));
    setMinimumSize(300, 300);
	QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setMargin(5);
	gridLayout->addWidget(tabWidget);
	QWidget *w = new QWidget ;
	w->setLayout(gridLayout);
    topSplitter->addWidget(w);
    topSplitter->addWidget(GLFrame);
//	topSplitter->setMargin(5);    
 //   w->setLayout(gridLayout);

    statusBar()->showMessage( "Ready", 2000 );
}

void MainWindow::newFile()
{
   
}

void MainWindow::open()
{
    
}

void MainWindow::save()
{
    
}

/*
 * Print the schedule graph.
 * Opens a dialog in which the user can select a printer, paper format,
 * and possibly other parameters.  Note that although the Qcode is portable,
 * the implementation of this function will vary across platforms.
 */
void MainWindow::print()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
    	QImage image = GLViewPort->grabFrameBuffer();
    	painter.drawImage(0,0, image);
    }    	
}

void MainWindow::undo()
{
    
}

void MainWindow::redo()
{
    
}

void MainWindow::cut()
{
    
}

void MainWindow::copy()
{
    
}

void MainWindow::paste()
{
    
}

void MainWindow::about()
{
    
    QMessageBox::about(this, tr("About PMSPro"),
            tr("PMS Pro Version 1.0\n\nBrought to you by:\n\nBobby Mozumder\nIan Kavanagh\nTimothy Forcier\nSteven Whaley"
            	));
}

void MainWindow::createActions()
{

	// File Actions

    prefAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/preferences.png"), tr("Preferences"), this);
	prefAct->setShortcut(tr("Ctrl+Shift+P"));
    prefAct->setStatusTip(tr("Edit Preferences"));
    prefAct->setToolTip(tr("Edit Preferences"));
    connect(prefAct, SIGNAL(triggered()), this, SLOT(editPreferences()));

    printAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/printer3.png"), tr("&Print"), this);
	printAct->setShortcut(tr("Ctrl+P"));
    printAct->setStatusTip(tr("Print"));
    printAct->setToolTip(tr("Print"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    newAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/document_new.png"), tr("&New"), this);
    newAct->setShortcut(tr("Ctrl+N"));
    newAct->setStatusTip(tr("Create a new file"));
    newAct->setToolTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/folder_out.png"), tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    openAct->setStatusTip(tr("Open an existing file"));
    openAct->setToolTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/disk_blue.png"), tr("&Save"), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    saveAct->setStatusTip(tr("Save the document to disk"));
    saveAct->setToolTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/folder_new.png"), tr("Save &As..."), this);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    saveAsAct->setToolTip(tr("Save the document under a new name"));
//    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/exit.png"), tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setToolTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	// Edit Actions

    cutAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/cut.png"), tr("Cu&t"), this);
    cutAct->setShortcut(tr("Ctrl+X"));
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    cutAct->setToolTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
	//connect(cutAct, SIGNAL(triggered()), TextEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/copy.png"), tr("&Copy"), this);
    copyAct->setShortcut(tr("Ctrl+C"));
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    copyAct->setToolTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
	//connect(copyAct, SIGNAL(triggered()), TextEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcut(tr("Ctrl+V"));
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    pasteAct->setToolTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
	//connect(pasteAct, SIGNAL(triggered()), TextEdit, SLOT(paste()));

	// View Actions

    ganttAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/refresh.png"), tr("Gantt Chart"), this);
    ganttAct->setShortcut(Qt::Key_G);
    ganttAct->setStatusTip(tr("Show Gantt Chart"));
    ganttAct->setToolTip(tr("Show Gantt Chart"));
    connect(ganttAct, SIGNAL(triggered()), GLViewPort, SLOT(ganttMode()));
	
    pertAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/refresh.png"), tr("Pert Chart"), this);
    pertAct->setShortcut(Qt::Key_P);
    pertAct->setStatusTip(tr("Show Pert Chart"));
    pertAct->setToolTip(tr("Show Pert Chart"));
    connect(pertAct, SIGNAL(triggered()), GLViewPort, SLOT(pertMode()));

//    redrawAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/refresh.png"), tr("Redraw"), this);
//    redrawAct->setShortcut(Qt::Key_R);
//    redrawAct->setStatusTip(tr("Redraw"));
//    redrawAct->setToolTip(tr("Redraw"));
//    connect(redrawAct, SIGNAL(triggered()), GLViewPort, SLOT(redraw()));

    zoomInAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/zoom_in.png"), tr("Zoom In"), this);
    zoomInAct->setShortcut(Qt::Key_Z);
    zoomInAct->setStatusTip(tr("Zoom In"));
    zoomInAct->setToolTip(tr("Zoom In"));
    connect(zoomInAct, SIGNAL(triggered()), GLViewPort, SLOT(zoomIn()));

    zoomOutAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/zoom_out.png"), tr("Zoom Out"), this);
    zoomOutAct->setShortcut(Qt::SHIFT + Qt::Key_Z);
    zoomOutAct->setStatusTip(tr("Zoom Out"));
    zoomOutAct->setToolTip(tr("Zoom Out"));
    connect(zoomOutAct, SIGNAL(triggered()), GLViewPort, SLOT(zoomOut()));

    zoomFitAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/fit_to_size.png"), tr("Zoom Fit"), this);
    zoomFitAct->setShortcut(Qt::Key_F);
    zoomFitAct->setStatusTip(tr("Zoom Fit"));
    zoomFitAct->setToolTip(tr("Zoom Fit"));
    connect(zoomFitAct, SIGNAL(triggered()), GLViewPort, SLOT(zoomFit()));

    panUpAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_up_green.png"), tr("Pan Up"), this);
    panUpAct->setShortcut(Qt::Key_Up);
    panUpAct->setStatusTip(tr("Pan Up"));
    panUpAct->setToolTip(tr("Pan Up"));
    connect(panUpAct, SIGNAL(triggered()), GLViewPort, SLOT(panUp()));

    panDownAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_down_green.png"), tr("Pan Down"), this);
    panDownAct->setShortcut(Qt::Key_Down);
    panDownAct->setStatusTip(tr("Pan Down"));
    panDownAct->setToolTip(tr("Pan Down"));
    connect(panDownAct, SIGNAL(triggered()), GLViewPort, SLOT(panDown()));

    panLeftAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_left_green.png"), tr("Pan Left"), this);
    panLeftAct->setShortcut(Qt::Key_Left);
    panLeftAct->setStatusTip(tr("Pan Left"));
    panLeftAct->setToolTip(tr("Pan Left"));
    connect(panLeftAct, SIGNAL(triggered()), GLViewPort, SLOT(panLeft()));

    panRightAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_right_green.png"), tr("Pan Right"), this);
    panRightAct->setShortcut(Qt::Key_Right);
    panRightAct->setStatusTip(tr("Pan Right"));
    panRightAct->setToolTip(tr("Pan Right"));
    connect(panRightAct, SIGNAL(triggered()), GLViewPort, SLOT(panRight()));

    panUpRightAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_up_right_green.png"), tr("Pan Up Right"), this);
    panUpRightAct->setStatusTip(tr("Pan Up Right"));
    panUpRightAct->setToolTip(tr("Pan Up Right"));
    connect(panUpRightAct, SIGNAL(triggered()), GLViewPort, SLOT(panUpRight()));

    panUpLeftAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_up_left_green.png"), tr("Pan Up Left"), this);
    panUpLeftAct->setStatusTip(tr("Pan Up Left"));
    panUpLeftAct->setToolTip(tr("Pan Up Left"));
    connect(panUpLeftAct, SIGNAL(triggered()), GLViewPort, SLOT(panUpLeft()));

    panDownRightAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_down_right_green.png"), tr("Pan Down Right"), this);
    panDownRightAct->setStatusTip(tr("Pan Down Right"));
    panDownRightAct->setToolTip(tr("Pan Down Right"));
    connect(panDownRightAct, SIGNAL(triggered()), GLViewPort, SLOT(panDownRight()));

    panDownLeftAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/nav_down_left_green.png"), tr("Pan Down Left"), this);
    panDownLeftAct->setStatusTip(tr("Pan Down Left"));
    panDownLeftAct->setToolTip(tr("Pan Down Left"));
    connect(panDownLeftAct, SIGNAL(triggered()), GLViewPort, SLOT(panDownLeft()));

	// Help Actions
    aboutQtAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/help.png"), tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    aboutQtAct->setToolTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    aboutAct = new QAction(QIcon(":/images/ix_ap_all/32x32/shadow/about.png"), tr("&About"), this);
    aboutAct->setStatusTip(tr("About PMSPro"));
    aboutAct->setToolTip(tr("About PMSPro"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(prefAct);
    fileMenu->addAction(printAct);
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(ganttAct);
    viewMenu->addAction(pertAct);
    viewMenu->addAction(zoomFitAct);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
//    viewMenu->addAction(redrawAct);
// 	std::cout << "redraw added." << std::endl ;
    viewMenu->addAction(panUpAct);
    viewMenu->addAction(panDownAct);
    viewMenu->addAction(panLeftAct);
    viewMenu->addAction(panRightAct);
    viewMenu->addAction(panUpRightAct);
    viewMenu->addAction(panDownRightAct);
    viewMenu->addAction(panUpLeftAct);
    viewMenu->addAction(panDownLeftAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = new QToolBar(this);
    fileToolBar->setWindowTitle(tr("File"));
    fileToolBar->addAction(printAct);
//    fileToolBar->addAction(newAct);
//    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
	addToolBar(fileToolBar);

    editToolBar = new QToolBar(this);
    editToolBar->setWindowTitle(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
	addToolBar(editToolBar);

    viewToolBar = new QToolBar(this);
    viewToolBar->setWindowTitle(tr("View"));
    viewToolBar->addAction(ganttAct);
    viewToolBar->addAction(pertAct);
    viewToolBar->addAction(zoomFitAct);
    viewToolBar->addAction(zoomInAct);
    viewToolBar->addAction(zoomOutAct);
//    viewToolBar->addAction(redrawAct);
    viewToolBar->addAction(panUpAct);
    viewToolBar->addAction(panDownAct);
    viewToolBar->addAction(panLeftAct);
    viewToolBar->addAction(panRightAct);
    viewToolBar->addAction(panUpRightAct);
    viewToolBar->addAction(panDownRightAct);
    viewToolBar->addAction(panUpLeftAct);
    viewToolBar->addAction(panDownLeftAct);
	addToolBar(viewToolBar);
}

void MainWindow::createStatusBar()
{
    modLabel = new QLabel(tr(" MOD "));
    modLabel->setAlignment(Qt::AlignHCenter);
    modLabel->setMinimumSize(modLabel->sizeHint());
    modLabel->clear();

    statusBar()->addWidget(modLabel, 0);
}

void MainWindow::editPreferences()
{
}

