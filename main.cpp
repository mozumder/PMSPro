#include <QApplication>

//#include "main_window_files/MainWindow.h"
#include "data_classes_files/Kernel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Kernel kernel;
	kernel.login();
	kernel.connectDB();
	kernel.showMainWindow();
	return app.exec();
}
