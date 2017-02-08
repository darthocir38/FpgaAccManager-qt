#ifndef GENERATEGRIDDIALOG_H
#define GENERATEGRIDDIALOG_H

#include <QDialog>

namespace Ui {
class GenerateGridDialog;
}

class GenerateGridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateGridDialog(QWidget *parent = 0);
    ~GenerateGridDialog();

private:
    Ui::GenerateGridDialog *ui;
};

#endif // GENERATEGRIDDIALOG_H
