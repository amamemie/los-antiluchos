#!/usr/bin/env python3
"""
teambook_builder.py
--------------------
Genera teambook.tex a partir de una colección de archivos .cpp organizados
en carpetas, aplicando diseño moderno y orden por dificultad.
"""

import os
import re

OUTPUT = "teambook.tex"
TEAM_NAME = "Los Sabrossos"
NOTEBOOK_TITLE = "Los Sabrossos"

# ---------------------------------------------------------------------------
# 1. ORDEN POR DIFICULTAD
# ---------------------------------------------------------------------------
SECTION_DIFFICULTY = {
    "template": 0, "plantilla": 0, "basics": 1, "math": 2, "matematicas": 2, "number_theory_basic": 3,
    "data_structures": 10, "estructuras": 10, "segment_tree": 11, "fenwick": 12, "dsu": 13, "union_find": 13,
    "graphs": 20, "grafos": 20, "geometry": 30, "geometria": 30,
    "strings": 40, "flows": 41, "flujo": 41, "number_theory": 42, "teoria_numeros": 42, "advanced": 50,
}

ALGO_DIFFICULTY = [
    "bfs", "dfs", "flood_fill", "floodfill",
    "two_pointers", "sliding_window", "binary_search",
    "dijkstra", "bellman_ford", "bellmanford", "floyd_warshall", "floydwarshall",
    "prim", "kruskal", "mst",
    "topo", "topological", "scc", "tarjan", "kosaraju", "bridges", "articulation",
    "lca", "euler_tour",
    "matching", "bipartite", "hopcroft", "kuhn",
    "max_flow", "maxflow", "dinic", "ford_fulkerson", "mincost",
    "kmp", "z_function", "zfunction", "trie",
    "suffix_array", "suffix_automaton", "aho_corasick",
    "gcd", "sieve", "criba", "modpow", "mod_pow",
    "extended_gcd", "euler_totient", "phi",
    "crt", "chinese_remainder",
    "ntt", "fft",
]

def difficulty_rank_section(folder_key):
    key = folder_key.lower().strip()
    if key in SECTION_DIFFICULTY: return (SECTION_DIFFICULTY[key], key)
    for known, rank in SECTION_DIFFICULTY.items():
        if known in key: return (rank, key)
    return (1000, key)

def difficulty_rank_algo(filename):
    key = filename.lower().replace("_", "").replace("-", "")
    for idx, token in enumerate(ALGO_DIFFICULTY):
        token_norm = token.replace("_", "")
        if token_norm in key: return (idx, filename.lower())
    return (len(ALGO_DIFFICULTY) + 1000, filename.lower())

# ---------------------------------------------------------------------------
# 2. UTILIDADES
# ---------------------------------------------------------------------------
LOWERCASE_WORDS = {"of", "the", "and", "in", "to", "for", "with", "a", "an", "or", "by", "at", "on", "vs"}

def smart_title_case(text):
    words = text.split()
    result = []
    for i, word in enumerate(words):
        if word.isupper() and len(word) > 1: result.append(word); continue
        lower = word.lower()
        if i != 0 and lower in LOWERCASE_WORDS: result.append(lower)
        else: result.append(lower[:1].upper() + lower[1:])
    return " ".join(result)

def latex_escape(text):
    return text.replace("\\", "\\textbackslash{}").replace("_", "\\_").replace("%", "\\%").replace("#", "\\#").replace("&", "\\&").replace("{", "\\{").replace("}", "\\}").replace("~", "\\textasciitilde{}").replace("^", "\\textasciicircum{}").replace("$", "\\$")

def latex_escape_path(path):
    return path.replace("\\", "/")

# ---------------------------------------------------------------------------
# 3. HEADER LATEX
# ---------------------------------------------------------------------------
def escribir_header(f):
    f.write(r"""\documentclass[10pt]{article}
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}
\usepackage[a4paper, top=2.6cm, bottom=2.6cm, left=2.8cm, right=2.8cm]{geometry}
\usepackage{listings}
\usepackage{xcolor}
\usepackage{titlesec}
\usepackage{hyperref}
\usepackage{fancyhdr}
\usepackage{accsupp}

\definecolor{graphite}{HTML}{2B2D31}
\definecolor{navy}{HTML}{1B2A4A}
\definecolor{navyaccent}{HTML}{2E4A7D}
\definecolor{mutedgray}{HTML}{6B6E76}
\definecolor{rulegray}{HTML}{C9CBD1}
\definecolor{codebg}{HTML}{F7F7F8}
\definecolor{codekeyword}{HTML}{4A4E8C}
\definecolor{codecomment}{HTML}{6E7B6E}
\definecolor{codestring}{HTML}{96603D}
\definecolor{codenumber}{HTML}{B9B9BD}
\definecolor{codetype}{HTML}{3E6B6B}
\definecolor{ivory}{HTML}{FBFAF6}

\hypersetup{colorlinks=true, linkcolor=navyaccent, urlcolor=navyaccent, pdftitle={""" + NOTEBOOK_TITLE + r"""}, pdfauthor={Team """ + TEAM_NAME + r"""}}

\newcommand{\noncopynumber}[1]{\BeginAccSupp{method=plain,ActualText={}}#1\EndAccSupp{}}

\lstdefinestyle{cppstyle}{
  language=C++, basicstyle=\ttfamily\scriptsize, keywordstyle=\color{codekeyword}\bfseries,
  commentstyle=\color{codecomment}\itshape, stringstyle=\color{codestring}, numberstyle=\tiny\color{codenumber}\noncopynumber,
  numbers=left, frame=single, rulecolor=\color{rulegray}, backgroundcolor=\color{codebg},
  breaklines=true, xleftmargin=1.8em, framexleftmargin=1.8em
}
\lstset{style=cppstyle}

\titleformat{\section}{\Large\bfseries\color{navy}}{\thesection.\quad}{0em}{}[\vspace{2pt}{\color{rulegray}\titlerule[0.6pt]}]
\titleformat{\subsection}{\normalsize\bfseries\color{graphite}}{\thesubsection.\quad}{0em}{}

\pagestyle{fancy}
\fancyhf{}
\lhead{\small\color{mutedgray}\scshape\leftmark}
\lfoot{}\rfoot{\small\color{mutedgray}\thepage}
\renewcommand{\headrule}{{\color{rulegray}\hrule height 0.4pt}}

\fancypagestyle{plain}{\fancyhf{}\lfoot{}\rfoot{\small\color{mutedgray}\thepage}}

\begin{document}
\begin{titlepage}
    \pagecolor{ivory}
    \color{graphite}
    \centering
    \vspace*{0.35\textheight}

    {\color{navyaccent}\rule{0.32\textwidth}{0.6pt}}\\[1.8em]

    {\fontsize{36}{40}\selectfont\bfseries\color{navy} """ + latex_escape(NOTEBOOK_TITLE) + r"""}\\[1.8em]

    {\color{navyaccent}\rule{0.32\textwidth}{0.6pt}}

\end{titlepage}
\pagecolor{white}\newpage\pagenumbering{roman}\tableofcontents\newpage\pagenumbering{arabic}
""")

def main():
    with open(OUTPUT, "w", encoding="utf-8") as f:
        escribir_header(f)
        sections = []
        for current_root, dirs, files in os.walk("."):
            if current_root == ".": continue
            cpp_files = [file for file in files if file.lower().endswith(".cpp")]
            if not cpp_files: continue
            folder_name = os.path.basename(current_root)
            sec_rank, sec_key = difficulty_rank_section(folder_name)
            algo_entries = sorted([(difficulty_rank_algo(f)[0], os.path.join(current_root, f), f) for f in cpp_files])
            sections.append((sec_rank, sec_key, folder_name, algo_entries))
        
        sections.sort()
        for _, _, folder_name, algo_entries in sections:
            f.write(f"\n\\section{{{latex_escape(smart_title_case(folder_name.replace('_', ' ')))}}}\n")
            for _, path, file in algo_entries:
                algo_title = smart_title_case(re.sub(r"\.cpp$", "", file, flags=re.IGNORECASE).replace("_", " "))
                # Aquí se duplicaron las llaves para evitar el error de sintaxis del f-string
                f.write(f"\\subsection{{\\texorpdfstring{{{{{latex_escape(algo_title)}}}}}{{{{{algo_title}}}}}}}\n")
                f.write(f"\\lstinputlisting{{{latex_escape_path(path)}}}\n")
        f.write("\n\\end{document}\n")
    print(f"Generado: {OUTPUT}. Ejecuta: pdflatex {OUTPUT}")

if __name__ == "__main__":
    main()
