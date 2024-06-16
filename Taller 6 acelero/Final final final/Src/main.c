
//Llamado de librerias externas a utilizar
#include "main.h" //Libreria generada por cube mx para usar los archivos de HAL
#include "oled.h" //Librería de la oled
#include "stdio.h" 
#include "TJ_MPU6050.h" //Librería del acelerómetro
////////////////////////////


//Definición de variables a utilizar
float x1=0,y1=0,z1=0,x2=0; //Utilizados para extraer los datos que arroja el acelerómetro
float tem=0; //Guarda el tiempo en ms del pulso
float temdelay=0; //Compensa el pulso para dar un total de 20ms
int compara=1; //Se usa para elegir si se usará matlab o acelerómetro
 char* ang1 = "000"; 
char* ang2 = "000";
char* ang3 = "000";	
char* angs = "000";	
char dato_char1[6]; //Son usados para guardar la cadena de caracteres convertida
char dato_char2[6];
char dato_char3[6];
char dato_chars[6];
//////////////////////

void delay (float ms){ // Es el delay xd
	
	ms=ms*5333;
	for(int z=0;z<ms;z++){__ASM("NOP");}

}


void i2c_init(void){
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN; //Habilita el puerto b 
RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;  //Habilita el i2c
GPIOB->MODER|=0x55;  //Pone los pines B0 y B1 en salida, por aquí se enviará la señal a los servos
GPIOB->MODER|=0xA0000;  //Habilita los piness B8 y B9 para utilizar I2C
GPIOB->AFR[1]|=0x44;    //Se usa para definir el pin SDA
GPIOB->OTYPER|=GPIO_OTYPER_OT8|GPIO_OTYPER_OT9;  
I2C1->CR1=I2C_CR1_SWRST;  //Configuración por defecto
I2C1->CR1&=~I2C_CR1_SWRST;	
I2C1->CR2|=16;
I2C1->CCR|=0x2|(1<<15)|(1<<14); 
I2C1->TRISE=17; 
I2C1->CR1|=I2C_CR1_PE;
}


I2C_HandleTypeDef hi2c1; //Estructura utilizada para guardar datos de la transmisión (numero de transmisión, dispositivo, modo de comunicación, longitud de datos)

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void); //Prototipo del sistema de reloj que será usado para I2C
static void MX_GPIO_Init(void); //Prototipo de la configuración de GPIO realizada por cubemx para i2c
static void MX_I2C1_Init(void); //Prototipo para iniciar I2C
////////////////////////////////////////


RawData_Def myAccelRaw, myGyroRaw;  //Llama el dato en bruto obtenido del sensor, para el gyro y los ejes
ScaledData_Def myAccelScaled, myGyroScaled; //Llama el dato escalado obtenido del sensor para el gyro y los ejes
/////////////////////////////


	void USART2_Config(void){ //Esta es la configuración usada para el USART2
		
		GPIOA->MODER|=0x80;// Se configura el pin a3 en alterno, por donde se conecta la com serial
		GPIOA->AFR[0]|=0x7000;// Se configura el pin A3 para el af7=USART2
		RCC->APB1ENR|=(1UL<<17); //Habilita el usart2, valor por defecto
		USART2->BRR=0x683; //9600 Bausios 
		USART2->CR1|=0x2D; //Interrupcion habiliatado Se habilita el tx, el rx y la interrupción del usart
		USART2->CR1|=0x2000;  //Activa el usart
		NVIC_EnableIRQ(USART2_IRQn); //Activa vector de interrupción
	 USART2->CR1|=USART_CR1_RXNEIE; // Activa servicio de interrupción
		
	}
	
int main(void)
{
	RCC->AHB1ENR|=0xF; //Se habilitan todos los puertos
	MPU_ConfigTypeDef myMpuConfig; //LLama la configuración definida del acelerómetro
  HAL_Init(); //Inicia las secciones utilizadas de la libreria HAL
	i2c_init(); //Inicia la configuración de I2C
	delay(1000); //Otro delay xd
	oled_Init(); //Inicia la configuración de la OLED
  MX_GPIO_Init(); //Inicia las configuraciones generadas por cube mx para los puertos usados para i2c
  MX_I2C1_Init(); //Inicia la configuración utilizada para el acelerómetro
  
  
//////////Explicación del acelerómetro
	
	//Inicializa el modulo MPU6050 junto a I2C
	MPU6050_Init(&hi2c1);
	//2. Configura el eje y los parámetros de giro, configuración por defecto
	myMpuConfig.Accel_Full_Scale = AFS_SEL_4g;
	myMpuConfig.ClockSource = Internal_8MHz;
	myMpuConfig.CONFIG_DLPF = DLPF_184A_188G_Hz;
	myMpuConfig.Gyro_Full_Scale = FS_SEL_500;
	myMpuConfig.Sleep_Mode_Bit = 0;  //1: sleep mode, 0: normal mode
	MPU6050_Config(&myMpuConfig); //Guardará esto en myMpuConfig
	
	USART2_Config(); //Habilita la configuración del usart 2	
 
  while (1)
  {
			
//		//Raw data, se llama si se quieren leer los datos en bruto del acelerómetro, van en gravedades
//		MPU6050_Get_Accel_RawData(&myAccelRaw); // Gravedades
//		MPU6050_Get_Gyro_RawData(&myGyroRaw); //Angulos / segundo
		
		
		if (compara==0) { //Este compara será usado para que ejecute dentro del ciclo sin fin, dependiendo a lo que se busca usar, matlab o acelerómetro
			SystemClock_Config(); //Define la configuración usada por el acelerómetro
		MPU6050_Get_Accel_Scale(&myAccelScaled); //myAccelScaled es un dato tipo struct, aquí se solicita obtener los datos guardados en esta variable, x,y,z
		MPU6050_Get_Gyro_Scale(&myGyroScaled); //myGyroScaled es un dato tipo struct, aquí se solicita obtener los datos guardados en esta variable, x,y,z
		//Los datos escalados mantienen una proporción 1 a 1000 (1 cuando x es 1, 1000 cuando x es 180)
			
		x1=((myAccelScaled.x*90)/1000); //Se hace una conversión para que el dato ahora vaya de 0 a 180
		y1=((myAccelScaled.y*90)/1000); //Lo mismo de arriba
		z1=((myAccelScaled.z*90)/1000);
		
		if(x1>=0&&y1<=0){
			 z1=atan((x1)/(y1*-1))*180/3.1416;
		 }
		 else if(x1>=0&&y1>=0){
			 z1=atan((y1)/(x1))*180/3.1416+90;
		 }
		 else if(x1<=0&&y1>=0){
			 z1=atan((x1*-1)/(y1))*180/3.1416+180;
		 }
		 else if(x1<=0&&y1<=0){
			 z1=atan((y1*-1)/(x1*-1))*180/3.1416+270;
		 }
			
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		HAL_Delay(10); //Delay dado entre toma y toma de datos
		
		 sprintf(ang1, "%.2f", x1); //Toma el dato extraido de la coordenada, y ya que es tipo double, lo convierte a cadena de texto para mostrarlo en la OLED
	ang1=dato_char1; //Lo guarda en una variable usada para mostrarlo en la OLED
	
		 sprintf(ang2, "%.2f", y1); //Lo mismo de arriba
	ang2=dato_char2;
	
		 sprintf(ang3, "%.2f", z1);
	ang3=dato_char3;
	
	SSD1306_GotoXY (5, 5); //Define la sección de la OLED en la que va a escribir
	SSD1306_Puts ("Grados X: ", &Font_7x10, 1); //Escribe lo que se muestra
  SSD1306_GotoXY (5, 25); //Se repite
	SSD1306_Puts ("Grados Y: ", &Font_7x10, 1);
	 SSD1306_GotoXY (5, 45);
	SSD1306_Puts ("Grados Z: ", &Font_7x10, 1);
	SSD1306_UpdateScreen();


  SSD1306_GotoXY (75, 5); //Define la sección de la OLED
	SSD1306_Puts (ang1, &Font_7x10, 1); //Ahora, enviará a la oled la cadena de caracteres convertida del angulo que se está tomando
	SSD1306_GotoXY (75, 25); //Se repite
	SSD1306_Puts (ang2, &Font_7x10, 1);
	SSD1306_GotoXY (75, 45);
	SSD1306_Puts (ang3, &Font_7x10, 1);
	SSD1306_UpdateScreen(); //Actualiza la pantalla OLED
		}
		//////////////////////////

  }

}

void SystemClock_Config(void) //Configuración generada por defecto del reloj por cubemx, define la velocidad a usar
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI; //Configuración del PLL, se usa para que los datos transmistidos del acelerómetro 
  RCC_OscInitStruct.HSIState = RCC_HSI_ON; // Y la forma en la que se muestran los datos en la OLED sea a alta velocidad
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK //Más configuración generada por defecto
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_I2C1_Init(void) //Configuración por defecto para el uso de I2C, solo se usa para controlar el acelerómetro
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void) //Configuración generada por defecto, se utiliza para los drivers de la librería HAL, que se usa para controlar el acelerómetro
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

void Error_Handler(void) //Generado por defecto, hará una acción si detecta un error, no lo borramos porque si no molesta xd
{
}
