
from pathlib import Path
import sys

renames = {
    "Bit_Manipulation/Bits_Prendidos_in_A_Number_X_in_A_Posicion_Pos.cpp":
        "Set_Bits_in_a_Number.cpp",

    "Data Structures/Bit_1d.cpp":
        "1D_Binary_Indexed_Tree.cpp",
    "Data Structures/Bit_2d.cpp":
        "2D_Binary_Indexed_Tree.cpp",
    "Data Structures/Bit_2d_Infinite_Plane.cpp":
        "2D_Binary_Indexed_Tree_Infinite_Plane.cpp",
    "Data Structures/Bit_3d.cpp":
        "3D_Binary_Indexed_Tree.cpp",
    "Data Structures/Segment_Tree_Iterativo.cpp":
        "Iterative_Segment_Tree.cpp",

    "Dynamic_Programing/Fastfibo.cpp":
        "Fast_Fibonacci.cpp",

    "Math/Extended_Euclides.cpp":
        "Extended_Euclidean_Algorithm.cpp",
    "Math/Fft_for_Comparar_Rotaciones.cpp":
        "FFT_for_Comparing_Rotations.cpp",
    "Math/Fft_for_Matching.cpp":
        "FFT_for_Matching.cpp",
    "Math/Pollard_Rho_Rabin_Miller.cpp":
        "Pollard_Rho_and_Miller_Rabin.cpp",
    "Math/Fibonacci_Log(n).cpp":
        "Logarithmic_Fibonacci.cpp",

    "Tree Algorithms/Chuliuedmonds_Construction.cpp":
        "Chu_Liu_Edmonds_Construction.cpp",
    "Tree Algorithms/Chuliuedmonds.cpp":
        "Chu_Liu_Edmonds.cpp",
    "Tree Algorithms/Hld.cpp":
        "Heavy_Light_Decomposition.cpp",

    "Utilities/Plantilla_Python.cpp":
        "Python_Template.cpp",
    "Utilities/Preffix_Sum_2d.cpp":
        "2D_Prefix_Sum.cpp",
}

apply = "--apply" in sys.argv
root = Path(".")

# Validar todos los cambios antes de renombrar.
operations = []
targets = set()

for old, new_name in renames.items():
    src = root / old
    dst = src.with_name(new_name)

    if not src.is_file():
        print(f"NO ENCONTRADO: {src}")
        continue

    if dst.exists() and dst != src:
        print(f"CONFLICTO: {dst} ya existe")
        continue

    if dst in targets:
        print(f"CONFLICTO: destino repetido {dst}")
        continue

    targets.add(dst)
    operations.append((src, dst))

for src, dst in operations:
    print(f"{src} -> {dst}")

if apply:
    for src, dst in operations:
        src.rename(dst)
    print(f"\nRenombrados: {len(operations)} archivos")
else:
    print(f"\nSimulación: {len(operations)} cambios")
    print("Para aplicar: python3 renombrar.py --apply")
