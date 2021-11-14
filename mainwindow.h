#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QTextEdit"
#include "draw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QTextEdit* text;
    Draw* canvas;
    int rColor = 0;
    int gColor = 0;
    int bColor = 0;
    bool edit = false;
    int edit_rColor = 0;
    int edit_gColor = 0;
    int edit_bColor = 0;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void openFile();
    void saveFile();
    void quitApp();
    void closeEvent (QCloseEvent *event);
    void set_thickness(int size);
    void set_color(QColor color);
    void set_style(Qt::PenStyle style);
    void set_shape(std::string shape);
    void editShape();
    void editStyle(Qt::PenStyle style);

private slots:
    void on_radioButton_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_5_toggled(bool checked);

    void on_radioButton_6_toggled(bool checked);

    void on_horizontalSlider_valueChanged(int value);


    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_tabWidget_tabBarClicked(int index);

    void on_radioButton_7_toggled(bool checked);

    void on_radioButton_8_toggled(bool checked);

    void on_radioButton_9_toggled(bool checked);

    void on_pushButton_clicked();

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_10_valueChanged(int value);

    void on_horizontalSlider_11_valueChanged(int value);

    void on_horizontalSlider_12_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_horizontalSlider_13_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
