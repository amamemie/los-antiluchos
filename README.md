# Team NoteBook - Los Sabrossos

Este repositorio permite generar un TeamBook en PDF a partir de archivos `.cpp`.

---

## Generación del PDF

Siga los siguientes pasos:

### 1. Generar el archivo `.tex`

```bash
python3 script.py
```

### 2. Compilar el PDF

```bash
pdflatex teambook.tex && rm *.aux *.log *.out *.toc
```

### 3. Si el índice no aparece

```bash
pdflatex teambook.tex && rm *.aux *.log *.out *.toc
```
---

## Subir cambios a GitHub

### 1. Agregar archivos

```bash
git add .
```

### 2. Crear commit

```bash
git commit -m "Update"
```

### 3. Subir cambios

```bash
git push
```
