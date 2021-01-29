.RECIPEPREFIX = >

build: slist tail dlist

slist:
> gcc -o slist.out slist_main.c slist.c -Wall -Wextra

tail:
> gcc -o tail.out slist_tail_main.c slist_tail.c -Wall -Wextra

dlist:
> gcc -o dlist.out dlist_main.c dlist.c -Wall -Wextra

debug:
> gcc -g -o slist.out slist_main.c slist.c -Wall -Wextra
> gcc -g -o tail.out slist_tail_main.c slist_tail.c -Wall -Wextra
> gcc -g -o dlist.out dlist_main.c dlist.c -Wall -Wextra

clean:
> rm -f *.out
