# sudo apt-get install valgrind kcachegrind massif-visualizer


run:
	clang-17 -o main ${file} && ./main && rm main

