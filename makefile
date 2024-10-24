CC = gcc
CFLAGS = -Wall -g
TARGET = my_terminal

# Список исходных файлов
SRC = terminal.c fs/fs.c ipc/ipc.c

# Объектные файлы
OBJ = $(SRC:.c=.o)

# Правило по умолчанию
all: $(TARGET)

# Линковка исполняемого файла
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

# Правила для создания объектных файлов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) $(OBJ)
