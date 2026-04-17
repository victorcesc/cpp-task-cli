# Learn Modern C++ — Projeto Didático

Projeto para aprender **C++ moderno (C++20)** na prática através de uma CLI de gerenciamento de tarefas.

---

# 🎯 Objetivo

Aprender:

* Sintaxe moderna C++
* STL
* RAII
* Smart pointers
* File I/O
* CMake
* Organização de projeto
* Boas práticas

---

# 📁 Estrutura do Projeto

```
learn-modern-cpp/
│
├── CMakeLists.txt
├── README.md
├── .gitignore
├── .clang-format
├── .clang-tidy
│
├── .cursor/
│   └── rules.md
│
├── src/
│   ├── main.cpp
│   ├── Task.hpp
│   ├── Task.cpp
│   ├── TaskManager.hpp
│   ├── TaskManager.cpp
│   └── Storage.hpp
│
├── include/
│
├── data/
│   └── tasks.txt
│
├── tests/
│
└── build/
```

---

# 🧠 Configuração do Cursor

## `.cursor/rules.md`

```
You are helping me learn modern C++.
Do not generate full solutions.
Explain concepts step by step.
Prefer C++20 idioms.
Explain RAII, ownership and STL usage.
```

---

# ⚙️ Configuração CMake

```
cmake_minimum_required(VERSION 3.16)
project(learn-modern-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(learn-modern-cpp
    src/main.cpp
    src/Task.cpp
    src/TaskManager.cpp
)

target_include_directories(learn-modern-cpp PRIVATE src)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)
```

---

# 🎨 `.clang-format`

```
BasedOnStyle: LLVM
IndentWidth: 4
ColumnLimit: 100
AllowShortFunctionsOnASingleLine: Empty
BreakBeforeBraces: Allman
```

---

# 🔍 `.clang-tidy`

```
Checks: >
  modernize-*,
  performance-*,
  readability-*,
  bugprone-*,
  cppcoreguidelines-*

WarningsAsErrors: ''
HeaderFilterRegex: '.*'
```

---

# 🧾 `.gitignore`

```
build/
*.o
*.out
*.exe
compile_commands.json
.vscode/
```

---

# 🚀 Como Buildar

```
mkdir build
cd build
cmake ..
make
```

Executar:

```
./learn-modern-cpp
```

---

# 🧭 Roadmap

## WEEK 1 — CLI Básica

* `main.cpp`
* `argc/argv`
* `std::vector`
* comandos `add` e `list`

Objetivo:

```
task add "Estudar C++"
task list
```

---

## WEEK 2 — Classes

Criar classe `Task`

Aprender:

* class vs struct
* constructors
* encapsulamento

---

## WEEK 3 — STL + Lambdas

* `std::find_if`
* `std::remove_if`
* lambdas
* iterators

---

## WEEK 4 — Persistência

Salvar em:

```
data/tasks.txt
```

Aprender:

* fstream
* RAII
* exception safety

---

## WEEK 5 — C++ Moderno

* `enum class`
* `std::optional`
* `std::filesystem`
* structured bindings

---

## WEEK 6 — Smart Pointers

Refatorar para:

```
std::vector<std::unique_ptr<Task>>
```

Aprender:

* ownership
* move semantics
* `std::move`

---

## WEEK 7 — CMake

* targets
* includes
* flags
* build types

---

# 🎯 Funcionalidades finais

* [ ] task add
* [ ] task list
* [ ] task done
* [ ] task remove
* [ ] persistência em arquivo
* [ ] smart pointers
* [ ] CMake build

---

# 🏁 Resultado esperado

```
task add "Aprender C++"
task list
task done 1
task remove 1
```

---

# 📚 Conceitos que serão aprendidos

* C++ moderno (C++20)
* STL
* RAII
* Smart pointers
* File I/O
* CMake
* CLI parsing
* Organização de projeto

---

Happy hacking 🚀
