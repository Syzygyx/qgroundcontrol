#ifndef FLIGHTGEARGRABWIDGET_H
#define FLIGHTGEARGRABWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

//! This class is used to show the screenshots from FlightGear
class FlightGearGrabWidget : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	FlightGearGrabWidget(QWidget* pParent = 0);
	//! Destructor
	~FlightGearGrabWidget();

public slots:
	//! Tries to get a screenshot from FlightGear
	void GetScreenshot();

protected:
	//! Paints the saved pixmap
	void paintEvent(QPaintEvent*);

protected slots:
	//! Handles the received screenshot
	void HandleScreenshot();
	//! Handles the errors
	void HandleError(QNetworkReply::NetworkError);

private:
	//! Last screenshot recovered from FlightGear
	QPixmap m_pix;
	//! Pointer to the network access manager object
	QNetworkAccessManager* m_pNetManager;
	//! Set to true, while network access manager is downloading the screenshot
	bool m_bBusy;
	//! Timer for regularly requesting screenshots
	QTimer* m_pTimer;
};

#endif // FLIGHTGEARGRABWIDGET_H
