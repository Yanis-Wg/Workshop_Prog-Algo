#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include "random.hpp"
void only_green(sil::Image& img){
    for (glm::vec3& pixel : img.pixels())
    {
        pixel.r = 0.f;
        pixel.b = 0.f;
    }
    img.save("output/only_green.png");
}

void exchange_can(sil::Image& img){
    for (glm::vec3& pixel : img.pixels())
    {
        std::swap(pixel.r,pixel.b);
    }
    img.save("output/exchange_can.png");
}

void black_and_white(sil::Image& img){
    for (glm::vec3& pixel : img.pixels())
    {
        float nuance_de_gris=0.2126*pixel.r + 0.7152*pixel.g+ 0.0722*pixel.b;
        pixel = glm::vec3{nuance_de_gris};
    }
    img.save("output/black_and_white.png");
}

void negative_color(sil::Image& img){
    for (glm::vec3& pixel : img.pixels())
    {
        pixel.r=1-pixel.r;
        pixel.g=1-pixel.g;
        pixel.b=1-pixel.b;
    }
    img.save("output/negative_color.png");
}

void black_and_white_fade(){
    sil::Image image{300/*width*/, 200/*height*/};
    float fade=0.f;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x==0){
                image.pixel(x,y)=glm::vec3{0.f};
            }else if(x==299){
                image.pixel(x,y)=glm::vec3{1.f};
            }else{
                image.pixel(x,y)=glm::vec3{fade};
            }
        }
        fade+=1.f/300.f;
    }
    image.save("output/black_and_white_fade.png");
}

void mirror(sil::Image& img){
    int compteur=1;
    sil::Image img_intermediare=img;
    for (int x{0}; x < img.width()/2; x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x,y)=img.pixel(img.width()-compteur,y);
            img.pixel(img.width()-compteur,y)=img_intermediare.pixel(x,y);
        }
        compteur++;
    }
    // On cherche une formule qui, quand x vaut 0, le transforme en image.width() - 1, quand x vaut 1, le transforme en image.width() - 2, etc.
    img.save("output/mirror.png");
}

void noise(sil::Image img){
    int where = random_int(0, img.width()-1);
    for (int x{0}; x < img.width(); x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(random_int(0, img.width()-1),random_int(0, img.height()-1))=glm::vec3{random_float(0.f,1.f),random_float(0.f,1.f),random_float(0.f,1.f)};
        }
    }
    img.save("output/noise.png");
}

void rotation(sil::Image& img){
    // Création de l'image tournée
    sil::Image image_rotated(img.height(),img.width());
    // Variable qui sera décrémenté, correspond au ligne du deuxieme tableau
    int image_rotated_y=image_rotated.width()-1;
    // Boucle pour parcourir le tableau
    // Parcours colonne
    for(int x{0}; x<img.height();x++){
        // Parcours Ligne
        for(int y{0};y<img.width();y++){
            image_rotated.pixel(x,image_rotated_y)=img.pixel(y,x);
            image_rotated_y-=1;
        }
        image_rotated_y= image_rotated.width()-1;
    }
    image_rotated.save("output/rotated_img.png");
}

int main()
{
    sil::Image image{"images/logo.png"};
    // only_green(image);
    // exchange_can(image);
    // black_and_white(image);
    // negative_color(image);
    // black_and_white_fade();
    // mirror(image);
    // noise(image);
    rotation(image);
    return 0;
}


// // On passe sur tous les x et tous les y, et on accède au pixel correspondant :
// for (int x{0}; x < image.width(); x++)
// {
// for (int y{0}; y < image.height(); y++)
// {
// image.pixel(x, y).r = 0.f;
// }
// }
// // Ou alors, si on n'a pas besoin de connaître le x et le y, on a une syntaxe plus concise pour itérer sur tous les pixels :
// for (glm::vec3& color : image.pixels())
// {
// color.r = 0.f;
// }