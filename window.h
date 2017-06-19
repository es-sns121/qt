#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLineEdit>

#include "pv/pvaClient.h"

class Window : public QWidget {
	Q_OBJECT
	public:
		explicit Window(QWidget *parent = 0);
		void start(const std::string & channel_name);

	private:
		epics::pvaClient::PvaClientPtr            pva;
		epics::pvaClient::PvaClientChannelPtr     channel;
		epics::pvaClient::PvaClientMonitorPtr     monitor;
		epics::pvaClient::PvaClientMonitorDataPtr data;
	
		std::string channel_name;

		QLineEdit   *_text;
};

#endif /* WINDOW_H */
