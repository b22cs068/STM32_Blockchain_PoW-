# STM32_Blockchain_PoW-
Implementation of Blockchain
Proof-of-Work Consensus on STM32F4
Embedded Device
B22CS068 - Embedded Systems Course Project
June 7, 2025
1 Introduction
Blockchain technology relies on consensus algorithms to validate transactions across dis-
tributed networks. While extensively applied in high-performance environments, imple-
menting such mechanisms on embedded devices opens up novel use cases in IoT and
edge computing. This project explores the feasibility of implementing the Proof-of-Work
(PoW) consensus algorithm on an STM32F4 microcontroller.
2 Objective
• Implement PoW on STM32F429ZI using C (bare-metal).
• Use a custom SHA-256 implementation.
• Display mining output using UART.
• Compare implementation with existing lightweight blockchain frameworks.
3 Hardware and Software Setup
• Microcontroller: STM32F429ZI (Cortex-M4)
• IDE: Keil 5
• Communication: UART3 at 115200 baud
• Hashing Algorithm: Custom SHA-256
• Source Code: GitHub Repository
4 Implementation
4.1 Mining Algorithm
The miner searches for a nonce such that the SHA-256 hash of the data concatenated
with the nonce starts with a specified number of zeros (difficulty).
1
4.2 UART Communication
Bare-metal UART3 initialization and transmission functions are implemented to relay
the mined hash and nonce.
4.3 SHA-256 Hashing
The full SHA-256 algorithm is implemented from scratch in C, adhering to FIPS 180-4
standards.
5 Sample Output
=== UART3 Working! ===
Nonce: 345827
Hash: 0000fbdabc1e9e64f8190a4b3e21ab55fc4c8c41d1a542a7c83e3ae95fe3cabc
=== Mining Complete ===
6 Performance Metrics
Metric Value (Difficulty = 4)
Execution Time 15-20 seconds
Clock Frequency 180 MHz
Code Size 15 KB
RAM Usage ¡ 4 KB
Power Consumption 150 mW (estimated)
7 Comparison with Reference Paper
Paper: Design and Implementation of Lightweight Blockchain Consensus Algorithm for
Resource-Constrained IoT Devices
Aspect Our Implementation Research Paper
Consensus Algorithm Proof-of-Work Token-based lightweight con-
sensus
Device Used STM32F429ZI Raspberry Pi Zero W,
STM32L152RE
Hash Function Full SHA-256 Custom hash/truncated SHA
Power Optimization Not applied Aggressive power-saving via
design
Mining Scope Local node mining Networked node mining
Communication UART LoRaWAN, MQTT
8 Key Learnings and Future Work
8.1 Learnings
• Feasible to implement PoW with SHA-256 on STM32.
• Bare-metal UART communication is effective for logging.
2
• Embedded devices can perform cryptographic hashing, albeit slowly.
8.2 Future Work
• Optimize SHA-256 using DMA or LUTs.
• Try lightweight hash functions like BLAKE2s.
• Enable networked embedded blockchain simulation.
• Add on-board LCD visualization.
9 Conclusion
This project demonstrates that embedded systems like the STM32F429ZI can execute
PoW-based blockchain consensus mechanisms. While the processing overhead is high,
the implementation proves that cryptographic operations are feasible on microcontrollers,
opening doors for secure IoT frameworks.
10 References
• Wiley (2021). Design and Implementation of Lightweight Blockchain Consensus Al-
gorithm for Resource-Constrained IoT Devices. https://doi.org/10.1155/2021/9918697
• STM32F429ZI Reference Manual.
• FIPS PUB 180-4: Secure Hash Standard (SHA).
3
