#ifndef HEALTHTRACKERUI_H
#define HEALTHTRACKERUI_H

#include <QMainWindow>

namespace Ui {
class HealthTrackerUI;
}

class HealthTrackerUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit HealthTrackerUI(QWidget *parent = 0);
    ~HealthTrackerUI();

private:
    Ui::HealthTrackerUI *ui;
};

#endif // HEALTHTRACKERUI_H
