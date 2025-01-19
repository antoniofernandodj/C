# sudo apt-get install valgrind kcachegrind massif-visualizer

run1:
	clang-17 -Wall -Wextra -Werror -o main ${file} && ./main && rm main

run2:
	cmake -S . -B ./build && cmake --build ./build && ./build/main

run:
	./dockerfiles/build.sh
	docker run main
