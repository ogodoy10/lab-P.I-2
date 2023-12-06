#include <allegro5/allegro.h> //inclui todas as bibliotecas que vai usar
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include "personagem.h"

//structs dos personagens
struct personagem soldado1;
struct inimigo inimigos[7];
struct bala balas[1500]; //QUANTIDADE DE BALAS DO SOLDADO 
struct bala balaInimigo[1000]; //QUANTIDADE DE BALA DOS INIMIGOS
struct inimigo chefe;
struct cone cones[4];
double last_shot_time = 0;
double shot_delay = 0.5;

int displayMode = 0; //SERVE PARA TELA DO MENU  

bool colisao(struct bala bala, struct inimigo inimigos) {

    // Verifique a colisão
    if (bala.x < inimigos.x + inimigos.largura &&
        bala.x + 10 > inimigos.x &&
        bala.y < inimigos.y + inimigos.altura &&
        bala.y + bala.y > inimigos.y) {
        // Colisão detectada
        return true;
    }

    // Nenhuma colisão detectada
    return false;
}

// Função para verificar colisão entre a bala do inimigo e o soldado
bool colisaoSoldado(struct bala balaInimigo, struct personagem soldado1) {
    // Verifique a colisão
    if (balaInimigo.x < soldado1.pos_x + 10 &&
        balaInimigo.x + 10 > soldado1.pos_x &&
        balaInimigo.y < soldado1.pos_y + soldado1.altura &&
        balaInimigo.y > soldado1.pos_y) {
        // Colisão detectada
        return true;
    }

    // Nenhuma colisão detectada
    return false;
}


bool colisaoCone(bala bala, cone cones) { //Colisão das balas com os cones
    if (bala.x < cones.x + cones.largura &&
        bala.x + 10 > cones.x &&
        bala.y < cones.y + cones.altura &&
        bala.y + 2 > cones.y) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    al_init(); //inicia o allegro
    al_init_image_addon(); //inicia a biblioteca de imagens 

    //instala o mouse, teclado e a bibilioteca para colocar formas geométricas na tela
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    //cria a tela do jogo
    ALLEGRO_DISPLAY* display = al_create_display(1000, 700);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "Campo de Guerra");


    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0); //FAZ RODAR OS EVENTOS A 20FPS

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
    ALLEGRO_BITMAP* boss = al_load_bitmap("./boss.png");

    //cria todos os eventos do allegro, incluindo o timer 
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    //especificações do soldado
    soldado1.frame = 0.f;
    soldado1.largura = 115.7;
    soldado1.altura = 77;
    soldado1.pos_x = 0;
    soldado1.pos_y = 575;
    soldado1.current_frame_y = 0;
    soldado1.time = 0;
    int velocidade = 5;
    int knockback = 10;

    //especificações dos cones

    cones[0].x = 570;
    cones[0].y = 570;

    cones[1].x = 1380;
    cones[1].y = 570;

    cones[2].x = 360;
    cones[2].y = 630;

    cones[3].x = 1040;
    cones[3].y = 625;

    //especificações inimigos 
    inimigos[0].frame = 4;
    inimigos[0].largura = 96;
    inimigos[0].altura = 100;
    inimigos[0].current_frame_y = inimigos[0].altura * 2;
    inimigos[0].time = 0;
    inimigos[0].x = 380;
    inimigos[0].y = 615;
    inimigos[0].vida;

    // Inimigo 1
    inimigos[1].frame = 4;
    inimigos[1].largura = 96;
    inimigos[1].altura = 100;
    inimigos[1].current_frame_y = inimigos[1].altura * 2;
    inimigos[1].time = 0;
    inimigos[1].x = 540;
    inimigos[1].y = 675;
    inimigos[1].vida;

    //// Inimigo 2
    inimigos[2].frame = 4;
    inimigos[2].largura = 96;
    inimigos[2].altura = 100;
    inimigos[2].current_frame_y = inimigos[2].altura * 2;
    inimigos[2].time = 0;
    inimigos[2].x = 1030;
    inimigos[2].y = 615;
    inimigos[2].vida;

    //// Inimigo 3
    inimigos[3].frame = 4;
    inimigos[3].largura = 96;
    inimigos[3].altura = 100;
    inimigos[3].current_frame_y = inimigos[3].altura * 2;
    inimigos[3].time = 0;
    inimigos[3].x = 1350;
    inimigos[3].y = 675;
    inimigos[3].vida;

    //// Inimigo 4
    inimigos[4].frame = 4;
    inimigos[4].largura = 96;
    inimigos[4].altura = 100;
    inimigos[4].current_frame_y = inimigos[4].altura * 2;
    inimigos[4].time = 0;
    inimigos[4].x = 1700;
    inimigos[4].y = 615;
    inimigos[4].vida;

    //// Inimigo 5
    inimigos[5].frame = 4;
    inimigos[5].largura = 96;
    inimigos[5].altura = 100;
    inimigos[5].current_frame_y = inimigos[5].altura * 2;
    inimigos[5].time = 0;
    inimigos[5].x = 1700;
    inimigos[5].y = 675;
    inimigos[5].vida;

    //// Inimigo 6
    inimigos[6].frame = 4;
    inimigos[6].largura = 96;
    inimigos[6].altura = 100;
    inimigos[6].current_frame_y = inimigos[6].altura * 2;
    inimigos[6].time = 0;
    inimigos[6].x = 2380;
    inimigos[6].y = 570;
    inimigos[6].vida = 10;


    chefe.frame = 3;
    chefe.largura = 178;
    chefe.altura = 190;
    chefe.current_frame_y = chefe.altura * 0;
    chefe.time = 0;
    chefe.x = 2380;
    chefe.y = 690;
    chefe.vida = 10;

    int inimigoAtirando = 0; // Variável para controlar qual inimigo está atirando

    //especificações da câmera 
    float camera_posX = 0;

    int limiteKnockback = 0; //INIDICA O LIMITE DE ONDE O KNOCKBACK DO SOLDADO PODE IR 

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

    // Inicializa as balas dos inimigos
    for (int i = 0; i < 7; i++) {
        balaInimigo[i].dx = -5.0;  // As balas dos inimigos se movem para a esquerda

        // Posição inicial das balas é a posição dos inimigos
        balaInimigo[i].x = inimigos[i].x - camera_posX;

        // Ajusta a altura inicial da bala com base na rua dos inimigos
        if (i < 3) {  // Inimigos da rua de cima
            balaInimigo[i].y = inimigos[i].y - 55;  // Altura ajustada para a rua de cima
        }
        else {  // Inimigos da rua de baixo
            balaInimigo[i].y = inimigos[i].y - 25;  // Altura ajustada para a rua de baixo
        }
    }

    while (true) {
        ALLEGRO_EVENT event; //ARMAZENA EVENTOS, COMO ENTRADA DE TECLADO E MOUSE
        al_wait_for_event(event_queue, &event); //BLOQUEIA O PROGRAMA ATÉ OCORRER UM EVENTO
        ALLEGRO_MOUSE_STATE state;
        al_get_mouse_state(&state); //OBTÉM O ESTADO ATUAL DO MOUSE E SALVA NA VARIÁVEL STATE 
        double current_time = al_get_time(); //RETORNA O TEMPO ATUAL EM SEGUNDOS DESDE QUE A BIBLIOTECA FOI INICIADA 

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
            if (soldado1.pos_x <= 6480) {
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
            if (soldado1.pos_y <= 570) { //esse primeiro if faz com que o personagem não passe do chão
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
            if (soldado1.pos_y >= 525) { //faz com q a posição y do personagem não passe da altura da rua 
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
        if (state.buttons & 1) { // Botão esquerdo do mouse
            soldado1.current_frame_y = soldado1.altura * 0.9;
            soldado1.frame += 0.4f;

            if (soldado1.frame > 4) {
                soldado1.frame -= 3; //frame do personagem atirando 
            }
            soldado1.time = 0;

            if (state.buttons & 1 && current_time - last_shot_time >= shot_delay) {
                if (num_balas < 1000) {
                    // Disparar uma bala se o botão esquerdo do mouse estiver pressionado e a última bala disparada estiver pelo menos 10 pixels à esquerda
                    balas[num_balas].x = soldado1.pos_x + 109; // A posição x da bala corresponde à posição x do personagem + 109px pra frente
                    balas[num_balas].y = soldado1.pos_y + 55; // A posição y da bala corresponde à posição y do personagem + 55px
                    balas[num_balas].dx = 5.0; // mover para a direita
                    last_bullet_x = balas[num_balas].x;
                    num_balas++;

                    last_shot_time = current_time; //O TEMPO DA ÚLTIMA BALA DO SOLDADO VAI SER O TEMPO ATUAL DO CURRENT TIME 
                }
            }
        }


        //personagem parado
        if (soldado1.time > 10) {
            soldado1.current_frame_y = soldado1.altura * 3;
            soldado1.frame += 0.1f;
            if (soldado1.frame > 1) {
                soldado1.frame -= 1;
            }
        }


        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { //Serve para saber se o usuário clicou no botão de jogar
            if ((mouseX > 331 && mouseX < 675) && (mouseY > 393 && mouseY < 488)) {
                displayMode = 1;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0)); //LIMPA A TELA 

        if (displayMode == 0) { //serve para exibir o menu na tela
            al_draw_bitmap(menu, 0, 0, 0);
        }

        if (displayMode == 1) { //faz com que ao usuario clicar o menu saia e comece o jogo

            if (soldado1.pos_x == 6485) {//faz o jogo reiniciar ao usuario passar dessa coordenada
                displayMode = 0;
                soldado1.pos_x = 0;
            }

            if (soldado1.pos_x < 5580) {
                al_draw_scaled_bitmap(fundo, 0, 0, 3310, 700, -camera_posX, 0, 3310 * 2, 401 * 3.1, 0); //desenha o fundo na tela
            }

            //COLISÃO DOS CONES DE CIMA 
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

            if (soldado1.pos_x < 5580) {
                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - camera_posX), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0); //desenha o soldado na tela

                if (inimigos[6].vida == 0) {

                    chefe.frame -= 0.2f;
                    if (chefe.frame < 0) {
                        chefe.frame = 0;
                    }
                    chefe.time = 0;
                    //BOSS MORRENDO 
                    al_draw_scaled_bitmap(boss, chefe.largura * (int)chefe.frame, chefe.current_frame_y, chefe.largura, chefe.altura, 2380 - camera_posX, chefe.y - chefe.altura, chefe.largura, chefe.altura, 0);
                }
                else {
                    //BOSS FICANDO 
                    al_draw_scaled_bitmap(inimigo, inimigos[6].largura * (int)inimigos[6].frame, inimigos[6].current_frame_y, inimigos[6].largura, inimigos[6].altura, 2380 - camera_posX, inimigos[6].y - inimigos[6].altura, inimigos[6].largura * 1.8, inimigos[6].altura * 1.9, 0);

                }
            }
            else {
                al_draw_scaled_bitmap(fundo, 0, 0, 3310, 700, -5580, 0, 3310 * 2, 401 * 3.1, 0);

                al_draw_scaled_bitmap(soldado, soldado1.largura * (int)soldado1.frame, soldado1.current_frame_y, soldado1.largura, soldado1.altura, (soldado1.pos_x - 5580), soldado1.pos_y, soldado1.largura * 1.5, soldado1.altura * 1.5, 0);
            }




            //COLISÃO DOS CONES DEBAIXO
            for (int i = 2; i < 4; i++) {
                al_draw_scaled_bitmap(cone, 0, 0, 95, 150, (cones[i].x - camera_posX), cones[i].y, 95 / 2, 150 / 2, 0);
                // Verifica a colisão
                if (soldado1.pos_x < cones[i].x + 95 &&
                    soldado1.pos_x + soldado1.largura > cones[i].x &&
                    soldado1.pos_y < cones[i].y + 1 &&
                    soldado1.pos_y + soldado1.altura > cones[i].y &&
                    soldado1.pos_y == 575) {

                    velocidade = 0;
                }
            }


            // DESENHA OS INIMIGOS NA TELA EM SUAS COORDENADAS
            for (int i = 0; i < 3; i++) { //DESENHA OS INIMIOGOS DA RUA DE CIMA 
                if (inimigos[i].vida > 0) { // Verifica se o inimigo está vivo antes de desenhá-lo
                    al_draw_scaled_bitmap(inimigo, inimigos[i].largura * (int)inimigos[i].frame, inimigos[i].current_frame_y, inimigos[i].largura, inimigos[i].altura, (inimigos[i].x - camera_posX), inimigos[i].y - inimigos[i].altura, inimigos[i].largura * 1.2, inimigos[i].altura * 1.2, 0);
                }
            }

            for (int i = 3; i < 6; i++) { //DESENHA OS INIMIGOS DA RUA DEBAIXO
                if (inimigos[i].vida > 0) {
                    al_draw_scaled_bitmap(inimigo, inimigos[i].largura * (int)inimigos[i].frame, inimigos[i].current_frame_y, inimigos[i].largura, inimigos[i].altura, (inimigos[i].x - camera_posX), inimigos[i].y - inimigos[i].altura, inimigos[i].largura * 1.2, inimigos[i].altura * 1.2, 0);
                }
            }


            //DESENHA AS BALAS E COLISÃO DAS BALAS DO SOLDADO COM O INIMIGO
            for (int i = 1; i < num_balas; i++) {
                balas[i].x += balas[i].dx;

                // Ajusta a posição da bala com base na posição da câmera, não faz a bala surgir pra frente do personagem 
                float ajustaBala = balas[i].x - camera_posX;

                al_draw_line(ajustaBala, balas[i].y, ajustaBala + 10, balas[i].y, al_map_rgb(255, 255, 0), 2.0);

                // COLISÃO DAS BALAS DO SOLDADO COM O INIMIGO
                for (int j = 0; j < 7; j++) {
                    // Verifica a colisão apenas se a vida do inimigo for maior que 0
                    if (inimigos[j].vida > 0 && colisao(balas[i], inimigos[j])) {
                        // Decrementa a vida do inimigo
                        inimigos[j].vida--;

                        if (colisao(balas[i], inimigos[j])) {
                            balas[i].x = -30000; // Move a bala para fora da tela
                        }
                    }

                }
            }



            //COLISÃO DAS BALAS DOS INIMIGOS COM O SOLDADO
            for (int i = 0; i < 7; i++) {
                // Verifica se o inimigo está vivo antes de atirar
                if (inimigos[i].vida > 0) {
                    // Verifica se a bala colidiu com o soldado
                    if (colisaoSoldado(balaInimigo[i], soldado1)) {
                        // Aplica o knockback apenas uma vez por colisão
                        if (balaInimigo[i].x != -1000) {
                            soldado1.pos_x -= knockback; // Faz o soldado tomar knockback
                        }

                        balaInimigo[i].x = -1000; // Move a bala para fora da tela
                    
                        // Para o knockback depois de um certo limite
                        if (soldado1.pos_x <= limiteKnockback) {
                            soldado1.pos_x = limiteKnockback;
                        }
                    }
                    else {
                        balaInimigo[i].x += balaInimigo[i].dx;
                        al_draw_line(balaInimigo[i].x, balaInimigo[i].y, balaInimigo[i].x, balaInimigo[i].y, al_map_rgb(255, 0, 0), 2.0);
                    }
                }
            }


            //COLISÃO DAS BALAS COM OS CONES
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 4; j++) {
                    if (balaInimigo[i].vida > 0 && colisaoCone(balaInimigo[i], cones[j])) {
                        // A bala desaparece ao atingir o cone
                        balaInimigo[i].vida = 0;
                    }
                }
            }

            //FAZ OS INIMIGOS ATIRAREM 
            for (int i = 0; i < 7; i++) {
                // Verifica se o inimigo está vivo e se é o inimigo que está atirando no momento
                if (inimigos[i].vida > 0 && i == inimigoAtirando) {

                    balaInimigo[i].x += balaInimigo[i].dx;
                    al_draw_line(balaInimigo[i].x, balaInimigo[i].y, balaInimigo[i].x + 10, balaInimigo[i].y, al_map_rgb(255, 0, 0), 2.0);

                    // Verifica se a bala do inimigo saiu da tela
                    if (balaInimigo[i].x < 0) {
                        // Reinicia a posição da bala para o início
                        balaInimigo[i].x = inimigos[i].x;
                        balaInimigo[i].y = inimigos[i].y;

                        // Muda para o próximo inimigo atirar
                        inimigoAtirando = (inimigoAtirando + 1) % 7;
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

            camera_posX = soldado1.pos_x; //a camera spwana junto com o soldado no começo da tela 

            if (v1X < 1000) { //faz com que o avião percorra o caminho indo e voltando na tela
                al_draw_bitmap(veiculo1, v1X, 100, 0); //desenha os aviões na tela
                v1X += 5;
            }
            else {
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


        al_flip_display(); //ATUALIZA A TELA
    }


    al_destroy_bitmap(veiculo1);
    al_destroy_bitmap(veiculo1_invertido);
    al_destroy_bitmap(veiculo2);
    al_destroy_bitmap(veiculo2_invertido);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(soldado);
    al_destroy_bitmap(inimigo);
    al_destroy_bitmap(boss);
    al_destroy_bitmap(cone);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}