#include "gaugewidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QRect>
#include <cmath>

GaugeWidget::GaugeWidget(const QString &label, 
                         double minValue, 
                         double maxValue, 
                         const QString &unit,
                         QWidget *parent)
    : QWidget(parent)
    , m_label(label)
    , m_unit(unit)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
    , m_currentValue(minValue)
    , m_warningThreshold(maxValue * 0.7)
    , m_criticalThreshold(maxValue * 0.9)
{
    setMinimumSize(180, 200);
    setStyleSheet("background-color: #f5f5f5; border-radius: 8px;");
}

void GaugeWidget::setValue(double value)
{
    m_currentValue = value;
    update();
}

void GaugeWidget::setThresholds(double warningThreshold, double criticalThreshold)
{
    m_warningThreshold = warningThreshold;
    m_criticalThreshold = criticalThreshold;
    update();
}

QColor GaugeWidget::getStatusColor() const
{
    if (m_currentValue >= m_criticalThreshold)
        return QColor(220, 53, 69);  // Red
    else if (m_currentValue >= m_warningThreshold)
        return QColor(255, 193, 7);  // Orange
    else
        return QColor(40, 167, 69);  // Green
}

void GaugeWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QRect rect = this->rect();
    
    // Draw the gauge background
    drawGaugeBackground(painter, rect);
    
    // Draw the needle
    drawGaugeNeedle(painter, rect);
    
    // Draw labels and values
    drawGaugeLabels(painter, rect);
}

void GaugeWidget::drawGaugeBackground(QPainter &painter, const QRect &rect)
{
    int centerX = rect.width() / 2;
    int centerY = rect.height() / 2 + 10;
    int radius = 60;
    
    // Draw outer circle
    painter.setPen(QPen(QColor(200, 200, 200), 2));
    painter.setBrush(QColor(245, 245, 245));
    painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
    
    // Draw colored arc background (green -> orange -> red)
    // Green arc (0° to ~90°)
    painter.setPen(QPen(QColor(40, 167, 69), 3));
    painter.drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 
                    40 * 16, 100 * 16);
    
    // Orange arc
    painter.setPen(QPen(QColor(255, 193, 7), 3));
    painter.drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 
                    140 * 16, 60 * 16);
    
    // Red arc
    painter.setPen(QPen(QColor(220, 53, 69), 3));
    painter.drawArc(centerX - radius, centerY - radius, radius * 2, radius * 2, 
                    200 * 16, 40 * 16);
}

void GaugeWidget::drawGaugeNeedle(QPainter &painter, const QRect &rect)
{
    int centerX = rect.width() / 2;
    int centerY = rect.height() / 2 + 10;
    int radius = 60;
    
    // Calculate needle angle based on current value
    // Map value to angle: minValue -> 220°, maxValue -> 320°
    double range = m_maxValue - m_minValue;
    double normalized = (m_currentValue - m_minValue) / range;
    double angle = 220 + normalized * 100;  // 220° to 320°
    
    // Convert to radians
    double radians = angle * M_PI / 180.0;
    
    // Calculate needle endpoint
    int needleX = centerX + radius * cos(radians);
    int needleY = centerY + radius * sin(radians);
    
    // Draw needle
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(centerX, centerY, needleX, needleY);
    
    // Draw center circle
    painter.setBrush(QColor(50, 50, 50));
    painter.drawEllipse(QPoint(centerX, centerY), 5, 5);
}

void GaugeWidget::drawGaugeLabels(QPainter &painter, const QRect &rect)
{
    int centerX = rect.width() / 2;
    int centerY = rect.height() / 2 + 10;
    int radius = 60;
    
    // Draw min/max labels on gauge
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 8));
    
    // Min value (220°)
    double minRad = 220 * M_PI / 180.0;
    int minX = centerX + (radius + 15) * cos(minRad);
    int minY = centerY + (radius + 15) * sin(minRad);
    painter.drawText(QRect(minX - 15, minY - 10, 30, 20), Qt::AlignCenter, 
                     QString::number(m_minValue, 'f', 0));
    
    // Max value (320°)
    double maxRad = 320 * M_PI / 180.0;
    int maxX = centerX + (radius + 15) * cos(maxRad);
    int maxY = centerY + (radius + 15) * sin(maxRad);
    painter.drawText(QRect(maxX - 15, maxY - 10, 30, 20), Qt::AlignCenter, 
                     QString::number(m_maxValue, 'f', 0));
    
    // Draw label at top
    painter.setFont(QFont("Arial", 9, QFont::Bold));
    QColor statusColor = getStatusColor();
    painter.setPen(statusColor);
    painter.drawText(rect.adjusted(5, 5, -5, 0), Qt::AlignTop | Qt::AlignHCenter, m_label);
    
    // Draw current value and unit in center-bottom
    painter.setFont(QFont("Arial", 11, QFont::Bold));
    painter.setPen(statusColor);
    QString valueStr = QString::number(m_currentValue, 'f', 1) + " " + m_unit;
    painter.drawText(QRect(0, centerY + 30, rect.width(), 30), 
                     Qt::AlignCenter, valueStr);
}

void GaugeWidget::update_gauge()
{
    update();
}
