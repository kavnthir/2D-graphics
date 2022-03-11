#include "RayWidget.h"

RayWidget::RayWidget(QWidget * parent): QWidget(parent){
	pos = QPointF();
}

void RayWidget::updatePos(){
	if(pos == QCursor::pos() - frameGeometry().topLeft())
		return;

	pos = QCursor::pos() - frameGeometry().topLeft();

	this->update();

	// std::cout << "x: " << frameGeometry().x() << ", y: " << frameGeometry().y() << '\n';
	//std::cout << "x: " << pos.x() << ", y: " << pos.y() << '\n';
}

void RayWidget::paintEvent(QPaintEvent *event){

	QDesktopWidget desktop;
	QPainter painter(this);
	QPen pen(Qt::white);
	pen.setWidthF(1);
	painter.setPen(pen);
	painter.translate(pos);

	double stepSize = 3;
	for(double i = 0; i < 360; i+=stepSize){
		painter.drawLine(QPoint(0, 0), QPoint(0, 0) + QPoint(0, - desktop.width()));
		painter.rotate(stepSize);

	}
	
}


