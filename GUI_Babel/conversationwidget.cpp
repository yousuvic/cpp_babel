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

void conversationWidget::lauchCall()
{
	_sW->addWidget(call);
	_sW->setCurrentWidget(call);
}