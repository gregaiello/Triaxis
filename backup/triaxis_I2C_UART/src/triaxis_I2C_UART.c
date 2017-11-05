
#include "chip.h"

// Defines
#define SPEED_100KHZ         (uint32_t) 100000
#define SPEED_400KHZ         (uint32_t) 400000
#define SLAVE_ADDRESS 		 (uint8_t) 0xC
#define I2C_DATA_LENGTH		 (int) 7
#define I2C_TRIAXIS_READ     (uint8_t) 0x4E
#define I2C_TRIAXIS_RESET    (uint8_t) 0xF0
#define I2C_TRIAXIS_POLLING  (uint8_t) 0x3E
#define I2C_TRIAXIS_SB_MODE  (uint8_t) 0xE
#define DELAY 				 100000
#define BAUDRATE_UART 		 115200
#define UART_DATA_LENGTH     (int) 7
#define pin_LED_RED 		 7
#define pin_LED_GREEN 		 8
#define pin_LED_BLUE 		 9

// Private functions
void I2C_Init(void);
void LED_Init(void);
void TRIAXIS_Init(void);
void UART_Init(void);

// Global variables
uint8_t data[I2C_DATA_LENGTH];
uint8_t status;
bool LED_state = true;

int main(void) {
    SystemCoreClockUpdate();

    I2C_Init();
    LED_Init();
    TRIAXIS_Init();
    UART_Init();

    while(1)
    {
    	for(int i=0;i<DELAY;i++){}
    	Chip_I2C_MasterCmdRead(I2C0, SLAVE_ADDRESS, I2C_TRIAXIS_POLLING, &status, 1);
    	for(int i=0;i<DELAY;i++){}
    	if(Chip_I2C_MasterCmdRead(I2C0, SLAVE_ADDRESS, I2C_TRIAXIS_READ, data, I2C_DATA_LENGTH))
    	{
    		Chip_GPIO_SetPinState(LPC_GPIO, 0, pin_LED_BLUE, LED_state);
    		LED_state = !LED_state;
    		Chip_UART_SendBlocking(LPC_USART, (const void *) data, UART_DATA_LENGTH);
    	}
    }
    return 0 ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void UART_Init(void)
{
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_6, (IOCON_FUNC1 | IOCON_MODE_INACT)); // Changing the pin function: 1 per UART RX, 0 per GPIO
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO1_7, (IOCON_FUNC1 | IOCON_MODE_INACT)); // Changing the pin function: 0 per UART TX, 0 per GPIO
	Chip_UART_Init(LPC_USART); // UART clock and generic initialization
	Chip_UART_SetBaud(LPC_USART, BAUDRATE_UART); // Baud rate
	Chip_UART_ConfigData(LPC_USART, (UART_LCR_WLEN8 | UART_LCR_SBS_1BIT)); // Configuration length of the packet
	Chip_UART_SetupFIFOS(LPC_USART, (UART_FCR_FIFO_EN)); // ENABLE
	Chip_UART_TXEnable(LPC_USART); // Transmit Enable Register (automatically set to 1 after the reset but better to double check)
}

void TRIAXIS_Init(void)
{
	Chip_I2C_MasterCmdRead(I2C0, SLAVE_ADDRESS, I2C_TRIAXIS_RESET, &status, 1); //
	for(int i=0;i<DELAY;i++){}
}

void I2C_Init(void)
{
	Chip_SYSCTL_PeriphReset(RESET_I2C0);
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_4, IOCON_FUNC1 | SPEED_400KHZ); // Default speed = 100kHz
	Chip_IOCON_PinMuxSet(LPC_IOCON, IOCON_PIO0_5, IOCON_FUNC1 | SPEED_400KHZ);
	Chip_I2C_Init(I2C0);
	Chip_I2C_SetClockRate(I2C0, SPEED_400KHZ);
	NVIC_DisableIRQ(I2C0_IRQn);
	Chip_I2C_SetMasterEventHandler(I2C0, Chip_I2C_EventHandlerPolling);
}

void LED_Init(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, pin_LED_RED);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, pin_LED_BLUE);
	Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, pin_LED_GREEN);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, pin_LED_RED, true);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, pin_LED_BLUE, true);
	Chip_GPIO_SetPinState(LPC_GPIO, 0, pin_LED_GREEN, true);
}
