#include "RayWidget.h"

RayWidget::RayWidget(QWidget * parent): QWidget(parent){
	pos = QPoint(-1,-1);
}

void RayWidget::updatePos(){
	if(pos == QCursor::pos())
		return;

	pos = QCursor::pos() - frameGeometry().topLeft();

	this->update();

	// std::cout << "x: " << frameGeometry().x() << ", y: " << frameGeometry().y() << '\n';
	//std::cout << "x: " << pos.x() << ", y: " << pos.y() << '\n';
}

void RayWidget::paintEvent(QPaintEvent *event){

	QPainter painter(this);
	QPen pen(Qt::white);
	painter.setPen(pen);
	painter.drawEllipse(pos, 1, 1);
	
}

