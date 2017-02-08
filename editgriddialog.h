#ifndef EDITGRIDDIALOG_H
#define EDITGRIDDIALOG_H

#include <QDialog>

namespace Ui {
class EditGridDialog;
}

class EditGridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGridDialog(QWidget *parent = 0);
    ~EditGridDialog();

private:
    Ui::EditGridDialog *ui;
};

#endif // EDITGRIDDIALOG_H
