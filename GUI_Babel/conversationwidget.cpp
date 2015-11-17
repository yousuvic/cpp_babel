#include "conversationwidget.h"
#include "callwidget.h"

conversationWidget::conversationWidget(std::string user, QStackedWidget *sW, QWidget *parent)
: QWidget(parent), _sW(sW)
{
	ui.setupUi(this);
	ui.userLbl->setText(QString::fromStdString(user));
	call = new callWidget();
	QObject::connect(ui.callBtn, SIGNAL(clicked()), this, SLOT(lauchCall()));
}

conversationWidget::~conversationWidget()
{
	delete (call);
}

DWORD WINAPI myThread(LPVOID lpParameter)
{
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	while (myCounter < 0xFFFFFFFF) ++myCounter;
	return 0;
}

void conversationWidget::lauchCall()
{
	_sW->addWidget(call);
	_sW->setCurrentWidget(call);

	thread = new QThread();
	worker = new Worker();

	worker->moveToThread(thread);
	thread->start();
	connect(this, SIGNAL(running()), worker, SLOT(run()));
	emit running();
}