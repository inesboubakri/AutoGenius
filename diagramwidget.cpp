// diagramwidget.cpp
#include "diagramwidget.h"
#include <QPainter>

DiagramWidget::DiagramWidget(QWidget *parent) : QWidget(parent)
{
}

void DiagramWidget::setChartPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;  // Store the pixmap
    update();  // Request a repaint
}

void DiagramWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!m_pixmap.isNull()) {
        painter.drawPixmap(0, 0, m_pixmap);  // Draw the pixmap onto the widget
    }
}
