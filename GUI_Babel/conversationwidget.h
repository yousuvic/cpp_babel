#ifndef CONVERSATIONWIDGET_H
#define CONVERSATIONWIDGET_H

#include <QWidget>
#include <qstackedwidget.h>
#include <windows.h>
#include <process.h>
#include "QThread"
#include "ui_conversationwidget.h"
#include "callwidget.h"
#include "worker.h"

class conversationWidget : public QWidget
{
	Q_OBJECT

public:
	conversationWidget(std::string user, QStackedWidget *sW, QWidget *parent = 0);
	~conversationWidget();

private:
	QStackedWidget *_sW;
	Ui::conversationWidget ui;
	callWidget *call;

	QThread *thread;
	Worker *worker;

private slots:
	void lauchCall();
};

#endif // CONVERSATIONWIDGET_H
