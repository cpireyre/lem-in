# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lem-bench.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpireyre <cpireyre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/25 06:57:08 by cpireyre          #+#    #+#              #
#    Updated: 2018/11/25 07:27:53 by cpireyre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo "Testing lem-in."
echo "\t\x1b[4m--flow-one:\x1b[0m\n"
for i in {1..3}
do
	./tests/generator --flow-one > a
	grep --max-count=1 required < a
	echo "vs.\t\t\t\t\c"
	./lem-in < a | grep L | wc -l
done
echo "\t\x1b[4m--flow-ten:\x1b[0m\n"
for i in {1..3}
do
	./tests/generator --flow-ten > a
	grep --max-count=1 required < a
	echo "vs.\t\t\t\t\c"
	./lem-in < a | grep L | wc -l
done
echo "\t\x1b[4m--flow-thousand:\x1b[0m\n"
for i in {1..10}
do
	./tests/generator --flow-thousand > a
	grep --max-count=1 required < a
	echo "vs.\t\t\t\t\c"
	./lem-in < a | grep L | wc -l
done
