#include <QPainter>
#include <QDebug>

#include "FlightGearGrabWidget.h"

//-----------------------------------------------------------------------------

FlightGearGrabWidget::FlightGearGrabWidget(QWidget* pParent) :
	QWidget(pParent)
{
	m_pNetManager = new QNetworkAccessManager(this);
	m_bBusy = false;

	// make sure the screenshots will be grabbed 10 times per second
	// maybe it's too fast, but m_bBusy flag will protect the app from
	// simultaneous requests
	m_pTimer = new QTimer(this);
	m_pTimer->setInterval(100);
	connect(m_pTimer, SIGNAL(timeout()), this, SLOT(GetScreenshot()));
	m_pTimer->start();

	setMinimumSize(320, 240);
}

//-----------------------------------------------------------------------------

FlightGearGrabWidget::~FlightGearGrabWidget()
{
	delete m_pNetManager;
	delete m_pTimer;
}

//-----------------------------------------------------------------------------

void FlightGearGrabWidget::GetScreenshot()
{
	// prevent multiple requests
	if (m_bBusy == true)
		return;

	// Build the request
	QNetworkRequest request;
	request.setUrl(QUrl("http://localhost:8080/screenshot"));
	request.setRawHeader("User-Agent", "QGroundControl");

	QNetworkReply* pReply = m_pNetManager->get(request);
	connect(pReply, SIGNAL(finished()), this, SLOT(HandleScreenshot()));
	connect(
				pReply,
				SIGNAL(error(QNetworkReply::NetworkError)),
				this,
				SLOT(HandleError(QNetworkReply::NetworkError))
				);
}

//-----------------------------------------------------------------------------

void FlightGearGrabWidget::paintEvent(QPaintEvent*)
{
	// resize the pix to fit into widget
	QPixmap pix = m_pix.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QPainter P(this);
	// draw it centered
	P.drawPixmap(
				(width() - pix.width())/2,
				(height() - pix.height())/2,
				pix
				);
}

//-----------------------------------------------------------------------------

void FlightGearGrabWidget::HandleScreenshot()
{
	QNetworkReply* pReply = dynamic_cast<QNetworkReply*>(sender());
	if (pReply != 0 && pReply->error() == QNetworkReply::NoError) {
		// read the received data and convert it into pixmap
		QByteArray ba = pReply->readAll();
		m_pix.loadFromData(ba, "JPEG");
	}
	m_bBusy = false;
	update();
	pReply->deleteLater();
}

//-----------------------------------------------------------------------------

void FlightGearGrabWidget::HandleError(QNetworkReply::NetworkError)
{
	m_pix = QPixmap(size());
	m_pix.fill(Qt::transparent);

	QPainter P(&m_pix);

	P.setPen(Qt::darkRed);
	QFont fnt = P.font();
	int iS = width()/15;
	if (iS < 12)
		iS = 12;
	else if (iS > 48)
		iS = 48;
	fnt.setPixelSize(iS);
	fnt.setBold(true);
	P.setFont(fnt);
	P.drawText(0, 0, width(), height(), Qt::AlignCenter, tr("FlightGear not running!"));

	m_bBusy = false;

	update();
}

//-----------------------------------------------------------------------------

