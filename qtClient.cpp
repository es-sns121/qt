
#include <QApplication>
#include "window.h"

int main (int argc, char **argv) {
	
	QApplication app (argc, argv);

	Window window;
	window.start("PVRubyte");
	
	window.show();

	return app.exec();
}
