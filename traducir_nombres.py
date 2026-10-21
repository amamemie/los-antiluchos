from pathlib import Path
import re
import sys

# Añade aquí más traducciones cuando las necesites.
translations = {
    "camino": "Path",
    "caminos": "Paths",
    "mas": "Most",
    "corto": "Shortest",
    "corta": "Shortest",
    "largos": "Longest",
    "largo": "Longest",
    "numero": "Number",
    "numeros": "Numbers",
    "suma": "Sum",
    "resta": "Difference",
    "multiplicacion": "Multiplication",
    "division": "Division",
    "arbol": "Tree",
    "arboles": "Trees",
    "grafo": "Graph",
    "grafos": "Graphs",
    "minimo": "Minimum",
    "minima": "Minimum",
    "maximo": "Maximum",
    "maxima": "Maximum",
    "maxima": "Maximum",
    "minima": "Minimum",
    "distancia": "Distance",
    "distancias": "Distances",
    "matriz": "Matrix",
    "cadenas": "Strings",
    "cadena": "String",
    "subcadena": "Substring",
    "subarreglo": "Subarray",
    "arreglo": "Array",
    "conjunto": "Set",
    "conjuntos": "Sets",
    "consulta": "Query",
    "consultas": "Queries",
    "actualizacion": "Update",
    "actualizaciones": "Updates",
    "ordenar": "Sort",
    "ordenamiento": "Sorting",
    "busqueda": "Search",
    "busqueda_binaria": "Binary_Search",
    "pares": "Pairs",
    "par": "Pair",
    "impares": "Odd",
    "impar": "Odd",
    "primo": "Prime",
    "primos": "Primes",
    "factorial": "Factorial",
    "factorizacion": "Factorization",
    "puntos": "Points",
    "punto": "Point",
    "rectangulo": "Rectangle",
    "rectangulos": "Rectangles",
    "circulo": "Circle",
    "circulos": "Circles",
    "juego": "Game",
    "juegos": "Games",
    "monedas": "Coins",
    "moneda": "Coin",
    "mochila": "Knapsack",
    "colores": "Colors",
    "color": "Color",
    "contar": "Count",
    "conteo": "Counting",
    "cantidad": "Amount",
    "operaciones": "Operations",
    "operacion": "Operation",
    "permutacion": "Permutation",
    "permutaciones": "Permutations",
    "combinacion": "Combination",
    "combinaciones": "Combinations",
    "probabilidad": "Probability",
    "probabilidades": "Probabilities",
    "respuesta": "Answer",
    "respuestas": "Answers",
    "solucion": "Solution",
    "soluciones": "Solutions",
    "facil": "Easy",
    "dificil": "Hard",
    "rapido": "Fast",
    "rapida": "Fast",
    "grande": "Large",
    "grandes": "Large",
    "pequeno": "Small",
    "pequena": "Small",
    "izquierda": "Left",
    "derecha": "Right",
    "arriba": "Up",
    "abajo": "Down",
    "dia": "Day",
    "dias": "Days",
    "noche": "Night",
    "secuencia": "Sequence",
    "secuencias": "Sequences",
    "digito": "Digit",
    "digitos": "Digits",
    "cero": "Zero",
    "uno": "One",
    "dos": "Two",
    "tres": "Three",
    "cuatro": "Four",
    "cinco": "Five",
    "seis": "Six",
    "siete": "Seven",
    "ocho": "Eight",
    "nueve": "Nine",
    "diez": "Ten",
    "de": "of",
    "del": "of_the",
    "y": "and",
    "en": "in",
    "con": "with",
    "sin": "without",
    "para": "for",
    "por": "by",
    "entre": "between",
    "sobre": "on",
    "un": "a",
    "una": "a",
    "el": "the",
    "la": "the",
    "los": "the",
    "las": "the",
}

small_words = {
    "of", "in", "on", "is", "and", "or", "the", "to",
    "for", "by", "with", "without", "between", "at", "from"
}

def translate_filename(stem):
    # Conserva los separadores como palabras separadas.
    words = re.split(r"[_\s-]+", stem.lower())
    translated = []

    for word in words:
        if not word:
            continue
        translated.extend(translations.get(word, word).split("_"))

    result = []
    for i, word in enumerate(translated):
        if i == 0 or word not in small_words:
            result.append(word.capitalize())
        else:
            result.append(word)

    return "_".join(result)

apply = "--apply" in sys.argv

for path in Path(".").rglob("*.cpp"):
    new_name = translate_filename(path.stem) + path.suffix
    target = path.with_name(new_name)

    if target == path:
        continue

    if target.exists():
        print(f"CONFLICTO: {path} -> {target} (ya existe)")
        continue

    print(f"{path} -> {target}")

    if apply:
        path.rename(target)

if not apply:
    print("\nSimulación solamente. Para aplicar los cambios:")
    print("python3 traducir_nombres.py --apply")
