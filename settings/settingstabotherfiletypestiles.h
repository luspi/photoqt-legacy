/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SETTINGSTABOTHERFILETYPESTILES_H
#define SETTINGSTABOTHERFILETYPESTILES_H

#include "../customelements/customcheckbox.h"
#include "../customelements/customlabel.h"

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>

class SettingsTabOtherFileTypesTiles : public QWidget {

	Q_OBJECT

public:
	SettingsTabOtherFileTypesTiles(QString ftype, QWidget *parent = 0);
	~SettingsTabOtherFileTypesTiles();

	QString filetype;

	// The label that's being styled
	CustomLabel *back;

	// And the checkbox to enable or disable this tile
	CustomCheckBox *enabled;

	// Set this checkbox checked
	void setChecked(bool chkd);
	bool isChecked() { return enabled->isChecked(); }
	void setEnabled(bool);
	void setUnavailable(bool unavail);
	void setToolTip(const QString &tt) { tooltipString = tt; QWidget::setToolTip((unavailable ? QString(tr("UNAVAILABLE") + " - ") : "") + tooltipString); }

private:
	// Different css styles
	QString css;
	QString cssOff;
	QString cssBackgroundNorm;
	QString cssBackgroundOffNorm;
	QString cssBackgroundHov;
	QString cssBackgroundOffHov;
	QString cssBackgroundHoverUnavailable;
	QString cssBackgroundNormUnavailable;
	QString cssToolTip;

	QString tooltipString;
	bool unavailable;


private slots:
	// A click on a checkbox
	void checkboxClicked();

protected:
	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *);
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *);

};

#endif // SETTINGSTABOTHERFILETYPESTILES_H
