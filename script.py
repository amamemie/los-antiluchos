import os

OUTPUT = "teambook.tex"

def format_section(text):
    text = os.path.basename(text)
    text = text.replace("_", " ")
    return text.upper()

def format_subsection(text):
    text = text.replace(".cpp", "")
    text = text.replace("_", " ")
    text = text.lower()
    return text.capitalize()

def latex_escape(text):
    return (text.replace("\\", "\\textbackslash{}")
                .replace("_", "\\_")
                .replace("%", "\\%")
                .replace("#", "\\#")
                .replace("&", "\\&")
                .replace("{", "\\{")
                .replace("}", "\\}"))

def escribir_header(f):
    f.write(r"""
\documentclass[11pt]{article}

\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}

\usepackage[a4paper,margin=1in]{geometry}

\usepackage{listings}
\usepackage{xcolor}
\usepackage{titlesec}
\usepackage{hyperref}

\hypersetup{
    colorlinks=true,
    linkcolor=black,
    urlcolor=blue
}

\lstdefinestyle{cppstyle}{
    language=C++,
    basicstyle=\ttfamily\footnotesize,
    keywordstyle=\color{blue!60!black},
    commentstyle=\color{gray!70},
    stringstyle=\color{green!40!black},
    numbers=left,
    numberstyle=\tiny\color{gray},
    breaklines=true,
    frame=single,
    rulecolor=\color{black!20},
    tabsize=2,
    showstringspaces=false,
    columns=fullflexible,
    keepspaces=true,
    literate=
        {→}{{$\rightarrow$}}1
        {≤}{{$\leq$}}1
        {≥}{{$\geq$}}1
}

\lstset{style=cppstyle}

\begin{document}

% -------- PORTADA --------
\begin{titlepage}
    \centering
    \vspace*{\fill}
    {\Huge amamemie competitive programming book}
    \vspace*{\fill}
\end{titlepage}

% -------- PAGINA EN BLANCO --------
\newpage
\thispagestyle{empty}
\mbox{}

% -------- INDICE --------
\newpage
\tableofcontents
\newpage
""")

def escribir_footer(f):
    f.write("\n\\end{document}")

def main():
    with open(OUTPUT, "w") as f:
        escribir_header(f)

        for root, dirs, files in os.walk("."):
            if root == ".":
                continue

            cpp_files = [file for file in files if file.endswith(".cpp")]

            if cpp_files:
                section_name = latex_escape(format_section(root))
                f.write(f"\n\\section{{{section_name}}}\n")

                for file in sorted(cpp_files):
                    path = os.path.join(root, file)

                    subsection_name = latex_escape(format_subsection(file))
                    index_name = subsection_name.capitalize()

                    f.write(
                        f"\n\\subsection{{\\texorpdfstring{{{subsection_name}}}{{{index_name}}}}}\n"
                    )
                    f.write(f"\\lstinputlisting{{{path}}}\n")

        escribir_footer(f)

if __name__ == "__main__":
    main()
