# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lem-bench.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboissel <tboissel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/25 06:57:08 by cpireyre          #+#    #+#              #
#    Updated: 2018/12/17 17:10:24 by cpireyre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

echo "Testing lem-in."
echo "\t\x1b[4m--flow-one:\x1b[0m\n"
./tools/generator --flow-one > a && grep --max-count=1 required < a && echo "vs.\t\t\t\t\c" && ./lem-in < a | grep L | wc -l && rm a
echo "\t\x1b[4m--flow-ten:\x1b[0m\n"
./tools/generator --flow-ten > a && grep --max-count=1 required < a && echo "vs.\t\t\t\t\c" && ./lem-in < a | grep L | wc -l && rm a
echo "\t\x1b[4m--flow-thousand:\x1b[0m\n"
./tools/generator --flow-thousand > a && grep --max-count=1 required < a && echo "vs.\t\t\t\t\c" && ./lem-in < a | grep L | wc -l && rm a
