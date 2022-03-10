#include "RayWidget.h"

RayWidget::RayWidget(QWidget * parent): QWidget(parent){
	pos = QCursor::pos();
}

void RayWidget::updatePos(){
	if(pos == QCursor::pos())
		return;

	pos = QCursor::pos();	
	QPainter painter;
	painter.drawEllipse( pos, 5, 5);

	std::cout << "x: " << pos.x() << ", y: " << pos.y() << '\n';
}


