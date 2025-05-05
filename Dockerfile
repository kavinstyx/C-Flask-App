FROM ubuntu:latest

# Install dependencies
RUN apt update && \
    apt install -y build-essential python3-pip python3-flask gcc

WORKDIR /app

COPY . .

# Install Flask via APT instead of pip
# RUN apt install -y python3-flask  # Already included above

# Compile C binary
RUN gcc -o employee_app main.c bst.c -Wall -Wextra

# Run Flask app
CMD ["python3", "app.py"]