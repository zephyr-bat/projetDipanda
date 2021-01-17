#include "mainwindow.h"
#include "ui_mainwindow.h"
//affichage
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
//calcul
#include <iostream>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AfficherImage(){
    ui->label->resize(Image.width(),Image.height());
    ui->label->setPixmap(Image);
    ui->label->setScaledContents(true);
    this->resize(Image.width(),Image.height());
}
bool MainWindow::Testbinariser(){

    bool result = true;
     if(ImageOp.isNull()){result = false;}
    QColor pixel;
    for(int x=0; x<ImageOp.width();x++) {
        for (int y=0; y<ImageOp.height(); y++) {
            pixel = ImageOp.pixel(x, y);
            unsigned int test = pixel.blue();
            if(test != 255){
                if (test != 0){result = false;}
            }
        }
    }
    return result;
}

bool MainWindow::TestImageBinaireVide(QImage ImageO){
    bool result = true;
    QColor pixel;
    for(int x=0; x<ImageO.width();x++) {
        for (int y=0; y<ImageO.height(); y++) {
            pixel = ImageO.pixel(x, y);
            unsigned int test = pixel.blue();
            if(test == 255){
                result = false;
            }
        }
    }
    return result;
}

QImage MainWindow::Binarisation(QImage ImageO,int seuil){
    QImage temp = ImageO;
    QColor pixel;
    for(int x=0; x<ImageO.width();x++) {
        for (int y=0; y<ImageO.height(); y++) {
            pixel = temp.pixel(x, y);
             unsigned int X = 0;
            if(pixel.value()>seuil){
                X = 255;
            }
            pixel.setGreen(X);
            pixel.setBlue(X);
            pixel.setRed(X);
            temp.setPixel(x,y,pixel.rgb());
        }
    }
    return temp;
}

QImage MainWindow::Dilater(QImage ImageO){

    QSize Size( ImageO.width(),ImageO.height());
    QColor pixel;
    QImage result (Size,ImageO.format());
    std::vector<int> tableauEntier;
    for(int x=0; x<ImageO.width();x++) {
        for (int y=0; y<ImageO.height(); y++) {
            tableauEntier.clear();
            //0   y+1  0
            //x-1 x,y x+1
            //0   y-1  0
            int xo = x;
            int yo = y;
            for(int i = -1;i<2;i++){
                pixel = ImageO.pixel(xo+i,yo);
                tableauEntier.push_back(pixel.value());
            }
            for(int j = -1;j<2;j++){
               pixel = ImageO.pixel(xo,yo+j);
               tableauEntier.push_back(pixel.value());
            }

            //recherche du blanc
            bool Avaleur = false;
            int taille = tableauEntier.size();
            for(int i =0; i<taille;i++){
                if(tableauEntier[i]== 255){Avaleur = true;}
            }
            if (Avaleur){
                pixel.setGreen(255);
                pixel.setRed(255);
                pixel.setBlue(255);
                result.setPixel(x,y,pixel.rgb());
                //result.setPixel(x,y,1);
            }else{
                pixel.setGreen(0);
                pixel.setRed(0);
                pixel.setBlue(0);
                result.setPixel(x,y,pixel.rgb());
                //result.setPixel(x,y,0);
            }
        }
    }
    return result;
}
QImage MainWindow::Eroder(QImage ImageO){
    QSize Size( ImageO.width(),ImageO.height());
    QColor pixel;
    QImage result (Size,ImageO.format());
    std::vector<int> tableauEntier;
    for(int x=0; x<ImageO.width();x++) {
        for (int y=0; y<ImageO.height(); y++) {
            tableauEntier.clear();
            //0   y+1  0
            //x-1 x,y x+1
            //0   y-1  0
            int xo = x;
            int yo = y;
            for(int i = -1;i<2;i++){
                pixel = ImageO.pixel(xo+i,yo);
                tableauEntier.push_back(pixel.value());
            }
            for(int j = -1;j<2;j++){
                pixel = ImageO.pixel(xo,yo+j);
                tableauEntier.push_back(pixel.value());
            }
            //recherche du noir
            bool Avaleur = false;
            int taille = tableauEntier.size();
            for(int i =0; i<taille;i++){
                if(tableauEntier[i]== 0){Avaleur = true;}
            }
            if (Avaleur){
                pixel.setGreen(0);
                pixel.setRed(0);
                pixel.setBlue(0);
                result.setPixel(x,y,pixel.rgb());
                //result.setPixel(x,y,0);
            }else{
                pixel.setGreen(255);
                pixel.setRed(255);
                pixel.setBlue(255);
                result.setPixel(x,y,pixel.rgb());
                //result.setPixel(x,y,1);
            }
        }
    }
    return result;
}
QImage MainWindow::Union(QImage Image1,QImage Image2){
    QSize Size( Image1.width(),Image1.height());
    QImage result (Size,Image1.format());
    QColor pixel1;
    QColor pixel2;
    QColor pixelX;
    for(int x=0; x<Image1.width();x++) {
        for (int y=0; y<Image1.height(); y++) {
            pixel1 = Image1.pixel(x,y);
            pixel2 = Image2.pixel(x,y);
            unsigned int geen1 = pixel1.green();
            unsigned int geen2 = pixel2.green();
            int p= 0;
            if(geen1 == 255){
                p = 255;
            }
            if(geen2 == 255){
                p=255;
            }
            pixelX.setGreen(p);
            pixelX.setRed(p);
            pixelX.setBlue(p);
            result.setPixel(x,y,pixelX.rgb());
        }
    }
    return result;
}
QImage MainWindow::Intersection(QImage Image1,QImage Image2){
    QSize Size( Image1.width(),Image1.height());
    QImage result (Size,Image1.format());
    QColor pixel1;
    QColor pixel2;
    QColor pixelX;
    std::vector<int> tableauVerif;
    for(int x=0; x<Image1.width();x++) {
        for (int y=0; y<Image1.height(); y++) {
            pixel1 = Image1.pixel(x,y);
            pixel2 = Image2.pixel(x,y);

            unsigned int green1 = pixel1.green();
            unsigned int green2 = pixel2.green();
            int p = 0;
            if (green1 == 255){
                if (green2 == 0){
                    p = 255;
                }
            }
            tableauVerif.push_back(p);
            pixelX.setGreen(p);
            pixelX.setBlue(p);
            pixelX.setRed(p);

            result.setPixel(x,y,pixelX.rgb());
        }
    }
    return result;
}
QImage MainWindow::Ouverture(QImage ImageO){
    QImage result = ImageO;
    result = Eroder(result);
    result = Dilater(result);
    return result;

}

QImage MainWindow::Fermeture(QImage ImageO){
    QImage result = ImageO;
    result = Dilater(result);
    result = Eroder(result);
    return result;
}

QImage MainWindow::EtapLantuejoul(QImage ImageO){
    //[érosion Intersection Ouverture]
    QImage ImageEroder = Eroder(ImageO);
    QImage ImageOuverte = Ouverture(ImageEroder);
    QImage result = Intersection(ImageEroder,ImageOuverte);
    return result;
}

QImage MainWindow::SquelettisationLantuejoul(QImage ImageO){
    bool estFini = false;
    QImage result = EtapLantuejoul(ImageOp);
    QImage temp = ImageOp;
    QImage x;
    while(!estFini){
        temp = Eroder(temp);
        if(!TestImageBinaireVide(temp)){
            x = EtapLantuejoul(temp);
            result = Union(result,x);

        }else{estFini = true;}
    }
    return result;
}
void MainWindow::on_actionOuvrir_une_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Ouvrir une image"), "//", tr("Images(*.png *.jpg *.bmp)"));
    if(!fileName.isNull()){
    QImage temp (fileName);
    ImageOp = temp;
    Image  = QPixmap::fromImage(temp);
    AfficherImage();}
}

void MainWindow::on_actionFermer_l_image_triggered()
{
    ui->label->clear();
    ImageOp = QImage ();
    Image = QPixmap ();
    save = QImage();
}

void MainWindow::on_actionEnregister_l_image_triggered()
{
    if(!Image.isNull()){
        QString savef = QFileDialog::getSaveFileName(this, tr("Enregister l'image"), "", tr("Images(*.png *.jpg *.bmp)"));
        Image.save(savef);
    }else{
        QMessageBox::information(this, "Attention", "Il n'y a pas d'image à enregistrer");
    }
}

void MainWindow::on_actionPasser_en_gris_triggered()
{
    if(!Image.isNull()){
        QImage temp = ImageOp;
        QColor pixel;
        for(int x=0; x<ImageOp.width();x++) {
            for (int y=0; y<ImageOp.height(); y++) {
                pixel = ImageOp.pixel(x, y);
                unsigned int average = (pixel.green()+ pixel.red() + pixel.blue()) / 3;
                pixel.setGreen(average);
                pixel.setBlue(average);
                pixel.setRed(average);
                temp.setPixel(x,y,pixel.rgb());
            }
        }
        save = ImageOp;
        ImageOp = temp;
        Image  = QPixmap::fromImage(temp);
        AfficherImage();
    }
    else{QMessageBox::information(this, "Attention", "Il n'y a pas d'image");}

}

void MainWindow::on_actionBinariser_triggered()
{
    if(!Image.isNull()){
        bool estGris = ImageOp.isGrayscale();
        if(estGris){
            bool ok;
            int seuil = QInputDialog::getInt(this,tr("Donner le seuil de Binarisation"),tr("seuil"),0,0,255, 1, &ok);
            if (ok){
                QImage result = Binarisation(ImageOp,seuil);
                save = ImageOp;
                ImageOp = result;
                Image  = QPixmap::fromImage(result);
                AfficherImage();
            }
        }else{
            QMessageBox::information(this, "Attention", "Donner une image en noir et blanc");
        }
    }else{
        QMessageBox::information(this, "Attention", "Il n'y a pas d'image");
    }

}

void MainWindow::on_actionDilater_triggered()
{
    if(Testbinariser()){

         QImage result = Dilater(ImageOp);
         save = ImageOp;
         ImageOp = result;
         Image  = QPixmap::fromImage(result);
         AfficherImage();
    }
}

void MainWindow::on_action_roder_triggered()
{
    if(Testbinariser()){

         QImage result = Eroder(ImageOp);
         save = ImageOp;
         ImageOp = result;
         Image  = QPixmap::fromImage(result);
         AfficherImage();
    }
}

void MainWindow::on_actionAddition_image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Choisisser une autre image"), "", tr("Images(*.png *.jpg *.bmp)"));
    QImage temp (fileName);

    if(!temp.isNull()){

        bool estdeMemeTaille = true;
        if(temp.width() != ImageOp.width()){estdeMemeTaille = false;}
        if(temp.height() != ImageOp.height()){estdeMemeTaille = false;}

        if(estdeMemeTaille){
            QImage result = Union(ImageOp,temp);
            save = ImageOp;
            ImageOp = result;
            Image  = QPixmap::fromImage(result);
            AfficherImage();
        }else{
            QMessageBox::information(this, "Attention", "Les images n'ont pas la même taille");
        }
    }
}

void MainWindow::on_actionSoustration_de_2_images_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Choisisser une autre image"), "", tr("Images(*.png *.jpg *.bmp)"));
    QImage temp (fileName);
    if(!temp.isNull()){
        //test taille identique
        bool estdeMemeTaille = true;
        if(temp.width() != ImageOp.width()){estdeMemeTaille = false;}
        if(temp.height() != ImageOp.height()){estdeMemeTaille = false;}

        if(estdeMemeTaille){
            QImage result = Intersection(ImageOp,temp);
            save = ImageOp;
            ImageOp = result;
            Image  = QPixmap::fromImage(ImageOp);
            AfficherImage();
        }else{
            QMessageBox::information(this, "Attention", "Les images n'ont pas la même taille");
        }
    }
}

void MainWindow::on_actionOuverture_triggered()
{
    if(Testbinariser()){
        //érosion, dilatation
        QImage result = Ouverture(ImageOp);
        save = ImageOp;
        ImageOp = result;
        Image  = QPixmap::fromImage(result);
        AfficherImage();
    }
}

void MainWindow::on_actionFermeture_triggered()
{
    if(Testbinariser()){
        //dilatation, érosion
        QImage result = Fermeture(ImageOp);
        save = ImageOp;
        ImageOp = result;
        Image  = QPixmap::fromImage(result);
        AfficherImage();
    }
}

void MainWindow::on_actionAmincissement_triggered()
{
    if(Testbinariser()){
        QImage ImageResult = EtapLantuejoul(ImageOp);
        save = ImageOp;
        ImageOp = ImageResult;
        Image  = QPixmap::fromImage(ImageResult);
        AfficherImage();
    }
}

void MainWindow::on_actionSquel_tisation_Lantuejoul_triggered()
{
    if(Testbinariser()){
        QImage result = SquelettisationLantuejoul(ImageOp);
        ImageOp = result;
        Image  = QPixmap::fromImage(result);
        AfficherImage();
    }
}

void MainWindow::on_actionundo_triggered()
{
    if(!save.isNull()){
    ImageOp = save;
    Image  = QPixmap::fromImage(ImageOp);
    AfficherImage();
    }
}
