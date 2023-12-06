struct personagem {
    float frame;
    float largura;
    int altura;
    int pos_x;
    int pos_y;
    int current_frame_y;
    int time;
    bool atirando = false; 
};

struct bala{
    int x;
    int y;
    float dx;
    int morto;
    int vida = 1;
};

struct inimigo{
    int x;
    int y;
    float frame;
    float largura;
    float altura;
    int current_frame_y;
    int time;
    int vida = 3;
    bool colisao;
    int bala;
};

struct cone{
    int x;
    int y;
    int largura = 95;
    int altura = 150;
};