# Team NoteBook - Los Sabrossos
---

## Generación del PDF

Siga los siguientes pasos:

### 1. Generar el archivo `.tex`

```bash
python3 script.py
```

### 2. Compilar el PDF

```bash
pdflatex teambook.tex
```

### 3. Si el índice no aparece, compilar otra vez

```bash
pdflatex teambook.tex
```
### 4. Eliminar archivos basura
```bash
rm *.aux *.log *.out *.toc
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
