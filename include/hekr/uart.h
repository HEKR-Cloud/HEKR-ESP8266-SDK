#ifndef UART_APP_H
#define UART_APP_H
#include "esp_def.h"

#ifdef __cplusplus
extern "C" {
#endif


#define RX_BUFF_SIZE    0x100   
#define TX_BUFF_SIZE    100

typedef  uint32_t t_uart_interrupt_progress_func(uint8_t *buf, uint16_t buf_len);

typedef enum {
	FIVE_BITS = 0x0,
	SIX_BITS = 0x1,
	SEVEN_BITS = 0x2,
	EIGHT_BITS = 0x3
} UartBitsNum4Char;

typedef enum {
	ONE_STOP_BIT = 0,
	ONE_HALF_STOP_BIT = BIT2,
	TWO_STOP_BIT = BIT2
} UartStopBitsNum;

typedef enum {
	NONE_BITS = 0,
	ODD_BITS = 0,
	EVEN_BITS = BIT4
} UartParityMode;

typedef enum {
	STICK_PARITY_DIS = 0,
	STICK_PARITY_EN = BIT3 | BIT5
} UartExistParity;

typedef enum {
	OFF = 0,
	BIT_RATE_9600 = 9600,
	BIT_RATE_19200 = 19200,
	BIT_RATE_38400 = 38400,
	BIT_RATE_57600 = 57600,
	BIT_RATE_74880 = 74880,
	BIT_RATE_115200 = 115200,
	BIT_RATE_230400 = 230400,
	BIT_RATE_460800 = 460800,
	BIT_RATE_921600 = 921600
} UartBautRate;

typedef enum {
	NONE_CTRL,
	HARDWARE_CTRL,
	XON_XOFF_CTRL
} UartFlowCtrl;

typedef enum {
	EMPTY,
	UNDER_WRITE,
	WRITE_OVER
} RcvMsgBuffState;

typedef struct {
	uint32	RcvBuffSize;
	uint8	*pRcvMsgBuff;
	uint8	*pWritePos;
	uint8	*pReadPos;
	uint8	TrigLvl;
	uint8	cell_flag;
	uint8	overflowFlag;
	RcvMsgBuffState  BuffState;
} RcvMsgBuff;

typedef struct {
	uint32   TrxBuffSize;
	uint8   *pTrxBuff;
} TrxMsgBuff;

typedef enum {
	BAUD_RATE_DET,
	WAIT_SYNC_FRM,
	SRCH_MSG_HEAD,
	RCV_MSG_BODY,
	RCV_ESC_CHAR,
} RcvMsgState;

typedef struct {
	UartBautRate 	     baut_rate;
	UartBitsNum4Char	 data_bits;
	UartExistParity      exist_parity;
	UartParityMode 		 parity;    // chip size in byte
	UartStopBitsNum      stop_bits;
	UartFlowCtrl         flow_ctrl;
	RcvMsgBuff           rcv_buff;
	TrxMsgBuff           trx_buff;
	RcvMsgState          rcv_state;
	int                  received;
	int                  buff_uart_no;  //indicate which uart use tx/rx buffer
} UartDevice;

typedef void(uart_data_received_cb_t)(uint8_t data);

extern UartDevice UartDev;
void ICACHE_FLASH_ATTR uart_init(UartBautRate uart0_br, UartBautRate uart1_br);
void ICACHE_FLASH_ATTR uart0_tx_buffer(uint8 *buf, uint16 len);
void ICACHE_FLASH_ATTR uart1_tx_buffer(uint8 *buf, uint16 len);
void ICACHE_FLASH_ATTR uart1_write_char(char c);
void ICACHE_FLASH_ATTR uart0_write_char(char c);
void  uart_config(uint8 uart_no);
void ICACHE_FLASH_ATTR register_uart_data_received_callback(uart_data_received_cb_t *cb);

#ifdef __cplusplus
}
#endif

#endif

