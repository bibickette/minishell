🇫🇷 Version française disponible [ici](README_FR.md)

---

# Project presentation - `libft`

## **Description**

This project involves creating a reusable personal static library (libft.a) by reimplementing useful standard C library functions, along with additional functions that will be helpful in future projects.

The purpose is to gain a deeper understanding of data structures and basic algorithms. At 42, we are often restricted from using certain standard libraries, so we build and expand our own library as we progress through the curriculum.

For example:

- `ft_printf` (with its own Makefile), a 42 project added to the library, see more [here](https://github.com/bibickette/ft_printf).
- `get_next_line`, a 42 project integrated into libft, see more [here](https://github.com/bibickette/get_next_line).

---

## Languages & Technologies

**Language**

- C (C99 standard)

**Technologies**

- Makefile
- Static library (.a)
- Dynamic memory allocation
- Memory manipulation
- String manipulation
- Linked lists

---

## What’s included in the library

The project instructions divide it into three sections:

1.  Libc Functions - Reimplementations of some standard C functions.
2.  Additional Functions - Extra utility functions considered useful for later projects.
3.  Linked List Functions - Functions used to manipulate linked lists.
4.  Personal Functions - Additional functions I implemented on my own.

| Libc Functions |                       Description                       |
| :------------: | :-----------------------------------------------------: |
|   ft_isalnum   |            Checks if a char is alphanumeric             |
|   ft_isalpha   |        Checks if a char is an alphabetic letter         |
|   ft_isascii   |        Checks if a char belongs to the ASCII set        |
|   ft_isdigit   |            Checks if a char is a digit (0-9)            |
|   ft_isprint   |              Checks if a char is printable              |
|   ft_tolower   |        Converts an uppercase letter to lowercase        |
|   ft_toupper   |        Converts a lowercase letter to uppercase         |
|    ft_bzero    |             Sets a block of memory to zero              |
|   ft_calloc    |       Allocates memory and initializes it to zero       |
|   ft_strncmp   | Compares two strings up to a given number of characters |
|   ft_strnstr   | Locates a substring within a string, limited by length  |
|   ft_memchr    |          Searches for a byte in a memory block          |
|   ft_memcmp    |               Compares two memory blocks                |
|   ft_memcpy    |        Copies memory from source to destination         |
|   ft_memmove   |   Copies memory safely, handling overlapping regions    |
|   ft_memset    |        Fills a memory block with a constant byte        |
|    ft_atoi     |             Converts a string to an integer             |
|   ft_strlcat   |        Concatenates strings with size limitation        |
|   ft_strlcpy   |          Copies a string with size limitation           |
|   ft_strlen    |             Returns the length of a string              |
|   ft_strrchr   |  Finds the last occurrence of a character in a string   |
|   ft_strchr    |  Finds the first occurrence of a character in a string  |
|   ft_strdup    |     Duplicates a string into newly allocated memory     |

| Additional Functions |                                Description                                |
| :------------------: | :-----------------------------------------------------------------------: |
|     ft_substr.c      |                    Extracts a substring from a string                     |
|      ft_strjoin      |                  Concatenates two strings into a new one                  |
|      ft_strtrim      |     Trims specified characters from the beginning and end of a string     |
|       ft_split       |         Splits a string into an array using a char as a delimiter         |
|       ft_itoa        |                      Converts an integer to a string                      |
|      ft_strmapi      | Creates a new string by applying a function to each character of a string |
|     ft_striteri      |  Applies a function to each character of a string, modifying it in place  |
|    ft_putchar_fd     |                    Writes a char to a file descriptor                     |
|     ft_putstr_fd     |                   Writes a string to a file descriptor                    |
|    ft_putendl_fd     |        Writes a string followed by a newline to a file descriptor         |
|     ft_putnbr_fd     |                  Writes an integer to a file descriptor                   |

| Linked list Functions |                        Description                        |
| :-------------------: | :-------------------------------------------------------: |
|    ft_lstadd_back     |      Adds a new element at the end of a linked list       |
|    ft_lstadd_front    |   Adds a new element at the beginning of a linked list    |
|      ft_lstclear      |      Deletes and frees all elements of a linked list      |
|     ft_lstdelone      |          Deletes and frees a single list element          |
|      ft_lstiter       |       Applies a function to each element of a list        |
|      ft_lstlast       |         Returns the last element of a linked list         |
|       ft_lstmap       | Creates a new list by applying a function to each element |
|       ft_lstnew       |             Creates a new linked list element             |
|      ft_lstsize       |      Returns the number of elements in a linked list      |

| Personal Functions |                                                      Description                                                      |
| :----------------: | :-------------------------------------------------------------------------------------------------------------------: |
|     ft_printf      | Custom implementation of the printf function supporting the following format specifiers: c, s, p, d, i, u, x, X and % |
|   get_next_line    |                                         Reads a file descriptor line by line                                          |
|     countwords     |                        Returns the number of words in a string separated by a given delimiter.                        |
|   strjoin_wfree    |                          Concatenates two strings into a new one and frees the first string                           |
|     factorial      |                                    Computes the factorial of a number recursively                                     |
|     fibonacci      |                                     Returns the Fibonacci number at a given index                                     |
|  find_next_prime   |                       Finds the smallest prime number greater than or equal to the given number                       |
| int_overflow_check |                                    Checks if the string represents a valid integer                                    |
|    nb_is_prime     |                                       Checks whether a number is a prime number                                       |
|      nb_sqrt       |                               Returns the integer square root of a number if it exists.                               |
|      power_nb      |                                 Computes a number raised to a given power recursively                                 |
| ft_is_white_space  |                                      Checks if a char is a space, tab or newline                                      |

---

# Using `libft`

## **Makefile rules**

1. **all** as _default rule_: builds the project, compiles all `.c` files into `.o`, then **creates** the library (`.a`)
2. **clean** : removes compiled object files (`.o`)
3. **fclean** : _clean_ rule and removes the library (`.a`)
4. **re** : _fclean_ then _all_ rule

---

## **How to use `libft`**

1.  Clone `libft` into your project folder first : `git clone https://github.com/bibickette/libft`
2.  Build `libft` using its Makefile : run `make -s -C libft`, this runs the Makefile in the `libft` folder.
3.  Include the `libft.h` header in your project to access the functions.
4.  Compile your project with the `libft` library: `cc your_files.o -L./libft -lft -o your_program`

Now your project can use `libft` functions !

---

_Project validation date : December 23, 2023_
