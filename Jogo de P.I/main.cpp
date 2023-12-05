#include <allegro5/allegro.h> //inclui todas as bibliotecas que vai usar
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "personagem.h"
#include <allegro5/allegro_font.h>

//FAZER OS INIMIGOS ATIRAREM E FAZER COM QUE A BALA QUE ACERTAR OS INIMIGOS DESAPAREÇAM 

//structs dos personagens
struct personagem soldado1;
struct inimigo inimigos[7]; 
struct bala balas[1500]; //QUANTIDADE DE BALAS DO SOLDADO 
struct bala balaInimigo[1000]; //QUANTIDADE DE BALA DOS INIMIGOS 
struct cones cones[4];
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

// Função para verificar colisão entre a bala do inimigo e o soldado
bool colisaoSoldado(struct bala balaInimigo, struct personagem soldado1) {
    // Verifique a colisão
    if (balaInimigo.x < soldado1.pos_x + soldado1.largura &&
        balaInimigo.x + 10 > soldado1.pos_x &&
        balaInimigo.y < soldado1.pos_y + soldado1.altura &&
        balaInimigo.y + 2 > soldado1.pos_y) { // Ajustado para bala.y + 2
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
    ALLEGRO_BITMAP* fundo = al_load_bitmap("./fundo2.jpg");
    ALLEGRO_BITMAP* veiculo1 = al_load_bitmap("./aviao1.png");
    ALLEGRO_BITMAP* veiculo1_invertido = al_load_bitmap("./aviao1invertido.png");
    ALLEGRO_BITMAP* veiculo2 = al_load_bitmap("./aviao2.png");
    ALLEGRO_BITMAP* veiculo2_invertido = al_load_bitmap("./aviao2invertido.png");
    ALLEGRO_BITMAP* inimigo = al_load_bitmap("./inimigoF.png");
    ALLEGRO_BITMAP* menu = al_load_bitmap("menu.jpg");
    ALLEGRO_BITMAP* cone = al_load_bitmap("./cone.png");

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
    int velocidade = 5; //NÃO ESQUECER DE MUDAR ANTES DA APRESENTAÇÃO (ALTERA PRA 2 SEU BURRO)

    /* coordenadas de onde os inimigos tem que estar na tela 
    x : 380  y : 580
    x:500    y : 524
    x : 1030 y : 580
    x: 1250  y:524
    x : 1420 y : 580
    x : 1700 y : 524
    x : 1700 y : 580
    x : 2380 y : 540
    */

    //especificações dos cones
    
    cones[0].x = 570;
    cones[0].y = 570;
    
    cones[1].x = 1380;
    cones[1].y = 570;
    
    cones[2].x = 360;
    cones[2].y = 630;
    
    cones[3].x = 1040;
    cones[3].y = 630;

    


    //especificações inimigos 
    inimigos[0].frame = 3;
    inimigos[0].largura = 66;
    inimigos[0].altura = 90; 
    inimigos[0].current_frame_y = inimigos[0].altura * 1.2; //inimigos[i].frame += 0.1f;
    inimigos[0].time = 0;
    inimigos[0].x = 380;
    inimigos[0].y = 620;
    inimigos[0].vida;

    // Inimigo 1
    inimigos[1].frame = 3;
    inimigos[1].largura = 66;
    inimigos[1].altura = 90;
    inimigos[1].current_frame_y = inimigos[1].altura * 1.2;
    inimigos[1].time = 0;
    inimigos[1].x = 540;
    inimigos[1].y = 680;
    inimigos[1].vida;

    // Inimigo 2
    inimigos[2].frame = 3;
    inimigos[2].largura = 66;
    inimigos[2].altura = 90;
    inimigos[2].current_frame_y = inimigos[2].altura * 1.2;
    inimigos[2].time = 0;
    inimigos[2].x = 1030;
    inimigos[2].y = 615;
    inimigos[2].vida;

    // Inimigo 3
    inimigos[3].frame = 3;
    inimigos[3].largura = 66;
    inimigos[3].altura = 90;
    inimigos[3].current_frame_y = inimigos[3].altura * 1.2;
    inimigos[3].time = 0;
    inimigos[3].x = 1350;
    inimigos[3].y = 675;
    inimigos[3].vida;

    // Inimigo 4
    inimigos[4].frame = 3;
    inimigos[4].largura = 66;
    inimigos[4].altura = 90;
    inimigos[4].current_frame_y = inimigos[4].altura * 1.2;
    inimigos[4].time = 0;
    inimigos[4].x = 1700;
    inimigos[4].y = 615;
    inimigos[4].vida;

    // Inimigo 5
    inimigos[5].frame = 3;
    inimigos[5].largura = 66;
    inimigos[5].altura = 90;
    inimigos[5].current_frame_y = inimigos[5].altura * 1.2;
    inimigos[5].time = 0;
    inimigos[5].x = 1700;
    inimigos[5].y = 675;
    inimigos[5].vida;

    // Inimigo 6
    inimigos[6].frame = 3;
    inimigos[6].largura = 66;
    inimigos[6].altura = 90;
    inimigos[6].current_frame_y = inimigos[6].altura * 1.2;
    inimigos[6].time = 0;
    inimigos[6].x = 2380;
    inimigos[6].y = 570;
    inimigos[6].vida;


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

        mouseX = al_get_mouse_state_axis(&state, 0);
        mouseY = al_get_mouse_state_axis(&state, 1);

        if (event.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
            
            continue;  // Volta para o início do loop para aguardar o próximo evento
        }

        //Fim do Programa
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            break;
        }

        //Andando
        if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D) {
            if (soldado1.pos_x <= 6480){
                //Movimentos pra direita
                soldado1.current_frame_y = 0;
                soldado1.pos_x += velocidade;
                soldado1.frame += 0.2f;
                if (soldado1.frame > 7) {
                    soldado1.frame -= 3;
                }
                soldado1.time = 0;
            }
        }
        else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A) {
            velocidade = 5;
            if (soldado1.pos_x - 20 >= 0) {
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
            velocidade = 5; 
            //Movimentos pra baixo
            if (soldado1.pos_y <= 570) { //esse primeiro if faz com que o personagem n passe do chão
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
            velocidade = 5; 
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
            if (soldado1.pos_x == 6500) {
                displayMode = 0;
                soldado1.pos_x = 0;
            }

            
            if (soldado1.pos_x < 5580) { //faz com que a câmera acompanhe o soldado até o fundo acabar e dps o soldado passa para outra fase 

                al_draw_scaled_bitmap(fundo, 0, 0, 3310, 700, - camera_posX, 0, 3310 * 2, 401 * 3.1, 0); //desenha o fundo na tela
               
                for (int i = 0; i < 2; i++) {
                    al_draw_scaled_bitmap(cone, 0, 0, 95, 150, (cones[i].x - camera_posX), cones[i].y, 95 / 2, 150 / 2, 0);
                    // Verifica a colisão
                    if (soldado1.pos_x < cones[i].x + 95 &&
                        soldado1.pos_x + soldado1.largura > cones[i].x &&
                        soldado1.pos_y < cones[i].y + 1 &&
                        soldado1.pos_y + soldado1.altura > cones[i].y && 
                        soldado1.pos_y == 520) {
                    
                        velocidade = 0;
                    }
                }

                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - camera_posX), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0); //desenha o soldado na tela
               
                //BOSS
                al_draw_scaled_bitmap(inimigo, inimigos[6].largura* (int)inimigos[6].frame, inimigos[6].current_frame_y, inimigos[6].largura, inimigos[6].altura, 2380 - camera_posX, inimigos[6].y - inimigos[6].altura, inimigos[6].largura * 1.8, inimigos[6].altura * 1.9, 0);
            }
            else {
                al_draw_scaled_bitmap(fundo, 0, 0, 3310, 700, -5580, 0, 3310 * 2, 401 * 3.1, 0);
                
                al_draw_scaled_bitmap(soldado, soldado1.largura* (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - 5580), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0);
            }


            //COLISÃO DOS CONES 
            for (int i = 2; i < 4; i++) {
                al_draw_scaled_bitmap(cone, 0, 0, 95, 150, (cones[i].x - camera_posX), cones[i].y, 95 / 2, 150 / 2, 0);
                // Verifica a colisão
                if (soldado1.pos_x < cones[i].x + 95 &&
                    soldado1.pos_x + soldado1.largura > cones[i].x &&
                    soldado1.pos_y < cones[i].y + 1 &&
                    soldado1.pos_y + soldado1.altura > cones[i].y &&
                    soldado1.pos_y == 580) {

                    velocidade = 0;
                }
            }


            // DESENHA OS INIMIGOS NA TELA EM SUAS COORDENADAS
            for (int i = 0; i < 3; i++) {
                if (inimigos[i].vida > 0) { // Verifica se o inimigo está vivo antes de desenhá-lo
                    al_draw_scaled_bitmap(inimigo, inimigos[i].largura * (int)inimigos[i].frame, inimigos[i].current_frame_y, inimigos[i].largura, inimigos[i].altura, (inimigos[i].x - camera_posX), inimigos[i].y - inimigos[i]. altura, inimigos[i].largura * 1.2, inimigos[i].altura * 1.2, 0);
                }
            }

            for (int i = 3; i < 6; i++) {
                if (inimigos[i].vida > 0) { // Verifica se o inimigo está vivo antes de desenhá-lo
                    al_draw_scaled_bitmap(inimigo, inimigos[i].largura * (int)inimigos[i].frame, inimigos[i].current_frame_y, inimigos[i].largura, inimigos[i].altura, (inimigos[i].x - camera_posX), inimigos[i].y - inimigos[i].altura, inimigos[i].largura * 1.2, inimigos[i].altura * 1.2, 0);
                }
            }


            //DESENHA AS BALAS
                for (int i = 1; i < num_balas; i++) {
                    balas[i].x += balas[i].dx;

                    // Ajusta a posição da bala com base na posição da câmera, não faz a bala surgir pra frente do personagem 
                    float ajustaBala = balas[i].x - camera_posX;

                    al_draw_line(ajustaBala, balas[i].y, ajustaBala + 10, balas[i].y, al_map_rgb(255, 255, 0), 2.0);

                    // Verifica se a bala colidiu com algum inimigo
                    for (int j = 0; j < 7; j++) {
                        // Verifica a colisão apenas se a vida do inimigo for maior que 0
                        if (inimigos[j].vida > 0 && colisao(balas[i], inimigos[j])) {
                            // Decrementa a vida do inimigo
                            inimigos[j].vida--;
                        }
                    }
                }

            // Verifica colisão da bala do inimigo com o jogador
            for (int i = 0; i < 7; i++) {
                if (inimigos[i].vida > 0 && colisaoSoldado(balaInimigo[i], soldado1)) {
                    // o soldado fica indo 10px pra trás a cada tiro recebido
                    soldado1.pos_x -= 10;
                }
            }

            for (int i = 0; i < 7; i++) {
                // Verifica se o inimigo está vivo antes de atirar
                if (inimigos[i].vida > 0) {
                    // Lógica para mover e desenhar a bala do inimigo
                    balaInimigo[i].x += balaInimigo[i].dx;
                    al_draw_line(balaInimigo[i].x, balaInimigo[i].y, balaInimigo[i].x + 10, balaInimigo[i].y, al_map_rgb(255, 0, 0), 2.0);
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
    al_destroy_bitmap(cone);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}