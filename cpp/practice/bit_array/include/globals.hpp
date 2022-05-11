/*****************************************************************************
Title: globals - Infinity Labs R&D 
Group: OL91
Author: Aviv
Reviewer: Miriam
Description: globals
******************************************************************************/

#define NUM_OF_WORDS(N) ((N + g_bits_in_word - 1) / g_bits_in_word)
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
#define COUNT_BITS B6(0), B6(1), B6(1), B6(2)
#define ASCII_SIZE 256

const std::size_t g_bytes_in_word = sizeof(std::size_t);
const std::size_t g_bits_in_word = (g_bytes_in_word * CHAR_BIT);
static std::size_t g_lut_set_bits[ASCII_SIZE] = {COUNT_BITS};

/*****************************************************************************/

