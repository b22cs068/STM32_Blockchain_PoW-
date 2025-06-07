
# Lightweight Proof-of-Work Implementation on STM32 Embedded Microcontroller

**Authors:**  
Yogita Mundankar (B22CS068)  
Qazi Talha Ali (B22CS087)  
**Course:** Embedded Systems  
**Instructor:** Binod Kumar  

---

## 📌 Project Summary

This project implements a **lightweight Proof-of-Work (PoW)** blockchain consensus algorithm on a **bare-metal STM32F4** microcontroller. It demonstrates the viability of integrating secure, decentralized validation mechanisms into resource-constrained **IoT and edge devices** using **custom SHA-256 hashing** and **UART-based output**.

---

## 🔗 Project Links

- 🧠 [GitHub Repository](https://github.com/b22cs068/STM32_Blockchain_PoW-/tree/main)
- 📽️ [Demo Video](https://drive.google.com/file/d/1gCNcgGKrrAJhNw0q9mAzjTv2bD_T4ttN/view?usp=sharing)

---

## 🔍 Introduction

Blockchain is a secure, decentralized ledger system that relies on consensus mechanisms to maintain integrity. The most widely used mechanism, **Proof-of-Work (PoW)**, involves solving cryptographic puzzles to validate transactions.

As embedded systems and IoT grow in importance, deploying blockchain consensus on such platforms is increasingly relevant. This project presents a **minimal, bare-metal PoW implementation** on the **STM32F412ZG** microcontroller.

---

## 🎯 Objective

- Implement and demonstrate a simplified blockchain **PoW algorithm**.
- Use a **custom SHA-256** software hash function.
- Transmit mining results over **UART**.
- Evaluate performance and resource feasibility on embedded platforms.

---

## 📚 Related Work

The implementation is inspired by:

> *Blockchain-Based Secure and Lightweight Authentication for Smart Home Applications in IoT Environment*  
> (Wiley, 2021)

This paper emphasized the need for **lightweight consensus** models on **edge devices**, aligning with our project goals.

---

## ⚙️ Algorithm Overview

- **Input Data:** Static string (e.g., `"Hello STM32 Blockchain!"`)
- **Nonce:** 32-bit counter, incremented to satisfy the hash condition.
- **Hash Function:** Custom SHA-256 implementation.
- **Difficulty:** Number of leading zeros required in the hash.
- **Output:** Mined nonce + valid hash sent via UART.

The algorithm loops until it finds a hash with the desired number of leading zeros.

---

## 🧰 Hardware & Software Setup

| Component        | Specification                           |
|------------------|-----------------------------------------|
| **MCU**          | STM32F412ZG (ARM Cortex-M4)             |
| **Clock**        | 16 MHz (Internal HSI)                   |
| **UART**         | USART3 (PD8 TX, PD9 RX) @ 9600 baud     |
| **Terminal**     | PuTTY or equivalent UART terminal       |
| **IDE**          | Keil µVision 5                          |
| **Hashing**      | Static-buffer SHA-256 (no heap usage)   |

---

## 🧑‍💻 Code Features

- Manual peripheral setup for **GPIO** and **UART** (register-level).
- Custom, lightweight **SHA-256 hashing** with no standard library dependencies.
- Adjustable **PoW mining difficulty**.
- Direct **UART3 communication** using register manipulation.
- **SysTick timer** for hash rate analysis.
- Optimized memory usage with static buffers only.

---

## 📈 Performance Analysis

### Mining Time vs Difficulty

| Difficulty | Time to Mine     |
|------------|------------------|
| 1          | ~0.5 seconds     |
| 2          | ~5–8 seconds     |
| 3          | ~45–60 seconds   |
| 4          | ~1+ minute       |

Performance scales exponentially with difficulty due to the nature of PoW.

---

## 🖥️ Sample UART Output

