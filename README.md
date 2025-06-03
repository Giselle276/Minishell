# Minishell

**Minishell** es una versión simplificada de un shell Unix, desarrollada como parte del currículo del proyecto de la escuela 42. El objetivo principal es entender el funcionamiento interno de un shell, la gestión de procesos, señales, redirecciones y la implementación de built-ins.

Este proyecto permite ejecutar comandos, manejar redirecciones, pipes, variables de entorno y señales, entre otras funcionalidades, simulando el comportamiento de Bash en modo interactivo.
## Funcionalidades

### ✔️ Parsing y ejecución
- Separación de comandos por `;` o nuevas líneas.
- Soporte de pipes `|`.
- Redirecciones de entrada `<`, salida `>` y `>>`.
- Soporte de heredocs `<<`.

### ✔️ Built-ins implementados
- `echo` / `echo -n` / `echo -nnnnn`
- `cd`: `cd -`, `cd ~`, `cd ..` (y actualización de **PWD** y **OLDPWD**)
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### ✔️ Variables de entorno
- Lectura, modificación y exportación de variables de entorno.
- Comportamiento similar a Bash:
  - `export VAR=valor`
  - `export VAR=`
  - `echo $VAR`
  - `$?` para obtener el último código de salida.

### ✔️ Señales
- Manejo de `SIGINT` (Ctrl+C) y `SIGQUIT` (Ctrl+\) como Bash.
- Ignora señales en heredoc cuando corresponde.

### ✔️ Gestión de errores y memoria
- Mensajes de error similares a Bash.
- Liberación completa de memoria en cada ciclo del shell.
- Manejo adecuado de errores de sistema (`execve`, `fork`, `pipe`, etc.).

---

## 📥Uso:

### 🛠️ Compilación

Para compilar el proyecto, ejecuta:

```bash
make
```

## Ejecución:
Para iniciar la shell:
```bash
./minishell
```
## 💡Resultado esperado:
Al ejecutar el programa, se mostrará un prompt interactivo personalizado, similar al de Bash:
```bash
minishell>
```
Desde ahí, el usuario puede escribir y ejecutar comandos como:
```bash
minishell> echo Hola Mundo
Hola Mundo
minishell> export VAR=42
minishell> echo $VAR
42
minishell> ls -l | grep minishell
```
* Puedes usar las flechas del teclado (↑ ↓) para navegar por el historial de comandos anteriores.
* La shell permanece activa hasta que el usuario ejecuta exit o presiona Ctrl+D en una línea vacía.
./folder           # Debe devolver 126 (permiso denegado o no ejecutable)
cd notadir         # Debe devolver 1 (directorio no existe)

### 📤 Comportamiento de echo
```bash
echo $$$$                          # Manejo correcto de múltiples signos $
echo -nnnn hola                    # El flag -n puede repetirse
echo -nnnnp hola                   # Este no debe considerarse como -n válido
echo "$USER '$USER'"              # Combinación de comillas dobles y simples
echo "'$USER'"                    # Todo entre comillas simples = literal
echo $''                          # Manejo de expansiones vacías
```
### 🧩 Comillas, variables y espacios
* Manejo correcto de:

* Comillas simples y dobles.

* Expansiones dentro de comillas.

* Combinaciones complejas: ec'h''o', ls '-la', etc.

* Expansión de variables: $USER, $HOME, $?, etc.

* Comandos con espacios y tabulaciones múltiples.

### 🌍 Export, unset y env

* Variables vacías:
```bash
export VAR=
echo $VAR   # debe mostrar vacío
```
* Variables duplicadas: el último valor debe prevalecer.
* Asignación dinámica:
```bash
export VAR=ls
$VAR
```
* unset VAR debe eliminarla correctamente.
* env no debe mostrar variables sin valor asignado.

### 📁 cd y actualización de PWD / OLDPWD
```bash
cd              # Va al HOME
cd -            # Vuelve al OLDPWD
cd ~            # Equivalente a cd
cd ..           # Sube un nivel
```
### 🚪exit y sus errores
```bash
exit                  # Sale con código 0
exit 42               # Sale con código 42
exit 999999999999     # Error: valor fuera de rango
exit hola             # Error: valor no numérico
exit 2 hola           # Error: demasiados argumentos
```
### Comprobaciones de ejecución simultánea: 
```bash
sleep 2 | ls
```
## by:
- 👩‍💻 **Claudia Sofía Gil** - [`cgil`](https://github.com/claauugil)
- 👩‍💻 **Giselle Maccha** - [`gmaccha-`](https://github.com/Giselle276)
