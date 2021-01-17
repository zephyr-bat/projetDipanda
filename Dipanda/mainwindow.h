#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void AfficherImage();

    bool Testbinariser();

    bool TestImageBinaireVide(QImage ImageO);

    QImage Binarisation(QImage ImageO,int seuil);

    QImage Dilater(QImage ImageO);

    QImage Eroder(QImage ImageO);

    QImage Union(QImage Image1,QImage Image2);

    QImage Intersection(QImage Image1,QImage Image2);

    QImage Ouverture(QImage ImageO);

    QImage Fermeture(QImage ImageO);

    QImage EtapLantuejoul(QImage ImageO);

    QImage SquelettisationLantuejoul(QImage ImageO);

    void on_actionOuvrir_une_image_triggered();

    void on_actionFermer_l_image_triggered();

    void on_actionEnregister_l_image_triggered();

    void on_actionPasser_en_gris_triggered();

    void on_actionBinariser_triggered();

    void on_actionDilater_triggered();

    void on_actionAddition_image_triggered();

    void on_actionSoustration_de_2_images_triggered();

    void on_action_roder_triggered();

    void on_actionOuverture_triggered();

    void on_actionFermeture_triggered();

    void on_actionAmincissement_triggered();

    void on_actionSquel_tisation_Lantuejoul_triggered();

    void on_actionundo_triggered();

private:
    Ui::MainWindow *ui;
    QPixmap Image;
    QImage ImageOp;
    QImage save;
};
#endif // MAINWINDOW_H
