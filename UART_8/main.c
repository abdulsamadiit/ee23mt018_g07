#include<stdint.h>
#include<stdbool.h>
#include"tm4c123gh6pm.h"

#define MASK_BITS 0x11
#define STCTRL *((volatile long *) 0xE000E010)
#define STRELOAD *((volatile long *) 0xE000E014)
#define STCURRENT *((volatile long *) 0xE000E018)

void config_gpio()
{
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_DEN_R = 0x1F;
    GPIO_PORTF_PUR_R = 0x11;
    // Interrupt for Port-F Handler
    GPIO_PORTF_IS_R &= ~MASK_BITS;
    GPIO_PORTF_IBE_R &= ~MASK_BITS;
    GPIO_PORTF_IEV_R &= ~MASK_BITS;
    GPIO_PORTF_IM_R &= ~MASK_BITS;
    GPIO_PORTF_ICR_R |= MASK_BITS;
    GPIO_PORTF_IM_R |= MASK_BITS;
    NVIC_EN0_R |=(1<<30);
    NVIC_PRI7_R &= 0xFF3FFFFF;
}
void config_uart()
{
    SYSCTL_RCGCGPIO_R |= 0x30;
    SYSCTL_RCGCUART_R |= (1<<7)|(1<<5);    // Enable clock to UART-5 & UART-7
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R |= 0xFF;
    GPIO_PORTE_AFSEL_R |= 0x33;
    GPIO_PORTE_PCTL_R |= (1<<20)|(1<<16)|(1<<4)|(1<<0);
    GPIO_PORTE_DIR_R = 0x33;               // setting PE5 and PE1 as output and PE4 and PE1 as input
    GPIO_PORTE_DEN_R |= 0x33;

    // UART-7 Configuration
    UART7_CTL_R &= ~(0x01);
    UART7_IBRD_R =104;
    UART7_FBRD_R = 11;
    UART7_LCRH_R = 0x62;;
    UART7_CC_R = 0;
    UART7_CTL_R |= ((1<<0)|(1<<8)|(1<<9));

    // UART-5 Configuration
    UART5_CTL_R &= ~(0x01);
    UART5_IBRD_R =104;
    UART5_FBRD_R = 11;
    UART5_LCRH_R =0x62;
    UART5_CC_R = 0;
    UART5_CTL_R |= ((1<<0)|(1<<8)|(1<<9));

    //Configuring NVIC and interrupt for UART-5
    UART5_IM_R &= ((0<<4)|(0<<5)|(0<<8));       //Mask Tx, Rx and Parity interrupts
    UART5_ICR_R &= ((0<<4)|(0<<5)|(0<<8));      //Clear Tx, Rx and Parity interrupts
    UART5_IM_R |= (1<<4);                       //Enable Rx interrupt
    NVIC_EN1_R |= (1<<29);                      //Interrupts enabled for UART5
    NVIC_PRI15_R &= 0xFFFF5FFF;                 //Interrupt Priority 2 to UART5
}

void main()
{
    config_uart();
    config_gpio();
    while(1){}
}
void sys_handler()
{
    GPIO_PORTF_DATA_R  = 0x00;
    GPIO_PORTF_ICR_R = MASK_BITS;
    GPIO_PORTF_IM_R |= MASK_BITS;
    UART5_IM_R |= (1<<4);
}
void gpiof_handler()
{
    int pressed;
    pressed=GPIO_PORTF_MIS_R;
    GPIO_PORTF_IM_R &= ~MASK_BITS;//sw1 and sw2 masked
    if(pressed & 0X10) // Switch-2 --> Send AA --> GREEN
    {
        UART7_DR_R = 0xF0;

    }
    if(pressed & 0X01) // Switch-1 -->. Send F0 ---> BLUE
    {
        UART7_DR_R = 0xAA;
    }
    GPIO_PORTF_IM_R |= MASK_BITS; //Unmasking & Clearing
    GPIO_PORTF_ICR_R |= MASK_BITS;

}
void uart_handler()
{
    UART5_IM_R &= (0<<4);       //Mask UART Rx interrupt
    if(UART5_FR_R & (1<<6))
    {
        if(UART5_DR_R == 0xAA)
            GPIO_PORTF_DATA_R = 0x08;
        if(UART5_DR_R == 0XF0)
            GPIO_PORTF_DATA_R = 0x04;
    }

    if(UART5_RSR_R & 0x0F)
       {GPIO_PORTF_DATA_R = 0x02;}

    UART5_ECR_R &= 0xFFFFFFF0; //Clear UART errors
    STRELOAD = 1000000*8;     //Delay half Second
    STCURRENT = 0;
    STCTRL |= ((1 << 2) | (1 << 0) | (1 << 1));}



