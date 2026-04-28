#ifndef JUMEAUNUMERIQUE_H
#define JUMEAUNUMERIQUE_H

#include <QWidget>
#include <QString>
#include <QTableWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QDate>
#include "gaugewidget.h"

/*
 * JumauNumerique — Machine Digital Twin Dashboard
 *
 * Two-panel layout:
 *   Left (30%):  Machine list (QTableWidget)
 *   Right (70%): Twin details with sensor data, tabs, and diagnostic form
 *
 * Features:
 *   - Tab 1 (Performance): Gauge widgets for sensors + Uptime card
 *   - Tab 2 (Anomalies): Rule-based anomaly detection vs thresholds
 *   - Tab 3 (Maintenance Prédictive): Next maintenance recommendation
 *   - Sensor data entry form
 *   - Claude API diagnostic call
 */

class JumauNumerique : public QWidget
{
    Q_OBJECT

public:
    explicit JumauNumerique(QWidget *parent = nullptr);
    ~JumauNumerique();

    void setDatabase(const QSqlDatabase &db);
    void loadMachines();
    void selectMachine(int machineId);

private slots:
    // Machine list
    void onMachineTableClicked(int row, int column);

    // Sensor data entry
    void onUpdateSensorsClicked();
    void onLaunchDiagnosticClicked();

    // Network response
    void onDiagnosticResponseReceived(QNetworkReply *reply);

    // Tab changes
    void onTabChanged(int index);

private:
    // Database
    QSqlDatabase m_db;

    // UI Components
    QTableWidget *m_machineTable;   // Left panel
    QLabel *m_machineNameLabel;      // Right panel header
    QLabel *m_machineTypeLabel;

    // Sensor input form
    QDoubleSpinBox *m_tempInput;
    QDoubleSpinBox *m_vibrationInput;
    QDoubleSpinBox *m_energyInput;
    QDoubleSpinBox *m_qualityInput;
    QDoubleSpinBox *m_downTimeInput;
    QDoubleSpinBox *m_chargeInput;
    QComboBox *m_componentStateCombo;

    // Tab widget
    QTabWidget *m_tabWidget;

    // Tab 1: Performance
    GaugeWidget *m_tempGauge;
    GaugeWidget *m_vibrationGauge;
    GaugeWidget *m_chargeGauge;
    QLabel *m_uptimeLabel;
    QLabel *m_healthScoreLabel;

    // Tab 2: Anomalies
    QTableWidget *m_anomalyTable;

    // Tab 3: Maintenance
    QLabel *m_lastDiagDateLabel;
    QLabel *m_nextMaintenanceLabel;
    QTextEdit *m_recommendationEdit;

    // Diagnostic results
    QTextEdit *m_diagnosticResultEdit;

    // Network
    int m_selectedMachineId;
    QNetworkAccessManager *m_network;

    // Helper methods
    void setupUI();
    void loadMachineDetails(int machineId);
    void updateGauges(int machineId);
    void updateAnomalies(int machineId);
    void updateMaintenanceTab(int machineId);
    void refreshDiagnosticResults(int machineId);

    // Health score calculation
    struct SensorData {
        double temperature;
        double vibration;
        double energia;
        double quality;
        double downTime;
        double charge;
        QString componentState;
    };

    SensorData readSensorData(int machineId);
    int calculateHealthScore(const SensorData &data);
    QString getHealthStatus(int score);
    QColor getHealthColor(int score);
    void updateNextMaintenance(int machineId);

    // Claude API
    static const QString CLAUDE_API_KEY;
    static const QString CLAUDE_API_URL;
    static const QString CLAUDE_MODEL;

    void launchDiagnosticAI(int machineId);
    QString buildDiagnosticPrompt(int machineId, const SensorData &data);
};

#endif // JUMEAUNUMERIQUE_H
