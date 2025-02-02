//Declaração das bibliotecas utilizadas
#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/pio.h"
#include "ws2818b.pio.h"
#include "hardware/timer.h"

// Definição dos pinos dos componentes
#define BOTAO_A 5      
#define BOTAO_B 6     
#define azul 11              //RGB
#define verde 12            //RGB
#define vermelho 13        //RGB

int valor_atual = 0; // Variavel do numero mostrado na matriz.
bool led_vermelho = false;
static volatile uint32_t last_time = 0;


/* Função para indexar as posições dos led da matriz */
int getIndex(int x, int y) {
    if (x % 2 == 0) {
        return  24 - (x * 5 + y);
    } else {
        return 24 - (x * 5 + (4 - y));
    }
}

//Inicializar os pinos do led RGB
void iniciar_rgb() {
  gpio_init(vermelho);
  gpio_init(verde);
  gpio_init(azul);

  //Configurando como saída
  gpio_set_dir(vermelho, GPIO_OUT);
  gpio_set_dir(verde, GPIO_OUT);
  gpio_set_dir(azul, GPIO_OUT);
}

// Função para acionar leds RGB e configurar o tempo ligado
void led() {
 gpio_put(vermelho, true);
 sleep_ms(50);
 gpio_put(vermelho, false);
 sleep_ms(150);
} 

//CONFIGURANDO A MATRIZ DE LEDS com a biblioteca ws2818b
// Definição da estrutura de cor para cada LED da matriz
struct pixel_t {
    uint8_t R, G, B;
};
typedef struct pixel_t npLED_t;
npLED_t leds[25];

// PIO e state machine para controle dos LEDs 
PIO np_pio;
uint sm;

// Função para atualizar os LEDs da matriz e salvar o estado "buffer"
void buffer() {
    for (uint i = 0; i < 25; i++) {
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
}

// Função de inicializar a matriz de LEDs com a ws2818b.
void iniciar_matriz() {
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;
    sm = pio_claim_unused_sm(np_pio, true);
    ws2818b_program_init(np_pio, sm, offset, 7, 800000.f);

    for (uint i = 0; i < 25; i++) {
        leds[i].R = leds[i].G = leds[i].B = 0;
    }
    buffer();
}

// Função para configurar a cor dos LEDs da matriz
void cor(const uint indice, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[indice].R = r;
    leds[indice].G = g;
    leds[indice].B = b;
}

// Conjunto de funções para ligar os leds e formar o numero na matriz
void num0() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0},{0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0},  {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0},  { 0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0},  {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0},{0, 0, 0}}
    };
    //Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num1() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num2() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num3() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0  }},
        {{0, 0, 0}, {0, 0, 0},     {0, 0,     0}, {0, 255, 0}, {0, 0,   0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0,   0}},
        {{0, 0, 0}, {0, 0, 0},     {0, 0,     0}, {0, 255, 0}, {0, 0,   0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0,   0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num4() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num5() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num6() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num7() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num8() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}
    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}

void num9() {
    int mat1[5][5][3] = {
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 0, 0}},
        {{0, 0, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 0, 0}}

    };

    // Exibir na matriz
    for (int linha = 0; linha < 5; linha++) {
        for (int cols = 0; cols < 5; cols++) {
            int posicao = getIndex(linha, cols);
            cor(posicao, mat1[linha][cols][0], mat1[linha][cols][1], mat1[linha][cols][2]);
        }
    }
    buffer();
}


// Função base com switch para atualizar do número na matriz de acordo com a variavel valor_atual
void atualizar_valor() {
    switch (valor_atual) {
        case 0:
            num0();
            
            break;
        case 1:
            num1();
            
            break;
        case 2:
            num2();
            
            break;
        case 3:
            num3();
            
            break;
        case 4:
            num4();
            
            break;
        case 5:
            num5();
            
            break;
        case 6:
            num6();
    
            break;
        case 7:
            num7();
        
            break;
        case 8:
            num8();
    
            break;
        case 9:
            num9();
        
            break;
    }
}

// Função para inicializar os pinos dos botões A e B como entrada e habilitar o pull up;
void iniciar_botoes() {
    gpio_init(BOTAO_A);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_set_dir(BOTAO_B, GPIO_IN);
    gpio_pull_up(BOTAO_A);
    gpio_pull_up(BOTAO_B);
}

void gpio_irq_handler(uint gpio, uint32_t events){
    // Obtém o tempo atual em us
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 250000) // 250 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento
        // BOTÃO A para incremento e BOTÃO B para decremento
        if (gpio == BOTAO_A) {
            valor_atual = (valor_atual + 1) % 10; //Número a ser exibido na matriz
        } else if (gpio == BOTAO_B) {
            valor_atual = (valor_atual - 1 + 10) % 10; //Número a ser exibido na matriz
        }
        atualizar_valor(); 
    }

}

// Função principal
int main() {
    //Funções de inicialização
    stdio_init_all();
    iniciar_matriz(); // Iniciando a matriz
    iniciar_botoes(); // Iniciando os botões
    iniciar_rgb();
    

    // Habilita as interrupções para os botões
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    

    while (true) {

        led(); //Função para altenar o esta do led vermelho e piscar 5 vezes por segundo
    }
    return 0; 
}
