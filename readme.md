# C + Flask Employee Management App

A simple web-based interface to manage employees using a BST implemented in C, wrapped with a Flask backend and basic HTML frontend.

## Features

- Insert Employees
- Search by Post ID
- Promote Employees
- Retire Employees

## How to Run

```bash
docker build -t employee-app .
docker run -p 3000:3000 employee-app