#include <allegro5/allegro.h> //inclui todas as bibliotecas que vai usar
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "personagem.h"
#include <allegro5/allegro_font.h>

//structs dos personagens
struct personagem soldado1;
struct personagem inimigo1;
struct personagem inimigo2;

int main() {
	al_init(); //inicia o allegro
	al_init_image_addon(); //inicia a biblioteca de imagens 
	
    //instala o mouse, teclado e a bibilioteca para colocar formas geométricas na tela
	al_install_keyboard();
	al_install_mouse();
	al_init_primitives_addon();
    al_init_font_addon();

    //cria a tela do jogo
    ALLEGRO_DISPLAY* display = al_create_display(1000, 700);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Campo de Guerra");

    
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);
    ALLEGRO_FONT* font = al_create_builtin_font(); 

    //geream todas as imagens do jogo
    ALLEGRO_BITMAP* soldado = al_load_bitmap("./soldado1.png");  
    ALLEGRO_BITMAP* fundo = al_load_bitmap("./fundo1.jpg");
    ALLEGRO_BITMAP* veiculo1 = al_load_bitmap("./aviao1.png");
    ALLEGRO_BITMAP* veiculo1_invertido = al_load_bitmap("./aviao1invertido.png");
    ALLEGRO_BITMAP* veiculo2 = al_load_bitmap("./aviao2.png");
    ALLEGRO_BITMAP* veiculo2_invertido = al_load_bitmap("./aviao2invertido.png");

    //cria todos os eventos do allegro, incluindo o timer 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    //especificações do struct soldado
    soldado1.frame = 0.f;
    soldado1.largura = 115.7;
    soldado1.altura = 77; 
    soldado1.pos_x = 0;
    soldado1.pos_y = 580;
    soldado1.current_frame_y = 0;
    soldado1.time = 0;
    int velocidade = 5;

    //especificações da câmera 
    float camera_posX = 0;

    //especificações dos aviões  
    int v1X = 0;
    int v1X_inverte = 900;
    int v2X = 900;
    int v2X_inverte = 0;


    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        //Fim do Programa
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }

        //Andando
        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D) {
            //Movimentos pra direita
            soldado1.current_frame_y = 0;
            soldado1.pos_x += velocidade;
            soldado1.frame += 0.2f;
            if (soldado1.frame > 4) {
                soldado1.frame -= 4;
            }
            soldado1.time = 0;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A) {
            if (soldado1.pos_x >= 0) {
                //Movimentos pra esquerda
                soldado1.current_frame_y = 0;
                soldado1.pos_x -= velocidade;
                soldado1.frame += 0.2f;
                if (soldado1.frame > 4) {
                    soldado1.frame -= 4;
                }
                soldado1.time = 0;
            }
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN || event.keyboard.keycode == ALLEGRO_KEY_S) {
            //Movimentos pra baixo
            if (soldado1.pos_y <= 580) { //esse primeiro if faz com que o personagem n passe do chão
                soldado1.current_frame_y = 0;
                soldado1.pos_y += velocidade;
                soldado1.frame += 0.2f;
                if (soldado1.frame > 4) {
                    soldado1.frame -= 4;
                }
                soldado1.time = 0;
            }
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_UP || event.keyboard.keycode == ALLEGRO_KEY_W) {
            if(soldado1.pos_y >= 525){ //faz com q a posição y do personagem n passe da altura da rua 
            //Movimentos pra cima
                soldado1.current_frame_y = 0;
                soldado1.pos_y -= velocidade;
                soldado1.frame += 0.2f;
                if (soldado1.frame > 4) {
                    soldado1.frame -= 4;
                }
                soldado1.time = 0;
            }
        }
        else {
            soldado1.time++;
        }
        //personagem parado
        if (soldado1.time > 10) {
            soldado1.current_frame_y = soldado1.altura * 3;
            soldado1.frame += 0.1f;
            if (soldado1.frame > 1) {
                soldado1.frame -= 1;
            }
        }
        // faz com que o personagem ao passar dessa largura volte ao começo
        if (soldado1.largura + soldado1.pos_x > 2789){
            soldado1.pos_x = 0;
        }
        

        al_clear_to_color(al_map_rgb(0, 0, 0));

        
        if (soldado1.pos_x < 1785) { //faz com que a câmera acompanhe o soldado até o fundo acabar e dps o soldado passa para outra fase
            al_draw_scaled_bitmap(fundo, 0, 0, 2789, 700, - camera_posX, 0, 2789, 700, 0); //desenha o fundo na tela
            al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - camera_posX), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0); //desenha o soldado
        }
        else {
            al_draw_scaled_bitmap(fundo, 0, 0, 2789, 700, - 1785, 0, 2789, 700, 0); 
            al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - 1785), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0); 
        }

        
        al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "soldado: (%d, %d)", soldado1.pos_x, soldado1.pos_y);

        camera_posX = soldado1.pos_x; //a camera spwana junto com o soldado no começo da tela 

        if (v1X < 1000) { //faz com que o avião percorra o caminho indo e voltando na tela
            al_draw_bitmap(veiculo1, v1X, 100, 0); //desenha os aviões na tela
            v1X += 5;
        }
        else{ 
            al_draw_bitmap(veiculo1_invertido, v1X_inverte, 100, 0); 
            v1X_inverte -= 5;

            if (v1X_inverte == -250) {
                v1X = -250;
                v1X_inverte = 900;
            }
        }


        if (v2X > -250) { //faz com que o avião percorra o caminho indo e voltando na tela
            al_draw_bitmap(veiculo2, v2X, 0, 0); 
            v2X -= 5;
        }
        else {
            al_draw_bitmap(veiculo2_invertido, v2X_inverte, 0, 0); 
            v2X_inverte += 5;

            if (v2X_inverte == 1000) {  
                v2X = 1000;
                v2X_inverte = -250;             
            }
        }

        al_flip_display();
    }


    al_destroy_bitmap(veiculo1); 
    al_destroy_bitmap(veiculo1_invertido);
    al_destroy_bitmap(veiculo2);
    al_destroy_bitmap(veiculo2_invertido);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(soldado);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}