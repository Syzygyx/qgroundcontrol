#ifndef VEHICLEWIDGET_H
#define VEHICLEWIDGET_H

#include <QWidget>
#include <QSvgRenderer>

#include "qcgaugewidget.h"

#define GAUGE_COUNT					7

//! This widget shows a top down view of the vehicle
class VehicleWidget : public QWidget
{
	Q_OBJECT

public:
	//! Constructor
	VehicleWidget(QWidget* pParent = 0);
	//! Destructor
	~VehicleWidget();
	/** Sets i-th gauge to the widget, calculates the correct position and size of gauge.
	 *  VehicleWidget will take ownership of the gauge widget, so do not delete it
	 *  outside of this class!
	 */
	void SetGauge(int i, QcGaugeWidget* pGauge);

public slots:
	//! Sets the temperature and RPM of i-th gauge
	void SetTempRPM(int i, double dTemp, double dRPM);

protected:
	//! Returns the center of i-th engine
	virtual QPoint GetCenter(int i) const;
	//! Returns the size of i-th engine
	virtual int GetSize(int i) const;

	//! Paints the widget
	void paintEvent(QPaintEvent*);
	//! This is intended to find locations for gauges
	void mousePressEvent(QMouseEvent* pME);
	//! Handles the resize events by moving the gauges as well
	void resizeEvent(QResizeEvent*);

	//! Creates the internal vehicle pixmap
	virtual void CreateVehiclePixmap();

protected:
	//! Object, which renders the vehicle widget from SVG
	QSvgRenderer* m_pSvgRender;
	//! Array of pointers to gauges
	QcGaugeWidget* m_apGauges[GAUGE_COUNT];
	//! Internal pixmap, which holds the vehicle photo
	QPixmap* m_pPixVehicle;
	//! Scaled vehicle pixmap
	QPixmap m_pixScaled;
};

#endif // VEHICLEWIDGET_H
