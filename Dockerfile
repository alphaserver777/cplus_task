FROM gcc:13

WORKDIR /app
COPY . .

RUN g++ -std=c++17 main.cpp task*/task*.cpp -o /app/student_tasks

CMD ["/app/student_tasks"]
