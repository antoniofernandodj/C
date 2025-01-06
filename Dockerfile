FROM gcc:latest AS builder

WORKDIR /app

COPY main.c .

RUN gcc -Wall -Wextra -Werror -o main main.c

FROM debian:bookworm-slim

# RUN apk add --no-cache gcc libc-dev

WORKDIR /app

COPY --from=builder /app/main .

CMD ["./main"]
