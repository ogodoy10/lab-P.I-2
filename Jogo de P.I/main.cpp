#include <allegro5/allegro.h> //inclui todas as bibliotecas que vai usar
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "personagem.h"
#include <allegro5/allegro_font.h>

//COLOCAR OS INIMIGOS NO FRAME E NO LUGAR DA TELA CERTO E FAZER ELES ATIRAREM 

//structs dos personagens
struct personagem soldado1;
struct inimigo inimigos[8];
struct bala balas[1500];
double last_shot_time = 0;
double shot_delay = 0.5;

int displayMode = 0;

bool colisao(struct bala bala, struct inimigo inimigos) {

    // Verifique a colisão
    if (bala.x < inimigos.x + inimigos.largura &&
        bala.x + 10 > inimigos.x &&
        bala.y < inimigos.y + inimigos.altura &&
        bala.y + bala.y > inimigos.y) { //SE DER ERRO TIRA O + bala.y
        // Colisão detectada
        return true;
    }

    // Nenhuma colisão detectada
    return false;
}

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

    //geram todas as imagens do jogo
    ALLEGRO_BITMAP* soldado = al_load_bitmap("./soldado1.png");  
    ALLEGRO_BITMAP* fundo = al_load_bitmap("./fundo1.jpg");
    ALLEGRO_BITMAP* veiculo1 = al_load_bitmap("./aviao1.png");
    ALLEGRO_BITMAP* veiculo1_invertido = al_load_bitmap("./aviao1invertido.png");
    ALLEGRO_BITMAP* veiculo2 = al_load_bitmap("./aviao2.png");
    ALLEGRO_BITMAP* veiculo2_invertido = al_load_bitmap("./aviao2invertido.png");
    ALLEGRO_BITMAP* inimigo = al_load_bitmap("./inimigo.png");
    ALLEGRO_BITMAP* menu = al_load_bitmap("menu.jpg");

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
    int velocidade = 20; //NÃO ESQUECER DE MUDAR ANTES DA APRESENTAÇÃO

    /*
    x : 380  y : 580
    x:500    y : 524
    x : 1030 y : 580
    x: 1250  y:524
    x : 1420 y : 580
    x : 1700 y : 524
    x : 1700 y : 580
    x : 2380 y : 540
    */



    //especificações inimigos 
    inimigos[0].frame = 0.f;
    inimigos[0].largura = 106.6 * 2;
    inimigos[0].altura = 78 * 2; //aqui esta fznd com que o inimigo suba e desça na tela
    inimigos[0].current_frame_y = 0;
    inimigos[0].time = 0;
    inimigos[0].x = 380;
    inimigos[0].y = 580;
    inimigos[0].vida;

    // Inimigo 1
    inimigos[1].frame = 0.f;
    inimigos[1].largura = 106.6;
    inimigos[1].altura = 78;
    inimigos[1].current_frame_y = 0;
    inimigos[1].time = 0;
    inimigos[1].x = 500;
    inimigos[1].y = 524;
    inimigos[1].vida;

    // Inimigo 2
    inimigos[2].frame = 0.f;
    inimigos[2].largura = 106.6;
    inimigos[2].altura = 78;
    inimigos[2].current_frame_y = 0;
    inimigos[2].time = 0;
    inimigos[2].x = 1030;
    inimigos[2].y = 580;
    inimigos[2].vida;

    // Inimigo 3
    inimigos[3].frame = 0.f;
    inimigos[3].largura = 106.6;
    inimigos[3].altura = 78;
    inimigos[3].current_frame_y = 0;
    inimigos[3].time = 0;
    inimigos[3].x = 1250;
    inimigos[3].y = 524;
    inimigos[3].vida;

    // Inimigo 4
    inimigos[4].frame = 0.f;
    inimigos[4].largura = 106.6;
    inimigos[4].altura = 78;
    inimigos[4].current_frame_y = 0;
    inimigos[4].time = 0;
    inimigos[4].x = 1420; 
    inimigos[4].y = 580;
    inimigos[4].vida;

    // Inimigo 5
    inimigos[5].frame = 0.f;
    inimigos[5].largura = 106.6;
    inimigos[5].altura = 78;
    inimigos[5].current_frame_y = 0;
    inimigos[5].time = 0;
    inimigos[5].x = 1700; 
    inimigos[5].y = 524;
    inimigos[5].vida;

    // Inimigo 6
    inimigos[6].frame = 0.f;
    inimigos[6].largura = 106.6;
    inimigos[6].altura = 78;
    inimigos[6].current_frame_y = 0;
    inimigos[6].time = 0;
    inimigos[6].x = 1700;
    inimigos[6].y = 580;
    inimigos[6].vida;

    // Inimigo 7

    inimigos[7].frame = 0.f;
    inimigos[7].largura = 106.6;
    inimigos[7].altura = 78;
    inimigos[7].current_frame_y = 0;
    inimigos[7].time = 0;
    inimigos[7].x = 2380;
    inimigos[7].y = 540;
    inimigos[7].vida;


    //especificações da câmera 
    float camera_posX = 0;

    //especificações dos aviões  
    int v1X = 0;
    int v1X_inverte = 900;
    int v2X = 900;
    int v2X_inverte = 0;


    //especificações da bala
    int num_balas = 0;

    // Variável para rastrear a posição da última bala disparada
    float last_bullet_x = 0;

    int mouseX;
    int mouseY;

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        ALLEGRO_MOUSE_STATE state;  
        al_get_mouse_state(&state);  
        double current_time = al_get_time();

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            
            continue;  // Volta para o início do loop para aguardar o próximo evento
        }

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
            if (soldado1.frame > 7) {
                soldado1.frame -= 3;
            }
            soldado1.time = 0;
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A) {
            if (soldado1.pos_x >= 0) {
                //Movimentos pra esquerda
                soldado1.current_frame_y = 0;
                soldado1.pos_x -= velocidade;
                soldado1.frame += 0.2f;
                if (soldado1.frame > 7) {
                    soldado1.frame -= 3;
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
                if (soldado1.frame > 7) {
                    soldado1.frame -= 3;
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
                if (soldado1.frame > 7) {
                    soldado1.frame -= 3;
                }
                soldado1.time = 0;
            }
        }

        

        //PERSONAGEM ATIRANDO 
        if(state.buttons & 1) { // Botão esquerdo do mouse
            soldado1.current_frame_y = soldado1.altura * 0.9;
            soldado1.frame += 0.4f;

            if(soldado1.frame > 4) {
                soldado1.frame -= 3; //frame do personagem atirando 
            }
            soldado1.time = 0;
           
            if(state.buttons & 1 && current_time - last_shot_time >= shot_delay) {
                if (num_balas < 1000) {
                    // Disparar uma bala se o botão esquerdo do mouse estiver pressionado e a última bala disparada estiver pelo menos 10 pixels à esquerda
                    balas[num_balas].x = soldado1.pos_x + 109; // A posição x da bala corresponde à posição x do personagem + 109px pra frente
                    balas[num_balas].y = soldado1.pos_y + 55; // A posição y da bala corresponde à posição y do personagem + 55px
                    balas[num_balas].dx = 5.0; // mover para a direita
                    last_bullet_x = balas[num_balas].x;
                    num_balas++;

                    last_shot_time = current_time;
                }
            }
        }


        //personagem parado
        if(soldado1.time > 10) {
            soldado1.current_frame_y = soldado1.altura * 3;
            soldado1.frame += 0.1f;
            if (soldado1.frame > 1) {
                soldado1.frame -= 1;
            }
        }

        for(int i = 0; i < 7; i++){
            if (inimigos[i].time > 10) {
                inimigos[i].current_frame_y = inimigos[i].altura * 1;
                inimigos[i].frame += 0.1f;
                if (inimigos[i].frame > 1) {
                    inimigos[i].frame -= 1;
                }
            }
        }

        // faz com que o personagem ao passar dessa largura volte ao começo
        if (soldado1.largura + soldado1.pos_x > 2789){
            soldado1.pos_x = 0;
        }
        
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if((mouseX > 331 && mouseX < 675) && (mouseY > 393 && mouseY < 488)){
                displayMode = 1;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (displayMode == 0) { //serve para exibir o menu na tela
            al_draw_bitmap(menu, 0, 0, 0);
        }

        if (displayMode == 1) { //faz com que ao usuario clicar o menu saia e comece o jogo

            if (soldado1.pos_x < 1785) { //faz com que a câmera acompanhe o soldado até o fundo acabar e dps o soldado passa para outra fase 
                al_draw_scaled_bitmap(fundo, 0, 0, 2789, 700, -camera_posX, 0, 2789, 700, 0); //desenha o fundo na tela
                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - camera_posX), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0); //desenha o soldado na tela
                //SPRITE PARA COLOCAR O BOSS
                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, 2380 - camera_posX, 540, soldado1.largura * 1.5, soldado1.altura * 1.5, 0);
            }
            else {
                al_draw_scaled_bitmap(fundo, 0, 0, 2789, 700, -1785, 0, 2789, 700, 0);
                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - 1785), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0);
                //SPRITE PARA COLOCAR O BOSS
                al_draw_scaled_bitmap(soldado, soldado1.largura* (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, 2380 - 1785, 540, soldado1.largura * 1.5, soldado1.altura * 1.5, 0);
            }

        

            // DESENHA OS INIMIGOS NA TELA EM SUAS COORDENADAS
            for (int i = 0; i < 7; i++) {
                if (inimigos[i].vida > 0) { // Verifica se o inimigo está vivo antes de desenhá-lo
                    al_draw_scaled_bitmap(inimigo, inimigos[i].largura * (int)inimigos[i].frame, inimigos[i].current_frame_y, inimigos[i].largura, inimigos[i].altura * 3, (inimigos[i].x - camera_posX), inimigos[i].y - inimigos[i]. altura, inimigos[i].largura * 2, inimigos[i].altura * 5, 0);
                }
            }

        



            for (int i = 1; i < num_balas; i++) {
                balas[i].x += balas[i].dx;
                al_draw_line(balas[i].x, balas[i].y, balas[i].x + 10, balas[i].y, al_map_rgb(255, 255, 0), 2.0);

                // Verifica se a bala colidiu com algum inimigo
                for (int j = 0; j < 7; j++) {
                    // Verifica a colisão apenas se a vida do inimigo for maior que 0
                    if (inimigos[j].vida > 0 && colisao(balas[i], inimigos[j])) {
                        // Decrementa a vida do inimigo
                        inimigos[j].vida--;
                    }
                }
            }

            // Verifica se o botão esquerdo do mouse foi solto
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if (event.mouse.button & 1) {
                    soldado1.atirando = false;
                }
            }
            else {
                soldado1.time++;
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

        }

        al_flip_display();
    }


    al_destroy_bitmap(veiculo1); 
    al_destroy_bitmap(veiculo1_invertido);
    al_destroy_bitmap(veiculo2);
    al_destroy_bitmap(veiculo2_invertido);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(soldado);
    al_destroy_bitmap(inimigo);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}