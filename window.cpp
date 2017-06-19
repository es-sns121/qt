#include "window.h"

#include <sstream>
#include <pthread.h>

using namespace std;
using namespace epics::pvaClient;
using namespace epics::pvData;

class thread_arg {
	public:
		PvaClientMonitorPtr monitor;
		QLineEdit * _text;
};

Window::Window(QWidget *parent) : 
	QWidget(parent) {

	setFixedSize(100, 100);

	_text = new QLineEdit(this);
	_text->setReadOnly(true);
	_text->setGeometry(10, 10, 80, 50);
}

void* poll(void *arg) {
	thread_arg *a = (thread_arg *) arg;

	while (true) {		
		a->monitor->waitEvent();
		
		a->monitor->getData();

		string value = a->monitor->getData()->getPVStructure()->getSubField<PVUByte>("value")->getAs<string>();
		
		a->_text->setText(value.c_str());

		a->monitor->releaseEvent();
	}
}

void Window::start(const string & channel_name) {
	this->channel_name = channel_name;
	pva = PvaClient::get();
	channel = pva->channel(channel_name);
	monitor = channel->monitor("");

	thread_arg *arg = new thread_arg();
	arg->monitor = monitor;
	arg->_text = _text;

	pthread_t poll_thread;
	pthread_create(&poll_thread, NULL, poll, (void *) arg);
	
}

