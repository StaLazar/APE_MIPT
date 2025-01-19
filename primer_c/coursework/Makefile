# Используемый компилятор:
CC ?= gcc

# Входные директории (папки с исходными кодами):
SOURCE_DIRS := $(CURDIR)/apps/ \
	$(CURDIR)/common/ \
	$(CURDIR)/sensors/ \
	$(CURDIR)/tools/
# Выходная директория (папка со всеми артефактами):
BUILD_DIR := $(CURDIR)/build/

# Список всех исходных файлов проекта (абсолютные пути, *.c):
CFILES := $(wildcard $(addsuffix *.c, $(SOURCE_DIRS)))
# Список всех объектных файлов проекта (абсолютные пути, *.o):
OFILES := $(addprefix $(BUILD_DIR), $(patsubst %.c, %.o, $(notdir $(CFILES))))

# Перечень директорий поиска заголовочных файлов для сборки объектных файлов:
INCLUDES := $(addprefix -I, $(SOURCE_DIRS))
# Список зависимостей, построенный компилятором с помощью опции -MD:
DEPS := $(wildcard $(addsuffix *.d, $(BUILD_DIR)))
# Используемые опции компилятора для сборки объектных файлов:
CFLAGS := -Wall $(INCLUDES) -MD

# Список библиотек, необходимых для успешной сборки приложения sensalyzer:
SENSALYZER_LIBS := $(addprefix -L, $(BUILD_DIR)) -lcommon -lsensors -ltools -lm

# Цель по умолчанию:
all: $(BUILD_DIR) apps

# Перечисление абстрактных целей (действий, не порождающих напрямую артефактов):
.PHONY: all apps $(BUILD_DIR) clean
# Очистка списка суффиксов по умолчанию:
.SUFFIXES:

# Цель по сборке всех приложений:
apps: $(OFILES) sensalyzer

# Цель по сборке приложения sensalyzer:
sensalyzer: $(addprefix $(BUILD_DIR), sensalyzer.o) common sensors tools
	$(CC) -o $(addprefix $(BUILD_DIR), sensalyzer) $(<) $(SENSALYZER_LIBS)

# Цель по сборке библиотеки common:
common: $(addprefix $(BUILD_DIR), vector.o) $(addprefix $(BUILD_DIR), timestamp.o)
	ar rcs $(addprefix $(BUILD_DIR), libcommon.a) $(^)

# Цель по сборке библиотеки sensors:
sensors: $(addprefix $(BUILD_DIR), temperature.o)
	ar rcs $(addprefix $(BUILD_DIR), libsensors.a) $(^)

# Цель по сборке библиотеки tools:
tools: $(addprefix $(BUILD_DIR), cmd_handler.o)
	ar rcs $(addprefix $(BUILD_DIR), libtools.a) $(^)

# Определение шаблона сборки объектных файлов из SOURCE_DIRS в BUILD_DIR:
include $(DEPS)
define MK_OBJ
$(PAIR)
	$$(CC) $$(CFLAGS) -c $$(^) -o $$(@)
endef
$(foreach PAIR, $(join $(addsuffix :, $(OFILES)), $(CFILES)), $(eval $(call MK_OBJ, $(PAIR))))

# Цель по созданию выходной директории лишь в случае ее отсутствия:
$(BUILD_DIR):
	test -d $(BUILD_DIR) || mkdir $(BUILD_DIR)

# Цель по очистке выходной директории лишь в случае ее присутствия:
clean:
	test ! -d $(BUILD_DIR) || rm -r $(BUILD_DIR)
