int function(int n, int *a) {
  int x = -1;
  for (int i = 1; i < n; i++, x += 2) {
    if (a[i] > x) {
      x = a[i];
    }
  }
  return x;
}