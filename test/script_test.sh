# **************************************************************************** #
#                                                                              #
#                                                     .-***-.  /\_!/\    \!    #
#    script_test.sh                                  /       \.'`  `',.--//    #
#                                                  -(        I       I   @\    #
#    By: adandres                                    \       /'.____.'\___|    #
#                                                     '-...-' __/ | \   (`)    #
#    Created: 2020/04/17 17:55:55 by adandres               /    /  /          #
#    Updated: 2020/07/01 18:36:26 by adandres                                  #
#                                                                              #
# **************************************************************************** #

#!/bin/bash
cd test/test_file
for i in `find *.txt`
	do 
		../.././my_shell $i > .res1 2>&-
		bash $i > .res2 2>&-
		diff .res1 .res2 && printf "%-21s\t%s\n" "$i" "OK" || printf "%-21s\t%s\n" "$i" "KO <--- :("
		rm .res1 .res2
done
