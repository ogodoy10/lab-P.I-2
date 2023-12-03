struct personagem {
    float frame;
    float largura;
    int altura;
    int pos_x;
    int pos_y;
    int current_frame_y;
    int time;
    bool atirando = false; //variavel para o personagem atirar
};

struct bala{
    int x;
    int y;
    float dx;
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
};