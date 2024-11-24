// diagramwidget.h
#ifndef DIAGRAMWIDGET_H
#define DIAGRAMWIDGET_H

#include <QWidget>
#include <QPixmap>

class DiagramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramWidget(QWidget *parent = nullptr);
    void setChartPixmap(const QPixmap &pixmap);  // Declare method to set pixmap

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pixmap;  // Member variable to store the pixmap
};

#endif // DIAGRAMWIDGET_H
