#ifndef AUTHORIZATIONWINDOW_H
#define AUTHORIZATIONWINDOW_H

#include <QWidget>

namespace Ui {
class AuthorizationWindow;
}

class AuthorizationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationWindow(QWidget *parent = nullptr);
    ~AuthorizationWindow();

private:
    Ui::AuthorizationWindow *ui;
};

#endif // AUTHORIZATIONWINDOW_H