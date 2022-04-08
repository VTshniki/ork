#ifndef TABLEUPLOADWINDOW_H
#define TABLEUPLOADWINDOW_H

#include <QWidget>

namespace Ui {
class TableUploadWindow;
}

class TableUploadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TableUploadWindow(QWidget *parent = nullptr);
    ~TableUploadWindow();

private:
    Ui::TableUploadWindow *ui;
};

#endif // TABLEUPLOADWINDOW_H
