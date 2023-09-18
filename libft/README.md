

# LIBFT
[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)
![mark-111_100](https://user-images.githubusercontent.com/92900172/200837644-658cfbb9-59de-4a0b-8aed-2462f9ecc173.svg)
![code-by-dscrtdv](https://user-images.githubusercontent.com/92900172/200837083-3fe44953-8c00-49be-9837-a2abb5437ea6.svg)

Libft is the very first project available at 42 schools.

## Description

The assignement is pretty straight forward: re-implement some of the LIBC functions. 
The point of doing such exercise, is to build basic knowledge on the inner working of C strings.
Re-implementing a library might seem tedious and potentially useless: "Why should I create tools that already exist?". 
Although I would argue it is crucial for any developper to aquire an advanced understanding of C. 
The way it forces the developper into implementing its own solutions from scratch, allows for great problem solving ability improvement. That added to the low level features of C, makes room for performance, freedom, and optimization.
This unforgiving language does not leave error, nor messy habits unpunished, which brings the developper towards cleaner, self-explanatory code.
I am not one to judge uppon the difficulty scale of different languages, as each purpose has its best suiting tool. 
That being said, it is important to remember the crucial role and influence C has within computer sciences history and its developpment. 
If a developper understands and masters C, it will most likely comprehend higher level of abstraction fairly easily.
There's always a developper to tell you to go lower level if you don't wanna be a neophyte. That is not an absolute truth.

Learn C though.

## Content
1.  **Libc Functions:** Some of the standard C functions.
2.  **Additional functions:** Functions that should be usefull in future projects.
3.  **Bonus Functions:** Functions for linked list manipulation.
4.  **Personal Functions:** Functions that I judge to be usefull in future projects. This section will be updated regularly.

Libc functions | Additional functions | Bonus Functions | Personal Functions | Others
:----------- | :-----------: | :-----------: | :----------: | -----------:
isalpha      |  ft_substr    |  ft_lstnew       | ft_putchar  | libft.h
isdigit      |  ft_strjoin   |  ft_lstadd_front | ft_putstr   | Makefile
isalnum      |  ft_strtrim   |  ft_lstsize      | ft_itoabase
isascii      |  ft_split     |  ft_lstlast      |
isprint      |  ft_itoa      |  ft_lstadd_back  |
strlen       |  ft_strmapi   |  ft_lstdelone    |
memset       |  ft_striteri  |  ft_lstclear     |
bzero        |  ft_putchar_fd|  ft_lstiter      |
memcpy       |  ft_putstr_fd |  ft_lstmap       |
strlcpy      |  ft_putendl_fd|
strlcat      |  ft_putnbr_fd |
toupper      |  
tolower      |
strchr       |
strrchr      |
strncmp      |
memchr       |
memcmp       |
strnstr      |
atoi         |
calloc       |
strdup       |
## Use

```
git clone https://github.com/DscrtDv/Libft_42.git
cd Libft_42
make
```
**This library comes with a makefile**
+ make: builds the whole project into an archive.
+ make bonus: adds bonus file to the archive (linked list).
+ make clean: deletes all object files.
+ make fclean: makes clean and deletes archive file.

## Project including libft
Printf: https://github.com/DscrtDv/Printf_42
## Author

DscrtDv
