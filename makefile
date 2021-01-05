all: console.c processor.c
	gcc -o console console.c
	gcc -o processor processor.c
run:
	echo "You need to run the two programs separately from terminal"
