#ifndef EDITREGISTERWINDOW_H
#define EDITREGISTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class editRegisterWindow;
}

class editRegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit editRegisterWindow(QWidget *parent = nullptr);
    ~editRegisterWindow();

private slots:
    void on_pushButton_2_clicked();
    void toggleElementsVisibility(bool visible);

    void on_searchButton_clicked();

    void on_applyChanges_clicked();

private:
    Ui::editRegisterWindow *ui;
};

#endif // EDITREGISTERWINDOW_H
