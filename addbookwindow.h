#ifndef ADDBOOKWINDOW_H
#define ADDBOOKWINDOW_H

#include <QMainWindow>

namespace Ui {
class addBookWindow;
}

class addBookWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit addBookWindow(QWidget *parent = nullptr);
    ~addBookWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::addBookWindow *ui;
};

#endif // ADDBOOKWINDOW_H
