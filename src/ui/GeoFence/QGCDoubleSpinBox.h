#ifndef QGCDOUBLESPINBOX_H
#define QGCDOUBLESPINBOX_H

#include <QDoubleSpinBox>

//! This class is derived from QDoubleSpinBox and reports when it receives focus
class QGCDoubleSpinBox : public QDoubleSpinBox
{
	Q_OBJECT

public:
	//! Constructor
	QGCDoubleSpinBox(QWidget* pParent = 0);
	//! Destructor
	~QGCDoubleSpinBox();

protected:
	//! Emits a signal when it receives focus
	void focusInEvent(QFocusEvent* pFE);

signals:
	/** This signal is emitted when the widget receives focus in order for parent widget
	 *  to know, which zone is current
	 */
	void SignalCurrent();
};

#endif // QGCDOUBLESPINBOX_H
