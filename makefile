NUM?=2
numbers=0 1 2 3 4 5 6 7 8
tests=$(NUM)-80

run:
	for number in $(numbers); \
	do \
		./lab$(NUM) $(tests)/input$$number.txt > $(tests)/answer.txt ; \
		diff $(tests)/answer$$number.txt $(tests)/answer.txt || (echo -e "diff failed on test $$number \n") ; \
	done
	rm $(tests)/answer.txt

compile:
	g++ -Wall -Werror -std=c++17 -g *.cpp -o lab$(NUM)
