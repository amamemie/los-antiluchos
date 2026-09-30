//cambia Node por el tipo de dato
sort(a.begin(), a.end(), [](Node A, Node B){
  return A.c * B.w > B.c * A.w;
});
