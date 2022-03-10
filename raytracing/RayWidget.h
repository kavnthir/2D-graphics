#ifndef RAYWIDGET_H
#define RAYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QCursor>
#include <iostream>

class RayWidget: public QWidget {
  Q_OBJECT

public:
	RayWidget(QWidget * parent = nullptr);

public slots:
	void updatePos();

private:
	QPointF pos;
	QPainter painter;
};

#endif
