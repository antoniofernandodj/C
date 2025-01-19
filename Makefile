# sudo apt-get install valgrind kcachegrind massif-visualizer


run1:
	clang-17 -Wall -Wextra -Werror -o main ${file} && ./main && rm main

run2:
	cmake -S . -B ./build && cmake --build ./build && ./build/main

drun:
	if [ "$$BUILD" = "1" ]; then docker build -t main_c -f Dockerfile .; fi
	docker compose run --rm --remove-orphans main_c
