#include <sil/sil.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "random.hpp"
#include <algorithm>
#include <complex>
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
    int y_old_img=0;
    // les colonnes de la nouvelle image
    for (int x{0}; x < img.height(); x++)
    {
        // les lignes de la nouvelle image
        for (int y{0};y<img.width(); y++)
        {
            image_rotated.pixel(img.height() - 1 - x, y)=img.pixel(y_old_img,x);
            y_old_img++;
        }
        y_old_img=0;
    }
    image_rotated.save("output/rotated_img.png");
}

void rgb_split(sil::Image& img){
    sil::Image image_rgb_split(img.width(),img.height());
    // decalage / de combien on 'tire' les logo version rouge et bleu
    int decalage{30};
    for (int col{0};col<image_rgb_split.width();col++){
        for(int line{0};line<image_rgb_split.height();line++){
            // On se promene dans le tableau à deux dimensions
            // Si le col-décalage est superieur ou égale à 0 alors on prend la valeur de rouge de col-decalage pour la "tirer" vers la droite
            if(col-decalage>=0){
                image_rgb_split.pixel(col, line).r = img.pixel(col - decalage, line).r;
            }
            // Si col+décalage est inférieur ou égale aux nombre max de col alors on prend la valeur de bleu à x+décalage et on la tire vers la gauche
            if(col + decalage<=image_rgb_split.width()-1){
                image_rgb_split.pixel(col,line).b=img.pixel(col+decalage, line).b;
            }

            // Comme sur l'image final le vers ne se déplace pas, on récupere le vert de chaque colonne et ligne sans avoir besoin de le "tirer"
            image_rgb_split.pixel(col,line).g = img.pixel(col,line).g;
        }
    }
    image_rgb_split.save("output/rgb_split.png");
}

void changeLighting(sil::Image img){
    sil::Image img_light=img;
    sil::Image img_dark=img;
    float p_light{0.8};
    float p_dark{1.2};
    for (glm::vec3& color : img_light.pixels())
    {
        color.r = pow(color.r,p_light);
        color.g = pow(color.g,p_light);
        color.b = pow(color.b,p_light);
    }
    for (glm::vec3& color : img_dark.pixels())
    {
        color.r = pow(color.r,p_dark);
        color.g = pow(color.g,p_dark);
        color.b = pow(color.b,p_dark);
    }
    img_light.save("output/img_light.png");
    img_dark.save("output/img_dark.png");
}

void draw_white_disc(){
    sil::Image img{500,500};
    int rayon{150};
    // permet de center le cercle
    int pos_x{250};
    int pos_y{250};
    for(int col{0}; col<500;col++)
    {
        for(int line{0};line<500;line++)
        {
            float distance = pow(col-pos_x,2)+pow(line-pos_y,2);
            if (distance<=pow(rayon,2)){
                img.pixel(col,line)=glm::vec3(1);
            }
        }
    }
    img.save("output/white_disc.png");
}

void draw_border_of_a_white_circle()
{
    sil::Image img{500,500};
    int rayon{150};
    // permet de center le cercle
    int pos_x{250};
    int pos_y{250};
    for(int col{0}; col<500;col++)
    {
        for(int line{0};line<500;line++)
        {
            float distance = pow(col-pos_x,2)+pow(line-pos_y,2);
            if (distance<=pow(rayon,2) && distance>=pow(rayon-10,2)){
                img.pixel(col,line)=glm::vec3(1);
            }
        }
    }
    img.save("output/white_border_of_a_white_circle.png");
}

void draw_white_disc_for_gif()
{
    sil::Image img{500,500};
    int rayon{150};
    // permet de center le cercle
    int pos_x{-50};
    int pos_y{250};
    int n_facteur{0};
    for (int fps{0};fps<25;fps++)
    {
        for(int col{0}; col<500;col++)
        {
            for(int line{0};line<500;line++)
            {
                float distance = pow(col-pos_x,2)+pow(line-pos_y,2);
                if (distance<=pow(rayon,2)){
                    img.pixel(col,line)=glm::vec3(1);
                }
            }
        }
        pos_x+=700/24;
        img.save("output/gif/white_disc_"+std::to_string(n_facteur)+".png");
        n_facteur++;
        for(int col{0}; col<500;col++)
        {
            for(int line{0};line<500;line++)
            {
                img.pixel(col,line)=glm::vec3(0);
            }
        }
    }
    
}

void draw_rosas(){
    // nombre de tour
    float pi=glm::pi<float>();
    int rayon{100};
    float angle=0.f;
    sil::Image img{500,500};
    // permet de center le cercle
    int pos_x{250};
    int pos_y{250};
    // Le premier cercle
    for(int col{0}; col<500;col++)
    {
        for(int line{0};line<500;line++)
        {
            float distance_centre = pow(col-pos_x,2)+pow(line-pos_y,2);
            if (distance_centre<=pow(rayon,2) && distance_centre>=pow(rayon-5,2)){
                img.pixel(col,line)=glm::vec3(1);
            }
        }
    }
    // Les autres cercles de la rosas
    for (int i{0};i<7;i++)
    {
        for(int x{0}; x<500;x++)
        {
            for(int y{0};y<500;y++)
            {
                float distance = pow(x-(250+rayon*cos((i*pi)/3)),2)+pow(y-(250+rayon*sin((i*pi)/3)),2);
                if (distance<=pow(rayon,2) && distance>=pow(rayon-5,2)){
                    img.pixel(x,y)=glm::vec3(1);
                }
            }
        }
    }
    
    img.save("output/rosas.png");
}

void mosaic_fail(sil::Image& img){
    sil::Image mosaic(img.width()*5,img.height()*5);
    int col_img{0};
    int line_img{0};
    for(int col{0};col<mosaic.width();col++)
    {
        for(int line{0};line<mosaic.height();line++)
        {
            mosaic.pixel(col,line)=img.pixel(col_img,line_img);
            line_img++;
            if(line_img==img.height())
            {
                line_img=0;
            }
        }
        col_img++;
        if(col_img==img.width())
        {
            col_img=0;
        }
    }
    mosaic.save("output/mosaic_fail.png");
}

void mosaic(sil::Image& img){
    sil::Image mosaic(img.width()*5,img.height()*5);
    int col_img{0};
    int line_img{0};
    for(int col{0};col<mosaic.width();col++)
    {
        line_img=0;
        for(int line{0};line<mosaic.height();line++)
        {
            mosaic.pixel(col,line)=img.pixel(col_img,line_img);
            line_img++;
            if(line_img==img.height())
            {
                line_img=0;
            }
        }
        col_img++;
        if(col_img==img.width())
        {
            col_img=0;
        }
    }
    mosaic.save("output/mosaic.png");
}

void mirror_mosaic_fail(sil::Image& img){
    // image final
    sil::Image mirror_mosaic(img.width()*5,img.height()*5);
    // image miroir
    int compteur=1;
    sil::Image mirror_img=img;
    for (int x{0}; x < img.width()/2; x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x,y)=img.pixel(img.width()-compteur,y);
            img.pixel(img.width()-compteur,y)=mirror_img.pixel(x,y);
        }
        compteur++;
    }


    int col_img{0};
    int line_img{0};
    
    int reverse_counter{0};

    for(int line{0};line<mirror_mosaic.height();line++)
    {
        line_img=0;
        for(int col{0};col<mirror_mosaic.width();col++){
            if(reverse_counter%2==0){
                mirror_mosaic.pixel(col,line)=img.pixel(col_img,line_img);
            }else{
                mirror_mosaic.pixel(col,line)=mirror_img.pixel(col_img,line_img);
            }
            col_img++;
            if(col_img==img.width())
            {
                col_img=0;
                reverse_counter++;
            }
        }
        line_img++;
        if(line_img==img.height())
        {
            line_img=0;
        }
    }
    mirror_mosaic.save("output/mirror_mosaic_fail.png");
}


void mirror_mosaic_fail_2(sil::Image& img){
    // image final
    sil::Image mirror_mosaic(img.width()*5,img.height()*5);
    // image normal
    sil::Image normal_img=img;
    // image mirroir
    sil::Image mirror_img=img;
    int compteur=1;
    for (int x{0}; x < img.width()/2; x++)
    {
        for (int y{0}; y < img.height(); y++)
        {
            img.pixel(x,y)=img.pixel(img.width()-compteur,y);
            img.pixel(img.width()-compteur,y)=mirror_img.pixel(x,y);
        }
        compteur++;
    }
    // Mosaique
    int col_img{0};
    int line_img{0};
    // Compteur pour savoir si on doit faire avec ou sans la mosaique miroir
    int reverse_counter{0};

    for(int line{0};line<mirror_mosaic.height();line++)
    {
        col_img=0;
        for(int col{0};col<mirror_mosaic.width();col++){
            if(reverse_counter%2==0){
                mirror_mosaic.pixel(col,line)=img.pixel(col_img,line_img);
            }else{
                mirror_mosaic.pixel(col,line)=mirror_img.pixel(col_img,line_img);
            }
            col_img++;
            if(col_img==img.width())
            {
                col_img=0;
            }
        }
        line_img++;
        reverse_counter++;
        if(line_img==img.height())
        {
            line_img=0;
        }
    }
    mirror_mosaic.save("output/mirror_mosaic_fail_2.png");
}


void mirror_mosaic_fail_3(sil::Image& img){
    // image final
    sil::Image mirror_mosaic(img.width()*5,img.height()*5);
    // image normal
    sil::Image normal_img=img;
    // image mirroir
    sil::Image mirror_img=img;
    int compteur=1;
    for (int x{0}; x < mirror_img.width()/2; x++)
    {
        for (int y{0}; y < mirror_img.height(); y++)
        {
            mirror_img.pixel(x,y)=mirror_img.pixel(mirror_img.width()-compteur,y);
            mirror_img.pixel(mirror_img.width()-compteur,y)=mirror_img.pixel(x,y);
        }
        compteur++;
    }
    // Mosaique
    int col_img{0};
    int line_img{0};
    // Compteur pour savoir si on doit faire avec ou sans la mosaique miroir
    int reverse_counter{0};

    for(int line{0};line<mirror_mosaic.height();line++)
    {
        col_img=0;
        for(int col{0};col<mirror_mosaic.width();col++){
            if(reverse_counter%2==0){
                mirror_mosaic.pixel(col,line)=img.pixel(col_img,line_img);
            }else{
                mirror_mosaic.pixel(col,line)=mirror_img.pixel(col_img,line_img);
            }
            col_img++;
            if(col_img==img.width())
            {
                col_img=0;
                reverse_counter++;  
            }
        }
        line_img++;
        if(line_img==img.height())
        {
            line_img=0;
        }
    }
    mirror_mosaic.save("output/mirror_mosaic_fail_3.png");
}

void mirror_mosaic(sil::Image& img){
    // image final
    sil::Image mirror_mosaic(img.width()*5,img.height()*5);
    // image mirroir
    sil::Image mirror_img=img;
    sil::Image img_intermediare=img;
    int compteur=1;
    for (int x{0}; x < mirror_img.width()/2; x++)
    {
        for (int y{0}; y < mirror_img.height(); y++)
        {
            mirror_img.pixel(x,y)=mirror_img.pixel(mirror_img.width()-compteur,y);
            mirror_img.pixel(mirror_img.width()-compteur,y)=img_intermediare.pixel(x,y);
        }
        compteur++;
    }

    // Mosaique
    int line_img{0};
    int col_img{0};

    // Compteur pour savoir si on doit faire avec ou sans la mosaique miroir
    int reverse_counter_line{0};
    int reverse_counter_col{0};

    for(reverse_counter_col=0;reverse_counter_col<5;reverse_counter_col++){
        int offset_y = reverse_counter_col*img.height();
        // ----------------------------------------------------- //
        if(reverse_counter_col%2!=0)
        {
            line_img=0;
            // ------------------------------------
            for(int line{0};line<img.height();line++)
            {
                col_img=0;
                reverse_counter_line=0;
                for(int col{0};col<mirror_mosaic.width();col++){
                    if(reverse_counter_line%2==0){
                        mirror_mosaic.pixel(col,offset_y + line)=img.pixel(col_img,(img.height() - 1 - line_img));
                    }else{
                        mirror_mosaic.pixel(col,offset_y + line)=mirror_img.pixel(col_img,(img.height() - 1 - line_img));
                    }
                    col_img++;
                    if(col_img==img.width())
                    {
                        col_img=0;
                        reverse_counter_line++;  
                    }
                }
                line_img++;
            }
        }else if(reverse_counter_col%2==0){
            line_img=0;
            for(int line{0};line<img.height();line++)
            {
                col_img=0;
                reverse_counter_line=0;
                for(int col{0};col<mirror_mosaic.width();col++){
                    if(reverse_counter_line%2==0){
                        mirror_mosaic.pixel(col,offset_y+line)=img.pixel(col_img,line_img);
                    }else{
                        mirror_mosaic.pixel(col,offset_y+line)=mirror_img.pixel(col_img,line_img);
                    }
                    col_img++;
                    if(col_img==img.width())
                    {
                        col_img=0;
                        reverse_counter_line++;  
                    }
                }
                line_img++;
            }
        }
        mirror_mosaic.save("output/mirror_mosaic.png");
    }
}

void glitch(sil::Image& img){
    sil::Image tab_stockage(img.width(),img.height());
    int how_much_glitch=random_int(15,60);
    for(int i{0}; i<how_much_glitch;i++)
    {
        // random x & y sur lesquelles on va se placer
        int r_x=random_int(0,img.width()-1);
        int r_y=random_int(0,img.height()-1);
        
        // combien de long on va prendre
        int how_much_x=random_int(0,img.width()-1-r_x);

        // combien de haut on va prendre
        int how_much_y=random_int(0,img.height()-1-r_y);


        int d_r_x=random_int(0,img.width()-1);
        while((d_r_x+how_much_x-1)>img.width())
        {
            d_r_x=random_int(0,img.width()-1); 
        }

        int d_r_y=random_int(0,img.height()-1);
        while((d_r_y+how_much_y-1)>img.height())
        {
            d_r_y=random_int(0,img.height()-1); 
        }

        for(int x{0};x<how_much_x;x++)
        {
            for(int y{0};y<how_much_y;y++)
            {
                tab_stockage.pixel(r_x+x,r_y+y)=img.pixel(r_x+x,r_y+y);
                img.pixel(r_x+x,r_y+y)=img.pixel(x+d_r_x,y+d_r_y);
                img.pixel(x+d_r_x,y+d_r_y)=tab_stockage.pixel(r_x+x,r_y+y);
            }
        }
    }
    img.save("output/glitch.png");
}

float brightness(glm::vec3 const& a){
    return (a.r + a.g + a.b) / 3.0f;
}

void sort_by_brightness_full_picture(sil::Image& img){
    std::sort(img.pixels().begin(), img.pixels().end(), [](glm::vec3 a, glm::vec3 b) {
        return brightness(a)<brightness(b);
    });
    img.save("output/sort_by_brightness_full_picture.png");
}

void sort_by_brightness(sil::Image& img){
    sil::Image tab_stockage(img.width(),img.height());
    int how_much_glitch=random_int(15,60);
    for(int i{0}; i<how_much_glitch;i++)
    {
        // random x & y sur lesquelles on va se placer
        int r_x=random_int(0,img.width()-1);
        int r_y=random_int(0,img.height()-1);
        
        // combien de long on va prendre
        int how_much_x=random_int(0,img.width()-1-r_x);

        // combien de haut on va prendre
        int how_much_y=1;   
        std::vector<glm::vec3>tmp_vec;

        for(int x{0};x<how_much_x;x++)
        {
            for(int y{0};y<how_much_y;y++)
            {
                tmp_vec.push_back(img.pixel(r_x+x,r_y+y));
            }
        }
        std::sort(tmp_vec.begin(), tmp_vec.end(), [](glm::vec3 a, glm::vec3 b) {
            return brightness(a)<brightness(b);
        });
        // on replace les éléments dans leur emplacement apres avoir trier dans le tab temp
        int index = 0;
        for(int x{0};x<how_much_x;x++)
        {
            for(int y{0};y<how_much_y;y++)
            {
                img.pixel(r_x+x,r_y+y)=tmp_vec[index];
                index++;
            }
        }
    }
    img.save("output/sort_by_brightness.png");
}

void fractal_mandelbrot()
{
    sil::Image img{500,500};
   
    for(int col{0};col<img.width();col++)
    {
        for(int line{0};line<img.height();line++)
        {
            std::complex<float> c{col*(4.f/500.f)-2.f,line*(4.f/500.f)-2.f};
            std::complex<float> z=0.f;
            int j=0;
            while(j<20){
                z = z * z + c;
                if(std::abs(z) > 2){
                    break;
                }
                j++;
            }
            if(j==20){
                img.pixel(col,line)=glm::vec3(1);
            }else{
                img.pixel(col,line)=glm::vec3(0);
            }

        }
    }
    img.save("output/mandelbrot.png");
}

void fade_first_version(){
    sil::Image image{300/*width*/, 200/*height*/};
    float fade=0.f;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x==0){
                image.pixel(x,y).r=1;
                image.pixel(x,y).g=0;
                image.pixel(x,y).b=0;
            }else if(x==299){
                image.pixel(x,y).r=0;
                image.pixel(x,y).g=1;
                image.pixel(x,y).b=0;
            }else if(image.pixel(x,y).r==1-fade>0.5){
                image.pixel(x,y).r=1-fade;
                image.pixel(x,y).g=0;
                image.pixel(x,y).b=0;
            }else{
                image.pixel(x,y).r=0;
                image.pixel(x,y).g=0+fade;
                image.pixel(x,y).b=0; 
            }
        }
        fade+=1.f/300.f;
    }
    image.save("output/fade_first_version_fail.png");
}

int main()
{
    // sil::Image image{"images/logo.png"};
    // only_green(image);
    // exchange_can(image);
    // black_and_white(image);
    // negative_color(image);
    // black_and_white_fade();
    // mirror(image);
    // noise(image);
    // rotation(image);
    // rgb_split(image);
    // sil::Image image{"images/photo.jpg"};
    // changeLighting(image);
    // draw_white_disc();
    // draw_border_of_a_white_circle();
    // draw_white_disc_for_gif();
    // draw_rosas();
    // sil::Image image{"images/logo.png"};
    // mirror_mosaic(image);
    // glitch(image);
    // sort_by_brightness(image);
    // fractal_mandelbrot();
    fade_first_version();
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