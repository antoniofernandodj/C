FROM cmake-builder AS builder

WORKDIR /app

COPY . .

RUN rm -rf build/CMakeCache.txt build/* && cmake -S . -B ./build && cmake --build ./build

# Etapa de Runtime
FROM debian:bookworm-slim

WORKDIR /app

COPY --from=builder /app/build/main .

CMD ["./main"]
