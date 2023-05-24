#include "freertos/FreeRTOS.h"
/*Standard Headers*/

//#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

/*Added by Me*/
#include "esp_log.h"

#include <stdio.h>
#include "string.h"

#include <freertos/task.h>
#include <dht.h>

#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "driver/uart.h"
#include "soc/uart_struct.h"
/* End of Added by Me*/


//	char data[256];



/*Beggining of Globals*/
	xQueueHandle Global_Queue_Handle = 0;		//Create a Global Queue Handle
	SemaphoreHandle_t SepHandle = NULL;		   // Create a Semaphore Handle
/*End of Globabls */




//THIS IS THE FUNCTION USED ON THE TX UART


#if defined(CONFIG_EXAMPLE_TYPE_DHT11)
#define SENSOR_TYPE DHT_TYPE_DHT11
#endif
#if defined(CONFIG_EXAMPLE_TYPE_AM2301)
#define SENSOR_TYPE DHT_TYPE_AM2301
#endif
#if defined(CONFIG_EXAMPLE_TYPE_SI7021)
#define SENSOR_TYPE DHT_TYPE_SI7021
#endif

#define TOFAR(temperature) ((temperature)*1.8 + 32)

#define UART_2_TX 17					//GPIO NUMBER 17
#define	UART_2_RX 16					//GPIO NUMBER 16


	void init_RS232()
	{
	    const uart_port_t uart_num = UART_NUM_2;
	    const int uart_buffer_size = 256;
	    QueueHandle_t uart_queue;

	    // 1 - Setting Communication Parameters
	    const uart_config_t uart_config = {
	        .baud_rate = 115200,
	        .data_bits = UART_DATA_8_BITS,
	        .parity = UART_PARITY_DISABLE,
	        .stop_bits = UART_STOP_BITS_1,
	        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};
	    uart_param_config(uart_num, &uart_config);

	    // 2 - Setting Communication Pins
	    uart_set_pin(uart_num, UART_2_TX, UART_2_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

	    uart_disable_intr_mask(uart_num, 0 |1);

	    uart_enable_rx_intr(uart_num);

	    // 3 - Driver Installation
	    uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0);


	}






void dht_read_and_send(void *pvParameters)
{
    float humidity, temperature;
    float tx_float = 0;

#ifdef CONFIG_EXAMPLE_INTERNAL_PULLUP
    gpio_set_pull_mode(dht_gpio, GPIO_PULLUP_ONLY);
#endif

    while (1)
    {

    if(xSemaphoreTake(SepHandle,portMAX_DELAY)==pdTRUE){
        if (dht_read_float_data(SENSOR_TYPE, CONFIG_EXAMPLE_DATA_GPIO, &humidity, &temperature) == ESP_OK)
           printf("Temp in C:%.1fC Temp in F:%.1fF\n \n", temperature, TOFAR(temperature));
        else
            printf("Could not read data from sensor\n");

        tx_float = temperature;


        if(! xQueueSend(Global_Queue_Handle,&tx_float,pdMS_TO_TICKS(2000))){
        	puts("Failed to send to queue!");
        }


   //     printf("Hello from Task 1!");	// WE CAN NOW PRINTF HERE! YAY! DO NOT! DO NOT! USE UART0!



        // If you read the sensor data too often, it will heat up
        // http://www.kandrsmith.org/RJS/Misc/Hygrometers/dht_sht_how_fast.html
        xSemaphoreGive(SepHandle);



    }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}



void myTask2_receive_q_with_UART(void *pvParam)
{
	float rx_float = 0;

	float uart_float = 0;

	char data[256];



	while(1){
		vTaskDelay(pdMS_TO_TICKS(2000));
    	if(xSemaphoreTake(SepHandle,portMAX_DELAY)==pdTRUE){

    		if(xQueueReceive(Global_Queue_Handle, &rx_float, pdMS_TO_TICKS(2000))){


    	  	uart_float = rx_float;

    	 	sprintf(data,"%.1f\n",uart_float);



    	 	printf("\n We are sending %s\n", data);		

    	 	uart_write_bytes_with_break(UART_NUM_2, data, strlen(data),pdMS_TO_TICKS(300));
            uart_flush(UART_NUM_2);

            bzero(data,256);
            memset(data, 0, sizeof(data));
            vTaskDelay(pdMS_TO_TICKS(100));



    	}




    		xSemaphoreGive(SepHandle);






	}




}
}





void app_main()
{

	Global_Queue_Handle = xQueueCreate(1,sizeof(float));
	SepHandle = xSemaphoreCreateMutex();
	xSemaphoreGive(SepHandle);

	setvbuf(stdout, NULL, _IONBF, 0);

	init_RS232();


    xTaskCreate(dht_read_and_send, "dht_test",4096, NULL, 1, NULL);
    xTaskCreate(myTask2_receive_q_with_UART,"rx",4096,NULL,2,NULL);

}
