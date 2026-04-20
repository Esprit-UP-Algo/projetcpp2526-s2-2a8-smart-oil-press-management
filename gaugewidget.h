#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QWidget>
#include <QString>

/*
 * GaugeWidget — Custom gauge-style sensor indicator
 *
 * Displays a circular gauge with needle pointing to current value,
 * color-coded status (green/orange/red), and numeric readout.
 */

class GaugeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GaugeWidget(const QString &label, 
                         double minValue, 
                         double maxValue, 
                         const QString &unit,
                         QWidget *parent = nullptr);

    void setValue(double value);
    void setThresholds(double warningThreshold, double criticalThreshold);
    
    // Optional: call this to update gauge appearance
    void update_gauge();

protected:
    void paintEvent(QPaintEvent *event) override;
    QSize sizeHint() const override { return QSize(180, 200); }

private:
    QString m_label;
    QString m_unit;
    double m_minValue;
    double m_maxValue;
    double m_currentValue;
    double m_warningThreshold;
    double m_criticalThreshold;

    // Helper methods for painting
    void drawGaugeBackground(QPainter &painter, const QRect &rect);
    void drawGaugeNeedle(QPainter &painter, const QRect &rect);
    void drawGaugeLabels(QPainter &painter, const QRect &rect);
    QColor getStatusColor() const;
};

#endif // GAUGEWIDGET_H
