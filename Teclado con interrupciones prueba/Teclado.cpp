#include "stm32f4xx.h"

// Definir los pines del teclado matricial
#define ROW1_PIN GPIO_Pin_0
#define ROW2_PIN GPIO_Pin_1
#define ROW3_PIN GPIO_Pin_2
#define ROW4_PIN GPIO_Pin_3
#define COL1_PIN GPIO_Pin_4
#define COL2_PIN GPIO_Pin_5
#define COL3_PIN GPIO_Pin_6
#define COL4_PIN GPIO_Pin_7
#define ROW1_PORT GPIOC
#define ROW2_PORT GPIOC
#define ROW3_PORT GPIOC
#define ROW4_PORT GPIOC
#define COL1_PORT GPIOC
#define COL2_PORT GPIOC
#define COL3_PORT GPIOC
#define COL4_PORT GPIOC

// Matriz de estado del teclado
bool keypad[4][4];

// Función para leer el estado de las filas del teclado
void readRows() {
  keypad[0][0] = (GPIO_ReadInputDataBit(ROW1_PORT, ROW1_PIN) == RESET);
  keypad[0][1] = (GPIO_ReadInputDataBit(ROW2_PORT, ROW2_PIN) == RESET);
  keypad[0][2] = (GPIO_ReadInputDataBit(ROW3_PORT, ROW3_PIN) == RESET);
  keypad[0][3] = (GPIO_ReadInputDataBit(ROW4_PORT, ROW4_PIN) == RESET);
}

// Función de interrupción para el timer
void TIM2_IRQHandler() {
  // Si la interrupción fue causada por el timer
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    // Leer el estado de las filas del teclado
    readRows();
    // Limpiar la bandera de interrupción del timer
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  }
}

int main() {
  // Habilitar el reloj para el puerto C
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

  // Configurar los pines del teclado matricial como entrada
  GPIO_InitTypeDef gpio_init;
  gpio_init.GPIO_Mode = GPIO_Mode_IN;
  gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init.GPIO_Pin = ROW1_PIN | ROW2_PIN | ROW3_PIN | ROW4_PIN;
  GPIO_Init(ROW1_PORT, &gpio_init);
  gpio_init.GPIO_Pin = COL1_PIN | COL2_PIN | COL3_PIN | COL4_PIN;
  GPIO_Init(COL1_PORT, &gpio_init);

  // Configurar el timer
  TIM_TimeBaseInitTypeDef tim_init;
  tim_init.TIM_Prescaler = 8400 - 1; // Frecuencia de 10 KHz
  tim_init.TIM_Period = 100 - 1; // Interrupción cada 100 ms
  tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
  tim_init.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &tim_init);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

  // Configurar la interrupción del timer
  NVIC_InitTypeDef nvic_init;
  nvic_init.NVIC_IRQChannel = TIM2_IRQn;
  nvic_init.NVIC_IRQChannelPreemptionPriority = 0;
    nvic_init.NVIC_IRQChannelSubPriority = 1;
  nvic_init.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_init);

  // Bucle principal
  while (1) {
    // Escanear el teclado matricial
    GPIO_SetBits(COL1_PORT, COL1_PIN);
    GPIO_ResetBits(COL2_PORT, COL2_PIN);
    GPIO_ResetBits(COL3_PORT, COL3_PIN);
    GPIO_ResetBits(COL4_PORT, COL4_PIN);
    keypad[1][0] = (GPIO_ReadInputDataBit(ROW1_PORT, ROW1_PIN) == RESET);
    keypad[1][1] = (GPIO_ReadInputDataBit(ROW2_PORT, ROW2_PIN) == RESET);
    keypad[1][2] = (GPIO_ReadInputDataBit(ROW3_PORT, ROW3_PIN) == RESET);
    keypad[1][3] = (GPIO_ReadInputDataBit(ROW4_PORT, ROW4_PIN) == RESET);
    GPIO_ResetBits(COL1_PORT, COL1_PIN);
    GPIO_SetBits(COL2_PORT, COL2_PIN);
    GPIO_ResetBits(COL3_PORT, COL3_PIN);
    GPIO_ResetBits(COL4_PORT, COL4_PIN);
    keypad[2][0] = (GPIO_ReadInputDataBit(ROW1_PORT, ROW1_PIN) == RESET);
    keypad[2][1] = (GPIO_ReadInputDataBit(ROW2_PORT, ROW2_PIN) == RESET);
    keypad[2][2] = (GPIO_ReadInputDataBit(ROW3_PORT, ROW3_PIN) == RESET);
    keypad[2][3] = (GPIO_ReadInputDataBit(ROW4_PORT, ROW4_PIN) == RESET);
    GPIO_ResetBits(COL2_PORT, COL2_PIN);
    GPIO_SetBits(COL3_PORT, COL3_PIN);
    GPIO_ResetBits(COL1_PORT, COL1_PIN);
    GPIO_ResetBits(COL4_PORT, COL4_PIN);
    keypad[3][0] = (GPIO_ReadInputDataBit(ROW1_PORT, ROW1_PIN) == RESET);
    keypad[3][1] = (GPIO_ReadInputDataBit(ROW2_PORT, ROW2_PIN) == RESET);
    keypad[3][2] = (GPIO_ReadInputDataBit(ROW3_PORT, ROW3_PIN) == RESET);
    keypad[3][3] = (GPIO_ReadInputDataBit(ROW4_PORT, ROW4_PIN) == RESET);
    GPIO_ResetBits(COL3_PORT, COL3_PIN);
    GPIO_SetBits(COL4_PORT, COL4_PIN);
    GPIO_ResetBits(COL1_PORT, COL1_PIN);
    GPIO_ResetBits(COL2_PORT, COL2_PIN);
    keypad[0][0] = (GPIO_ReadInputDataBit(ROW1_PORT, ROW1_PIN) == RESET);
    keypad[0][1] = (GPIO_ReadInputDataBit(ROW2_PORT, ROW2_PIN) == RESET);
    keypad[0][2] = (GPIO_ReadInputDataBit(ROW3_PORT, ROW3_PIN) == RESET);
    keypad[0][3] = (GPIO_ReadInputDataBit(ROW4_PORT, ROW4_PIN) == RESET);
    GPIO_ResetBits(COL4_PORT, COL4_PIN);

    // Procesar las teclas presionadas
    if (keypad[0][0]) {
      // Se presionó la tecla en la fila 1, columna 1
      // Realizar alguna acción
    } else if (keypad[0][1]) {
      // Se presionó la tecla en la fila 1, columna 2
      // Realizar alguna acción
    } else if (keypad[0][2]) {
      // Se presionó la tecla en la fila 1, columna 3
      // Realizar alguna acción
    } else if (keypad[0][3]) {
      // Se presionó la tecla en la fila 1, columna 4
      // Realizar alguna acción
    } else if (keypad[1][0]) {
      // Se presionó la tecla en la fila 2, columna 1
      // Realizar alguna acción
    } else if (keypad[1][1]) {
      // Se presionó la tecla en la fila 2, columna 2
      // Realizar alguna acción
    } else if (keypad[1][2]) {
      // Se presionó la tecla en la fila 2, columna 3
      // Realizar alguna acción
    } else if (keypad[1][3]) {
      // Se presionó la tecla en la fila 2, columna 4
      // Realizar alguna acción
    } else if (keypad[2][0]) {
      // Se presionó la tecla en la fila 3, columna 1
      // Realizar alguna acción
    } else if (keypad[2][1]) {
      // Se presionó la tecla en la fila 3, columna 2
      // Realizar alguna acción
    } else if (keypad[2][2]) {
      // Se presionó la tecla en la fila 3, columna 3
      // Realizar alguna acción
    } else if (keypad[2][3]) {
      // Se presionó la tecla en la fila 3, columna 4
      // Realizar alguna acción
    } else if (keypad[3][0]) {
      // Se presionó la tecla en la fila 4, columna 1
      // Realizar alguna acción
    } else if (keypad[3][1]) {
      // Se presionó la tecla en la fila 4, columna 2
      // Realizar alguna acción
    } else if (keypad[3][2]) {
      // Se presionó la tecla en la fila 4, columna 3
      // Realizar alguna acción
    } else if (keypad[3][3]) {
      // Se presionó la tecla en la fila 4, columna 4
      // Realizar alguna acción
    }

    // Esperar un corto tiempo para evitar rebotes
    for (int i = 0; i < 100000; i++);
  }
}


