if [ "$CMAKE_BUILD" = "1" ]; then \
	docker buildx build \
		--tag cmake-builder \
		--file ./dockerfiles/CMakeBuilder.dockerfile \
		.; \
fi

if [ "$MAIN_BUILD" = "1" ]; then \
	docker buildx build \
		--tag main \
		--file ./dockerfiles/Main.dockerfile \
		.; \
fi