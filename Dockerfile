FROM ubuntu:latest

RUN apt update && apt install -y build-essential python3-pip gcc

WORKDIR /app

COPY . .

RUN pip3 install flask

RUN gcc -o employee_app main.c bst.c -Wall -Wextra

EXPOSE 3001

CMD ["python3", "app.py"]