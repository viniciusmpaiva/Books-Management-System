#ifndef READREGISTERWINDOW_H
#define READREGISTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class readRegisterWindow;
}

class readRegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit readRegisterWindow(QWidget *parent = nullptr);
    ~readRegisterWindow();

private slots:
    void toggleElementsVisibility(bool visible);

    void on_pushButton_2_clicked();

    void on_returnButton_clicked();

private:
    Ui::readRegisterWindow *ui;
};




#endif // READREGISTERWINDOW_H
