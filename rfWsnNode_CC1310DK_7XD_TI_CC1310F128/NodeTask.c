/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***** Includes *****/
#include "NodeTask.h"

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>
#include <xdc/cfg/global.h>

#include <ti/sysbios/knl/Clock.h>

#include <ti/drivers/PIN.h>
#include <ti/drivers/I2C.h>
#include <stdint.h>


/* Board Header files */
#include "Board.h"

#include "SceAdc.h"
#include "NodeRadioTask.h"



/***** Defines *****/
#define NODE_TASK_STACK_SIZE 1024
#define NODE_TASK_PRIORITY   3

#define NODE_EVENT_ALL                  0xFFFFFFFF
#define NODE_EVENT_NEW_ADC_VALUE    (uint32_t)(1 << 0)

#define NODE_ACTIVITY_LED Board_LED0


/***** Variable declarations *****/
static Task_Params nodeTaskParams;
Task_Struct nodeTask;    /* not static so you can see in ROV */
static uint8_t nodeTaskStack[NODE_TASK_STACK_SIZE];
Event_Struct nodeEvent;  /* not static so you can see in ROV */
static Event_Handle nodeEventHandle;
static uint16_t latestAdcValue;
/* Pin driver handle */
static PIN_Handle ledPinHandle;
static PIN_State ledPinState;

/* Enable the 3.3V power domain used by the LCD */
PIN_Config pinTable[] = {
    NODE_ACTIVITY_LED | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
    PIN_TERMINATE
};


/***** Prototypes *****/
static void nodeTaskFunction(UArg arg0, UArg arg1);
void adcCallback(uint16_t adcValue);


/***** Function definitions *****/
void NodeTask_init(void) {

    /* Create event used internally for state changes */
    Event_Params eventParam;
    Event_Params_init(&eventParam);
    Event_construct(&nodeEvent, &eventParam);
    nodeEventHandle = Event_handle(&nodeEvent);

    /* Create the node task */
    Task_Params_init(&nodeTaskParams);
    nodeTaskParams.stackSize = NODE_TASK_STACK_SIZE;
    nodeTaskParams.priority = NODE_TASK_PRIORITY;
    nodeTaskParams.stack = &nodeTaskStack;
    Task_construct(&nodeTask, (Task_FuncPtr)nodeTaskFunction, &nodeTaskParams, NULL);
}

static void nodeTaskFunction(UArg arg0, UArg arg1)
{
    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, pinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board 3.3V domain pins\n");
    }

    /* Start the SCE ADC task with 1s sample period and reacting to change in ADC value.
     * A change mask of 0xFF0 means that changes in the lower 4 bits does not trigger a wakeup.
     * Minimum Report interval is 3s (in units of samplingTime)*/
    SceAdc_init(0x00010000, 3, 0xFF0);
    SceAdc_registerAdcCallback(adcCallback);
    SceAdc_start();




/*
    unsigned int    i;
    uint16_t        temperature;
    // uint8_t      txBuffer[2];
    uint8_t         rxBuffer[2];
    I2C_Handle      i2c;


    I2C_Params      i2cParams;
    I2C_Transaction i2cTransaction;

    uint8_t         txbuf_threshold[3];

     //Create I2C for usage
    I2C_Params_init(&i2cParams);

    i2cParams.bitRate = I2C_100kHz;

    i2c = I2C_open(Board_I2C_TMP, &i2cParams);

    if (i2c == NULL) {
    	System_abort("Error Initializing I2C\n");
    }
    else {
    	System_printf("I2C Initialized!\n");
    }

    txbuf_threshold[0] = 0x00;
    i2cTransaction.slaveAddress = Board_TMP112_ADDR;
    i2cTransaction.writeBuf = txbuf_threshold;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = 2;
    for (i = 0; i < 40; i++) {
    	if (I2C_transfer(i2c, &i2cTransaction)) {


    		// System_printf("Sample %d (C)\n", rxBuffer[0]);
    		System_flush();

    		//System_printf("Sample %d (C)\n", rxBuffer[1]);
    		System_flush();

    		temperature = (rxBuffer[0] << 4) | (rxBuffer[1] >> 4);
    		temperature /= 16;
    		System_printf("Sample %u: %d (C)\n", i, temperature);
    		System_flush();



    	}
    	else {
    		System_printf("I2C Bus fault\n");
    		System_flush();

    	}




    	System_flush();
    	Task_sleep(100000);
    }
    // Deinitialized I2C
    I2C_close(i2c);
    System_printf("I2C closed!\n");

    System_flush();

*/






    while(1) {
        /* Wait for event */
        uint32_t events = Event_pend(nodeEventHandle, 0, NODE_EVENT_ALL, BIOS_WAIT_FOREVER);

        /* If new ADC value, send this data */
        if(events & NODE_EVENT_NEW_ADC_VALUE) {
            /* Toggle activity LED */
            PIN_setOutputValue(ledPinHandle, NODE_ACTIVITY_LED,!PIN_getOutputValue(NODE_ACTIVITY_LED));

            /* Send ADC value to concentrator */
            NodeRadioTask_sendAdcData(latestAdcValue);
        }
    }
}

void adcCallback(uint16_t adcValue)
{
    /* Save latest value */
    latestAdcValue = adcValue;

    /* Post event */
    Event_post(nodeEventHandle, NODE_EVENT_NEW_ADC_VALUE);
}
