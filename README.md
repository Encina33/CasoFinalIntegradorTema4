# README - Tiny Lisp Variant Interpreter

Este documento describe cómo compilar, ejecutar y entender el proyecto de un intérprete "tiny-lisp" implementado en C++ usando la biblioteca `nlohmann/json.hpp` para manejar datos JSON.

---

## Requisitos Previos

1. **Compilador C++:** Necesitas un compilador compatible con C++17 o superior (por ejemplo, GCC, Clang o MSVC).
2. **Biblioteca JSON:** Descarga la biblioteca JSON moderna desde [nlohmann/json](https://github.com/nlohmann/json) y agrégala a tu proyecto.
3. **Entorno de Desarrollo:** Se recomienda usar CLion para un mejor soporte de herramientas y depuración.

---

## Estructura del Proyecto

### Archivos principales

- `main.cpp`: Contiene la implementación de la clase `Variant` y el punto de entrada principal.
- `nlohmann/json.hpp`: Biblioteca externa para manejar JSON.

### Clases y Componentes

1. **Clase `Variant`**

   La clase `Variant` es la pieza central del intérprete y permite manejar diferentes tipos de datos necesarios para evaluar expresiones Lisp.

2. **Métodos principales de `Variant`**

   - `to_string`: Convierte una instancia de `Variant` en una representación de cadena de texto.
   - `to_json_string`: Convierte una instancia de `Variant` en una representación JSON.
   - `from_json_string`: Crea una instancia de `Variant` a partir de una cadena JSON.
   - `parse_json`: Analiza un objeto JSON y lo convierte en una instancia de `Variant`.

3. **Tipos soportados por `Variant`**

   - **`Symbol` y `Cadena`:** Representan identificadores y cadenas de texto.
   - **`Number`:** Maneja valores numéricos.
   - **`List`:** Representa listas de elementos.
   - **`Proc` y `Lambda`:** Permiten manejar funciones y procedimientos (para futuras extensiones).

### Ejemplo de código

```cpp
int main() {
    // Crear una instancia de Variant
    Variant v1(Symbol, "hello");
    Variant v2(42.0);
    Variant v3(List);
    v3.list.push_back(v1);
    v3.list.push_back(v2);

    // Convertir a JSON
    std::cout << v3.to_json_string() << std::endl;

    // Parsear desde JSON
    std::string json_input = "[\"hello\", 42]";
    Variant parsed = Variant::from_json_string(json_input);
    std::cout << parsed.to_string() << std::endl;

    return 0;
}
```

---

## Cómo Compilar y Ejecutar

### Compilación en CLion

1. **Agregar `nlohmann/json.hpp`:** Coloca el archivo `json.hpp` en la carpeta `include` de tu proyecto o en el mismo directorio que el código fuente.

2. **Configurar CMakeLists.txt:**

   ```cmake
   cmake_minimum_required(VERSION 3.16)
   project(TinyLispInterpreter)

   set(CMAKE_CXX_STANDARD 17)

   add_executable(TinyLispInterpreter main.cpp)
   ```

3. **Compilar:** Usa la opción *Build* en CLion para compilar el proyecto.

4. **Ejecutar:** Ejecuta el programa desde el entorno de CLion o desde la terminal.

### Ejecución desde la Terminal

1. Abre una terminal en el directorio raíz del proyecto.
2. Compila el programa con un comando como este (asegúrate de tener un compilador compatible):

   ```bash
   g++ -std=c++17 main.cpp -o tiny_lisp
   ```

3. Ejecuta el programa:

   ```bash
   ./tiny_lisp
   ```

---

## Salida Esperada

### Ejemplo 1: Conversión a JSON

#### Código

```cpp
Variant v1(Symbol, "hello");
Variant v2(42.0);
Variant v3(List);
v3.list.push_back(v1);
v3.list.push_back(v2);
std::cout << v3.to_json_string() << std::endl;
```

#### Salida

```json
["hello", 42]
```

### Ejemplo 2: Parseo desde JSON

#### Código

```cpp
std::string json_input = "[\"hello\", 42]";
Variant parsed = Variant::from_json_string(json_input);
std::cout << parsed.to_string() << std::endl;
```

#### Salida

```lisp
( hello 42 )
```

---

## Explicación del Código

1. **`Variant` como Contenedor Genérico:**
   La clase permite representar varios tipos de datos, lo que es esencial para simular el comportamiento dinámico de Lisp.

2. **JSON como Representación Intermedia:**
   Usamos JSON tanto para serialización como para parseo de datos, lo que facilita el manejo estructurado de listas y valores.

3. **Extensibilidad:**
   Aunque este proyecto es un intérprete básico, puedes extenderlo para soportar evaluaciones reales de expresiones Lisp añadiendo un motor de evaluación basado en el entorno.

---

## Posibles Extensiones

- **Soporte para Evaluación:** Implementar un evaluador que pueda ejecutar funciones definidas en el entorno.
- **Manejo de Objetos JSON:** Permitir la conversión directa de objetos JSON a estructuras Lisp equivalentes.
- **Definiciones de Funciones:** Agregar soporte para definir funciones Lambda.

---

## Notas Finales

Este proyecto proporciona una base sólida para explorar cómo construir un intérprete simple en C++. Si tienes dudas o encuentras errores, no dudes en pedir ayuda.

