# README.md

## Советы по использованию

### 🔧 Ограничение типов
- **Проблемы с памятью:** При генерации большого количества типов неизбежны проблемы с памятью (стек не конечный, к сожалению, но можно увеличить, об этом позже).
- **Точность типов:** Типы с низкой точностью могут работать некорректно;
- **Большие типы:** Слишком большие типы могут вызывать сбои программы из-за особенностей начальной реализации.

### 📂 Работа с файлами
- **Чтение данных:**
  - Считывание происходит из файла `fluid.json`. в нём необходимо указывать значения перемнных и состояние воды.
- **Сохранение данных:**
  - Результаты сохраняются в файл `fluid_output.json` каждые 50 тиков, либо при изменении состояния частиц. Частота сохранения задается методом класса через `main`. Общее количество тиков также задается через `main` (в генерации).

---

## 🚀 Запуск программы

### 🔨 Компиляция
Программа поддерживает произвольные типы, указываемые при генерации с помощью `cmake`:

```bash
cmake -DTYPES=типы ..
```
> **Примечание:** Если тип содержит символы в скобках `()`, их нужно обернуть в кавычки:

```bash
cmake -DTYPES=FLOAT,"FAST_FIXED(13,7)","FIXED(64,15)" ..
```

### 📦 Генерация классов
При генерации основного файла создается количество классов, равное произведению `|TYPES| ^ 3 * |SIZES|`. Это может значительно увеличить потребление памяти, поэтому избегайте указания большого количества типов и размеров одновременно.
Пример:

```bash
cmake -DTYPES=FLOAT,"FAST_FIXED(13,7)","FIXED(64,15)" -DSIZES="S(36,84)","S(14,5)" ..
cmake --build .
```

### ▶️ Запуск программы
После сборки программу можно запустить с указанием параметров через командную строку:

```bash
./Fluid --p-type="FIXED(64,15)" --v-type="FAST_FIXED(13,7)" --v-flow-type="FIXED(64,15)" --size="36,84"
```

> **Важно:** При запуске необходимо указывать размер через параметр `--size`, так как в текущей реализации работа возможна только при явном указании этого параметра.

### 💾 Увеличение стека
Если памяти недостаточно для комбинаций из более чем двух типов, увеличьте размер стека командой:

```bash
ulimit -s bytes
```
> Эта команда требует прав администратора и должна быть выполнена вручную перед запуском программы. для 3-4 типов и 2-3 размеров хватит 100MB(ulimit -s 100000) стека

---

## ⚡ Производительность
Программа работает без потери производительности при использовании комбинаций типов, указанных в ТЗ. Следите за потреблением памяти, особенно при большом количестве классов и увеличении размеров.

---

Соблюдая эти рекомендации, вы сможете эффективно использовать программу и минимизировать риски возникновения ошибок.