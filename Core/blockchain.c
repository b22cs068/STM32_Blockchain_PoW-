#include "stm32f4xx.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>      // For sprintf
#include "sha256.h"     // Your C implementation
void delay(volatile uint32_t d);
void UART3_Init(void);
void UART3_SendChar(char c);
void UART3_SendString(const char *str);
void sha256_to_hex(uint8_t *hash, char *output);
int starts_with_n_zeros(char *hash_str, int difficulty);
void mine_block(const char *data, int difficulty);



// Simple delay function
void delay(volatile uint32_t d) { while(d--); }

void UART3_Init(void) {
    
    RCC->AHB1ENR |= (1 << 3);     // GPIODEN
    RCC->APB1ENR |= (1 << 18);    // USART3EN

    
    GPIOD->MODER &= ~((3 << 16) | (3 << 18));
    
    GPIOD->MODER |=  (2 << 16) | (2 << 18);

   
    GPIOD->AFR[1] &= ~((0xF << 0) | (0xF << 4));  // Clear bits
    GPIOD->AFR[1] |=  (7 << 0) | (7 << 4);        // Set to AF7

  
    USART3->BRR = 0x0683;

  
    USART3->CR1 = (1 << 3) | (1 << 13);  
}




// Send one character over UART3
void UART3_SendChar(char c) {
    while (!(USART3->SR & (1 << 7))); // Wait for TXE
    USART3->DR = (uint8_t)c;
}

// Send string over UART3
void UART3_SendString(const char *str) {
    while(*str) UART3_SendChar(*str++);
}

// Converts hash bytes to hex string
void sha256_to_hex(uint8_t *hash, char *output) {
    const char hex[] = "0123456789abcdef";
    for (int i = 0; i < 32; i++) {
        output[i*2]   = hex[(hash[i] >> 4) & 0xF];
        output[i*2+1] = hex[hash[i] & 0xF];
    }
    output[64] = 0;
}

// Check if hash starts with n zeros
int starts_with_n_zeros(char *hash_str, int difficulty) {
    for (int i = 0; i < difficulty; i++)
        if (hash_str[i] != '0') return 0;
    return 1;
}

// Proof-of-Work Miner
void mine_block(const char *data, int difficulty) {
    uint32_t nonce = 0;
    uint8_t hash[32];
    char input[128];
    char hash_str[65];
    char uart_msg[128];

    while (1) {
        sprintf(input, "%s%lu", data, (unsigned long)nonce);
        sha256((uint8_t *)input, strlen(input), hash);
        sha256_to_hex(hash, hash_str);

        if (starts_with_n_zeros(hash_str, difficulty)) {
            sprintf(uart_msg, "Nonce: %lu\r\nHash: %s\r\n", nonce, hash_str);
            UART3_SendString(uart_msg);
            break;
        }

        nonce++;
    }
}

int main(void) {
    
    UART3_Init();

    // Short delay for PuTTY to settle
    delay(500000);

    UART3_SendString("=== UART3 Working! ===\r\n");

    mine_block("Hello STM32 Blockchain!", 2);

    UART3_SendString("=== Mining Complete ===\r\n");

    while (1);
}
